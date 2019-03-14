#include "pch.h"
#include "ElementDataBase.h"
#include "Service.h"

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
#include <iterator>

ElementDataBase::ElementDataBase(const TwoDimensionalArray& a) {
	std::vector <std::vector<std::string>>::const_iterator row;
	std::vector<std::string>::const_iterator column;
	std::vector<std::vector<std::string>::const_iterator>::const_iterator iterSequenceIter;
	std::map <std::string, int> sequence;
	std::vector <std::vector<std::string>> vec(a.getVector());
	try {
		int i = 0;
		for (column = (vec.at(0)).begin(); column < (vec.at(0)).end(); column++, i++){
			if (*column == "Atomic number") {
				sequence.insert(std::map<std::string, int>::value_type("Atomic number", i));
			}
			if (*column == "Element Symbol") {
				sequence.insert(std::map<std::string, int>::value_type("Element Symbol", i));
			}
			if (*column == "Atomic mass") {
				sequence.insert(std::map<std::string, int>::value_type("Atomic mass", i));
			}
			if (*column == "Element name") {
				sequence.insert(std::map<std::string, int>::value_type("Element name", i));
			}
		}
	}
	catch (const std::out_of_range) {
		throw;
	}
	int atomNumber;
	std::string elemSymb;
	double atomMass;
	std::string elemName;
	indexNumberZBase.insert(std::map<int, Element>::value_type(0, Element(0, "Undefined element", 0.000, "Undefined element")));
	indexSymbolBase.insert(std::map<std::string, Element>::value_type("Undefined element", Element(0, "Undefined element", 0.000, "Undefined element")));
	//this element should be got if required element is not found in elementDataBase 
	//this Element automatically is added in the elementDataBase and can't be shown by ElementDataBase::write(std::ofstream*)
	for (row = ((vec.begin()) + 1); row < ((vec.end()) - 1); row++) {
		if ((sequence.find("Atomic number") != sequence.end()) &&
			(sequence.find("Element Symbol") != sequence.end()) &&
			(sequence.find("Atomic mass") != sequence.end()) &&
			(sequence.find("Element name") != sequence.end())) {

			try {
				elemSymb = row->at(sequence.find("Element Symbol")->second);
				elemName = row->at(sequence.find("Element name")->second);
				
				if (Service::isIntegerFromString(row->at(sequence.find("Atomic number")->second)) &&
					Service::isDoubleFromString(row->at(sequence.find("Atomic mass")->second))) {
					atomNumber = std::stoi(row->at(sequence.find("Atomic number")->second));
					atomMass = std::stod(row->at(sequence.find("Atomic mass")->second));
				}
				else {
					std::cerr << "Not valid value of Atomic number or mass (integer or double)" << std::endl;
					std::getchar();
					return;
				}
				if ((atomNumber < 1) || (atomMass <= 0) || (elemSymb == "Undefined element") || (elemName == "Undefined element")) {
					std::cerr << "Not valid value of element property (atomNumber < 1) || (atomMass <= 0) || (elemSymb == Undefined element) || (elemName == Undefined element)" << std::endl;
					std::getchar();
					return;
				}
			}
			catch (const std::out_of_range) {
				throw;
			}
			indexNumberZBase.insert(std::map<int, Element>::value_type(atomNumber, Element (atomNumber, elemSymb, atomMass, elemName)));
			indexSymbolBase.insert(std::map<std::string, Element>::value_type(elemSymb, Element(atomNumber, elemSymb, atomMass, elemName)));
		}
		else {
			std::cerr << "Check the first line with headers of the table at the element data base" << std::endl;
		}
	}
}

ElementDataBase::~ElementDataBase() {}

const Element &ElementDataBase::getElement(int numberZ) {
	if (indexNumberZBase.find(numberZ) != indexNumberZBase.end()) {
		return indexNumberZBase.find(numberZ)->second;
	}
	return indexNumberZBase.find(0)->second;
}

const Element &ElementDataBase::getElement(std::string symbol) {
	if (indexSymbolBase.find(symbol) != indexSymbolBase.end()) {
		return indexSymbolBase.find(symbol)->second;
	}
	return indexSymbolBase.find("Undefined element")->second;
}

void ElementDataBase::write(std::ofstream* fout) const {
	std::map<int, Element>::const_iterator i;
	(*fout) << "Atomic number" << ";" << "Element Symbol" << ";" << "Atomic mass" << ";" << "Element name" << "\n";
	for (i = indexNumberZBase.begin(); i != indexNumberZBase.end(); i++) {
		if ((i->second).getNumberZ() != 0) {
			(*fout) << (i->second).getNumberZ() << ";" << (i->second).getSymbol() << ";" << (i->second).getAtomicMass() << ";" << (i->second).getNameEN() << "\n";
		}
	}
}