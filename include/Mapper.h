#ifndef _MAPPER_H_
#define _MAPPER_H_

#include <Cartridge.h>
#include <functional>
#include <memory>


enum NameTableMirroring
{
    Horizontal  = 0,
    Vertical    = 1,
    FourScreen  = 8,
    OneScreenLower,
    OneScreenHigher,
};


class Mapper 
{

    public:
        enum Type 
        {
            NROM  = 0,     // mapper 0 对应最直观的ROM管理方式
            SxROM = 1,
            UxROM = 2,
            CNROM = 3,
        };
        Mapper(Cartridge& cart, Type t) : m_cartridge(cart), m_type(t) {};
        /* 虚函数 */
        virtual void WritePRG(Address addr, Byte value) = 0;
        virtual Byte ReadPRG (Address addr) = 0;

        virtual Byte ReadCHR (Address addr) = 0;
        virtual void WriteCHR (Address addr, Byte value) = 0;
        virtual NameTableMirroring getNameTableMirroring();
        
        bool inline HasExtendedRAM()
        {
            return m_cartridge.HasExtendedRAM();
        }
        static std::unique_ptr<Mapper> CreateMapper (Type mapper_t, Cartridge& cart, std::function<void(void)> mirroring_cb=nullptr);
        // 基类的虚构函数要定义为 virtual，不然会报警告 
        // delete called on 'Mapper' that is abstract but has non-virtual destructor 
        virtual ~Mapper() = default;
    protected:
        Cartridge& m_cartridge;
        Type m_type;
};


#endif  