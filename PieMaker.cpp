#include "PieMaker.h"
#include "CoolingWindow.h"

#include <random>

PieMaker::PieMaker(Pie::Type pieType, std::shared_ptr<IBakeryWindows> bakeryWindows)
	: _pieType(pieType),
	  _bakeryWindows(bakeryWindows)
{
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution(40,100);

	_pieProductionTimeMs = distribution(generator);
	printf("PieMaker of type %d will take %d ms to make pie\n", pieType, _pieProductionTimeMs);
}

PieMaker::~PieMaker()
{ }

PieMaker::PieMaker(PieMaker&& source)
	: _pieType(source._pieType),
	  _bakeryWindows(source._bakeryWindows)
{ }

void PieMaker::workerLoop()
{
	makePieIfOneIsNotMade();
	waitForOpenWindowAndSetPieToCool();
}

void PieMaker::makePieIfOneIsNotMade()
{
	if (_pie == nullptr)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(_pieProductionTimeMs));

		_pie = std::make_unique<Pie>(_pieType);
		printf("Finished Making Pie of type %d.\n", _pieType);
	}
}

void PieMaker::waitForOpenWindowAndSetPieToCool()
{
	_bakeryWindows->waitForEmptyWindowThenAddPie(std::move(_pie));
}

Pie::Type PieMaker::getPieType()
{
	return _pieType;
}




