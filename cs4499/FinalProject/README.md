# Final project
##Compile Instructions


Make sure that you have the boost math library installed on your system: `sudo apt-get install libboost-math-dev`

Compilation via cmake:
```
cmake .
make
```

Compilation via g++:
```
g++ -std=c++17 main.cpp -o FinalProject
```

Compilation via Visual Studio:
```
cmake .
```
Open generated solution in Visual Studio.

A pre-compiled Linux executable is also provided: FinalProject

##Run Instructions

To get the output of the final project, run `./FinalProject`. To generate a histogram, 
run `./FinalProject | python3 plot.py`. To save output to a file, run `./FinalProject > output.txt`. You
can also generate a plot from an existing output file using `python3 plot.py < output.txt`. To generate the plot,
make sure you have python 3 and matplotlib installed.

Commands to install plotting dependencies on ubuntu:
```
sudo apt-get install python3
sudo apt-get install python3-tk
sudo apt-get install python3-pip
sudo pip3 install matplotlib
```