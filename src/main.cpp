#include <iostream>
#include <Emulator.h>

int main(int argc, char **argv)
{
    Emulator emulator;
    if(argc < 2) 
    {
        std::cout<< "Usage: ./myNES [ROM File Path]"<< std::endl;
        return -1;
    }
    std::string romfile = argv[1];
    emulator.Run(romfile);
}