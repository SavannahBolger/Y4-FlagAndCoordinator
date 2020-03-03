#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

const int n = 5;
std::atomic<int> m_arrive[n], m_continue[n];
static int counter = -1;

void worker()
{
	counter = counter + 1;
	int i = counter;
	while (i < n)
	{
		m_arrive[i] = 1;
		std::cout << "\nThread: " << counter << "\nArrive:" << m_arrive[i] << std::endl;

		if (m_continue[i] == 1)
		{
			m_continue[i] = 0;
			std::cout << "\nThread: " << counter << "\nContinue:" << m_continue[i] << std::endl;
		}
	}
}

void coordinator()
{
	int i = counter;
	while (i < n)
	{
		if (m_arrive[i] == 1)
		{
			m_arrive[i] = 0;
			std::cout << "\nThread: " << counter << "\nArrive:" << m_arrive[i] << std::endl;
		}

		m_continue[i] = 1;
		std::cout << "\nThread: " << counter << "\nContinue:" << m_continue[i] << std::endl;
	}
}

int main()
{
	std::thread worker1(worker);
	std::thread worker2(worker);
	std::thread worker3(worker);
	std::thread worker4(worker);
	std::thread coordinator(coordinator);

	worker1.join();
	worker2.join();
	worker3.join();
	worker4.join();
	coordinator.join();

	std::cin.get();
}