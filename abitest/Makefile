
bar/bar: bar/bar.o
	$(CXX) bar.o -Wl,-rpath,foov1 -Wl,-rpath,foov2 -Wl,-rpath,foo_user1 -Wl,-rpath,foo_user2 -Lfoov1 -Lfoov2 -Lfoo_user1 -Lfoo_user2 -lfoo_user2 -lfoo_user1 -lfoo -o $@

bar/bar.o: bar/bar.cc foo_user1/libfoo_user1.so foo_user2/libfoo_user2.so
	$(CXX) -c bar/bar.cc -o $@ -Ifoo_user1/ -Ifoo_user2/

foo_user1/libfoo_user1.so: foo_user1/foo_user1.cc foov1/libfoo.so
	$(CXX) $< -o $@ -shared -I foov1/ -Lfoov2 -lfoo

foo_user2/libfoo_user2.so: foo_user2/foo_user2.cc foov2/libfoo.so
	$(CXX) $< -o $@ -shared -I foov2/ -Lfoov1 -lfoo

foov1/libfoo.so: foov1/foov1.cc
	$(CXX) $< -o $@ -shared

foov2/libfoo.so: foov2/foov2.cc
	$(CXX) $< -o $@ -shared

clean:
	rm -f */*.so bar/bar
