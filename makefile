all: exec

exec: main.o user.o vehicle.o
	gcc -g -o exec.out main.o ./user/user.o ./vehicle/vehicle.o

main.o: main.c
	gcc -g -o main.o main.c -c  -ansi -pedantic -Wno-comment

user.o:
	gcc -g -o ./user/user.o ./user/user.c -c  -ansi -pedantic -Wno-comment

vehicle.o:
	gcc -g -o ./vehicle/vehicle.o ./vehicle/vehicle.c -c  -ansi -pedantic -Wno-comment

# sets.o:
# 	gcc -g -o ./data/sets/sets.o ./data/sets/sets.c -c  -ansi -pedantic -lm

# parts.o:
# 	gcc -g -o ./data/parts/parts.o ./data/parts/parts.c -c  -ansi -pedantic -lm

# parts_sets.o:
# 	gcc -g -o ./data/parts_sets/parts_sets.o ./data/parts_sets/parts_sets.c -c  -ansi -pedantic -lm

# library.o:
# 	gcc -g -o ./data/library.o ./data/library.c -c  -ansi -pedantic -lm

clean:
	rm -rf *.o

run:
	make clean
	make all

