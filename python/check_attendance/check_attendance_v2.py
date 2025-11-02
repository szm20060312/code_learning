import pandas as pd
from datetime import datetime, time, timedelta

# ---------------------------
# 配置（每月只需改这里）
# ---------------------------
START_DATE = "2025-09-21"
END_DATE = "2025-10-20"
# 你给的不工作日（周末/休息日）
WEEKENDS = {
    "2025-09-21", "2025-09-27",
    "2025-10-01", "2025-10-02",
    "2025-10-03", "2025-10-04",
    "2025-10-05", "2025-10-06",
    "2025-10-07", "2025-10-08",
    "2025-10-12", "2025-10-18",
    "2025-10-19"
}
INPUT_FILE = "/Users/szm/code/python/check_attendance/10月考勤机.xls"
OUTPUT_FILE = "/Users/szm/code/python/check_attendance/考勤结果_四区间规则.xlsx"

# ---------------------------
# 四个区间（只在区间内的打卡有效）
# ---------------------------
def T(h, m, s=0):
    return time(h, m, s)

AM_ON_START = T(6, 0, 0)
AM_ON_END = T(9, 20, 0)         # 上午上班区间：06:00 - 09:20 （取最早）
AM_OFF_START = T(10, 45, 0)
AM_OFF_END = T(13, 45, 0)       # 上午下班区间：10:45 - 13:45 （取最晚）

PM_ON_START = T(13, 45, 0)
PM_ON_END = T(15, 50, 0)        # 下午上班区间：13:45 - 15:50 （取最早）
PM_OFF_START = T(16, 45, 0)
PM_OFF_END = T(18, 45, 0)       # 下午下班区间：16:45 - 18:45 （取最晚）

# ---------------------------
# 判定基准时间（用于计算迟到/早退）
# ---------------------------
AM_ON_NORMAL = T(8, 20, 59)
AM_LEAVE_EARLY_START = T(10, 45, 0)
AM_LEAVE_NORMAL_FROM = T(11, 45, 0)   # >=11:45视为正常下班（到13:45内都正常）

PM_ON_NORMAL = T(14, 50, 59)
PM_LEAVE_EARLY_START = T(16, 45, 0)
PM_LEAVE_NORMAL_FROM = T(17, 45, 0)   # >=17:45视为正常下班（到18:45内都正常）

# ---------------------------
# 工具函数
# ---------------------------
def time_in_range(t, start, end):
    """闭区间判断 time 是否在 start-end 之间"""
    if t is None:
        return False
    return start <= t <= end

