import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick

# naloži CSV
df = pd.read_csv("timing_results.csv")

# izračunaj speedup in učinkovitost
df["speedup"] = df["time_seconds"].iloc[0] / df["time_seconds"]
df["efficiency"] = df["speedup"] / df["threads"]

# skupna barva
color = "#1f77b4"

# 1. graf: čas izvajanja
plt.figure(figsize=(8, 5))
plt.barh(df["threads"], df["time_seconds"], color=color)
plt.xlabel("Čas izvajanja (s)")
plt.ylabel("Število threadov")
plt.title("Čas izvajanja glede na število threadov")
plt.gca().invert_yaxis()
plt.grid(axis="x", linestyle="--", alpha=0.6)
plt.tight_layout()
plt.savefig("graf_cas_izvajanja.png")

# 2. graf: speedup
plt.figure(figsize=(8, 5))
plt.barh(df["threads"], df["speedup"], color=color)
plt.plot(df["threads"], df["threads"], linestyle="--", color="gray", label="idealni speedup")
plt.xlabel("Speedup")
plt.ylabel("Število threadov")
plt.title("Dejanski vs. idealni speedup")
plt.gca().invert_yaxis()
plt.grid(axis="x", linestyle="--", alpha=0.6)
plt.legend()
plt.tight_layout()
plt.savefig("graf_speedup.png")

# 3. graf: učinkovitost
plt.figure(figsize=(8, 5))
plt.barh(df["threads"], df["efficiency"], color=color)
plt.xlabel("Učinkovitost")
plt.ylabel("Število threadov")
plt.title("Učinkovitost paralelizacije (speedup/threadi)")
plt.gca().invert_yaxis()
plt.gca().xaxis.set_major_formatter(mtick.PercentFormatter(1.0))
plt.grid(axis="x", linestyle="--", alpha=0.6)
plt.tight_layout()
plt.savefig("graf_ucinkovitost.png")