from sympy import symbols, Eq, solve

P_R, v_p, r_n, r_c, k_1, r_b, L_L, L_R = symbols('P_R v_p r_n r_c k_1 r_b L_L L_R')
eq1 = Eq(P_R*v_p+r_n, L_R*(r_c+k_1*r_b*L_L)**2)
eq2 = Eq((1-P_R)*v_p+r_n, L_L*(r_c+k_1*r_b*L_R)**2)

eq1 = Eq(P_R*v_p+r_n, L_R*r_c+r_b*L_R*L_L)
eq2 = Eq((1-P_R)*v_p+r_n, L_L*r_c++r_b*L_R*L_L)

print(solve((eq1, eq2), (L_R, L_L)))

