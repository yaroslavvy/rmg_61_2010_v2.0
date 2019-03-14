#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "PrintableObject.h"
#include "Element.h"
#include "ElementDataBase.h"
#include "Service.h"

class IndividualSubstanceComponent : public PrintableObject
{
public:
	IndividualSubstanceComponent();
	IndividualSubstanceComponent(const IndividualSubstanceComponent&);
	virtual ~IndividualSubstanceComponent();

	std::vector<Element> &getVector();
	const std::vector<Element> &getVector() const;

	const double molecularMass() const;
	const double averageAtomicMatrixNumber() const;

	virtual void write(std::ofstream*) const;
private:
	std::vector<Element> vec;

	static double sumOfAtomicMass(const double&, const Element&);
	static int sumOfAtomicNumber(const int&, const Element&);
};

