#include "PieBakery.h"
#include "PieMaker.h"
#include "PieEater.h"

PieBakery::PieBakery(std::shared_ptr<IBakeryWindows> bakeryWindows, std::vector<std::unique_ptr<IPieMaker>> pieMakers, std::vector<std::unique_ptr<IPieEater>> pieEaters)
	: _pieMakers(std::move(pieMakers)),
	  _bakeryWindows(bakeryWindows),
	  _pieEaters(std::move(pieEaters))
{
}

PieBakery::~PieBakery()
{ }

void PieBakery::start()
{
	_bakeryWindows->start();

	for (auto& pieMaker : _pieMakers)
	{
		dynamic_cast<PieMaker&>(*pieMaker.get()).start();
	}

	for (auto& pieEater : _pieEaters)
	{
		dynamic_cast<PieEater&>(*pieEater.get()).start();
	}
}

void PieBakery::stop()
{
	for (auto& pieMaker : _pieMakers)
	{
		printf(" > Stopping PieMaker type %d...\n", pieMaker->getPieType());
		dynamic_cast<PieMaker&>(*pieMaker.get()).requestStop();
	}

	_bakeryWindows->stop();

	for (auto& pieMaker : _pieMakers)
	{
		printf(" > Waiting for PieMaker type %d to terminate...\n", pieMaker->getPieType());
		dynamic_cast<PieMaker&>(*pieMaker.get()).requestStopAndWaitForTermination();
	}

	for (auto& pieEater : _pieEaters)
	{
		printf(" > Waiting for PieEater to terminate...\n");
		dynamic_cast<PieEater&>(*pieEater.get()).requestStopAndWaitForTermination();
	}
}
