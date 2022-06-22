#include <iostream>
#include <fstream>
#include <sstream>

void createFile(const std::string name, const int count, const char value) {
    std::fstream f;
    f.open(name.c_str(), std::ios::binary | std::ios::out);
    for (int i = 0; i < count; i++) {
        f.write((char*)&value,1);
    }
    f.close();
}

std::fstream logFile;

void openLog(std::string fileName) {
    logFile.open(fileName.c_str(), std::ios_base::app);
    if (!logFile.good() == true) {
        std::cout << "Cannot open log file " << "log.txt" << std::endl;
    }
}

void saveLog(std::string msg) {
    std::string ss;
    time_t currentTime = time(NULL);
    std::string txttime = (std::string)asctime(localtime(&currentTime));
    txttime = txttime.substr(0, txttime.length() - 1);
    ss = (std::string)"T: " + txttime + " M: " + msg + "\n";
    logFile << ss.c_str();
    logFile.flush();
    std::cout << ss.c_str();
    std::cout.flush();
}

void closeLog(void) {
    logFile.close();
}

uint8_t diffBit(uint8_t n1, uint8_t n2) {
    uint8_t x = n1 ^ n2;
    uint8_t setBits = 0;
    while (x > 0) {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}

struct result {
    double tot; 
    double err; 
    float ber;  
    clock_t t1; 
    clock_t t2; 
};

result calculateResult(std::string file1, std::string file2) {
    std::fstream f1, f2; 
    result results;
    results.t1 = 0;
    results.t2 = 0;
    results.ber = 0;
    results.err = 0;
    results.tot = 0;

    f1.open(file1.c_str(), std::ios::binary | std::ios::in);
    f2.open(file2.c_str(), std::ios::binary | std::ios::in);
    char a = 0x00;
    char b = 0x00;
    results.t1 = clock();

    while (!f1.eof()) {
        f1 >> a;
        f2 >> b;
        if (!f1.eof()) {
            results.err += diffBit(a, b); 
            results.tot += 8;
        }
    }

    results.ber = (float)results.err / results.tot; 
    results.t2 = clock(); 
    return results;
}
void printResults(result results) {
    std::stringstream message;
    message << "Results are: BER: " << results.ber << " Tot: " << results.tot << " Err: " << results.err << " Calc time: " << ((float)results.t2 - results.t1) / CLOCKS_PER_SEC << " sec ";
    saveLog(message.str());
}

int main(int argc, char** argv) {

    // createFile("file1.bin", 100, 0xFE); // - Create file 1 for test 2
    // createFile("file2.bin", 101, 0xFF); // - Create file 2 for test 2

    openLog("log.txt");
    if (argc != 3) {
        saveLog("Bads arguments");
    } else {
        saveLog("Start calculate");
        result results = calculateResult(argv[1], argv[2]);
        saveLog("End calculate");
        printResults(results);
    }
    closeLog();

    return 0;
}