#ifndef IPIEMAKER_H_
#define IPIEMAKER_H_

#include "Pie.h"

class IPieMaker
{
public:
	virtual ~IPieMaker() { }

	virtual Pie::Type getPieType() = 0;
};


#endif /* IPIEMAKER_H_ */
