#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <cmath>
using namespace std;

class Function
{

public:
	virtual double calc(double x) = 0;

	virtual void print(double x);

	virtual double derivative(double x);

	virtual double integrate(double a, double b);

	virtual double fMin(double a, double b);

	virtual double fMax(double a, double b);

	virtual ~Function() {}
};


class Parabola : public Function
{
private:
	double a, b, c;

public:
	Parabola(double a, double b, double c);

	double calc(double x) override;
};


class Hiperbola : public Function
{
private:
	double k;

public:
	Hiperbola(double k);

	double calc(double x) override;
};

class Exponenta : public Function
{
private:
	double a;

public:
	Exponenta(double a);

	double calc(double x) override;
};

class Polinom : public Function
{
private:
	int n;
	double* p;

public:
	Polinom(int n, double arr[]);

	double calc(double x) override;

	~Polinom();
};


#endif