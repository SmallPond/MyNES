#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <CPU.h>
#include <Cartridge.h>
#include <MainBus.h>
#include <Mapper.h>

class Emulator
{
    public:
        Emulator();
        void Run(std::string rom_path);
    private:
        CPU m_cpu;
        Cartridge m_cartridge;
        MainBus m_bus;
        std::unique_ptr<Mapper> m_mapper;
};


#endif /* _EMULATOR_H_ */