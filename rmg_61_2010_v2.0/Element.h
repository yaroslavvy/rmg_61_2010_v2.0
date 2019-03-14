#pragma once
#include <vector>
#include <fstream>
#include <string>

#include "PrintableObject.h"
class Element :	public PrintableObject
{

public:

	Element(int, std::string, double, std::string);
	Element(const Element&);
	virtual ~Element();

	const std::string &getSymbol() const;
	const std::string &getNameEN() const;
	const int getNumberZ() const;
	const double getAtomicMass() const;

	bool operator== (const Element&) const;
	bool operator< (const Element&) const;

	virtual void write(std::ofstream*) const;

private:

	int numberZ;
	std::string symbol;
	double atomicMass;
	std::string nameEN;
	
};

