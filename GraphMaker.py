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


def polarities_from_path(path):
    polarities = []
    for i in range(1, 21):
        data = read_data("MT_polarity"+str(i)+".txt", int, path)
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


lengths = read_data("MT_length_ed2.txt", float, "DATA/verifing/length_ed/")
states = read_data("MT_state_ed2.txt", int, "DATA/verifing/length_ed/")
lengths_gs = [[],[]]
for i in range(len(lengths)):
    lengths_gs[states[i]].append(lengths[i])
m0_gs = [m0(0.08, 0.16, 50, True)*len(lengths), m0(0.08, 0.16, 50, False)*len(lengths)]
create_hist_fit(lengths_gs[0], m0_gs[0], "Growing MTs")
create_hist_fit(lengths_gs[1], m0_gs[1], "Shrinking MTs")
create_hist_fit(lengths, m0_gs[1]+m0_gs[0], "All MTs")
# bindings = [0.00000000, 0.00000005, 0.00000008, 0.00000010, 0.00000011, 0.000000115, 0.00000012, 0.000000125, 0.00000013, 0.00000014, 0.00000015, 0.00000016, 0.00000017, 0.00000018, 0.00000019, 0.00000020, 0.00000021, 0.00000023, 0.00000025, 0.00000030]
#
# times_event = d_times_from_path("DATA/speed_event/")
# times_event_long = d_times_from_path("DATA/zero_event/")
# times_step01 = d_times_from_path("DATA/speed_step01/")
#
# polarities_event = polarities_from_path("DATA/speed_event/")
# polarities_event_long = polarities_from_path("DATA/zero_event/")
# polarities_step01 = polarities_from_path("DATA/speed_step01/")
#
# counts_event = read_data("step_counts.txt", int, "DATA/speed_event/")
# counts_step01 = read_data("step_counts.txt", int, "DATA/speed_step01/")
#
# counts_event_long = []
#
# for i in range(1, 21):
#     counts_event_long.append(sum(read_data("MT_polarity"+str(i)+".txt", int, "DATA/zero_event/")))
#
#
# step_time_event_long = get_step_time(times_event_long, counts_event_long)
# step_time_event= get_step_time(times_event, counts_event)
# step_time_step01= get_step_time(times_step01, counts_step01)
#
# step_time_event_long[0] = step_time_event[0]
#
# plt.plot(bindings[1:21], step_time_event_long[1:21], label="event driven: "+str("{:.2e}".format(sum(counts_event_long[1:21])))+" events")
# plt.plot(bindings[1:21], step_time_event[1:21], label="event driven: "+str("{:.2e}".format(sum(counts_event[1:21])))+" events")
# #plt.plot(bindings, times_event_long)
# plt.xlabel("binding rate (s^{-1} um^{-1})")
# plt.ylabel("time per step (s)")
# plt.legend(loc="best")
# plt.show()
#
# plt.plot(bindings[1:21], times_event[1:21], label="event driven")
# plt.plot(bindings[1:21], times_step01[1:21], label="timestep driven")
# #plt.plot(bindings, times_event_long)
# plt.xlabel("binding rate (s^{-1} um^{-1})")
# plt.ylabel("time (s)")
# plt.legend(loc="best")
# plt.show()
#
#
# plt.plot(bindings[1:21], counts_event[1:21], label="event driven")
# plt.plot(bindings[1:21], counts_step01[1:21], label="timestep driven")
# #plt.plot(bindings[1:21], counts_event_long[1:21], label="event driven")
# #plt.plot(bindings, counts_event_long)
# plt.xlabel("binding rate (s^{-1} um^{-1})")
# plt.ylabel("steps")
# plt.legend(loc="best")
# plt.show()
#
# plt.plot(bindings[1:21], polarities_event[1:21], label="event driven")
# plt.plot(bindings[1:21], polarities_step01[1:21], label="timestep driven")
# #plt.plot(bindings, polarities_event_long)
# plt.xlabel("binding rate (s^{-1} um^{-1})")
# plt.ylabel("steps")
# plt.legend(loc="best")
# plt.show()
#
# plt.plot(counts_event[1:21], times_event[1:21], "o", label="event driven")
# plt.plot(counts_step01[1:21], times_step01[1:21], "o", label="timestep driven")
# #plt.plot(counts_event_long, times_event_long, "o")
# plt.ylabel("time (s)")
# plt.xlabel("steps")
# plt.legend(loc="best")
# plt.show()
#plt.savefig("../pictures/overview.png", bbox_inches='tight')

# T_STEP = 1
# N_MICROTUBULES = 1000
# R_CATASTROPHE = 0.0016
# R_RESCUE = 0.0068
# R_UNBIND = 0.1
# V_GROW = 0.08
# V_SHRINK = 0.16
# P_RIGHT = 0.5
#
# l_bar = ((R_CATASTROPHE/V_GROW)-(R_RESCUE/V_SHRINK))**-1
#
# print(l_bar)
# R_CATASTROPHE = l_bar**-1*V_GROW
# print(R_CATASTROPHE)
# R_RESCUE = 0
# l_bar = ((R_CATASTROPHE/V_GROW)-(R_RESCUE/V_SHRINK))**-1
# print(l_bar)