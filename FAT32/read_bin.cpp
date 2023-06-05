/*
[TODO]
1) 시작위치 받기
2) class의 멤버변수로 ifstream 받기
2) output으로 적어서 저장하기
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

auto readBinaryFileBySize(const string& filename, const int& byteSize) -> long int
{
    ifstream file(filename, ios::binary);

    if (!file.is_open())
    {
        cerr << "no file" << endl;
        return -1;
    }

    unsigned char * buffer = (unsigned char*)malloc(byteSize);

    // 포인터 처음으로 이동
    file.seekg(0, ios::beg);
    // bytesize만큼 읽기
    file.read((char*)buffer, byteSize*2);

    long int value = 0;
    for (int i = 0; i < byteSize; ++i){
        /* 
        little endian으로 읽기 
            1) 각각 unsigned char로 변환하고
            2) 8칸 left shift : 앞으로 옮기고 뒤에는 0됨
            3) or 연산을 통해 다음 값이 뒤에 들어가게 됨
        즉, 첫 번째 바이트가 가장 낮은 자리, 마지막 바이트가 가장 높은 자리
        */
        value = ((value << 8) | buffer[i]);
        cout << i << "th value is " << hex << value << endl;
    }

    delete[] buffer;
    file.close();

    return value;
}

int main() {
    string filename = "leaf.jpg";

    // 1 bytes
    long int value1 = readBinaryFileBySize(filename, 1);
    cout << "1 bytes] hex : " <<  value1 << " dec : " << dec << value1 << endl << endl;

    // 2 bytes
    long int value2 = readBinaryFileBySize(filename, 2);
    cout << "2 bytes] hex : " << hex << value2 << " dec : " << dec << value2 << endl << endl;

    // 4 bytes
    long int value4 = readBinaryFileBySize(filename, 4);
    cout << "4 bytes] hex : " << hex << value4 << " dec : " << dec << value4 << endl << endl;

    // 8 bytes
    long int value8 = readBinaryFileBySize(filename, 8);
    cout << "8 bytes] hex : " << hex << value8 << " dec : " << dec << value8 << endl;

    return 0;
}