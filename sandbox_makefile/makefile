all:	test

main.o:	main.cpp main.h

%.o:	%.cpp
	$(CC) -c $< -o $@


test:	main.o life.o	
	$(CC) main.o life.o -o test


clean:
	rm -rf *.o test	

