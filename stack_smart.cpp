	#include <iostream>
	#include <memory>
	
	using namespace std;
	
	class foo
	{
		public:
		foo(shared_ptr<int> in) {
			cerr << in.get() << endl;
			cerr << var.use_count() << endl;
			var = in;
			cerr << var.use_count() << endl;
		};
	
		shared_ptr<int> var;
	};
	
	struct NoDelete {
		void operator()(int* p) {
			std::cout << "Not Deleting\n";
		};
	};
	
	int main()
	{
		int myval = 5;
	
		shared_ptr<int> valptr(&myval, NoDelete());
		foo staticinst(valptr);
	
		shared_ptr<int> dynptr(new int);
		*dynptr = 5;
		foo dynamicinst(dynptr);
	}
