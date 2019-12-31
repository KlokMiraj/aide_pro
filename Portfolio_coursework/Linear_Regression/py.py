#/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

w = 4
h = 3
d =20 
plt.figure(figsize=(w, h), dpi=d)
iris_data = np.genfromtxt(
    "iris.csv", names=True,
    dtype="float", delimiter=",")

plt.plot(iris_data["sepal_length"], iris_data["sepal_width"], "o")
plt.savefig("out.png")
