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
#include <clocale>
#include <cctype>

#include "PrintableObject.h"
#include "Inscription.h"
#include "Service.h"
#include "ElementDataBase.h"
#include "Element.h"
#include "IndividualSubstanceComponent.h"
#include "MixtureOfComponents.h"
#include "SubstanceSyntaxAnalyser.h"
#include "ParserException.h"

int main()
{
	std::setlocale(LC_ALL, "");
	try {
		/*std::vector<PrintableObject*> ptrContainer;
		ElementDataBase elementDB(TwoDimensionalArray("elementDataBase.csv"));
		
		IndividualSubstanceComponent CuSO4;
		(CuSO4.getVector()).push_back(elementDB.getElement("Cu"));
		(CuSO4.getVector()).push_back(elementDB.getElement("S"));
		(CuSO4.getVector()).push_back(elementDB.getElement("O"));
		(CuSO4.getVector()).push_back(elementDB.getElement("O"));
		(CuSO4.getVector()).push_back(elementDB.getElement("O"));
		(CuSO4.getVector()).push_back(elementDB.getElement("O"));

		IndividualSubstanceComponent c5H2O;
		for (int i = 0; i < 5; i++) {
			(c5H2O.getVector()).push_back(elementDB.getElement("H"));
			(c5H2O.getVector()).push_back(elementDB.getElement("H"));
			(c5H2O.getVector()).push_back(elementDB.getElement("O"));
		}
		
		MixtureOfComponents CuSO4c5H2O;
		(CuSO4c5H2O.getVector()).push_back(CuSO4);
		(CuSO4c5H2O.getVector()).push_back(c5H2O);
			   
		ptrContainer.push_back(&CuSO4c5H2O);

		std::string a("molecular mass = " + std::to_string(CuSO4c5H2O.molecularMass()));
		Inscription<std::string> ins1(a);
		ptrContainer.push_back(&ins1);

		a = ("average atomic number = " + std::to_string(CuSO4c5H2O.averageAtomicMatrixNumber()));
		Inscription<std::string> ins2(a);
		ptrContainer.push_back(&ins2);
		
		Service::writeInFile("report.csv", ptrContainer);*/

		ElementDataBase elementDB(TwoDimensionalArray("elementDataBase.csv"));
		std::vector<PrintableObject*> ptrContainer;
		MixtureOfComponents mixComp;
		std::string a;
		while (1) {
			std::getline(std::cin, a);
			if (a == "0" || a == "") {
				break;
			}
			mixComp = SubstanceSyntaxAnalyser::analyseMixtureOfComponents(a, elementDB);
			std::cout << std::endl << "Mr = " << mixComp.molecularMass() << " g/mol" << std::endl;
		}
		
	}
	catch (const std::out_of_range) {
		std::cerr << "Check the first line with headers of the table at the element data base" << std::endl;
		std::getchar();
	}
	catch (const ParserException a) {
		std::cerr << a.whatWrongString() << a.whatError() << std::endl;
		std::getchar();
	}
}

