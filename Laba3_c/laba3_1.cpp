#include <iostream>
#include <chrono>
#include <ctime>

int main() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_c);
    std::cout << "Сегодня: "
              << local_tm.tm_mday << "." << local_tm.tm_mon + 1 << "." << local_tm.tm_year + 1900 << std::endl;

    return 0;
}
