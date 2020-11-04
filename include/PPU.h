#ifndef _PPU_H_ 
#define _PPU_H_
#include <Chip.h>
#include <PictureBus.h>
#include <VirtualScreen.h>
#include <vector>

const int ScanlineCycleLength = 341;
const int ScanlineEndCycle = 340;
// NES 图像分辨率为 256 x 240（长 x 宽）
const int ScanlineVisibleDots = 256;
const int VisibleScanlines = 240;

const int FrameEndScanline = 261;

const int AttributeOffset = 0x3C0;

class PPU 
{
    public:
        PPU(PictureBus &bus, VirtualScreen &screen);

        void Reset();
        void Step();

        /*OAM (Object Attribute Memory) */

    private:
        Byte Read(Address addr);

        PictureBus &m_bus;
        VirtualScreen &m_screen;

        std::vector<Byte> m_spriteMemory;
        std::vector<Byte> m_scanlineSprites;

        enum PipelineState
        {
            PreRender,
            Render,
            PostRender,
            VerticalBlank
        } m_pipelineState;

        int m_cycle;
        int m_scanline;
        bool m_evenFrame;

        bool m_vblank;
        bool m_sprZeroHit;

        // 寄存器
        Address m_dataAddress;
        Address m_tempAddress;
        Byte m_fineXScroll;
        bool m_firstWrite;
        Byte m_dataBuffer;
        Byte m_spriteDataAddress;
        // Flags and variables

        bool m_longSprites;
        bool m_generateInterrupt;
        bool m_greyscaleMode;
        bool m_showSprites;
        bool m_showBackground;
        bool m_hideEdgeSprites;
        bool m_hideEdgeBackground;

        enum CharacterPage
        {
            Low,
            High,
        } m_bgPage, m_sprPage;
        std::vector<std::vector<sf::Color>> m_pictureBuffer;
};


#endif /* _PPU_H_ */