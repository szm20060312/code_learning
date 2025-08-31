import pandas as pd
from datetime import datetime

# ======================
# 读取考勤数据
# ======================
df = pd.read_excel("/Users/szm/code/python/8月考勤机.xls")  # 修改为你的文件路径

# 设置周末（不统计）
weekends = {"2025-07-26", "2025-07-27", "2025-08-02", "2025-08-03", "2025-08-04", 
            "2025-08-05", "2025-08-06", "2025-08-07", "2025-08-08", "2025-08-09", 
            "2025-08-10", "2025-08-16", "2025-08-17"}

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

df = df.groupby("姓名").apply(filter_duplicates).reset_index(drop=True)

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
# 定义考勤判断函数
# ======================
def check_attendance(records):
    result = []
    employees = records["姓名"].unique()
    for emp in employees:
        emp_records = records[records["姓名"] == emp]
        dates = emp_records["日期"].unique()
        for date in dates:
            day_records = emp_records[emp_records["日期"] == date]
            # 上午：8:20-11:45
            am_records = day_records[day_records["日期时间"].dt.hour < 13]
            # 下午：13:30后
            pm_records = day_records[day_records["日期时间"].dt.hour >= 13]

            def evaluate_half(records_half, half):
                # 半天没有打卡或不足两条记录 -> 旷工
                if records_half.empty or len(records_half) < 2:
                    return {"半天": half, "状态": "旷工"}
                first_time = records_half["日期时间"].min()
                last_time = records_half["日期时间"].max()
                status = []

                # 上午考勤
                if half == "上午":
                    if first_time.time() > datetime.strptime("08:21", "%H:%M").time() and first_time.time() < datetime.strptime("09:20", "%H:%M").time():
                        status.append("迟到")
                    if last_time.time() < datetime.strptime("11:44", "%H:%M").time() and last_time.time() > datetime.strptime("10:45", "%H:%M").time():
                        status.append("早退")

                # 下午考勤
                if half == "下午":
                    if first_time.time() > datetime.strptime("14:51", "%H:%M").time() and first_time.time() < datetime.strptime("15:50", "%H:%M").time():
                        status.append("迟到")
                    if last_time.time() < datetime.strptime("17:44", "%H:%M").time() and last_time.time() > datetime.strptime("16:45", "%H:%M").time():
                        status.append("早退")

                if not status:
                    return {"半天": half, "状态": None}  # 正常不显示
                return {"半天": half, "状态": ", ".join(status)}

            am_status = evaluate_half(am_records, "上午")
            pm_status = evaluate_half(pm_records, "下午")

            # 仅记录有异常的半天
            if am_status["状态"]:
                result.append({"姓名": emp, "日期": date, **am_status})
            if pm_status["状态"]:
                result.append({"姓名": emp, "日期": date, **pm_status})

    return pd.DataFrame(result)

# ======================
# 生成详细异常表（只显示异常）
# ======================
detailed_df = check_attendance(merged_df)

# ======================
# 生成汇总表（三列格式）
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