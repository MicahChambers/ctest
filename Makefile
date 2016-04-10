#CFLAGS="-mtune=generic"
#CFLAGS=-std=c++11 -O3 -march=native -I/usr/include/eigen3 -Wno-deprecated-declarations
CXX=clang++
CFLAGS=-std=c++11 -ggdb -march=native -I/usr/include/eigen3 -Wno-deprecated-declarations

all: math array copy zero bspline graph sinc gradtest linesearch plottest \
	bspline_regularize goldensearch struct_construct
clean:
	rm -f array zero bspline graph sinc gradtest
%: %.cpp
	g++ $< -o $@ -std=c++11 ${CFLAGS}

%: %.cxx
	g++ $< -o $@ -std=c++11 ${CFLAGS}

point_match: point_match.cpp
	$(CXX) point_match.cpp -o point_match $(CFLAGS)

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

gzip: gzip.cpp
	g++ gzip.cpp -o gzip -std=c++11 -lz

#libtemplate.so: template_shared_object.cpp
#	g++ $< -shared -o $@ -Wl,-soname,libtemplate.so -fPIC -std=c++11 ${CFLAGS}
#
#template_user: template_user.cpp libtemplate.so
#	g++ -v template_user.cpp -fPIC -o $@ -std=c++11 ${CFLAGS} -L. -ltemplate

constexp: constexp.cpp
	g++ constexp.cpp -o constexp
