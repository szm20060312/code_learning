import pandas as pd
from datetime import datetime, time, timedelta

# ---------------------------
# 配置（每月只需改这里）
# ---------------------------
START_DATE = "2025-10-21"
END_DATE = "2025-11-20"
WEEKENDS = {
    "2025-10-25", "2025-10-26",
    "2025-11-01", "2025-11-02",
    "2025-11-08", "2025-11-09",
    "2025-11-15", "2025-11-16",
}
INPUT_FILE = "/Users/szm/code/python/check_attendance/11月考勤机.xls"
OUTPUT_FILE = "result.xlsx"

# ---------------------------
# 四个区间（只在区间内的打卡有效）
# ---------------------------
def T(h, m, s=0):
    return time(h, m, s)

AM_ON_START = T(6, 0, 0)
AM_ON_END = T(9, 20, 0)
AM_OFF_START = T(10, 45, 0)
AM_OFF_END = T(13, 45, 0)

PM_ON_START = T(13, 45, 0)
PM_ON_END = T(15, 50, 0)
PM_OFF_START = T(16, 45, 0)
PM_OFF_END = T(18, 45, 0)

# ---------------------------
# 判定基准时间（用于计算迟到/早退）
# ---------------------------
AM_ON_NORMAL = T(8, 20, 59)
AM_LEAVE_NORMAL_FROM = T(11, 45, 0)

PM_ON_NORMAL = T(14, 50, 59)
PM_LEAVE_NORMAL_FROM = T(17, 45, 0)

# ---------------------------
# 工具函数
# ---------------------------
def time_in_range(t, start, end):
    if t is None:
        return False
    return start <= t <= end

