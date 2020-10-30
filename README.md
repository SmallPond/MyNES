# C++一步步实现红白机模拟器

选择不同的分支来查看每次增加的内容，以达到分解整个项目实现的目的。

## Day1:
 
模拟6502 CPU 、总线和内存RAM，实现CPU可从内存中读写数据和取指令 
## Day2: 

参考6502 CPU 的datasheet，实现了CPU对指令的解码执行
## Day3

NES 软件编写示例，位于`example/nes`目录下，主要包括文件
- `nes.cfg`：指定了链接方式
- `example.asm`： 实现了一个简单的4+2的操作


### 编译器下载安装

- MacOS: `brew install cc65`
- [Linux: 下载安装](https://debian.trikaliotis.net/cc65/)
- Windows: 下载安装 [https://sourceforge.net/projects/cc65/files/cc65-snapshot-win32.zip]

### 编译链接
```
# 编译
ca65 example.asm -o example.o 
ld65 -C nes.cfg example.o -o example.nes
```

### 查看生成的.nes文件

vscode下安装`hexdump for vscode`,使用二进制阅读器打开后可看到:
- 0x0000：一行自动补齐了NES文件的header
- 0x0010：一行中`A9 04`对应了汇编语句`LDA #$4`, `69 02`对应了汇编语句`ADC #$2`
- 0x8000：中断向量表中保存了目标地址`0x8000`，这是因为我们在 example/nes/nes.cfg文件中指定了`PRG: start = $8000`，也就是我们汇编代码中的main函数首地址。

```
00000000: 4E 45 53 1A 02 00 00 00 00 00 00 00 00 00 00 00    NES.............
00000010: A9 04 69 02 00 00 00 00 00 00 00 00 00 00 00 00
...
...
00008000: 00 00 00 00 00 00 00 00 00 00 00 80 00 80 00 80
```

### 编译执行模拟器
```
# 编译模拟器
make
# 运行
./myNES
```

执行结果如下：
```c
Reading ROM from path: ./examples/nes/example.nes
Reading header, it dictates: 
16KB PRG-ROM Banks: 2
8KB CHR-ROM Banks: 0
ROM is NTSC compatible.
a9 4 69 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
Cartridge with CHR-RAM.
MainBus Read a Byte: 0
MainBus Read a Byte: 80
[+]After reset, the PC is: 8000
MainBus Read a Byte: a9
MainBus Read a Byte: 4
MainBus Read a Byte: 69
MainBus Read a Byte: 2
[+]执行4+2的操作后，ACC寄存器的值为:6
```