#include "CPU.h"

#include <CPU.h>




void CPU::reset()
{
    reset(readAddress(ResetVector));
}

void CPU::reset(Address start_addr)
{
    m_skipCycles = m_cycles = 0;
    r_A = r_X = r_Y = 0;
    f_I = true;
    f_C = f_D = f_N = f_V = f_Z = false;
    r_PC = start_addr;
    r_SP = 0xfd; //documented startup state
}