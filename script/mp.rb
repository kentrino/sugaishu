
D_MAX = 1664510
x = 198709817235
n = 102938709872

x_s = x % D_MAX
x_m = (x / INT_MAX) % D_MAX
x_l = x / (D_MAX ** 2)

r = 0
r += x_s * x_s
# D_max ** 4
r += D_MAX ** 2 * x_m * x_m
# D_max ** 6
D_MAX ** 4 * x_l * x_l
D_MAX ** 3 * 2 * x_l * x_m
D_MAX ** 2 * 2 * x_l * x_s
D_MAX ** 1 * 2 * x_m * x_s

