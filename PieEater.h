#ifndef PIEEATER_H_
#define PIEEATER_H_

#include "WorkerBase.h"
#include "IPieEater.h"

#include "IBakeryWindows.h"

#include <memory>

class PieEater : public IPieEater, public WorkerBase {
public:
	PieEater(std::shared_ptr<IBakeryWindows> bakeryWindows);
	virtual ~PieEater();

private:
	std::shared_ptr<IBakeryWindows> _bakeryWindows;

	void workerLoop() override;
};

#endif /* PIEEATER_H_ */
