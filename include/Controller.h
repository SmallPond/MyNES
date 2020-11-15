#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <Chip.h>
#include <SFML/Window.hpp>
#include <vector>


class Controller
{
    public:
        Controller();
        enum Buttons 
        {
            A,
            B,
            Select,
            Start,
            Up,
            Down,
            Left,
            Right,
            TotalButtons,
        };
        void Write(Byte b);
        /* 获取各个按键的状态 */
        Byte Read();
        /* 映射键盘到红黄机各个button的关系 */
        void SetKeyBindings(const std::vector<sf::Keyboard::Key> &keys);
    private:
        bool m_strobe;
        unsigned int m_buttonStates;
        // sfml 库的 key 类型绑定各个按键
        std::vector<sf::Keyboard::Key> m_keyBindings;

};


#endif /* _CONTROLLER_H_ */