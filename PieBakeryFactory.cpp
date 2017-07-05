#include "PieBakeryFactory.h"

#include "PieBakery.h"
#include "PieMaker.h"
#include "PieEater.h"
#include "BakeryWindows.h"

#include <vector>
#include <boost/range/irange.hpp>

PieBakeryFactory::PieBakeryFactory()
{ }

PieBakeryFactory::~PieBakeryFactory()
{ }

std::unique_ptr<IPieBakery> PieBakeryFactory::create()
{
	const int numCoolingWindows = 8;
	const int numPieEaters = 2;

	auto bakeryWindows = openBakeryWindows(numCoolingWindows);
	auto pieMakers = hirePieMakers(bakeryWindows);
	auto pieEaters = attractPieEaters(numPieEaters, bakeryWindows);

	return std::make_unique<PieBakery>(bakeryWindows, std::move(pieMakers), std::move(pieEaters));
}

std::shared_ptr<IBakeryWindows> PieBakeryFactory::openBakeryWindows(int numWindows)
{
	return std::make_shared<BakeryWindows>(createCoolingWindows(numWindows));
}

std::vector<std::unique_ptr<ICoolingWindow>> PieBakeryFactory::createCoolingWindows(int numWindows)
{
	std::vector<std::unique_ptr<ICoolingWindow>> windows;

	for (auto i : boost::irange(0, numWindows)) //<-- disabled due to lots of annoying warnings from external Boost code
	{
		windows.push_back(std::make_unique<CoolingWindow>(i));
	}

	return windows;
}

std::vector<std::unique_ptr<IPieMaker>> PieBakeryFactory::hirePieMakers(std::shared_ptr<IBakeryWindows> bakeryWindows)
{
	std::vector<std::unique_ptr<IPieMaker>> pieMakers;

	for (auto pieType : {Pie::Apple, Pie::PBChocolate, Pie::Pecan, Pie::Rhubarb})
	{
		pieMakers.push_back(std::make_unique<PieMaker>(pieType, bakeryWindows));
	}

	return pieMakers;
}

std::vector<std::unique_ptr<IPieEater>> PieBakeryFactory::attractPieEaters(int numPieEaters, std::shared_ptr<IBakeryWindows> bakeryWindows)
{
	std::vector<std::unique_ptr<IPieEater>> pieEaters;

	for (auto i : boost::irange(0, numPieEaters)) //<-- disabled due to lots of annoying warnings from external Boost code
	{
		pieEaters.push_back(std::make_unique<PieEater>(bakeryWindows));
	}

	return pieEaters;
}

