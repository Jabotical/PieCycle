#include "WorkerBase.h"

WorkerBase::WorkerBase() {
	_stopRequested = false;
}

WorkerBase::~WorkerBase() {
	// TODO Auto-generated destructor stub
}

void WorkerBase::start()
{
	_stopRequested = false;
	_worker = std::thread(&WorkerBase::worker, this);
}

void WorkerBase::requestStop()
{
	_stopRequested = true;
}

void WorkerBase::requestStopAndWaitForTermination()
{
	_stopRequested = true;
	_worker.join();
}

void WorkerBase::worker()
{
	while(!_stopRequested)
	{
		workerLoop();
	}
}
