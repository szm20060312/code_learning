import pandas as pd
from datetime import datetime, timedelta

# 周末日期（不统计）
weekends = {
    "2025-07-26", "2025-07-27", "2025-08-02", "2025-08-03",
    "2025-08-09", "2025-08-10", "2025-08-16", "2025-08-17"
}

# 考勤判断规则
def check_attendance(times, date):
    # 分上午和下午
    morning_times = [t for t in times if t.time() <= datetime.strptime("13:30", "%H:%M").time()]
    afternoon_times = [t for t in times if t.time() > datetime.strptime("13:30", "%H:%M").time()]

    details = []
    result = {"迟到": 0, "早退": 0, "旷工": 0}

    # 上午
    if len(morning_times) < 2:
        details.append(f"{date} 上午旷工")
        result["旷工"] += 1
    else:
        morning_in = morning_times[0]
        morning_out = morning_times[-1]
        if morning_in.time() > datetime.strptime("08:21", "%H:%M").time():
            details.append(f"{date} 上午迟到")
            result["迟到"] += 1
        if morning_out.time() < datetime.strptime("11:44", "%H:%M").time():
            details.append(f"{date} 上午早退")
            result["早退"] += 1

    # 下午
    if len(afternoon_times) < 2:
        details.append(f"{date} 下午旷工")
        result["旷工"] += 1
    else:
        afternoon_in = afternoon_times[0]
        afternoon_out = afternoon_times[-1]
        if afternoon_in.time() > datetime.strptime("14:46", "%H:%M").time():
            details.append(f"{date} 下午迟到")
            result["迟到"] += 1
        if afternoon_out.time() < datetime.strptime("17:44", "%H:%M").time():
            details.append(f"{date} 下午早退")
            result["早退"] += 1

    return result, details

def analyze_attendance(file):
    df = pd.read_excel(file)

    # 只保留姓名和打卡时间
    df = df[["姓名", "日期时间"]]
    df["日期时间"] = pd.to_datetime(df["日期时间"])

    # 按姓名排序
    df = df.sort_values(["姓名", "日期时间"])

    # 过滤 10 分钟内重复打卡，保留最早一次
    def filter_close(group):
        filtered = []
        last_time = None
        for t in group["日期时间"]:
            if last_time is None or (t - last_time) > pd.Timedelta(minutes=10):
                filtered.append(t)
                last_time = t
        return pd.DataFrame({"姓名": group["姓名"].iloc[0], "日期时间": filtered})

    df = df.groupby("姓名", group_keys=False).apply(filter_close).reset_index(drop=True)

    # 增加日期列
    df["日期"] = df["日期时间"].dt.date.astype(str)

    # 获取员工顺序（按 Excel 首次出现顺序）
    employees = df.drop_duplicates(subset=["姓名"])["姓名"].tolist()

    # 获取所有工作日
    all_dates = sorted(set(df["日期"].unique()) - weekends)

    # 初始化记录
    detailed_records = {name: [] for name in employees}
    summary = {name: {"迟到":0, "早退":0, "旷工":0} for name in employees}

    # 逐人逐日处理
    for name in employees:
        emp_df = df[df["姓名"] == name]
        emp_dates = set(emp_df["日期"].unique()) - weekends

        for date in all_dates:
            if date in emp_dates:
                times = sorted(emp_df[emp_df["日期"] == date]["日期时间"].tolist())
                check, details = check_attendance(times, date)
            else:
                # 整天缺勤 -> 上午+下午旷工
                check = {"迟到": 0, "早退": 0, "旷工": 2}
                details = [f"{date} 上午旷工", f"{date} 下午旷工"]

            # 保存详细异常
            detailed_records[name].extend(details)

            # 保存汇总统计
            for k in check:
                summary[name][k] += check[k]

    # 转换为 DataFrame
    detailed_df = pd.DataFrame([
        {"姓名": name, "异常情况": d} 
        for name in employees 
        for d in detailed_records[name]
    ])

    summary_df = pd.DataFrame([
        {"姓名": name, **summary[name]} 
        for name in employees
    ])

    # 保存为 Excel
    with pd.ExcelWriter("考勤异常统计1.xlsx") as writer:
        detailed_df.to_excel(writer, sheet_name="详细异常表", index=False)
        summary_df.to_excel(writer, sheet_name="异常统计表", index=False)

    print("考勤异常统计已保存为 '考勤异常统计.xlsx'。")

if __name__ == "__main__":
    file = "/Users/szm/code/python/8月考勤机.xls"  # 替换为你的 Excel 文件路径
    analyze_attendance(file)