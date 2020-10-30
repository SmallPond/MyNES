#include <MainBus.h>
#include <iostream>
/*  0x800 = 2KB */
MainBus::MainBus() : m_RAM(0x800, 0)
{
}

/* 
在day3时这样写并不准确，因为还没考虑mapper，
仅仅为了测试CPU能否正常执行指令
*/
MainBus::MainBus(Cartridge& cartridge):
m_RAM(0x800, 0), cartridge(cartridge)
{

}

Byte MainBus::Read(Address addr)
{
    /* 0x2000 =  8KB RAM  */

    if (addr < 0x2000)
    {
        /* 实际只有2KB RAM(如上定义的0x800)，所以采用addr & 0x7ff的操作 */
        return m_RAM[addr & 0x7ff];
    }

    if (addr >= 0x8000)
    {
        Byte val = cartridge.GetROM()[addr - 0x8000];
        std::cout << "MainBus Read a Byte: " << std::hex << static_cast<int>(val) << std::endl;
        return val;
    }
    return 0;
}

void MainBus::Write(Address addr, Byte val)
{
    if (addr < 0x2000)
    {
        m_RAM[addr & 0x7ff] = val;
    }
}