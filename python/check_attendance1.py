import pandas as pd
from datetime import datetime, time

# === 配置部分 ===
file_path = "/Users/szm/code/python/8月考勤机.xls"   # 修改为你的文件路径
weekends = ["2025/7/26","2025/7/27","2025/8/2","2025/8/3","2025/8/9","2025/8/10","2025/8/16","2025/8/17"]

# 读取 Excel（自动选择引擎）
def read_excel_auto(path):
    if path.endswith(".xlsx"):
        return pd.read_excel(path, engine="openpyxl")
    else:
        return pd.read_excel(path, engine="xlrd")

df = read_excel_auto(file_path)

# 只保留姓名、时间列
df = df[["姓名", "日期时间"]].copy()
df["日期时间"] = pd.to_datetime(df["日期时间"])

# 添加日期列
df["日期"] = df["日期时间"].dt.date

# 去掉周末
weekends = [pd.to_datetime(d).date() for d in weekends]
df = df[~df["日期"].isin(weekends)]

# 存储结果
results = []

# 按姓名+日期分组
for (name, date), group in df.groupby(["姓名", "日期"]):
    times = sorted(group["日期时间"].dt.time)
    
    # 判断旷工
    if len(times) < 4:
        results.append((name, date, "旷工"))
        continue
    
    # 上午/下午分界线 13:00
    am_times = [t for t in times if t < time(13,0)]
    pm_times = [t for t in times if t >= time(13,0)]
    
    status = []
    if am_times:
        if min(am_times) > time(8,21):   # 严格晚于 08:21 才算迟到
            status.append("迟到(上午)")
        if max(am_times) < time(11,44):  # 严格早于 11:44 才算早退
            status.append("早退(上午)")
    if pm_times:
        if min(pm_times) > time(14,46):  # 严格晚于 14:46 才算迟到
            status.append("迟到(下午)")
        if max(pm_times) < time(17,44):  # 严格早于 17:44 才算早退
            status.append("早退(下午)")
    
    if status:
        results.append((name, date, "、".join(status)))

# 转为 DataFrame 输出
res_df = pd.DataFrame(results, columns=["姓名", "日期", "异常情况"])
print(res_df)

# 如果需要保存成Excel
res_df.to_excel("考勤异常结果1.xlsx", index=False)
