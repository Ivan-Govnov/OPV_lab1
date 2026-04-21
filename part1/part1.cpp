#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex cout_mutex;

void printThread(int threadNum, int range, int milliSeconds) {
    for (int i = 1; i <= range; i++) {
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Поток " << threadNum << ": " << i << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
    }
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Поток " << threadNum << " завершил работу" << std::endl;
    }
}

int main() {
    std::cout << "Главный поток запускает дочерние потоки" << std::endl;

    std::thread t1(printThread, 1, 20, 300);
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Главный поток: поток t1 запущен." << std::endl;
    }

    std::thread t2(printThread, 2, 30, 200);
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Главный поток: поток t2 запущен." << std::endl;
    }
    
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Главный поток продолжает работу" << std::endl;
    }
    

    for (int i = 1; i <= 100; i++) {
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Главный поток: сообщение " << i << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Главный поток ожидает завершения потоков..." << std::endl;
    }

    // t1.join();
    // t2.join();
    
    std::cout << "Главный поток: все потоки завершены" << std::endl;
}