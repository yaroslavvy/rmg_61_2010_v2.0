#pragma once

#include <string>
#include <vector>

#include "PrintableObject.h"
#include "TwoDimensionalArray.h"

class Service {

public:

	Service();
	virtual ~Service();

	static void writeInFile(const std::string&, const std::vector<PrintableObject*>&);
};