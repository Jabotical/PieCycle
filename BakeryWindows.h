#ifndef BAKERYWINDOWS_H_
#define BAKERYWINDOWS_H_

#include "IBakeryWindows.h"

#include "ICoolingWindow.h"

#include <vector>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <boost/optional.hpp>

class BakeryWindows  : public IBakeryWindows {
public:
	BakeryWindows(std::vector<std::unique_ptr<ICoolingWindow>> coolingWindows);
	virtual ~BakeryWindows();

	void start() override;
	void stop() override;

	void waitForEmptyWindowThenAddPie(std::unique_ptr<Pie>) override;
	std::unique_ptr<Pie> getEdiblePieIfAvailableNullOtherwise() override;

private:
	std::vector<std::unique_ptr<ICoolingWindow>> _coolingWindows;

	std::condition_variable _pieAvailabilityCondition;
	std::mutex _makerLock;
	std::mutex _eaterLock;

	std::atomic<bool> _stopRequested;

	boost::optional<ICoolingWindow&> getEmptyWindow();

	void signalEmptyWindowAvailable();

	void releaseAllMakerLocks();
};

#endif /* BAKERYWINDOWS_H_ */
