#include "CoolingWindow.h"

CoolingWindow::CoolingWindow(int windowIndex)
	: _index(windowIndex)
{
}

CoolingWindow::~CoolingWindow()
{
}

CoolingWindow::CoolingWindow(CoolingWindow&& source)
{ }

void CoolingWindow::addPie(std::unique_ptr<Pie> pie)
{
	std::lock_guard<std::mutex> guard(_pieLock);

	_pie = std::move(pie);
}

std::unique_ptr<Pie> CoolingWindow::getPie()
{
	std::lock_guard<std::mutex> guard(_pieLock);

	return std::move(_pie);
}

bool CoolingWindow::containsPieCoolEnoughToEat()
{
	std::lock_guard<std::mutex> guard(_pieLock);

	if (_pie == nullptr)
	{
		return false;
	}

	return _pie->isCoolEnoughToEat();
}

bool CoolingWindow::isEmpty()
{
	std::lock_guard<std::mutex> guard(_pieLock);

	return (_pie == nullptr);
}

void CoolingWindow::workerLoop()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(_coolingIntervalMs));

	std::lock_guard<std::mutex> guard(_pieLock);

	if (_pie == nullptr)
	{
		return;
	}

	_pie->cool(_coolingPerSecondDegreesC);
}

int CoolingWindow::getIndex()
{
	return _index;
}