def minutes_diff_later(later: time, earlier: time):
    """返回 later - earlier 的分钟差（向下取整整数分钟，可能为0）"""
    dt_l = datetime.combine(datetime.today(), later)
    dt_e = datetime.combine(datetime.today(), earlier)
    return int((dt_l - dt_e).total_seconds() // 60)

# ---------------------------
# 读取并预处理
# ---------------------------
df = pd.read_excel(INPUT_FILE, dtype=str)
# 关键列名假设输入文件列名包含“姓名”和“日期时间”，若不同请调整
df.columns = df.columns.str.strip()
if "姓名" not in df.columns or "日期时间" not in df.columns:
    raise RuntimeError("输入表需包含列：姓名 和 日期时间（例如 '2025/7/21 8:34'）")

# 解析时间
df["日期时间_parsed"] = pd.to_datetime(df["日期时间"], errors="coerce")
df = df.dropna(subset=["日期时间_parsed"])
df["日期"] = df["日期时间_parsed"].dt.date.astype(str)  # 字符串形式便于与 WEEKENDS 比较
df["时刻"] = df["日期时间_parsed"].dt.time

# 仅保留处理区间内的日期范围
start_dt = datetime.strptime(START_DATE, "%Y-%m-%d").date()
end_dt = datetime.strptime(END_DATE, "%Y-%m-%d").date()
df = df[(df["日期时间_parsed"].dt.date >= start_dt) & (df["日期时间_parsed"].dt.date <= end_dt)]

# 删除在 WEEKENDS 中的日期
df = df[~df["日期"].isin(WEEKENDS)].copy()

# ---------------------------
# 按姓名 + 日期 聚合：把打卡分到四个区间内（区间外直接丢弃）
# ---------------------------
records = []
grouped = df.groupby(["姓名", "日期"])
for (name, date), g in grouped:
    times = g["时刻"].tolist()
    # 把时间放到对应区间列表
    am_on_list = [t for t in times if time_in_range(t, AM_ON_START, AM_ON_END)]
    am_off_list = [t for t in times if time_in_range(t, AM_OFF_START, AM_OFF_END)]
    pm_on_list = [t for t in times if time_in_range(t, PM_ON_START, PM_ON_END)]
    pm_off_list = [t for t in times if time_in_range(t, PM_OFF_START, PM_OFF_END)]

    # 按规则取值：上班区间取最早，上班取 min；下班区间取最晚，取 max
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

# 若某人当日完全没有打卡（在四区间均无记录），也需要加一条：表示全天无记录 -> 两次旷工
# 找出在日期范围内但未出现于 daily 的人员日期组合（可选：若需统计所有工作日）
# 对于本任务，我们只统计出现过打卡的日子；若需要把整个月每人每工作日都列出，请告诉我我会加入自动扩展。

# ---------------------------
# 判定每半天状态并生成说明
# ---------------------------
detail_rows = []
for _, row in daily.iterrows():
    name = row["姓名"]
    date = row["日期"]

    # 上午判断
    am_on = row["am_on"]
    am_off = row["am_off"]
    if (am_on is None) or (am_off is None):
        am_status = "旷工"
        am_note = "上午缺上或下班打卡"
    else:
        # 若上班打卡晚于 09:20 -> 根据规则这可能要判旷工（因为超出上班区间），但我们已只保留区间内的打卡
        # 上班迟到判断
        if am_on > AM_ON_NORMAL and am_on <= AM_ON_END:
            minutes = minutes_diff_later(am_on, AM_ON_NORMAL)
            am_status = "迟到"
            am_note = f"上午迟到 {minutes} 分钟"
        # 下班早退判断（10:45:00 ～ 11:44:59）
        elif am_off >= AM_LEAVE_EARLY_START and am_off < AM_LEAVE_NORMAL_FROM:
            # 早退分钟 = (11:45:00 - actual_off)
            minutes = minutes_diff_later(AM_LEAVE_NORMAL_FROM, am_off)
            am_status = "早退"
            am_note = f"上午早退 {minutes} 分钟"
        else:
            # 否则视为正常（包括中午11:45~13:45 的正常下班）
            am_status = "正常"
            am_note = ""

    # 下午判断
    pm_on = row["pm_on"]
    pm_off = row["pm_off"]
    if (pm_on is None) or (pm_off is None):
        pm_status = "旷工"
        pm_note = "下午缺上或下班打卡"
    else:
        if pm_on > PM_ON_NORMAL and pm_on <= PM_ON_END:
            minutes = minutes_diff_later(pm_on, PM_ON_NORMAL)
            pm_status = "迟到"
            pm_note = f"下午迟到 {minutes} 分钟"
        elif pm_off >= PM_LEAVE_EARLY_START and pm_off < PM_LEAVE_NORMAL_FROM:
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

detail_df = pd.DataFrame(detail_rows).sort_values(["姓名", "日期"])

# ---------------------------
# 汇总统计：按人统计 迟到 / 早退 / 旷工 次数（半天计数）
# ---------------------------
def count_status(df, name, status):
    return ((df["姓名"] == name) & ((df["上午"] == status) | (df["下午"] == status))).sum()

summary = []
for name in detail_df["姓名"].unique():
    dsub = detail_df[detail_df["姓名"] == name]
    late = ((dsub["上午"] == "迟到") | (dsub["下午"] == "迟到")).sum()
    early = ((dsub["上午"] == "早退") | (dsub["下午"] == "早退")).sum()
    absent = ((dsub["上午"] == "旷工") | (dsub["下午"] == "旷工")).sum()
    summary.append({"姓名": name, "迟到": int(late), "早退": int(early), "旷工": int(absent)})

summary_df = pd.DataFrame(summary)

# ---------------------------
# 导出 Excel（两个表）
# ---------------------------
with pd.ExcelWriter(OUTPUT_FILE) as writer:
    detail_df.to_excel(writer, sheet_name="详细异常表", index=False)
    summary_df.to_excel(writer, sheet_name="汇总统计表", index=False)

print("处理完成，结果保存：", OUTPUT_FILE)
