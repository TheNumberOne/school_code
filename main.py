from turtle import *

colors = [(1, 0, 0), "green", "blue"]
for i in range(500):
    speed(i)
    color(colors[i // 100 % 3])
    left(57.263)
    forward(1)
    up(52)
    forward(1)
look_from(0, 5, 20)
look_at(0, 0, 0)
main_loop()
