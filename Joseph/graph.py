import numpy as np
import matplotlib.pyplot as plt
import os

os.makedirs("plots", exist_ok=True)

data_list = np.genfromtxt('results/linelist_results.csv', delimiter=';', skip_header=1, encoding='utf-8-sig')
n_list = data_list[:, 0]
t_list = data_list[:, 2]

data_arr = np.genfromtxt('results/array_results.csv', delimiter=';', skip_header=1, encoding='utf-8-sig')
n_arr = data_arr[:, 0]
t_arr = data_arr[:, 2]

coef_list = np.polyfit(n_list, t_list, 1)
poly_list = np.poly1d(coef_list)

coef_arr = np.polyfit(n_arr, t_arr, 2)
poly_arr = np.poly1d(coef_arr)

# прогноз до 2 млн
n_future = np.linspace(max(n_list), 2_000_000, 100)
t_future_list = poly_list(n_future)
t_future_arr = poly_arr(n_future)

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

# LineList
ax1.plot(n_list, t_list, 'o-', color='darkred', label='данные', linewidth=2, markersize=5, zorder=3)
ax1.plot(n_list, poly_list(n_list), 's-', color='blue', label='тренд', linewidth=2, markersize=4, zorder=2)
ax1.plot(n_future, t_future_list, '--', color='green', label='прогноз', linewidth=2, zorder=1)
ax1.set_xlabel('N')
ax1.set_ylabel('время (сек)')
ax1.set_title('LineList')
ax1.legend()
ax1.grid(True, alpha=0.3)

# Array
ax2.plot(n_arr, t_arr, 'o-', color='darkred', label='данные', linewidth=2, markersize=5, zorder=3)
ax2.plot(n_arr, poly_arr(n_arr), 's-', color='blue', label='тренд', linewidth=2, markersize=4, zorder=2)
ax2.plot(n_future, t_future_arr, '--', color='green', label='прогноз', linewidth=2, zorder=1)
ax2.set_xlabel('N')
ax2.set_ylabel('время (сек)')
ax2.set_title('Array')
ax2.legend()
ax2.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('plots/result.png', dpi=150)
plt.show()