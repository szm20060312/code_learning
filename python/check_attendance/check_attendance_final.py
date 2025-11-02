import pandas as pd
from datetime import datetime

# ======================
# 读取考勤数据
# ======================
df = pd.read_excel("/Users/szm/code/python/check_attendance/8月考勤机.xls")  # 修改为你的文件路径

# 设置周末（不统计）
# weekends = {"2025-08-23", "2025-08-24", "2025-08-30", "2025-08-31", "2025-09-06", 
#             "2025-09-07", "2025-09-13", "2025-09-14", "2025-09-20"}
weekends = {"2025-07-26", "2025-07-27", "2025-08-02", "2025-08-03", "2025-08-04", "2025-08-05", "2025-08-06", "2025-08-07", "2025-08-08", "2025-08-09", "2025-08-10", "2025-08-16", "2025-08-17"} 

# 转换日期时间格式
df["日期时间"] = pd.to_datetime(df["日期时间"])
df["日期"] = df["日期时间"].dt.date

# 过滤周末
df = df[~df["日期"].astype(str).isin(weekends)]

# 按员工、日期排序
df.sort_values(by=["姓名", "日期时间"], inplace=True)

# ======================
# 去重：10分钟内同一人重复打卡只保留最早一次
# ======================
def filter_duplicates(group):
    group = group.sort_values("日期时间")
    filtered = []
    last_time = None
    for _, row in group.iterrows():
        if last_time is None or (row["日期时间"] - last_time).total_seconds() > 600:
            filtered.append(row)
            last_time = row["日期时间"]
    return pd.DataFrame(filtered)

df = df.groupby("姓名", group_keys=False).apply(filter_duplicates).reset_index(drop=True)

# ======================
# 构造完整“员工 × 日期”表（考虑整天缺勤）
# ======================
all_employees = df["姓名"].unique()
all_dates = pd.date_range(start=df["日期"].min(), end=df["日期"].max(), freq='D')
all_dates = [d.date() for d in all_dates if d.strftime("%Y-%m-%d") not in weekends]

full_index = pd.MultiIndex.from_product([all_employees, all_dates], names=["姓名", "日期"])
full_df = pd.DataFrame(index=full_index).reset_index()

# 合并原始考勤数据
merged_df = pd.merge(full_df, df, on=["姓名", "日期"], how="left")

# ======================
# 定义考勤判断函数（分钟数比较法 + 下班过早判旷工）
# ======================
def time_to_minutes(dt):
    return dt.dt.hour * 60 + dt.dt.minute

# 上下班有效分钟区间
time_ranges_min = {
    "上午上班": (0, 10*60),        # 00:00~10:00
    "上午下班": (10*60+1, 13*60+30),  # 10:01~13:30
    "下午上班": (13*60+31, 16*60),    # 13:31~16:00
    "下午下班": (16*60+1, 23*60+59),  # 16:01~23:59
}

# 迟到/早退分钟区间
late_early_min = {
    "上午迟到": (8*60+21, 9*60+20),
    "上午早退": (10*60+45, 11*60+44),
    "下午迟到": (14*60+51, 15*60+50),
    "下午早退": (16*60+45, 17*60+44),
}

# 下班最早允许时间（否则算旷工）
min_checkout = {
    "上午": 10*60+45,
    "下午": 16*60+45,
}

def check_attendance(records):
    result = []
    employees = records["姓名"].unique()
    for emp in employees:
        emp_records = records[records["姓名"] == emp]
        dates = emp_records["日期"].unique()
        for date in dates:
            day_records = emp_records[emp_records["日期"] == date]

            if not day_records.empty:
                day_records = day_records.copy()
                day_records["分钟"] = time_to_minutes(day_records["日期时间"])
            else:
                day_records["分钟"] = pd.Series(dtype=int)

            # 上午上下班卡
            am_start_cards = day_records[(day_records["分钟"] >= time_ranges_min["上午上班"][0]) &
                                         (day_records["分钟"] <= time_ranges_min["上午上班"][1])]
            am_end_cards   = day_records[(day_records["分钟"] >= time_ranges_min["上午下班"][0]) &
                                         (day_records["分钟"] <= time_ranges_min["上午下班"][1])]

            # 下午上下班卡
            pm_start_cards = day_records[(day_records["分钟"] >= time_ranges_min["下午上班"][0]) &
                                         (day_records["分钟"] <= time_ranges_min["下午上班"][1])]
            pm_end_cards   = day_records[(day_records["分钟"] >= time_ranges_min["下午下班"][0]) &
                                         (day_records["分钟"] <= time_ranges_min["下午下班"][1])]

            def evaluate_half(start_cards, end_cards, half):
                if start_cards.empty or end_cards.empty:
                    return {"半天": half, "状态": "旷工"}

                first_min = start_cards["分钟"].min()
                last_min = end_cards["分钟"].max()

                # 下班早于最早允许时间 → 旷工
                if last_min < min_checkout[half]:
                    return {"半天": half, "状态": "旷工"}

                status = []
                if half == "上午":
                    if late_early_min["上午迟到"][0] <= first_min <= late_early_min["上午迟到"][1]:
                        status.append("迟到")
                    if late_early_min["上午早退"][0] <= last_min <= late_early_min["上午早退"][1]:
                        status.append("早退")
                else:
                    if late_early_min["下午迟到"][0] <= first_min <= late_early_min["下午迟到"][1]:
                        status.append("迟到")
                    if late_early_min["下午早退"][0] <= last_min <= late_early_min["下午早退"][1]:
                        status.append("早退")

                if not status:
                    return {"半天": half, "状态": None}
                return {"半天": half, "状态": ", ".join(status)}

            am_status = evaluate_half(am_start_cards, am_end_cards, "上午")
            pm_status = evaluate_half(pm_start_cards, pm_end_cards, "下午")

            if am_status["状态"]:
                result.append({"姓名": emp, "日期": date, **am_status})
            if pm_status["状态"]:
                result.append({"姓名": emp, "日期": date, **pm_status})

    return pd.DataFrame(result)

# ======================
# 生成详细异常表
# ======================
detailed_df = check_attendance(merged_df)

# ======================
# 汇总表
# ======================
summary_df = detailed_df.groupby("姓名").agg(
    迟到=("状态", lambda x: sum("迟到" in s for s in x)),
    早退=("状态", lambda x: sum("早退" in s for s in x)),
    旷工=("状态", lambda x: sum("旷工" in s for s in x))
).reset_index()

# ======================
# 输出 Excel 文件
# ======================
with pd.ExcelWriter("attendance_report.xlsx") as writer:
    detailed_df.to_excel(writer, sheet_name="详细异常表", index=False)
    summary_df.to_excel(writer, sheet_name="汇总统计表", index=False)

print("考勤分析完成，详细异常表仅显示异常记录")