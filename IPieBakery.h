#ifndef IPIEBAKERY_H_
#define IPIEBAKERY_H_

//#include <boost/optional.hpp>
#include "CoolingWindow.h"
#include "Pie.h"

class IPieBakery
{
public:
	virtual ~IPieBakery() {} // TBD...

	virtual void start() = 0;
	virtual void stop() = 0;
};


#endif /* IPIEBAKERY_H_ */
