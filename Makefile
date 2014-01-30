all: math array zero bspline graph sinc gradtest linesearch plottest bspline_regularize goldensearch
clean: 
	rm -f array zero bspline graph sinc gradtest
%: %.cpp
	g++ $< -o $@ -std=c++11 -mtune=generic

%: %.cxx
	g++ $< -o $@ -std=c++11 -mtune=generic

bspline_regularize: bspline_regularize.cpp plot.cpp tga.cpp plot.h
	g++ tga.cpp plot.cpp bspline_regularize.cpp -o bspline_regularize -std=c++11 -O3 -march=native

plottest: plottest.cpp plot.cpp tga.cpp
	g++ tga.cpp plot.cpp plottest.cpp -o plottest -g -std=c++11 -mtune=generic

gradtest: gradtest.cpp
	g++ tga.cpp gradtest.cpp -o gradtest -g -std=c++11 -mtune=generic

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

