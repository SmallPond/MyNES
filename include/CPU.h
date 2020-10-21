#ifndef _CPU_H_
#define _CPU_H_
#include<MainBus.h>

/* 6502 CPU 16-bit address 8-bit data */
using Byte = std::uint8_t;
using Address = std::uint16_t;


class CPU {
    public:
        CPU();

        void Reset();
        void ResetAddress(Address start_address);
        void Step();
    private:
        Address ReadAddress(Address addr);

        /* CPU exec instruction*/
        void PushStack(Byte value);
        Byte PopStack();


        int m_skipCycles;
        int m_cycles;

        //Registers
        Address r_PC;    // PC
        Byte r_SP;       /* Stack Pointer */ 
        Byte r_A;        /* Accumulator */
        Byte r_X;        /* index Reg X */
        Byte r_Y;        /* index Reg Y */

        /* Processor Status Reg */ 
        //Is storing them in one byte better ?
        bool f_C;         /* Carry */
        bool f_Z;         /* Zero */
        bool f_I;         /* IRQ disable */
//      bool f_B;         /* Brk command */
        bool f_D;         /* Decimal mode */
        bool f_V;         /* Overflow  */
        bool f_N;         /* Negative */
}

#endif 