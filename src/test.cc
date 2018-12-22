#include <iostream>
#include <elf.h>
#include <unistd.h>
#include <string.h>
int main() {

    if (ELFMAG[0] == 0x7f){
        std::cout << "ok " << std::endl;
    }

}