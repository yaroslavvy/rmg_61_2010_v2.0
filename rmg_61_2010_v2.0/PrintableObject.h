#pragma once

#include <fstream>

class PrintableObject {

public:

	virtual ~PrintableObject();

	virtual void write(std::ofstream*) const = 0;
};

