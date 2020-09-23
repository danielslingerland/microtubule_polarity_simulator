from numpy.ma import sqrt
from sympy import symbols, Eq, solve
import matplotlib.pyplot as plt
# P_R, v_p, r_n, r_c, k_1, r_b, L_L, L_R = symbols('P_R v_p r_n r_c k_1 r_b L_L L_R')
# eq1 = Eq(P_R*v_p+r_n, L_R*(r_c+k_1*r_b*L_L)**2)
# eq2 = Eq((1-P_R)*v_p+r_n, L_L*(r_c+k_1*r_b*L_R)**2)
#
# eq1 = Eq(P_R*v_p+r_n, L_R*r_c+r_b*L_R*L_L)
# eq2 = Eq((1-P_R)*v_p+r_n, L_L*r_c++r_b*L_R*L_L)
#
# print(solve((eq1, eq2), (L_R, L_L)))


# L = 1
# d =2
# lr=3
# b = 4
# ll=5
# Lr = L+lr
# Ll = L+ll
#
# eq1 = (2*Lr*(1+b*Ll)**2)
# eq2 = 4*b*ll*L*(1+b*L)+2*Lr*(1+b*L)**2
# eq3 = 2*Lr*b**2*L**2+4*Lr*b**2*ll+2*Lr*b**2*ll**2+4*Lr*b*L+4*Lr*b*ll+2*Lr
# eq4 = 4*b*lr*L*(1+b*L)+2*Ll*(1+b*L)**2
#
# l = 3
# r = 2
# eq5 = (2/d)*L**3*b**2+ (4/d)*L**2*b+(2/d)*L+2*L*b**2*d*l**2+ 4*L*d*l*r + 4*b*d*l*r+2*b*d**2*l**2*r - 1
# eq4 = 2*Lr*b*ll*(2*b+b*ll+2) - 4*b*ll*L*(1+b*L)
# print(eq5)




r_c = 0.005
r_r = 0.0068
r_u = 0.1
r_n = 1
r_b = 0.001

v_p = 0.08
v_m = 0.16


P_R = []
for p in range(100):
    P_R.append(p/100)

Q = []

for q in range(100):
    N_R = (-(r_c - (r_b*r_n/r_c)*(2*P_R[q] - 1))+sqrt((r_c - (r_b*r_n/r_c)*(2*P_R[q] - 1))**2+4*r_b*r_n*P_R[q]))/r_b**2
    N_L = (-(r_c + (r_b*r_n/r_c)*(2*P_R[q] - 1))+sqrt((r_c + (r_b*r_n/r_c)*(2*P_R[q] - 1))**2+4*r_b*r_n*(1 -P_R[q])))/r_b**2
    Q.append((N_R-N_L)/(N_R+N_L))

plt.plot(P_R, Q)
plt.xlabel("P_R")
plt.ylabel("Q")
plt.show()
