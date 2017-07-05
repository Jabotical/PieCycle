#ifndef WORKERBASE_H_
#define WORKERBASE_H_

#include <thread>
#include <atomic>

class WorkerBase {
public:
	WorkerBase();
	virtual ~WorkerBase();

	void start();
	void requestStop();
	void requestStopAndWaitForTermination();

protected:
	std::thread _worker;
	std::atomic<bool> _stopRequested;

	virtual void workerLoop() = 0;

private:
	void worker();
};

#endif /* WORKERBASE_H_ */
