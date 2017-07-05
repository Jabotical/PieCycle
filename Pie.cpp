#include "Pie.h"

#include <algorithm>
#include <iostream>

Pie::Pie(Pie::Type type)
{
	_type = type;
	_temperatureCelcius = _bakedTempCelcius;
}

Pie::~Pie()
{
}

bool Pie::isCoolEnoughToEat()
{
	return _temperatureCelcius <= _edibleTempCelcius;
}

void Pie::cool(double degreesCToCool)
{
	_temperatureCelcius = std::max(_temperatureCelcius - degreesCToCool, _roomTempCelcius);
}

Pie::Type Pie::getType()
{
	return _type;
}
