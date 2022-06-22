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

std::fstream logFile;

void openLog(std::string fileName)
{
    logFile.open(fileName.c_str(), std::ios_base::app);
    if (!logFile.good() == true)
    {
        std::cout << "Cannot open log file " << "log.txt" << std::endl;
    }
}

int main(int argc, char** argv) {

    // createFile("file1.bin", 100, 0xFF); - Create file 1
    // createFile("file2.bin", 100, 0xFE); - Create file 2


  
    return 0;
}