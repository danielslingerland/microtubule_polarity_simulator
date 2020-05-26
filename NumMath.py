#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt


def solve_abc(a, b, c):
    D = b**2-4*a*c
    s1 = (-b+np.sqrt(D))/(2*a)
    s2 = (-b-np.sqrt(D))/(2*a)
    print("1th solution (+): ", str(s1))
    print("2th solution (-): ", str(s2))


def solve_ab(a, b):
    print("solution: ", str(-b/a))


r_binding = 0.0000001
l_L = 0#500*50
r_c = 0.005
rng = 0.5
ld_L = 0.01

x_limit = 2.0e3#2.0e7
y_limit = 0.2e2#0.2e6
x = np.linspace(-x_limit, x_limit, 100)
y1 = 0.5*r_binding*-ld_L*x**2 + (r_binding*l_L+r_c)*x+np.log(rng)
y2 = 0.5*r_binding*ld_L*x**2 + (r_binding*l_L+r_c)*x+np.log(rng)
y3 = r_c*x+np.log(rng)
y4 = 0*x
plt.xlim(-x_limit, x_limit)
plt.ylim(-y_limit, y_limit)
plt.plot(x, y4, '-', color="gray")
plt.axvline(0, -y_limit, y_limit, color="gray")
plt.plot(x, y1, '-r', label="r_b > 0, a > 0")
plt.plot(x, y2, '-b', label="r_b > 0, a < 0")
plt.plot(x, y3, '-g', label="r_b = 0, a = 0")

plt.legend(loc='best')

plt.show()

solve_abc(0.5*r_binding*-ld_L, (r_binding*l_L+r_c), np.log(rng))
solve_ab(r_c, np.log(rng))
solve_abc(0.5*r_binding*ld_L, (r_binding*l_L+r_c), np.log(rng))






