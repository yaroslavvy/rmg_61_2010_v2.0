#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "PrintableObject.h"
#include "Element.h"
#include "ElementDataBase.h"
#include "Service.h"
#include "IndividualSubstanceComponent.h"

class MixtureOfComponents :	public PrintableObject
{
public:
	MixtureOfComponents();
	MixtureOfComponents(const MixtureOfComponents&);
	virtual ~MixtureOfComponents();

	std::vector<IndividualSubstanceComponent> &getVector();
	const std::vector<IndividualSubstanceComponent> &getVector() const;

	const double molecularMass() const;
	const double averageAtomicMatrixNumber() const;

	virtual void write(std::ostream*) const;
private:
	std::vector<IndividualSubstanceComponent> vec;

	static const double sumOfIndividualSubstancesMass(const double&, const IndividualSubstanceComponent&);
	static const int sumOfAtomicNumber(const int&, const IndividualSubstanceComponent&);
	static const int amountOfAtoms(const int&, const IndividualSubstanceComponent&);
};

