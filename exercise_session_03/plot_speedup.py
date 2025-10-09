import re, glob, sys
import matplotlib.pyplot as plt

# expects files like run_sum_omp_t1.txt, ... containing "Computed in X seconds"
times = {}
for path in sorted(glob.glob("run_sum_omp_t*.txt")):
    with open(path) as f:
        txt = f.read()
    m = re.search(r"Computed in\s+([0-9.]+)\s+seconds", txt)
    if not m: 
        print(f"Skip {path} (no time)"); 
        continue
    p = int(re.search(r"t(\d+)", path).group(1))
    times[p] = float(m.group(1))

if 1 not in times:
    print("Need the 1-thread result (run_sum_omp_t1.txt)."); sys.exit(1)

p_sorted = sorted(times)
T1 = times[1]
S = [T1 / times[p] for p in p_sorted]

plt.figure()
plt.plot(p_sorted, S, marker='o', label='measured')
plt.plot(p_sorted, p_sorted, '--', label='ideal')
plt.xlabel('Threads (p)'); plt.ylabel('Speedup S(p)=T1/Tp)')
plt.title('OpenMP speedup for sum')
plt.grid(True); plt.legend()
plt.tight_layout()
plt.savefig('speedup.png', dpi=150)
print("Wrote speedup.png")
