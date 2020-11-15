#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <CPU.h>
#include <Cartridge.h>
#include <MainBus.h>
#include <chrono>
#include <Mapper.h>
#include <SFML/Graphics.hpp>
#include <VirtualScreen.h>
#include <PPU.h>
#include <PictureBus.h>
#include <Controller.h>


const int NESVideoWidth = ScanlineVisibleDots;
const int NESVideoHeight = VisibleScanlines;






class Emulator
{
    public:
        Emulator();
        void Run(std::string rom_path);
    private:
        void DMA(Byte page);
        CPU m_cpu;
        PPU m_ppu;
        PictureBus m_pictureBus;
        VirtualScreen m_emulatorScreen;

        Cartridge m_cartridge;
        MainBus m_bus;
        std::unique_ptr<Mapper> m_mapper;
        sf::RenderWindow m_window;
        // 两个游戏手柄
        Controller m_controller1, m_controller2;
        // 控制屏幕缩放
        float m_screenScale;
        // 计时
        std::chrono::high_resolution_clock::time_point m_cycleTimer;
        std::chrono::high_resolution_clock::duration m_elapsedTime;
        std::chrono::nanoseconds m_cpuCycleDuration;
};


#endif /* _EMULATOR_H_ */