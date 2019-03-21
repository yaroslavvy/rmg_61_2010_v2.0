#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "PrintableObject.h"

class TwoDimensionalArray :	public PrintableObject {

public:

	TwoDimensionalArray(const std::string&);
	TwoDimensionalArray(const TwoDimensionalArray&);
	virtual ~TwoDimensionalArray();

	const std::vector<std::vector<std::string>>& getVector() const;

	virtual void write(std::ostream*) const;

	bool readFromFile(const std::string&);

private:

	std::vector<std::vector<std::string>> vec;
};

