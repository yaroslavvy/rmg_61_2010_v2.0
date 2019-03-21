#include "pch.h"
#include "MixtureOfComponents.h"

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

MixtureOfComponents::MixtureOfComponents() {}

MixtureOfComponents::MixtureOfComponents(const MixtureOfComponents& a)
	:vec(a.getVector()){}

MixtureOfComponents::~MixtureOfComponents() {}

std::vector<IndividualSubstanceComponent> &MixtureOfComponents::getVector() {
	return vec;
}
const std::vector<IndividualSubstanceComponent> &MixtureOfComponents::getVector() const {
	return vec;
}

const double MixtureOfComponents::molecularMass() const {
	return std::accumulate(vec.begin(), vec.end(), 0.0, MixtureOfComponents::sumOfIndividualSubstancesMass);
}

const double MixtureOfComponents::averageAtomicMatrixNumber() const {
	return (static_cast<double>(std::accumulate(vec.begin(), vec.end(), 0.0, MixtureOfComponents::sumOfAtomicNumber))) / (static_cast<double>(std::accumulate(vec.begin(), vec.end(), 0.0, MixtureOfComponents::amountOfAtoms)));
}

void MixtureOfComponents::write(std::ostream* fout) const {
	for (std::vector<IndividualSubstanceComponent>::const_iterator i = vec.begin(); i < vec.end(); i++) {
		i->write(fout);
		if (i < (vec.end() - 1)) {
			(*fout) << "*";
		}
	}
	(*fout) << "\n";
}

const double MixtureOfComponents::sumOfIndividualSubstancesMass(const double& accumulator, const IndividualSubstanceComponent &next) {
	return (accumulator + (next.molecularMass()));
}

const int MixtureOfComponents::sumOfAtomicNumber(const int &accumulator, const IndividualSubstanceComponent &next) {
	return (accumulator + (next.sumAtomicNumber()));
}

const int MixtureOfComponents::amountOfAtoms(const int &accumulator, const IndividualSubstanceComponent &next) {
	return (accumulator + (next.amountOfAtoms()));
}