CC := g++

all: test.out

test.out: main.o user.o publisher.o customer.o commandprocessor.o exceptions.o film.o manager.o  
	$(CC) main.o user.o publisher.o customer.o commandprocessor.o exceptions.o film.o manager.o -o test.out
main.o: main.cpp info.h publisher.h user.h customer.h commandprocessor.h manager.h exceptions.h
	$(CC) -c main.cpp
user.o: user.h user.cpp info.h film.h exceptions.h
	$(CC) -c user.cpp
publisher.o: publisher.cpp publisher.h info.h film.h user.h exceptions.h
	$(CC) -c publisher.cpp
customer.o: customer.cpp customer.h info.h film.h user.h
	$(CC) -c customer.cpp
commandprocessor.o: commandprocessor.cpp commandprocessor.h info.h manager.h exceptions.h
	$(CC) -c commandprocessor.cpp
exceptions.o: exceptions.cpp exceptions.h info.h
	$(CC) -c exceptions.cpp
film.o: film.cpp film.h info.h user.h exceptions.h
	$(CC) -c film.cpp
manager.o: manager.cpp manager.h info.h user.h film.h publisher.h customer.h 
	$(CC) -c manager.cpp




.PHONY:clean
clean:
	rm -r *.o
