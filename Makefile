#CFLAGS="-mtune=generic"
#CFLAGS=-std=c++11 -O3 -march=native -I/usr/include/eigen3 -Wno-deprecated-declarations
CXX=clang++
QTLIBS=-lQt53DCore -lQt53DExtras -lQt53DInput -lQt53DLogic -lQt53DQuickExtras -lQt53DQuickInput -lQt53DQuickRender -lQt53DQuick -lQt53DRender -lQt5Bluetooth -lQt5Charts -lQt5CLucene -lQt5Concurrent -lQt5Core -lQt5DataVisualization -lQt5DBus -lQt5DesignerComponents -lQt5Designer -lQt5EglFSDeviceIntegration -lQt5EglFsKmsSupport -lQt5Gamepad -lQt5Gui -lQt5Help -lQt5Location -lQt5MultimediaQuick_p -lQt5Multimedia -lQt5MultimediaWidgets -lQt5Network -lQt5Nfc -lQt5OpenGL -lQt5Positioning -lQt5PrintSupport -lQt5Qml -lQt5QuickControls2 -lQt5QuickParticles -lQt5Quick -lQt5QuickTemplates2 -lQt5QuickTest -lQt5QuickWidgets -lQt5Script -lQt5ScriptTools -lQt5Scxml -lQt5Sensors -lQt5SerialBus -lQt5SerialPort -lQt5Sql -lQt5Svg -lQt5Test -lQt5WaylandClient -lQt5WaylandCompositor -lQt5WebChannel -lQt5WebEngineCore -lQt5WebEngine -lQt5WebEngineWidgets -lQt5WebKit -lQt5WebKitWidgets -lQt5WebSockets -lQt5WebView -lQt5Widgets -lQt5X11Extras -lQt5XcbQpa -lQt5XmlPatterns -lQt5Xml
CFLAGS=-std=c++11 -ggdb -march=native -I/usr/include/eigen3 -Wno-deprecated-declarations
CXX_FLAGS = -fPIC -O3 -Wall -w -std=c++11 -I/usr/include/eigen3 -I/usr/include/qt -I.

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

bspline_fit: bspline_fit.cpp
	${CXX} ${CXX_FLAGS} ${QTLIBS} $< -o $@

: gzip.cpp
	g++ gzip.cpp -o gzip -std=c++11 -lz

#libtemplate.so: template_shared_object.cpp
#	g++ $< -shared -o $@ -Wl,-soname,libtemplate.so -fPIC -std=c++11 ${CFLAGS}
#
#template_user: template_user.cpp libtemplate.so
#	g++ -v template_user.cpp -fPIC -o $@ -std=c++11 ${CFLAGS} -L. -ltemplate

constexp: constexp.cpp
	g++ constexp.cpp -o constexp
