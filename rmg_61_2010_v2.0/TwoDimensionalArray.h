#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "PrintableObject.h"

class TwoDimensionalArray :	public PrintableObject {

public:

	TwoDimensionalArray();
	TwoDimensionalArray(const TwoDimensionalArray&);
	virtual ~TwoDimensionalArray();

	virtual void write(std::ofstream*) const;

	bool readFromFile(const std::string&);

private:

	std::vector<std::vector<std::string>> vec;
};

