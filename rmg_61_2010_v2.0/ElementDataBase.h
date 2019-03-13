#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "PrintableObject.h"
#include "TwoDimensionalArray.h"
#include "Element.h"

class ElementDataBase :	public PrintableObject
{
public:
	ElementDataBase(const TwoDimensionalArray&);
	virtual ~ElementDataBase();

	const Element &getElement(int);
	const Element &getElement(std::string);

	virtual void write(std::ofstream*) const;

private:
	std::map<int, Element> indexNumberZBase;
	std::map<std::string, Element> indexSymbolBase;
	
};

