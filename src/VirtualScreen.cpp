#include <VirtualScreen.h>

/*
 *  SMFL(Simple and Fast Multimedia Library)
 *  API 文档： https://www.sfml-dev.org/documentation/2.5.1/
*/
void VirtualScreen::Create(unsigned int width, unsigned int height, float pixel_size, sf::Color color)
{
    // 为什么要乘以6？
    m_vertices.resize(width * height * 6);
    // 二元组，
    m_screenSize = {width, height};
    m_vertices.setPrimitiveType(sf::Triangles);
    // 像素大小
    m_pixelSize = pixel_size;
    for (std::size_t x = 0; x < width; ++x)
    {
        for (std::size_t y = 0; y < height; ++y)
        {
            auto index = (x * m_screenSize.y + y);
            // float 型 二元组
            sf::Vector2f coord2d (x * m_pixelSize, y * m_pixelSize);
            // 上左
            m_vertices[index].position = coord2d;
            m_vertices[index].color = color;

            // 上右
            m_vertices[index + 1].position = coord2d + sf::Vector2f{m_pixelSize, 0};
            m_vertices[index + 1].color = color;

            // 下右
            m_vertices[index + 2].position = coord2d + sf::Vector2f{m_pixelSize, m_pixelSize};
            m_vertices[index + 2].color = color;
            
            //bottom-right
            m_vertices[index + 3].position = coord2d + sf::Vector2f{m_pixelSize, m_pixelSize};
            m_vertices[index + 3].color = color;

            //bottom-left
            m_vertices[index + 4].position = coord2d + sf::Vector2f{0, m_pixelSize};
            m_vertices[index + 4].color = color;

            //top-left
            m_vertices[index + 5].position = coord2d;
            m_vertices[index + 5].color    = color;
        }
    }
}


void VirtualScreen::SetPixel(std::size_t x, std::size_t y, sf::Color color)
{
    /* 同样，为什么要乘以 6 */
    auto index = (x * m_screenSize.y + y) * 6;
    if (index >= m_vertices.getVertexCount())
        return;
    
    // sf::Vector2f coord2d (x * m_pixelSize, y * m_pixelSize);

    //Triangle-1
    //top-left
    m_vertices[index].color    = color;

    //top-right
    m_vertices[index + 1].color = color;

    //bottom-right
    m_vertices[index + 2].color = color;

    //Triangle-2
    //bottom-right
    m_vertices[index + 3].color = color;

    //bottom-left
    m_vertices[index + 4].color = color;

    //top-left
    m_vertices[index + 5].color    = color;
}

void VirtualScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw primitives defined by a vertex buffer.
    target.draw(m_vertices, states);
}