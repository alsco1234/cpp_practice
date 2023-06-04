#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void readBinaryFileBySize(const string& filename, int byteSize) {
    ifstream file(filename, ios::binary);

    if (!file) {
        cerr << "no file" << endl;
        return;
    }

    char* buffer = new char[byteSize];
    file.read(buffer, byteSize);
    unsigned char value = buffer[0];
    cout << hex << setw(2) << setfill('0') << static_cast<unsigned int>(value) << " ";

    delete[] buffer;
    file.close();
}

int main() {
    string filename = "leaf.jpg";

    // 2바이트씩 읽기
    cout << "2bytes: " << endl;
    readBinaryFileBySize(filename, 2);

    // 4바이트씩 읽기
    cout << "4bytes: " << endl;
    readBinaryFileBySize(filename, 4);

    // 8바이트씩 읽기
    cout << "8bytes: " << endl;
    readBinaryFileBySize(filename, 8);

    // 16바이트씩 읽기
    cout << "16bytes: " << endl;
    readBinaryFileBySize(filename, 16);

    return 0;
}