#ifndef _CARTRIDGE_H_
#define _CARTRIDGE_H_

#include <vector>
#include <string>
#include <cstdint>
/*
 * cartridge: 卡带
 * 卡带中 NES 文件格式：
 * |Header|Trainer|PGR|CHR|
 * |16B   |0或者512B |n*16KB|n*8KB|
 * Header 中 Trainer 的 flag 为 1，则此区域为 512 字节，否则为 0。
 * 模拟可不考虑 Trainer 段
 * 
*/

using Byte = std::uint8_t;
using Address = std::uint16_t;

class Cartridge
{
    public:
        Cartridge();
        bool LoadFromFile(std::string path);
        const std::vector<Byte>& GetROM();
        const std::vector<Byte>& GetVROM();
        bool HasExtendedRAM();
        Byte GetMapper();
        Byte GetNameTableMirroring();

    private:
        std::vector<Byte> m_PRG_ROM;   // 存放 NES 程序数据
        std::vector<Byte> m_CHR_ROM;   // 角色只读存储器，用于图像显示

        Byte m_nameTableMirroring;   
        Byte m_mapperNumber;            // mappper号 最基础为0
        bool m_extendedRAM;             // 卡带中是否存在扩展RAM
};


#endif 