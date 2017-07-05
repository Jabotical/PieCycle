#ifndef IBAKERYWINDOWS_H_
#define IBAKERYWINDOWS_H_

#include "ICoolingWindow.h"

class IBakeryWindows
{
public:
	virtual ~IBakeryWindows() {}

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void waitForEmptyWindowThenAddPie(std::unique_ptr<Pie>) = 0;
	virtual std::unique_ptr<Pie> getEdiblePieIfAvailableNullOtherwise() = 0;
};


#endif /* IBAKERYWINDOWS_H_ */
