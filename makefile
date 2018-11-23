# AS = arm-linux-gnueabi-as
# ASFLAGS = -march=armv8-a
# CC = arm-linux-gnueabi-gcc
# CCFLAGS = -march=armv8-a

final_project: src/main.o src/explode.o src/file_input.o src/file_output.o src/int_to_string.o src/merge_sort.o src/string_to_int.o
	$(CC) $(CCFLAGS) -o final_project src/main.o src/explode.o src/file_input.o src/file_output.o src/int_to_string.o src/merge_sort.o src/string_to_int.o
