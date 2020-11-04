#include <Emulator.h>
#include <Log.h>


Emulator::Emulator(): 
    m_cpu(m_bus),
    m_screenScale(2.f)
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

    m_window.create(sf::VideoMode(NESVideoWidth * m_screenScale, NESVideoHeight * m_screenScale),
                    "MyNES", sf::Style::Titlebar | sf::Style::Close);
    m_window.setVerticalSyncEnabled(true);
    sf::CircleShape shape(NESVideoWidth);
    // 颜色填充
    shape.setFillColor(sf::Color::Red);
    m_emulatorScreen.Create(NESVideoWidth, NESVideoHeight, m_screenScale, sf::Color::White);

    // sf::Event event;
    
    while(m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }

            m_window.draw(shape);
            m_window.display();
                
        }
    }

}