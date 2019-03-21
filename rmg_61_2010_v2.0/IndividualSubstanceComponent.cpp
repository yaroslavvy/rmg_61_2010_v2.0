#include "pch.h"
#include "IndividualSubstanceComponent.h"

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
#include <sstream>
#include <numeric>
#include <iterator>
#include <set>

IndividualSubstanceComponent::IndividualSubstanceComponent() {}

IndividualSubstanceComponent::IndividualSubstanceComponent(const IndividualSubstanceComponent& a) 
	: vec(a.getVector()) {}

IndividualSubstanceComponent::~IndividualSubstanceComponent() {}

std::vector<Element> &IndividualSubstanceComponent::getVector() {
	return vec;
}

const std::vector<Element> &IndividualSubstanceComponent::getVector() const {
	return vec;
}

const double IndividualSubstanceComponent::molecularMass() const {
	return std::accumulate(vec.begin(), vec.end(), 0.0, IndividualSubstanceComponent::sumOfAtomicMass);
}

const int IndividualSubstanceComponent::sumAtomicNumber() const {
	return std::accumulate(vec.begin(), vec.end(), 0, IndividualSubstanceComponent::sumOfAtomicNumber);
}

const int IndividualSubstanceComponent::amountOfAtoms() const {
	return vec.size();
}

const int IndividualSubstanceComponent::amountAtomsOfElementInSubstance(const Element& element) const {
	return std::count(vec.begin(), vec.end(), element);
}

const IndividualSubstanceComponent &IndividualSubstanceComponent::operator+=(const IndividualSubstanceComponent &right) {
	std::copy(right.getVector().begin(), right.getVector().end(), std::back_inserter(this->getVector()));
	return *this;
}

void IndividualSubstanceComponent::write(std::ostream* fout) const {
	std::set<Element> setCopyVec;
	std::copy(vec.begin(), vec.end(), std::inserter(setCopyVec, setCopyVec.begin()));
	int amount = 0;
	for (std::set<Element>::const_iterator a = setCopyVec.begin(); a != setCopyVec.end(); a++) {
		(*fout) << a->getSymbol();
		amount = std::count(vec.begin(), vec.end(), (*a));
		if (amount > 1) {
			(*fout) << amount;
		}
	}
}

const double IndividualSubstanceComponent::sumOfAtomicMass(const double &accumulator, const Element &next) {
	return (accumulator + (next.getAtomicMass()));
}

const int IndividualSubstanceComponent::sumOfAtomicNumber(const int &accumulator, const Element &next) {
	return (accumulator + (next.getNumberZ()));
}