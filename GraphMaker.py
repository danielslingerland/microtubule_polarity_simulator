#!/usr/bin/env python3

# import matplotlib
# matplotlib.use('Agg')
from datetime import datetime

import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import numpy as np

import os


def read_time(filename, path):

    f = open(path + filename, "r")
    for line in f:
        line = line.replace("\n", "")
        line = line.replace("simulation started writing at: ", "")
        line = line.replace("  ", " ")
        return datetime.strptime(line, "%a %b %d %H:%M:%S %Y")


def read_binding_rate(filename, path):
    f = open(path + filename, "r")
    for line in f:
        line = line.replace("\n", "")
        if "BINDING_PER_LENGTH_PER_TIME:" in line:
            line = line.replace("BINDING_PER_LENGTH_PER_TIME: ", "")
            return float(line)


def read_multiple_times(filename, path):
    f = open(path + filename, "r")
    times = []
    for line in f:
        if "simulation started writing at: " in line:
            line = line.replace("\n", "")
            line = line.replace("simulation started writing at: ", "")
            line = line.replace("  ", " ")
            times.append(datetime.strptime(line, "%a %b %d %H:%M:%S %Y"))
    return times


def read_data(filename, type_to, path):
    # f = open("../DATA/" + filename, "r")
    f = open(path + filename, "r")
    reading_data = False
    data = []
    i = 0
    for line in f:
        line = line.replace("\n", "")
        i += 1
        if i == 100000000:
            break
        if reading_data:
            data.append(type_to(line))
        else:
            print(line)
            if line == "DATA":
                print("start reading data " + filename)
                reading_data = True
    print("finsihed reading " + filename)
    return data


def create_hist_fit(data, m_null, title):
    # the histogram of the data
    bins = []
    for bin in range(301):
        bins.append(bin)
    plt.hist(data, bins, density=False, facecolor='g', alpha=0.75, label="Simulation")
    plt.xlabel('length')
    plt.ylabel('number of microtubules')
    plt.title(title)
    plt.xlim(0, 300)
    xl = np.linspace(0, 300, 100)
    yl = m_null * np.exp(-xl / 50)
    plt.plot(xl, yl, '-r', label="Theoretical")
    plt.legend(loc='best')
    plt.grid()
    plt.show()


def create_hist(data, title, i):
    # the histogram of the data
    bins = []
    for bin in range(101):
        bins.append(bin/100)
    plt.hist(data, bins, density=False, facecolor='g', alpha=0.75, label="Simulation")
    plt.xlabel('length L / length total')
    plt.ylabel('number of systems')
    plt.xlim(0, 1)
    plt.title(title)
    plt.grid()
    plt.savefig("../pictures/MT_polarity" +str(i)+ ".png", bbox_inches='tight')


def create_bar(data, title, i):
    x_as = []
    for j in range(len(data)):
        x_as.append(j/len(data))
    plt.bar(data, x_as)
    plt.title(title)
    plt.xlabel("L/(L+R)")
    plt.ylabel("counts")
    plt.show()
    #plt.savefig("../pictures/MT_polarity" +str(i)+ ".png", bbox_inches='tight')


def m0(v_grow, v_shrink, l_bar, growing):
    if growing:
        v_var = v_grow
    else:
        v_var = v_shrink
    return 1 / (v_var * l_bar * ((1 / v_grow) + (1 / v_shrink)))


# def create_overview():
#     data = []
#     for i in range(1, 12):
#         data.append(read_data("MT_polarity"+str(i)+".txt"))
#     for d in data:
#         create_hist(d, "test")


def polarity_from_bins(data_bins):
    denominator = 0
    nominator = 0
    for d in range(len(data_bins)):
        denominator += data_bins[d]
        polarity = abs((d/len(data_bins))-0.5+(1/len(data_bins))*0.5)*2
        nominator += data_bins[d]*polarity
    return nominator/denominator

def d_times_from_path(path):
    if os.path.exists(path+"step_counts.txt"):
        times = [read_time("step_counts.txt", path)]
    else:
        times = [read_time("MT_polarity1.txt", path)]

    for j in range(1, 21):
        times.append(read_time("MT_polarity"+str(j)+".txt", path))
    dtimes = []
    for j in range(20):
        dtimes.append((times[j+1]-times[j]).total_seconds())
    return dtimes

