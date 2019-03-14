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
#include "ElementDataBase.h"
#include "Element.h"
#include "IndividualSubstanceComponent.h"

int main()
{
	try {
		std::vector<PrintableObject*> ptrContainer;
		ElementDataBase elementDB(TwoDimensionalArray("elementDataBase.csv"));
		
		IndividualSubstanceComponent H2SO4;
		(H2SO4.getVector()).push_back(elementDB.getElement("H"));
		(H2SO4.getVector()).push_back(elementDB.getElement("H"));
		(H2SO4.getVector()).push_back(elementDB.getElement("S"));
		(H2SO4.getVector()).push_back(elementDB.getElement("O"));
		(H2SO4.getVector()).push_back(elementDB.getElement("O"));
		(H2SO4.getVector()).push_back(elementDB.getElement("O"));
		(H2SO4.getVector()).push_back(elementDB.getElement("O"));
		ptrContainer.push_back(&H2SO4);
		std::string a("molecular mass = " + std::to_string(H2SO4.molecularMass()));
		Inscription<std::string> ins1(a);
		ptrContainer.push_back(&ins1);
		a = ("average atomic number = " + std::to_string(H2SO4.averageAtomicMatrixNumber()));
		Inscription<std::string> ins2(a);
		ptrContainer.push_back(&ins2);
		Service::writeInFile("report.csv", ptrContainer);

	}
	catch (const std::out_of_range) {
		std::cerr << "Check the first line with headers of the table at the element data base" << std::endl;
		std::getchar();
		std::abort(); // What function should it call in this case?
	}
}

