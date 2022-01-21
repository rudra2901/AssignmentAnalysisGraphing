from turtle import color
import matplotlib.pyplot as plt
import numpy as np

X = np.loadtxt("sizesmt.txt", dtype=int)

Y = np.loadtxt("countmt.txt", dtype=int)

Z = np.loadtxt("timemt.txt", dtype=float)

countF, ax = plt.subplots(2, 1)

ax[0].plot(X, Y, color="red")
ax[0].set_title("Program step Graph in Matrix Transpose")
ax[0].set_ylabel("Program Step count")

ax[1].plot(X, Z, color="red")
ax[1].set_title("Time Graph in Matrix Transpose")
ax[1].set_xlabel("Input size (n)")
ax[1].set_ylabel("Time in millisecond")

plt.show()
