import re

import math
from matplotlib import pyplot as plt


def watt(e):
    return .4865 * math.sinh(math.sqrt(2 * e)) * math.exp(-e)


while input() != "Bins:":
    continue

valid_num = re.compile(r"\d+")
bin_nums, bin_counts = [list(map(float, filter(valid_num.match, input().split(" ")))) for i in range(2)]
total_count = sum(bin_counts)

scale_bins = 8 / len(bin_nums)
bin_xs = [scale_bins * (x + .5) for x in bin_nums]
bin_ys = bin_counts

plt.bar(bin_xs, bin_ys, width=.1)

desired_y = [total_count * watt(x) * scale_bins for x in bin_xs]
plt.plot(bin_xs, desired_y, 'r--')

plt.ylabel("Frequency")
plt.xlabel("E")
plt.show()
