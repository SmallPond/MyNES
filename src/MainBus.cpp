#include <MainBus.h>

/*  0x800 = 2KB */
MainBus::MainBus() : m_RAM(0x800, 0)
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

    return 0;
}

void MainBus::Write(Address addr, Byte val)
{
    if (addr < 0x2000)
    {
        m_RAM[addr & 0x7ff] = val;
    }
}