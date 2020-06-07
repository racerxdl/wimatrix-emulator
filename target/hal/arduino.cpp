#include <arduino.h>
#include <chrono>
#include <thread>

void delay(unsigned long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}