#ifndef _MAIN_BUS_H_
#define _MAIN_BUS_H_

#include <Chip.h>
#include <vector>

#include <Cartridge.h>

/* 总线下不仅仅挂载了内存，如何设计这个类名还值得细细考虑一下 */
class MainBus
{
public:
    MainBus();
    /* 
    在day3时这样写并不准确，因为还没考虑mapper，
    仅仅为了测试CPU能否正常执行指令
    */
    MainBus(Cartridge& cartridge);
   
    Byte Read(Address addr);
    void Write(Address addr, Byte val);

private:
    /* 使用vector 保存内存信息*/
    std::vector<Byte> m_RAM;
    std::vector<Byte> m_extRAM; /* 扩展 RAM */
    /* 在day3时这么定义并不准备，因为还没考虑mapper的存在 */
    Cartridge cartridge;
};

#endif