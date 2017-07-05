#ifndef COOLINGWINDOW_H_
#define COOLINGWINDOW_H_

#include "ICoolingWindow.h"
#include "WorkerBase.h"
#include "Pie.h"
#include <memory>
#include <mutex>
#include <boost/optional.hpp>

class CoolingWindow : public ICoolingWindow, public WorkerBase  {
public:
	CoolingWindow(int windowIndex);
	virtual ~CoolingWindow();
	CoolingWindow(CoolingWindow&& source);

	void addPie(std::unique_ptr<Pie> pie) override;
	std::unique_ptr<Pie> getPie() override;

	bool containsPieCoolEnoughToEat() override;
	bool isEmpty() override;

	int getIndex() override;


private:
	std::unique_ptr<Pie> _pie;
	std::mutex _pieLock;
	int _index;

	const double _coolingPerSecondDegreesC = 10;
	const int _coolingIntervalMs = 100;
	const double _coolingPerCoolingIntervalDegreesC = (_coolingPerSecondDegreesC) * ((double)(_coolingIntervalMs) / 1000);

	void workerLoop() override;
};

#endif /* COOLINGWINDOW_H_ */
