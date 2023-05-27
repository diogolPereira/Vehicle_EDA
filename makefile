all: exec

exec: main.o user.o vehicle.o rent.o graph.o
	gcc -g -o vehicle-rental-system.exe main.o ./user/user.o ./rent/rent.o ./vehicle/vehicle.o ./graph/graph.o

main.o: main.c
	gcc -g -o main.o main.c -c  -ansi -pedantic -Wno-comment -Wno-declaration-after-statement

user.o:
	gcc -g -o ./user/user.o ./user/user.c -c  -ansi -pedantic -Wno-comment -Wno-declaration-after-statement
	
rent.o:
	gcc -g -o ./rent/rent.o ./rent/rent.c -c  -ansi -pedantic -Wno-comment -Wno-declaration-after-statement

vehicle.o:
	gcc -g -o ./vehicle/vehicle.o ./vehicle/vehicle.c -c  -ansi -pedantic -Wno-comment -Wno-declaration-after-statement

graph.o:
	gcc -g -o ./graph/graph.o ./graph/graph.c -c  -ansi -pedantic -Wno-comment -Wno-declaration-after-statement

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

