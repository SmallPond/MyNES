#include <Emulator.h>
#include <Log.h>


Emulator::Emulator(): 
    m_cpu(m_bus)
{

}
void Emulator::Run(std::string rom_path)
{
    if (!m_cartridge.LoadFromFile(rom_path))
    {
        LOG(Error) << "Unable to load ROM from file:" << rom_path << std::endl;
        return;
    }

    m_mapper = Mapper::CreateMapper(static_cast<Mapper::Type>(m_cartridge.GetMapper()),
                                    m_cartridge);

    if(!m_mapper)
    {
        LOG(Error) << "Creating Mapper failed. Probably unsupported." << std::endl;
        return;
    }
    /* 待添加PPU总线的mapper设置 */
    if(!m_bus.SetMapper(m_mapper.get()))
    {
        return;
    }

    m_cpu.Reset();


}