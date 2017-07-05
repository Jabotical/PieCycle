#include <iostream>
using namespace std;

#include "PieBakeryFactory.h"

int main() {
	setbuf(stdout, NULL);

	auto bakery = PieBakeryFactory::create();

	printf("Starting up Bakery...\n");
	bakery->start();

	printf("(waiting while Bakery runs...)\n");
	std::this_thread::sleep_for(std::chrono::seconds(6));

	printf("Stopping Bakery...\n");
	bakery->stop();

	printf("Pie Cycle Complete.\n");
	fflush(stdout);
	std::cout.flush();
	return 0;
}
