'''
Program Name: DiscoveryTimePlot.py
Class: ENSE496AE Digital Security
Group: B

Author: Mckenzie Busenius

Professor: Dr. Yasser Morgan

Description: The purpose of this program is to use python's machine learning library to plot the large
             dataset of prime values and their discovery time.

'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load data into a dataset
discoverytime_PrimeNumber = pd.read_csv('PrimeBank.csv', low_memory=False)

# Set the X and Y axis
x = discoverytime_PrimeNumber['Prime Numbers']
y = discoverytime_PrimeNumber['Discovery Time']

# Plot the data and set the parameters
plt.plot(x, y, color= "orange")
plt.axis([0, 41642171, 0, 0.0125])
#plt.ylim((0.02,0))
# x-axis label
plt.xlabel('Prime Numbers (Range: 1 - 41,642,171)')
# frequency label
plt.ylabel('Discovery Time(ms)')
# plot title
plt.title('Python Plot -- Prime Number vs Discovery Time (Filtered)')
plt.show()
