#pragma once

#include <fstream>

class PrintableObject {

public:

	virtual ~PrintableObject();

	virtual void write(std::ostream*) const = 0;
};

