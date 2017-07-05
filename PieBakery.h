#ifndef PIEBAKERY_H_
#define PIEBAKERY_H_

#include "IPieBakery.h"
#include "IBakeryWindows.h"
#include "IPieMaker.h"
#include "IPieEater.h"

#include <vector>
#include <memory>

#include <boost/optional.hpp>

class PieBakery: public IPieBakery {
public:
	const int _numWindows = 15;

	PieBakery(std::shared_ptr<IBakeryWindows> bakeryWindows, std::vector<std::unique_ptr<IPieMaker>> pieMakers, std::vector<std::unique_ptr<IPieEater>> pieEaters);
	virtual ~PieBakery();

	void start() override;
	void stop() override;

private:
	std::vector<std::unique_ptr<IPieMaker>> _pieMakers;
	std::shared_ptr<IBakeryWindows> _bakeryWindows;

	std::vector<std::unique_ptr<IPieEater>> _pieEaters;
};

#endif /* PIEBAKERY_H_ */
