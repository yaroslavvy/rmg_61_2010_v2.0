#include "pch.h"
#include <iostream>

#include <windows.h>
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cmath>
#include <stdarg.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#include "PrintableObject.h"
#include "Inscription.h"
#include "Service.h"

int main()
{
	std::vector<PrintableObject*> ptr_container;

	Inscription<int> jjool1(4);
	Inscription<double> jjool2(4.34141);
	Inscription<std::string> jjool3("hfoew");

	ptr_container.push_back(&jjool1);
	ptr_container.push_back(&jjool2);
	ptr_container.push_back(&jjool3);

	TwoDimensionalArray a;
	a.readFromFile("1.csv");
	ptr_container.push_back(&a);

	TwoDimensionalArray b;
	b.readFromFile("2.csv");
	ptr_container.push_back(&b);

	TwoDimensionalArray c;
	c.readFromFile("3.csv");
	ptr_container.push_back(&c);

	TwoDimensionalArray d;
	d.readFromFile("4.csv");
	ptr_container.push_back(&d);

	TwoDimensionalArray e;
	e.readFromFile("5.csv");
	ptr_container.push_back(&e);

	TwoDimensionalArray f;
	f.readFromFile("6.csv");
	ptr_container.push_back(&f);

	TwoDimensionalArray g;
	g.readFromFile("7.csv");
	ptr_container.push_back(&g);

	Service::writeInFile("report.csv", ptr_container);
}

