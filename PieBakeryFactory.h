#ifndef PIEBAKERYFACTORY_H_
#define PIEBAKERYFACTORY_H_

#include "IPieBakery.h"
#include "IPieMaker.h"
#include "IPieEater.h"
#include "IBakeryWindows.h"

#include <vector>
#include <memory>

class PieBakeryFactory {
public:
	PieBakeryFactory();
	virtual ~PieBakeryFactory();

	static std::unique_ptr<IPieBakery> create();

private:
	static std::vector<std::unique_ptr<IPieMaker>> hirePieMakers(std::shared_ptr<IBakeryWindows> bakeryWindows);
	static std::shared_ptr<IBakeryWindows> openBakeryWindows(int numWindows);
	static std::vector<std::unique_ptr<ICoolingWindow>> createCoolingWindows(int numWindows);
	static std::vector<std::unique_ptr<IPieEater>> attractPieEaters(int numPieEaters, std::shared_ptr<IBakeryWindows> bakeryWindows);
};

#endif /* PIEBAKERYFACTORY_H_ */
