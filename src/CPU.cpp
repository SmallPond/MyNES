#include <CPU.h>
#include <CPUOpcodes.h>
#include <MainBus.h>
/* CPU 6502 */

CPU::CPU(MainBus &mem) : m_bus(mem) 
{
    
}

void CPU::Reset()
{
    Reset(ReadAddress(ResetVector));
}

void CPU::Step()
{
    Byte opcode = m_bus.Read(r_PC++);
    // 待实现解码执行
}
Address CPU::ReadAddress(Address addr)
{
    return m_bus.Read(addr) | m_bus.Read(addr + 1) << 8;
}

void CPU::Reset(Address start_addr)
{
    m_skipCycles = m_cycles = 0;
    r_A = r_X = r_Y = 0;
    f_I = true;
    f_C = f_D = f_N = f_V = f_Z = false;
    r_PC = start_addr;
    /* Sp start at 0xfd */
    r_SP = 0xfd; //documented startup state
}
/*
 * 从内存的栈中读/写数据
*/
void CPU::PushStack(Byte val)
{
    m_bus.Write(0x100 | r_SP, val);
    --r_SP;                         /**/
}

Byte CPU::PullStack()
{
    return m_bus.Read(0x100 | ++r_SP);
}