import matplotlib.pyplot as plt
import numpy as np


def read_data(filename):
    f = open("DATA_AMOLF/DATA/" + filename, "r")
    reading_data = False
    data = []
    i = 0
    for line in f:
        line = line.replace("\n", "")
        i += 1
        if reading_data:
            data.append(float(line))
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


def create_hist(data, title):
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
    plt.show()


def m0(v_grow, v_shrink, l_bar, growing):
    if growing:
        v_var = v_grow
    else:
        v_var = v_shrink
    return 1 / (v_var * l_bar * ((1 / v_grow) + (1 / v_shrink)))


def create_overview():
    data = []
    for i in range(1, 12):
        data.append(read_data("MT_polarity"+str(i)+".txt"))
    for d in data:
        create_hist(d, "test")


#create_overview()
#create_hist(read_data("MT_polarity10.txt"), "2.0e-7 per s per um ")

bindings = [0.00000000, 0.00000005, 0.00000008, 0.00000010, 0.00000011, 0.000000115, 0.00000012, 0.000000125, 0.00000013, 0.00000014, 0.00000015, 0.00000016, 0.00000017, 0.00000018, 0.00000019, 0.00000020, 0.00000021, 0.00000023, 0.00000025, 0.00000030]
polarities = []
for i in range(1,21):
    data = read_data("MT_polarity"+str(i)+".txt")
    create_hist(data, str(bindings[i-1])+" s-1 um-1")
    data_man = [abs(j -0.5) for j in data]
    polarities.append(sum(data_man)/len(data_man))


plt.plot(bindings, polarities)
plt.xlabel("bindings per second per micrometer (*10^-7)")
plt.ylabel("average distance from 0.5")
plt.show()
#0.5e-7
# testdata = [1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 140, 250, 300, 1, 2, 3, 4, 12, 4, 34, 23, 43]
# m_test_null = m0(0.08, 0.16, 50, True)*len(testdata)
# create_hist_fit(testdata, m_test_null, "test")
# length = read_data("MT_length2.txt")
# state = read_data("MT_state2.txt")
#
# growing_length = []
#
# shrinking_length = []
#
# for x in range(len(length)):
#     if round(state[x]) == 0:
#         growing_length.append(length[x])
#     else:
#         shrinking_length.append(length[x])
#
# print("finished splitting data in growing and shrinking")
# m_plus_null = m0(0.08, 0.16, 50, True)*len(length)
# m_minus_null = m0(0.08, 0.16, 50, False)*len(length)
#
# create_hist_fit(growing_length, m_plus_null, "Growing microtubules")
# create_hist_fit(shrinking_length, m_minus_null, "Shrinking microtubules")
