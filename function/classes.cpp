#include "classes.h"

void Function::print(double x)
{
	cout << "f(" << x << ") = " << calc(x) << endl;
}


double Function::derivative(double x)
{
	double h = 0.0001;
	return (calc(x + h) - calc(x)) / h;

}

double Function::integrate(double a, double b)
{
	int n = 1000;
	double h = (b - a) / n;
	double sum = 0;

	for (int i = 0; i < n; i++)
	{
		double x = a + i * h;
		sum += calc(x);
	}

	return sum * h;
}

double Function::fMin(double a, double b)
{
	double m = calc(a);
	for (double x = a; x <= b; x += 0.1)
	{
		if (calc(x) < m)
		{
			m = calc(x);
		}
	}

	return m;
}

double Function::fMax(double a, double b)
{
	double m = calc(a);
	for (double x = a; x <= b; x += 0.1)
	{
		if (calc(x) > m)
		{
			m = calc(x);
		}
	}

	return m;
}

// parabola
Parabola::Parabola(double a, double b, double c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

double Parabola::calc(double x)
{
	return a * x * x + b * x + c;
}

// hiperbola
Hiperbola::Hiperbola(double k)
{
	this->k = k;
}

double Hiperbola::calc(double x)
{
	if (x == 0)
	{
		cout << "Error" << endl;
		return 0;
	}
	return k / x;
}

// exponentta
Exponenta::Exponenta(double a)
{
	this->a = a;
}


double Exponenta::calc(double x)
{
	return exp(a * x);
}

// polinom
Polinom::Polinom(int n, double arr[])
{
	this->n = n;
	p = new double[n + 1];

	for (int i = 0; i <= n; i++)
	{
		p[i] = arr[i];
	}
}

double Polinom::calc(double x)
{
	double sum = 0;
	for (int i = 0; i <= n; i++)
	{
		sum += p[i] * pow(x, i);
	}


	return sum;
}

Polinom::~Polinom()
{
	delete[] p;
}
