#include <iostream>
#include <vector>
#include "mlp.cpp"

using namespace std;

int main(int argc, char**argv){
    MLP mlp;
    std::vector<double> input;
    input.push_back(1.0);
    input.push_back(2.0);
    input.push_back(3.0);
    assert(mlp.train(input) == true);

    return 0;
}