#include <iostream>
#include "CPU.h"
#include "MainBus.h"

int main()
{
    MainBus bus;
    CPU test_cpu(bus);

    test_cpu.Reset();
    std::cout << "After reset the PC is :" << test_cpu.GetPC() << std::endl;
    // CPU取指解码执行，目前仅实现取指操作
    test_cpu.Step();
    std::cout << "After Step the PC is :" << test_cpu.GetPC() << std::endl;

    return 0;
}