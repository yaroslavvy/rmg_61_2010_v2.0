#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "PrintableObject.h"
#include "Element.h"
#include "ElementDataBase.h"
#include "Service.h"
#include "IndividualSubstanceComponent.h"

class MixtureOfComponents :
	public PrintableObject
{
public:
	MixtureOfComponents();
	virtual ~MixtureOfComponents();
};

