#ifndef _CPU_H_
#define _CPU_H_
#include <MainBus.h>

class CPU {
    public:
        /* CPU 连接总线 */
        CPU(MainBus &mem);

        void Reset();
        void Reset(Address start_address);

        void Step();
        Address GetPC() { return r_PC; }
    private:
        Address ReadAddress(Address addr);
        
        /* 模拟指令执行 */
        bool ExecuteImplied(Byte opcode);
        bool ExecuteBranch(Byte opcode);
        bool ExecuteType0(Byte opcode);
        bool ExecuteType1(Byte opcode);
        bool ExecuteType2(Byte opcode);

        void SetPageCrossed(Address a, Address b, int inc = 1);
        /* CPU exec instruction*/
        void PushStack(Byte value);
        Byte PullStack();
        void SetZN(Byte value);

        int m_skipCycles;
        int m_cycles;

        //Registers 参考 doc/rockwell_r650x.pdf文件
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
        // bool f_B;         /* Brk command */
        bool f_D;         /* Decimal mode */
        bool f_V;         /* Overflow  */
        bool f_N;         /* Negative */

        MainBus &m_bus;
};

#endif 