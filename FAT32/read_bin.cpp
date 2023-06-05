"""
[TODO]
1) little endian으로 읽기
2) class의 멤버변수로 ifstream 받기
3) output으로 적어서 저장하기
"""

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

auto readBinaryFileBySize(const string& filename, int byteSize) -> int
{
    ifstream file(filename, ios::binary);

    if (!file)
    {
        cerr << "no file" << endl;
        return -1;
    }

    char* buffer = new char[byteSize];

    file.seekg(0, ios::beg);
    file.read(buffer, byteSize);
    
    int value = 0;
    for (int i = 0; i < byteSize; i++)
        // 1바이트 left shiift해서 int에 저장
        value = (value << 8) | static_cast<unsigned char>(buffer[i]);

    delete[] buffer;
    file.close();

    return value;
}

int main() {
    string filename = "leaf.jpg";

    // 2 bytes
    int value2 = readBinaryFileBySize(filename, 2);
    cout << "2 bytes] hex : " << hex << value2 << " dec : " << dec << value2 << endl;
    // 4 bytes
    int value4 = readBinaryFileBySize(filename, 4);
    cout << "4 bytes] hex : " << hex << value4 << " dec : " << dec << value4 << endl;

    // 8 bytes
    int value8 = readBinaryFileBySize(filename, 8);
    cout << "8 bytes] hex : " << hex << value8 << " dec : " << dec << value8 << endl;

    // 16 bytes
    int value16 = readBinaryFileBySize(filename, 16);
    cout << "16 bytes] hex : " << hex << value16 << " dec : " << dec << value16 << endl;

    return 0;
}