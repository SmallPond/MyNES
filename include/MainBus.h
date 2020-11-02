#ifndef _MAIN_BUS_H_
#define _MAIN_BUS_H_

#include <Chip.h>
#include <vector>

#include <Cartridge.h>
#include <Mapper.h>

/* 总线下不仅仅挂载了内存，如何设计这个类名还值得细细考虑一下 */
class MainBus
{
public:
    MainBus();
    
    bool SetMapper(Mapper *mapper);
   
    Byte Read(Address addr);
    void Write(Address addr, Byte val);

private:
    /* 使用vector 保存内存信息*/
    std::vector<Byte> m_RAM;
    std::vector<Byte> m_extRAM; /* 扩展 RAM */
    Mapper* m_mapper;

};

#endif