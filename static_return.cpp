// Tests whether its possible to return the outward type from a function if
// the function is static

class testfoo
{
	int a;
public:
	static testfoo make()
	{
		testfoo out;
		out.a = 1;
		return out;
	}
};

int main()
{
	testfoo a = testfoo::make();
}
