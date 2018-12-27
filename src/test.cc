#include <iostream>
#include <elf.h>
#include <unistd.h>
#include <string.h>

#define TO_NAME(x) #x

class Test {

};

int main() {

    char *a = new char [0];
    std::cout << a << std::endl;
}