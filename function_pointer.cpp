
double foo(double a, double b)
{
	return 0;
}

double other(double(*bar)(double, double))
{
	return bar(1,3);
}

int main()
{
	other(foo);
}
