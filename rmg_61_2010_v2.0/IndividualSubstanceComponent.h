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
	const int sumAtomicNumber() const;
	const int amountOfAtoms() const;
	const int amountAtomsOfElementInSubstance(const Element&) const;

	const IndividualSubstanceComponent &operator+=(const IndividualSubstanceComponent &);

	virtual void write(std::ostream*) const;
private:
	std::vector<Element> vec;

	static const double sumOfAtomicMass(const double&, const Element&);
	static const int sumOfAtomicNumber(const int&, const Element&);
};

