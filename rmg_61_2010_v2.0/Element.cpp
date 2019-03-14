#include "pch.h"
#include "Element.h"

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


Element::Element(int Z, std::string symb, double atMass, std::string elName) 
	: numberZ(Z),
	symbol(symb),
	atomicMass(atMass),
	nameEN(elName) {}

Element::Element(const Element &right)
	: numberZ(right.getNumberZ()),
	symbol(right.getSymbol()),
	atomicMass(right.getAtomicMass()),
	nameEN(right.getNameEN()) {}

Element::~Element() {}

const std::string &Element::getSymbol() const {
	return symbol;
}

const std::string &Element::getNameEN() const {
	return nameEN;
}

const int Element::getNumberZ() const {
	return numberZ;
}

const double Element::getAtomicMass() const {
	return atomicMass;
}

bool Element::operator== (const Element& right) const{
	if ((numberZ == right.getNumberZ()) && (symbol == right.getSymbol()) && (atomicMass == right.getAtomicMass()) && (nameEN == right.getNameEN())) {
		return true;
	}
	else {
		return false;
	}
}

bool Element::operator< (const Element& right) const{
	if (numberZ < right.getNumberZ()) {
		return true;
	}
	else {
		return false;
	}
}

void Element::write(std::ofstream* fout) const {
	(*fout) << symbol << "\n";
}