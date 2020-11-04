#ifndef _MAPPER_NROM_H_
#define _MAPPER_NROM_H_

#include <Mapper.h>

class MapperNROM : public Mapper 
{
    public:
        MapperNROM(Cartridge& cart);
        void WritePRG(Address addr, Byte value);
        Byte ReadPRG(Address addr);
        
        Byte ReadCHR(Address addr);
        void WriteCHR(Address addr, Byte value);
    private:
        bool m_oneBank;
        bool m_usesCharacterRAM;

        std::vector<Byte> m_characterRAM;
};

#endif 