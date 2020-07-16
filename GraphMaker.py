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
        polarity = abs((d/len(data_bins))-0.5+(1/len(data_bins))*0.5)
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


def polarities_from_path(path):
    polarities = []
    for i in range(1, 21):
        data = read_data("MT_polarity"+str(i)+".txt", float, path)
        #data_man = [abs(j -0.5) for j in data]
        polarities.append(polarity_from_bins(data))
        #plt.plot(data)
        #plt.show()
    return polarities


def get_step_time(time, steps):
    step_times = []
    for j in range(len(time)):
        step_times.append(time[j]/steps[j])
    return step_times


n1 = polarities_from_path("D:/Documenten_D/Stage_AMOLF/DATA/number_dependent15_7c/")
l1 = polarities_from_path("D:/Documenten_D/Stage_AMOLF/DATA/length_dependent15_7d/")

nl1 = read_data("MT_length.txt", float, "D:/Documenten_D/Stage_AMOLF/DATA/number_dependent15_7c/")
ll1 = read_data("MT_length.txt", float, "D:/Documenten_D/Stage_AMOLF/DATA/length_dependent15_7d/")
plt.plot(n1, "o", color="blue")
plt.plot(l1, "o", color="red")
plt.show()

plt.plot(nl1, "x", color="blue")
plt.plot(ll1, "x", color="red")

plt.show()