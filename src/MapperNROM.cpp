#include<MapperNROM.h>
#include<Log.h>

/* NROM-Mapper0: 最简单的实现方式 */


MapperNROM::MapperNROM(Cartridge& cart): 
    Mapper(cart, Mapper::NROM)
{
    /* 0x4000 = 16 KB */
    if (cart.GetROM().size() == 0x4000) //1 bank
    {
        m_oneBank = true;
    }
    else //2 banks
    {
        m_oneBank = false;
    }

    if (cart.GetVROM().size() == 0)
    {
        m_usesCharacterRAM = true;
        m_characterRAM.resize(0x2000);
        LOG(Info) << "Uses character RAM" << std::endl;
    }
    else
    {
        LOG(Info) << "Using CHR-ROM" << std::endl;
        m_usesCharacterRAM = false;
    }
}

Byte MapperNROM::ReadPRG(Address addr)
{
    if (!m_oneBank)
    {
        return m_cartridge.GetROM()[addr - 0x8000];
    }  
    else //镜像读
    {
        return m_cartridge.GetROM()[(addr - 0x8000) & 0x3fff];
    }
        
}

void MapperNROM::WritePRG(Address addr, Byte value)
{
    LOG(InfoVerbose) << "ROM memory write attempt at " << +addr << " to set " << +value << std::endl;
}

Byte MapperNROM::ReadCHR(Address addr)
{
    // 这里不进行越界判断？
    if (m_usesCharacterRAM)
    {
        return m_characterRAM[addr];
    }
    else
    {
        return m_cartridge.GetVROM()[addr];
    }
}


void MapperNROM::WriteCHR(Address addr, Byte value)
{
    if (m_usesCharacterRAM)
    {
        m_characterRAM[addr] = value;
    }
    else
    {
        LOG(Info) << "Read-only CHR memory write attempt at " << std::hex << addr << std::endl;
    }
        
}