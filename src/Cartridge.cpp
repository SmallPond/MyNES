#include<Cartridge.h>
#include<fstream>
#include <Log.h>

Cartridge::Cartridge()
{

}
const std::vector<Byte>& Cartridge::GetROM()
{
    return m_PRG_ROM;
}
const std::vector<Byte>& Cartridge::GetVROM()
{
    return m_CHR_ROM;
}

Byte Cartridge::GetMapper()
{
    return m_mapperNumber;
}

Byte Cartridge::GetNameTableMirroring()
{
    return m_nameTableMirroring;
}

bool Cartridge::HasExtendedRAM()
{
    return m_extendedRAM;
}

/*
 * .NES 文件头格式 https://wiki.nesdev.com/w/index.php/INES
 * 0-3: Constant $4E $45 $53 $1A ("NES" followed by MS-DOS end-of-file)
 * 4: Size of PRG ROM in 16 KB units
 * 5: Size of CHR ROM in 8 KB units (Value 0 means the board uses CHR RAM)
 * 6: Flags 6 - Mapper, mirroring, battery, trainer
 * 7: Flags 7 - Mapper, VS/Playchoice, NES 2.0
 * 8: Flags 8 - PRG-RAM size (rarely used extension)
 * 9: Flags 9 - TV system (rarely used extension)
 * 10: Flags 10 - TV system, PRG-RAM presence (unofficial, rarely used extension)
 * 11-15: Unused padding (should be filled with zero, but some rippers put their name across bytes 7-15
*/
bool Cartridge::LoadFromFile(std::string path)
{

    std::ifstream romFile (path, std::ios_base::binary | std::ios_base::in);
    if (!romFile) 
    {
        LOG(Error) << "Could not open ROM file from path: " << path << std::endl;
        return false;
    }
    
    LOG(Info) << "Reading ROM from path: " << path << std::endl;

    // 读取.NES文件中的 header
    std::vector<Byte> header;
    header.resize(0x10);

    if (!romFile.read(reinterpret_cast<char*>(&header[0]), 0x10))
    {
        LOG(Error) << "Reading iNES header failed." << std::endl;
        return false;
    }

    if (std::string{&header[0], &header[4]} != "NES\x1A")
    {
        LOG(Error) << "Not a valid iNES image. Magic number: "
                    << std::hex << header[0] << " "
                    << header[1] << " " << header[2] << " " << int(header[3]) << std::endl
                    << "Valid magic number : N E S 1a" << std::endl;
        return false;
    }

    LOG(Info) << "Reading header, it dictates: \n-*--*--*--*--*--*--*--*-\n";

    Byte banks = header[4];
    LOG(Info) << "16KB PRG-ROM Banks: " << +banks << std::endl;
    if (!banks)
    {
        LOG(Error) << "ROM has no PRG-ROM banks. Loading ROM failed." << std::endl;
        return false;
    }
    // vidio banks
    Byte vbanks = header[5];
    LOG(Info) << "8KB CHR-ROM Banks: " << +vbanks << std::endl;
    // nameTableMirroring
    m_nameTableMirroring = header[6] & 0xB;
    LOG(Info) << "Name Table Mirroring: " << +m_nameTableMirroring << std::endl;
    // mapper Number 
    m_mapperNumber = ((header[6] >> 4) & 0xf) | (header[7] & 0xf0);
    LOG(Info) << "Mapper number #: " << +m_mapperNumber << std::endl;

    m_extendedRAM = header[6] & 0x2;
    LOG(Info) << "Extended (CPU) RAM: " << std::boolalpha << m_extendedRAM << std::endl;

    // 模拟器暂不支持 使用 Trainer 格式的 .NES 文件
    if (header[6] & 0x4)
    {
        LOG(Error) << "Trainer is not supported." << std::endl;
        return false;
    }

    if ((header[0xA] & 0x3) == 0x2 || (header[0xA] & 0x1))
    {
        LOG(Error) << "PAL ROM not supported." << std::endl;
        return false;
    }
    else
        LOG(Info) << "ROM is NTSC compatible.\n";

    //PRG-ROM 16KB banks
    // 将0x4000(16KB) * banks 内容写到 m_PGR_ROM 中
    m_PRG_ROM.resize(0x4000 * banks);
    if (!romFile.read(reinterpret_cast<char*>(&m_PRG_ROM[0]), 0x4000 * banks))
    {
        LOG(Error) << "Reading PRG-ROM from image file failed." << std::endl;
        return false;
    }

    //CHR-ROM 8KB banks
    if (vbanks)
    {
        m_CHR_ROM.resize(0x2000 * vbanks);
        if (!romFile.read(reinterpret_cast<char*>(&m_CHR_ROM[0]), 0x2000 * vbanks))
        {
            LOG(Error) << "Reading CHR-ROM from image file failed." << std::endl;
            return false;
        }

    }
    else
        LOG(Info) << "Cartridge with CHR-RAM." << std::endl;
    LOG(Info) << "-*--*--*--*--*--*--*--*-\n" << std::endl;
    return true;
}