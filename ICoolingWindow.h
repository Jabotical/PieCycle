#ifndef ICOOLINGWINDOW_H_
#define ICOOLINGWINDOW_H_

#include <memory>

#include "Pie.h"

class ICoolingWindow
{
public:
	virtual ~ICoolingWindow() {}

	virtual void addPie(std::unique_ptr<Pie> pie) = 0;
	virtual std::unique_ptr<Pie> getPie() = 0;

	virtual bool containsPieCoolEnoughToEat() = 0;
	virtual bool isEmpty() = 0;

	virtual int getIndex() = 0;
};



#endif /* ICOOLINGWINDOW_H_ */
