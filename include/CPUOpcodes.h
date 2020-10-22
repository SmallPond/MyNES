#ifndef _CPUOPCODES_H_
#define _CPUOPCODES_H_

/* 6502 CPU 操作码相关定义*/

/* 复位向量地址，当CPU复位时，CPU将从此处地址开始取指执行 */
const auto ResetVector = 0xfffc;

#endif