app: main.o libcopying.a
	gcc -Wall -o app main.o -L. -lcopying -lstdc++
main.o: main.cpp copying.hpp
	gcc -c main.cpp
copying.o: copying.cpp copying.hpp
	gcc -c copying.cpp
libcopying.a: copying.o
	ar cr libcopying.a copying.o
clean:
	rm *.o *.a app
