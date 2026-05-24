#include "classes.h"

int main()
{
	Function* f;

	cout << "Parabola" << endl;
	f = new Parabola(1, -2, 1);
	f->print(2);
	cout << "Derivative: " << f->derivative(2) << endl;
	cout << "Integral: " << f->integrate(0, 2) << endl;
	cout << "Min: " << f->fMin(-5, 5) << endl;
	cout << "Max: " << f->fMax(-5, 5) << endl;
	delete f;

	cout << endl;
	cout << "Hiperbola" << endl;
	f = new Hiperbola(5);
	f->print(2);
	cout << "Derivative: " << f->derivative(2) << endl;
	delete f;

	cout << endl;
	cout << "Exponenta" << endl;
	f = new Exponenta(2);
	f->print(1);
	cout << "Integral: " << f->integrate(0, 1) << endl;
	delete f;

	cout << endl;
	cout << "Polinom" << endl;
	double arr[] = { 1, 2, 3 };
	f = new Polinom(2, arr);
	f->print(2);
	cout << "Max: " << f->fMax(-2, 2) << endl;
	delete f;

	return 0;
}
