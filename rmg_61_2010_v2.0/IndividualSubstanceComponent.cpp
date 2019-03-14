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

const double IndividualSubstanceComponent::averageAtomicMatrixNumber() const {
	return (static_cast<double>(std::accumulate(vec.begin(), vec.end(), 0, IndividualSubstanceComponent::sumOfAtomicNumber)))/(static_cast<double>(vec.size()));
}

void IndividualSubstanceComponent::write(std::ofstream* fout) const {
	std::set<Element> setCopyVec;
	std::copy(vec.begin(), vec.end(), std::inserter(setCopyVec, setCopyVec.begin()));
	for (std::set<Element>::const_iterator a = setCopyVec.begin(); a != setCopyVec.end(); a++) {
		(*fout) << a->getSymbol() << std::count(vec.begin(), vec.end(), (*a));
	}
	(*fout) << "\n";
}

double IndividualSubstanceComponent::sumOfAtomicMass(const double &accumulator, const Element &next) {
	return (accumulator + (next.getAtomicMass()));
}

int IndividualSubstanceComponent::sumOfAtomicNumber(const int &accumulator, const Element &next) {
	return (accumulator + (next.getNumberZ()));
}