#ifndef PIEMAKER_H_
#define PIEMAKER_H_

#include "WorkerBase.h"
#include "IPieMaker.h"

#include "Pie.h"
#include "IBakeryWindows.h"

#include <memory>

class PieMaker : public IPieMaker, public WorkerBase  {
public:
	PieMaker(Pie::Type pieType, std::shared_ptr<IBakeryWindows> bakeryWindows);
	virtual ~PieMaker();

	PieMaker(PieMaker&& source);

	std::unique_ptr<Pie> _pie;

	Pie::Type getPieType() override;

private:
	Pie::Type _pieType;
	int _pieProductionTimeMs;

	std::shared_ptr<IBakeryWindows> _bakeryWindows;

	void makePieIfOneIsNotMade();
	void waitForOpenWindowAndSetPieToCool();
	void setPieToCool();

	void workerLoop() override;
};

#endif /* PIEMAKER_H_ */
