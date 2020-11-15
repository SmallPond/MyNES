#include <Controller.h>

/*
 * 参考 https://wiki.nesdev.com/w/index.php/Standard_controller
*/

Controller::Controller() : 
    m_buttonStates(0),
    m_keyBindings(TotalButtons)
{

}

/*
 * 建立PC键盘与 红白机模拟器各个button 的映射
 * 
*/
void Controller::SetKeyBindings(const std::vector<sf::Keyboard::Key> &keys)
{
    m_keyBindings = keys;
}

/*
 * 
7  bit  0
---- ----
xxxx xxxS
        |
        +- Controller shift register strobe
 * Strobe, 寄存器写时的回调函数
 * While S (strobe) is high, 
 * the shift registers in the controllers are continuously reloaded from the button states,
 * 我的理解：控制器的正常流程应该是每次 stobe为1的时候，都会读一个按键的状态并且保存
 * 但这里的实现简化了这个过程：直接在为 0 的时候一起读入？
*/
void Controller::Write(Byte b)
{
    // Input ($4016 write) bit0是S（Strobe）位，该bit位的作用如该函数的注释所描述
    m_strobe = (b & 1 );
    if (!m_strobe)
    {
        m_buttonStates = 0;
        int shift = 0;
        for (int button = A; button < TotalButtons; ++button)
        {
            // 读按键状态
            m_buttonStates |= (sf::Keyboard::isKeyPressed(m_keyBindings[static_cast<Buttons>(button)]) << shift);
            ++shift;
        }
    }
}

/*
 * While S (strobe) is high, 
 * the shift registers in the controllers are continuously reloaded from the button states,
 * and reading $4016/$4017 will keep returning the current state of the first button (A).
 * Once S goes low, this reloading will stop. Hence a 1/0 write sequence is required to get the button states, 
 * after which the buttons can be read back one at a time.
 * 当 Strobe 位为高时，控制器中的移位寄存器会根据按钮状态不断重新加载
 * 读寄存器时的回调函数
 * 当 Strobe 为 1 时，控制器将会一直返回 A 按键的状态
 * 当 Strobe 为 0 时, 控制器将依次返回各个button的状态
*/
Byte Controller::Read()
{
    Byte ret;
    if (m_strobe)
        ret = sf::Keyboard::isKeyPressed(m_keyBindings[A]);
    else 
    {
        ret = (m_buttonStates & 1);
        m_buttonStates >>= 1;
    }
    /* 0x40 = 0b100_0000*/
    // 为什么要 | 一个 0x40 
    return ret | 0x40;
}