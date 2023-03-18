all: exec

exec: main.o user.o vehicle.o rent.o
	gcc -g -o vehicle-rental-system.exe main.o ./user/user.o ./rent/rent.o ./vehicle/vehicle.o

main.o: main.c
	gcc -g -o main.o main.c -c  -ansi -pedantic -Wno-comment

user.o:
	gcc -g -o ./user/user.o ./user/user.c -c  -ansi -pedantic -Wno-comment
	
rent.o:
	gcc -g -o ./rent/rent.o ./rent/rent.c -c  -ansi -pedantic -Wno-comment

vehicle.o:
	gcc -g -o ./vehicle/vehicle.o ./vehicle/vehicle.c -c  -ansi -pedantic -Wno-comment


clean:
	rm -rf *.o

run:
	make clean
	make all

