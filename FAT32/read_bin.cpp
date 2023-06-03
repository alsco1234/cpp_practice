#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

void readBinaryFileBySize(const std::string& filename, int byteSize) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "no file" << std::endl;
        return;
    }

    char* buffer = new char[byteSize];
    while (file.read(buffer, byteSize)) {
        for (int i = 0; i < byteSize; i++) {
            unsigned char value = buffer[i];
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(value) << " ";
        }
        std::cout << std::endl;
    }

    delete[] buffer;
    file.close();
}

int main() {
    std::string filename = "leaf.jpg";

    // 2바이트씩 읽기
    std::cout << "2bytes" << std::endl;
    readBinaryFileBySize(filename, 2);

    // 4바이트씩 읽기
    std::cout << "4bytes" << std::endl;
    readBinaryFileBySize(filename, 4);

    // 8바이트씩 읽기
    std::cout << "8bytes" << std::endl;
    readBinaryFileBySize(filename, 8);

    // 16바이트씩 읽기
    std::cout << "16bytes" << std::endl;
    readBinaryFileBySize(filename, 16);

    return 0;
}
