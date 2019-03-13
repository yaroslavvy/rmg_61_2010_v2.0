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

int main()
{
	std::vector<PrintableObject*> ptrContainer;

	try {
		ElementDataBase DB(TwoDimensionalArray("elementDataBase.csv"));
		ptrContainer.push_back(&DB);
		Service::writeInFile("report.csv", ptrContainer);
	}
	catch (const std::out_of_range) {
		std::cerr << "Check the first line with headers of the table at the element data base" << std::endl;
		std::getchar();
		std::abort(); // What function should it call in this case?
	}
}

