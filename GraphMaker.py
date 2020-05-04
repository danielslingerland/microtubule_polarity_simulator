#!/usr/bin/env python3

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np


def read_data(filename, type_to):
    # f = open("../DATA/" + filename, "r")
    f = open("../DATA/" + filename, "r")
    reading_data = False
    data = []
    i = 0
    for line in f:
        line = line.replace("\n", "")
        i += 1
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
    plt.savefig("../pictures/MT_polarity" +str(i)+ ".png", bbox_inches='tight')


def create_bar(data, title):
    x_as = []
    for j in range(len(data)):
        x_as.append(j/len(data))
    plt.bar(data, x_as)
    plt.title(title)
    plt.xlabel("L/(L+R)")
    plt.ylabel("counts")
    plt.savefig("../pictures/MT_polarity" +str(i)+ ".png", bbox_inches='tight')


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
        polarity = abs((d/len(data_bins))-0.5+(1/len(data_bins))*0.5)
        nominator += data_bins[d]*polarity
    return nominator/denominator


bindings = [0.00000000, 0.00000005, 0.00000008, 0.00000010, 0.00000011, 0.000000115, 0.00000012, 0.000000125, 0.00000013, 0.00000014, 0.00000015, 0.00000016, 0.00000017, 0.00000018, 0.00000019, 0.00000020, 0.00000021, 0.00000023, 0.00000025, 0.00000030]
polarities = []
for i in range(0, 20):
    data = read_data("MT_polarity"+str(i)+".txt", int)
    create_bar(data, str(bindings[i-1])+" s-1 um-1")
    #data_man = [abs(j -0.5) for j in data]
    polarities.append(polarity_from_bins(data))
    plt.figure(i+2)

plt.plot(bindings, polarities)
plt.xlabel("binding rate (s^{-1} um^{-1})")
plt.ylabel("average distance from 0.5")
plt.savefig("../pictures/overview.png", bbox_inches='tight')


