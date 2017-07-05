#include "PieEater.h"

PieEater::PieEater(std::shared_ptr<IBakeryWindows> bakeryWindows)
	: _bakeryWindows(bakeryWindows)
{
}

PieEater::~PieEater()
{
}

void PieEater::workerLoop()
{
	const int eatingIntervalMs = 15;
	std::this_thread::sleep_for(std::chrono::milliseconds(eatingIntervalMs));

	auto pie = _bakeryWindows->getEdiblePieIfAvailableNullOtherwise();
	if (pie == nullptr)
	{
		return;
	}

	printf("~ Eating pie of type %d\n", pie->getType());
	pie.release();
}
