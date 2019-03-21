#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "ParserException.h"
#include "PrintableObject.h"
#include "TwoDimensionalArray.h"
#include "ElementDataBase.h"
#include "Element.h"
#include "IndividualSubstanceComponent.h"
#include "MixtureOfComponents.h"

class SubstanceLexAnalyser
{
public:
	SubstanceLexAnalyser();
	virtual ~SubstanceLexAnalyser();

	static const Element& analyseElement(const std::string&, const ElementDataBase&);//should be inline without open implementation
};

