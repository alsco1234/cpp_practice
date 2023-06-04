#include <iostream>
#include <fstream>
#include <string>

using namespace std;

auto readBinaryFileBySize(const string& filename, int byteSize) -> int
{
    ifstream file(filename, ios::binary);

    if (!file) {
        cerr << "no file" << endl;
        return -1;
    }

    char* buffer = new char[byteSize];
    file.read(buffer, byteSize);
    
    int value = 0;
    for (int i = 0; i < byteSize; i++) {
        value = (value << 8) | static_cast<unsigned char>(buffer[i]);
    }

    delete[] buffer;
    file.close();

    return value;
}

int main() {
    string filename = "leaf.jpg";

    // 2 bytes
    int value2 = readBinaryFileBySize(filename, 2);
    cout << "2 bytes: " << hex << value2 << endl;

    // 4 bytes
    int value4 = readBinaryFileBySize(filename, 4);
    cout << "4 bytes: " << hex << value4 << endl;

    // 8 bytes
    int value8 = readBinaryFileBySize(filename, 8);
    cout << "8 bytes: " << hex << value8 << endl;

    // 16 bytes
    int value16 = readBinaryFileBySize(filename, 16);
    cout << "16 bytes: " << hex << value16 << endl;

    return 0;
}