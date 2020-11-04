#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <CPU.h>
#include <Cartridge.h>
#include <MainBus.h>
#include <Mapper.h>
#include <SFML/Graphics.hpp>
#include <VirtualScreen.h>
#include <PPU.h>


const int NESVideoWidth = ScanlineVisibleDots;
const int NESVideoHeight = VisibleScanlines;

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
        sf::RenderWindow m_window;
        VirtualScreen m_emulatorScreen;
        // 控制屏幕缩放
        float m_screenScale;
};


#endif /* _EMULATOR_H_ */