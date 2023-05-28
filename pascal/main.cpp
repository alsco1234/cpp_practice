#include <iostream>
#include <vector>

using namespace std;

class Pascal {
public:
    Pascal(int len)
    {   
        this->nums = len;
        this->triangle = vector<vector<int>>(len, vector<int>(len, 0));

        for (int i = 0; i < nums; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    triangle[i][j] = 1;
                } else {
                    triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
                }
            }
        }
    }

    void printPascal() 
    {
        for (int i = 0; i < nums; i++) {
            for (int j = 0; j <= i; j++) {
                cout << triangle[i][j] << " ";
            }
            cout << endl;
        }
    }

private:
    int nums;
    vector<vector<int>> triangle;
};

int main(int argc, char** argv) {
    Pascal pascal(atoi(argv[1]));

    pascal.printPascal();

    return 0;
}