def d_times_from_times(times):
    dtimes = []
    for j in range(len(times)-1):
        dtimes.append((times[j+1]-times[j]).total_seconds())
    return dtimes


def polarities_from_path(path, n=20, name="MT_polarity"):
    polarities = []
    for i in range(1, n+1):
        data = read_data(name+str(i)+".txt", float, path)
        #data_man = [abs(j -0.5) for j in data]
        polarities.append(polarity_from_bins(data))
        #plt.plot(data)
        #plt.show()
    return polarities

def binding_rates_from_path(path, n=20):
    binding_rates = []
    for i in range(1, n+1):
        data = read_binding_rate("MT_polarity"+str(i)+".txt", path)
        binding_rates.append(data)
    return binding_rates


def get_step_time(time, steps):
    step_times = []
    for j in range(len(time)):
        step_times.append(time[j]/steps[j])
    return step_times

def make_Q_over_Pr():
    Pr = np.linspace(0, 1, 100)
    rb = 1
    rc = 0.005
    rn = 1
    Mr = (-(rc-rb*rn*(2*Pr-1)/rc)+np.sqrt((rc-rb*rn*(2*Pr-1)/rc)**2+4*rb*rn*Pr))/rb**2
    Ml = (-(rc+rb*rn*(2*Pr-1)/rc)+np.sqrt((rc+rb*rn*(2*Pr-1)/rc)**2+4*rb*rn*(1-Pr)))/rb**2
    Q = (Mr-Ml)/(Mr+Ml)
    plt.plot(Pr, Q, '-r', label="Q(P_R)")
    plt.xscale('linear')
    plt.ylabel("polarity")
    plt.xlabel("Probability of Right nucleation")
    plt.legend(loc='best')
    plt.show()

#make_Q_over_Pr()

def length_v_number():
    n2 = polarities_from_path("D:/Documenten_D/Stage_AMOLF/DATA/number_dependent20_7/", 40)
    nl2= read_data("MT_length.txt", float, "D:/Documenten_D/Stage_AMOLF/DATA/number_dependent20_7/")
    rbn2= binding_rates_from_path("D:/Documenten_D/Stage_AMOLF/DATA/number_dependent20_7/", 40)

    l2 = polarities_from_path("D:/Documenten_D/Stage_AMOLF/DATA/length_dependent20_7/", 40)
    ll2= read_data("MT_length.txt", float, "D:/Documenten_D/Stage_AMOLF/DATA/length_dependent20_7/")
    rbl2= binding_rates_from_path("D:/Documenten_D/Stage_AMOLF/DATA/length_dependent20_7/", 40)

    plt.plot(rbn2, n2, "x", color="blue", label="number")
    plt.plot(rbl2, l2, "x", color="red", label="length")
    plt.xscale('log')
    plt.ylabel("polarity")
    plt.xlabel("binding rate")
    plt.legend()
    plt.show()
    plt.plot(rbn2[0:40], nl2[0:40], "x", color="blue", label="number")
    plt.plot(rbl2[0:40], ll2[0:40], "x", color="red", label="length")
    plt.xscale('log')
    plt.ylabel("length (um)")
    plt.xlabel("binding rate")
    plt.legend()
    plt.show()

polarity = []
for n in range(301):
    polarity.append((n/150)-1)

d = read_data("MT_polarity9.txt", float, "D:/Documenten_D/Stage_AMOLF/DATA/rescues_disabled/")
r_b = read_binding_rate("MT_polarity9.txt","D:/Documenten_D/Stage_AMOLF/DATA/rescues_disabled/")
plt.title(r"$r_b = $"+str(r_b))
plt.plot(polarity, d, "x")
plt.xlabel(r"polarity $\frac{L_R-L_L}{L_R+L+L}$")
plt.ylabel("counts")
plt.show()


p = polarities_from_path("D:/Documenten_D/Stage_AMOLF/DATA/host_panalty50/")
b = binding_rates_from_path("D:/Documenten_D/Stage_AMOLF/DATA/host_panalty50/")
p0= read_data("polarities_zero.txt", float, "D:/Documenten_D/Stage_AMOLF/DATA/zc_simplified/")
for i in range(20):
    p0[i] *= 2
