all: array zero bspline graph sinc
clean: 
	rm -f array zero bspline graph sinc

%: %.cpp
	g++ $< -o $@.o -std=c++11 -mtune=generic

%: %.cxx
	g++ $< -o $@.o -std=c++11 -mtune=generic

lanczos: lanczos.cpp
	g++ lanczos.cpp -o lanczos -std=c++11 -g

hash: hash.cpp
	g++ hash.cpp -o hash -std=c++11 -g

generic_functor: generic_functor.cpp
	g++ generic_functor.cpp -o generic_functor -std=c++11 -g

sort: sort.cpp
	g++ sort.cpp -o sort -std=c++11 -g

extern: extern_1.cpp extern_1.h extern_2.cpp
	g++ extern_1.cpp extern_2.cpp -o extern

