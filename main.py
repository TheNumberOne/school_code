from turtle import *

colors = ["red", "green", "blue"]
for i in range(500):
    color(colors[i % 3])
    left(57.263)
    forward(1)
    up(52)
    forward(1)
main_loop()