plt.plot(b, p, "x", label=r"host penalty: 50% $v^+$")
plt.plot(b, p0, "x", label="no host penalty")
plt.xlabel(r"$r_b (s^{-1}\mu m^{-1})$")
plt.ylabel("absolute value of polairity")
plt.legend()
plt.show()

volumes = []
xs = []
ys = []
zs = []
for z in range(10):
    for y in range(10):
        for x in range(10):
            volumes.append(50*x*50*y*50*z)
            xs.append(x)
            ys.append(y)
            zs.append(z)

# for f in range(1, 400):
#     data = read_data("polarity"+str(f)+".txt", int, "D:/Documenten_D/Stage_AMOLF/DATA/3d/")
#     plt.plot(data)
#     plt.show()

dd = polarities_from_path("D:/Documenten_D/Stage_AMOLF/DATA/3d/", 1000, "polarity")
dd_non_zeros = []
volumes_non_zeros = []
for i in range(1000):
    if volumes[i] != 0:
        dd_non_zeros.append(dd[i])
        volumes_non_zeros.append(volumes[i])

plt.plot(dd[0:100], "x", color="blue", label="number")
plt.plot(dd[100:200], "x", color="red", label="number")
plt.plot(dd[200:300], "x", color="green", label="number")
plt.plot(dd[300:400], "x", color="black", label="number")
plt.plot(dd[400:500], "x", color="gray", label="number")
plt.plot(dd[500:600], "x", color="purple", label="number")
plt.show()


plt.plot(volumes[100:200],dd[100:200], "x", color="red", label="number")
plt.plot(volumes[200:300],dd[200:300], "x", color="green", label="number")
plt.plot(volumes[300:400],dd[300:400], "x", color="black", label="number")
plt.plot(volumes[400:500],dd[400:500], "x", color="gray", label="number")
plt.plot(volumes[500:600],dd[500:600], "x", color="purple", label="number")

plt.show()
#
# plt.plot(xs[0:100],dd[0:100], "x", color="blue", label="number")
# plt.plot(xs[100:200],dd[100:200], "x", color="red", label="number")
# plt.plot(xs[200:300],dd[200:300], "x", color="green", label="number")
# plt.plot(xs[300:400],dd[300:400], "x", color="black", label="number")
# plt.show()
#
# plt.plot(ys[0:100],dd[0:100], "x", color="blue", label="number")
# plt.plot(ys[100:200],dd[100:200], "x", color="red", label="number")
# plt.plot(ys[200:300],dd[200:300], "x", color="green", label="number")
# plt.plot(ys[300:400],dd[300:400], "x", color="black", label="number")
# plt.show()
#
# plt.plot(zs[0:100],dd[0:100], "x", color="blue", label="number")
# plt.plot(zs[100:200],dd[100:200], "x", color="red", label="number")
# plt.plot(zs[200:300],dd[200:300], "x", color="green", label="number")
# plt.plot(zs[300:400],dd[300:400], "x", color="black", label="number")
# plt.show()

plt.plot(volumes[0:1000], dd[0:1000], "x", color="red", label="number")
plt.ylabel("polarity")
plt.xlabel("volume")
plt.legend()
plt.show()

plt.plot(volumes_non_zeros, dd_non_zeros, "x", color="red", label="number")
plt.ylabel("absolute value of polarity")
plt.xlabel(r"volume ($\mu m^3$)")
plt.legend()
plt.show()

plt.plot(volumes_non_zeros, dd_non_zeros, "x", color="red", label="number")
plt.ylabel("absolute value of polarity")
plt.xlabel(r"volume ($\mu m^3$)")
plt.xlim([0, 1.45e7])
plt.ylim([0, 1])
plt.show()

plt.plot(xs[0:1000], dd[0:1000], "x", color="red", label="number")
plt.ylabel("polarity")
plt.xlabel("length x")
plt.legend()
plt.show()

plt.plot(zs[0:1000], dd[0:1000], "x", color="red", label="number")
plt.ylabel("polarity")
plt.xlabel("length z")
plt.legend()
plt.show()

plt.plot(ys[000:1000], dd[0:1000], "x", color="red", label="number")
plt.ylabel("polarity")
plt.xlabel("length y")
plt.legend()
plt.show()

# box = []
# for i in range(10):
#     box.append([])
# for i in range(600):
#     box[ys[i]].append(dd[i])