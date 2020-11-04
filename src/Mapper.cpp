#include <Mapper.h>
#include <MapperNROM.h>


NameTableMirroring Mapper::GetNameTableMirroring()
{
    return static_cast<NameTableMirroring>(m_cartridge.GetNameTableMirroring());
}

std::unique_ptr<Mapper> Mapper::CreateMapper(Mapper::Type mapper_t, 
                                             Cartridge& cart,  
                                            std::function<void(void)> mirroring_cb)
{
    std::unique_ptr<Mapper> ret(nullptr);
    switch (mapper_t)
    {
        case NROM:
            ret.reset(new MapperNROM(cart));
            break;
        case SxROM:
            // to do 
            break;
        case UxROM:
            // to do 
            break;
        case CNROM:
            // to do 
            break;
    }
    return ret;
}