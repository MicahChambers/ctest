all: array zero bspline

%: %.cpp
	g++ $< -o $@ -std=c++11 -mtune=generic

lanczos: lanczos.cpp
	g++ lanczos.cpp -o lanczos -std=c++11 -g

hash: hash.cpp
	g++ hash.cpp -o hash -std=c++11 -g

generic_functor: generic_functor.cpp
	g++ generic_functor.cpp -o generic_functor -std=c++11 -g

sort: sort.cpp
	g++ sort.cpp -o sort -std=c++11 -g

