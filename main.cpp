#include <iostream>
#include <fstream>
#include <sstream>

void createFile(const std::string name, const int count, const char value) {
    std::fstream f;
    f.open(name.c_str(), std::ios::binary | std::ios::out);
    for (int i = 0; i < count; i++)
    {
        f.write((char*)&value,1);
    }
    f.close();
}

int main(int argc, char** argv) {
    createFile("file1.bin", 100, 0xFF);
    createFile("file2.bin", 100, 0xFE);
  
    return 0;
}