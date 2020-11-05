#include <cstdint>

/*
 * 参考：https://blog.csdn.net/qq_34254642/article/details/104193445
 * NES使用两个调色板，
 * 每个有16个条目，图像调色板($3F00-$3F0F)和精灵调色板($3F10-$3F1F)。
 * 图像调色板显示当前背景块可用的颜色。精灵调色板显示精灵当前可用的颜色。这些调色板不存储实际的颜色值，而是系统调色板中的颜色索引。由于只需要64个唯一值，所以可以忽略第6和第7位。
 * 
 * 调色板条目$3F00是背景色，用于透明。
 * 使用镜像使调色板中的每四个字节是$3F00的一个副本。
 * 因此，$3F04、$3F08 $3FOC、$3F10、$3F14、$3F18和$3F1C只是$3F00的副本。
 * 每个调色板的颜色是13，而不是16。因此，在任何时候，屏幕上的颜色总数是52种颜色中的25种。两个调色板也镜像到$3F20-$3FFF。
*/


//Colors in RGBA (8 bit colors)
// red green blue alpha 格式
// 由调色板映射实际显示的颜色
// 7 * 8
const std::uint32_t colors[] = {
    0x666666ff, 0x002a88ff, 0x1412a7ff, 0x3b00a4ff, 0x5c007eff, 0x6e0040ff, 0x6c0600ff, 0x561d00ff,
    0x333500ff, 0x0b4800ff, 0x005200ff, 0x004f08ff, 0x00404dff, 0x000000ff, 0x000000ff, 0x000000ff,
    0xadadadff, 0x155fd9ff, 0x4240ffff, 0x7527feff, 0xa01accff, 0xb71e7bff, 0xb53120ff, 0x994e00ff,
    0x6b6d00ff, 0x388700ff, 0x0c9300ff, 0x008f32ff, 0x007c8dff, 0x000000ff, 0x000000ff, 0x000000ff,
    0xfffeffff, 0x64b0ffff, 0x9290ffff, 0xc676ffff, 0xf36affff, 0xfe6eccff, 0xfe8170ff, 0xea9e22ff,
    0xbcbe00ff, 0x88d800ff, 0x5ce430ff, 0x45e082ff, 0x48cddeff, 0x4f4f4fff, 0x000000ff, 0x000000ff,
    0xfffeffff, 0xc0dfffff, 0xd3d2ffff, 0xe8c8ffff, 0xfbc2ffff, 0xfec4eaff, 0xfeccc5ff, 0xf7d8a5ff,
    0xe4e594ff, 0xcfef96ff, 0xbdf4abff, 0xb3f3ccff, 0xb5ebf2ff, 0xb8b8b8ff, 0x000000ff, 0x000000ff,
};

