#include <MainBus.h>
#include <iostream>
#include <Log.h>
/*  0x800 = 2KB */
MainBus::MainBus() : m_RAM(0x800, 0)
{
}


bool MainBus::SetMapper(Mapper *mapper)
{
    m_mapper = mapper;

    if (!mapper)
    {
        LOG(Error) << "Mapper pointer is nullptr" << std::endl;
        return false;
    }

    if(mapper->HasExtendedRAM())
        m_extRAM.resize(0x2000);
    
    return true;
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
        // Byte val = cartridge.GetROM()[addr - 0x8000];
        // std::cout << "MainBus Read a Byte: " << std::hex << static_cast<int>(val) << std::endl;
        // return val;
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