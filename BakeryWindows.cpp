#include "BakeryWindows.h"
#include "CoolingWindow.h"

#include <iostream>
#include <boost/range/algorithm.hpp>

BakeryWindows::BakeryWindows(std::vector<std::unique_ptr<ICoolingWindow>> coolingWindows)
	: _coolingWindows(std::move(coolingWindows))
{
}

BakeryWindows::~BakeryWindows()
{
}

void BakeryWindows::start()
{
	_stopRequested = false;

	for (auto& window : _coolingWindows)
	{
		dynamic_cast<CoolingWindow&>(*window.get()).start();
	}
}

void BakeryWindows::stop()
{
	_stopRequested = true;

	for (auto& window : _coolingWindows)
	{
		dynamic_cast<CoolingWindow&>(*window.get()).requestStopAndWaitForTermination();
	}

	releaseAllMakerLocks();
}


void BakeryWindows::waitForEmptyWindowThenAddPie(std::unique_ptr<Pie> pie)
{
	auto pieType = pie->getType();
	auto emptyWindow = getEmptyWindow();

	if (!emptyWindow)
	{
		std::unique_lock<std::mutex> lock(_makerLock);
		_pieAvailabilityCondition.wait(lock);

		if (_stopRequested)
		{
			return;
		}

		emptyWindow = getEmptyWindow();
	}

	emptyWindow->addPie(std::move(pie));
	printf("Added pie type %d to window %d.\n", pieType, emptyWindow->getIndex());
}

boost::optional<ICoolingWindow&> BakeryWindows::getEmptyWindow()
{
	auto it = boost::range::find_if(_coolingWindows, [&](std::unique_ptr<ICoolingWindow>& window) { return window->isEmpty(); });

	if (it == _coolingWindows.end())
	{
		return boost::none;
	}

	return boost::optional<ICoolingWindow&>(*it->get());
}

std::unique_ptr<Pie> BakeryWindows::getEdiblePieIfAvailableNullOtherwise()
{
	std::lock_guard<std::mutex> guard(_eaterLock);

	auto it = boost::range::find_if(_coolingWindows, [&](std::unique_ptr<ICoolingWindow>& window) { return window->containsPieCoolEnoughToEat(); });

	if (it == _coolingWindows.end())
	{
		return nullptr;
	}

	auto pie = it->get()->getPie();
	printf(" -retrieved pie type %d from window %d...\n", pie->getType(), it->get()->getIndex());

	signalEmptyWindowAvailable();

	return std::move(pie);
}

void BakeryWindows::signalEmptyWindowAvailable()
{
	std::unique_lock<std::mutex> lock(_makerLock);
	lock.unlock();
	_pieAvailabilityCondition.notify_one();
}

void BakeryWindows::releaseAllMakerLocks()
{
	std::unique_lock<std::mutex> lock(_makerLock);
	lock.unlock();
	_pieAvailabilityCondition.notify_all();
}
