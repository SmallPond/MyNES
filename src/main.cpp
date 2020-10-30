#include <iostream>
#include "CPU.h"
#include "MainBus.h"
#include <Cartridge.h>

int main()
{
    // Cartridge cartridge;
    // cartridge.LoadFromFile("./examples/nes/example.nes");
    // MainBus bus(cartridge);
    MainBus bus;
    CPU test_cpu(bus);

    test_cpu.Reset();
    
    std::cout << "[+]After reset, the PC is: " 
              << std::hex << test_cpu.GetPC() << std::endl;
    // CPU取指解码执行
    int cycle = 4;
    while(cycle--) 
    {
        test_cpu.Step();
    }
    // Byte accVal = test_cpu.GetACC();
    // /* 一定要记得加强制转换，不然输出为空白，调试半天，我还以为哪里出了bug*/
    // std::cout << "[+]执行4+2的操作后，ACC寄存器的值为:" 
    //          << static_cast<int>(accVal) << std::endl;
    return 0;
}