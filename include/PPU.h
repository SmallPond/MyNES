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
        void SetInterruptCallback(std::function<void(void)> cb);
        /*OAM (Object Attribute Memory) */


        void SetMask(Byte mask);
        Byte GetStatus();
        void SetDataAddress(Byte addr);
        Byte GetData();
        void SetData(Byte data);
        Byte GetOAMData();
        void Control(Byte ctrl);
        void SetOAMAddress(Byte addr);
        void SetOAMData(Byte value);
        void SetScroll(Byte scroll);
        void DoDMA(const Byte* page_ptr);
    private:
        Byte Read(Address addr);
        Byte ReadOAM(Byte addr);
        void WriteOAM(Byte addr, Byte value);
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
        // v blank 消隐
        std::function<void(void)> m_vblankCallback;
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


        Address m_dataAddrIncrement;

        // 存颜色的vector 的 vector
        // picture 缓存
        std::vector<std::vector<sf::Color>> m_pictureBuffer;
};


#endif /* _PPU_H_ */