def minutes_diff_later(later: time, earlier: time):
    dt_l = datetime.combine(datetime.today(), later)
    dt_e = datetime.combine(datetime.today(), earlier)
    return int((dt_l - dt_e).total_seconds() // 60)

# ---------------------------
# 生成全体工作日
# ---------------------------
def generate_workdays(start_date, end_date, weekends):
    start_dt = datetime.strptime(start_date, "%Y-%m-%d").date()
    end_dt = datetime.strptime(end_date, "%Y-%m-%d").date()
    workdays = []
    current = start_dt
    while current <= end_dt:
        if current.strftime("%Y-%m-%d") not in weekends:
            workdays.append(current.strftime("%Y-%m-%d"))
        current += timedelta(days=1)
    return workdays

all_workdays = generate_workdays(START_DATE, END_DATE, WEEKENDS)

# ---------------------------
# 读取并预处理
# ---------------------------
df = pd.read_excel(INPUT_FILE, dtype=str)
df.columns = df.columns.str.strip()
if "姓名" not in df.columns or "日期时间" not in df.columns:
    raise RuntimeError("输入表需包含列：姓名 和 日期时间")

df["日期时间_parsed"] = pd.to_datetime(df["日期时间"], errors="coerce")
df = df.dropna(subset=["日期时间_parsed"])
df["日期"] = df["日期时间_parsed"].dt.date.astype(str)
df["时刻"] = df["日期时间_parsed"].dt.time

start_dt = datetime.strptime(START_DATE, "%Y-%m-%d").date()
end_dt = datetime.strptime(END_DATE, "%Y-%m-%d").date()
df = df[(df["日期时间_parsed"].dt.date >= start_dt) & (df["日期时间_parsed"].dt.date <= end_dt)]
df = df[~df["日期"].isin(WEEKENDS)].copy()

# ---------------------------
# 按姓名 + 日期 聚合到四区间
# ---------------------------
records = []
grouped = df.groupby(["姓名", "日期"])
for (name, date), g in grouped:
    times = g["时刻"].tolist()
    am_on_list = [t for t in times if time_in_range(t, AM_ON_START, AM_ON_END)]
    am_off_list = [t for t in times if time_in_range(t, AM_OFF_START, AM_OFF_END)]
    pm_on_list = [t for t in times if time_in_range(t, PM_ON_START, PM_ON_END)]
    pm_off_list = [t for t in times if time_in_range(t, PM_OFF_START, PM_OFF_END)]

    am_on = min(am_on_list) if am_on_list else None
    am_off = max(am_off_list) if am_off_list else None
    pm_on = min(pm_on_list) if pm_on_list else None
    pm_off = max(pm_off_list) if pm_off_list else None

    records.append({
        "姓名": name,
        "日期": date,
        "am_on": am_on,
        "am_off": am_off,
        "pm_on": pm_on,
        "pm_off": pm_off,
    })

daily = pd.DataFrame(records)

# ---------------------------
# 填补没有打卡的工作日（全天旷工）
# ---------------------------
all_names = df["姓名"].unique()
daily.set_index(["姓名","日期"], inplace=True)

for name in all_names:
    for workday in all_workdays:
        if (name, workday) not in daily.index:
            daily.loc[(name, workday), ["am_on","am_off","pm_on","pm_off"]] = [None,None,None,None]

daily.reset_index(inplace=True)

# ---------------------------
# 判定每半天状态并生成说明
# ---------------------------
detail_rows = []
for _, row in daily.iterrows():
    name = row["姓名"]
    date = row["日期"]
    am_on = row["am_on"]
    am_off = row["am_off"]
    pm_on = row["pm_on"]
    pm_off = row["pm_off"]

    # 上午
    if (am_on is None) or (am_off is None):
        am_status = "旷工"
        am_note = "上午缺上或下班打卡"
    else:
        if am_on > AM_ON_NORMAL and am_on <= AM_ON_END:
            minutes = minutes_diff_later(am_on, AM_ON_NORMAL)
            am_status = "迟到"
            am_note = f"上午迟到 {minutes} 分钟"
        elif am_off >= AM_OFF_START and am_off < AM_LEAVE_NORMAL_FROM:
            minutes = minutes_diff_later(AM_LEAVE_NORMAL_FROM, am_off)
            am_status = "早退"
            am_note = f"上午早退 {minutes} 分钟"
        else:
            am_status = "正常"
            am_note = ""

    # 下午
    if (pm_on is None) or (pm_off is None):
        pm_status = "旷工"
        pm_note = "下午缺上或下班打卡"
    else:
        if pm_on > PM_ON_NORMAL and pm_on <= PM_ON_END:
            minutes = minutes_diff_later(pm_on, PM_ON_NORMAL)
            pm_status = "迟到"
            pm_note = f"下午迟到 {minutes} 分钟"
        elif pm_off >= PM_OFF_START and pm_off < PM_LEAVE_NORMAL_FROM:
            minutes = minutes_diff_later(PM_LEAVE_NORMAL_FROM, pm_off)
            pm_status = "早退"
            pm_note = f"下午早退 {minutes} 分钟"
        else:
            pm_status = "正常"
            pm_note = ""

    detail_rows.append({
        "姓名": name,
        "日期": date,
        "上午": am_status,
        "上午说明": am_note,
        "下午": pm_status,
        "下午说明": pm_note,
    })

detail_df = pd.DataFrame(detail_rows).sort_values(["姓名","日期"])

# ---------------------------
# 汇总统计
# ---------------------------
summary = []
for name in detail_df["姓名"].unique():
    dsub = detail_df[detail_df["姓名"] == name]
    late = ((dsub["上午"]=="迟到") | (dsub["下午"]=="迟到")).sum()
    early = ((dsub["上午"]=="早退") | (dsub["下午"]=="早退")).sum()
    absent = ((dsub["上午"]=="旷工") | (dsub["下午"]=="旷工")).sum()
    summary.append({"姓名":name,"迟到":int(late),"早退":int(early),"旷工":int(absent)})

summary_df = pd.DataFrame(summary)

# ---------------------------
# 导出 Excel
# ---------------------------
with pd.ExcelWriter(OUTPUT_FILE) as writer:
    detail_df.to_excel(writer, sheet_name="详细异常表", index=False)
    summary_df.to_excel(writer, sheet_name="汇总统计表", index=False)

print("处理完成，结果保存：", OUTPUT_FILE)
