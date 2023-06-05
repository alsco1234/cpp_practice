/*
[TODO]
1) class의 멤버변수로 ifstream 받기
2) output으로 적어서 저장하기
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

auto readBinaryFileBySize(const string& filename, const int& byteSize) -> int
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
    
    cout << hex << buffer[0] << endl;

    int value = 0;
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
    int value1 = readBinaryFileBySize(filename, 1);
    cout << "1 bytes] hex : " <<  value1 << " dec : " << dec << value1 << endl;
    // 2 bytes
    int value2 = readBinaryFileBySize(filename, 2);
    cout << "2 bytes] hex : " << hex << value2 << " dec : " << dec << value2 << endl;

    // 4 bytes
    int value4 = readBinaryFileBySize(filename, 4);
    cout << "4 bytes] hex : " << hex << value4 << " dec : " << dec << value4 << endl;

    // 8 bytes
    int value8 = readBinaryFileBySize(filename, 8);
    cout << "8 bytes] hex : " << hex << value8 << " dec : " << dec << value8 << endl;

    return 0;
}

/* 
FF D8 FF E1 01 B6 45 78 69 66 00 00 4D 4D 00 2A 이 있을때

1) FF를 읽으려면
FF

2) FF D8 읽으려면
D8 먼저읽고, 그다음 FF읽기
D8FF를 변환하기

3) FF D8 FF 읽으려면
FF 먼저읽고, 그다음 D8읽고, FF읽기
FFD8FF를 변환하기

4) FF D8 FF E1 읽려면
E1 먼저읽고, 그다음 FF읽고, D8읽고, FF읽기

...
    0  1  2  .. n-1
N) FF D8 .. 읽으려면
buffer[0] = [n-1]byte
buffer[1] = [n-2]byte
...
buffer[n-1] = [0]byte

==

for(int i=0; i<buffer_size)
*/