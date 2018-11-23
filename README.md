# Final Project for CS2275

The build and run files on here are for building/running on ubuntu.

Packages installed on ubuntu: `qemu-system`, `arm-linux-gnueabi`, `arm-linux-gnueabi-dbg`, `gcc-arm-linux-gnueabi`, `gdb-multiarch`

To build simply do `make` on a raspberry pi. Binary is `final_project`. To call do: `final_project input.txt output.txt`.  

Input format is a comma separated list of positive integers. Any invalid numbers will be converted to -1, along with adjacent
text and digits to the nearest commas or end/start of file. Newline characters and leading and trailing whitespace also have
this behavior. If extra commas are adjacent to each other, it is assumed that no number is specified. Here are some examples:

 * `1, 546,4,6` is converted to `1,-1,4,6`
 * `1,2,3` is converted to `1,2,3`
 * `45,83,12,960,-4,0,2` is converted to `45,83,12,960,-1,0,2`
 * `1,2,4,5\n` is converted to `1,2,4,-1`


The program then takes the input and sorts it. It then outputs the input to the specified file. It uses a comma as a delimeter
and outputs no trailing newlines. Warning: null characters will cause undefined behavior.

This project also contains a number of helpful scripts. One such script is `gen_test.sh`. To use, call as `gen_test.sh n input.txt`.
This will generate the numbers `1` to `n` in a random order and insert them into `input.txt`.

Another script is the `run.sh` script. This script executes `final_project` on the qemu arm virtual machine and forwards all arguments
to it. `debug.sh` is similar. However, it also opens a gdb console and pauses the program at the start of the `main` function. Both of
these two scripts are intended to be ran on ubuntu. They would likely work on other systems though.
