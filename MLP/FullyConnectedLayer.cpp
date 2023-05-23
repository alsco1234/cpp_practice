#include <iostream>
#include <vector>

using namespace std;

class FullyConnectedLayer
{
    public:
        FullyConnectedLayer(int inputSize, int outputSize) : inputSize(inputSize), outputSize(outputSize)
        {

        }

        auto forward(vector<double>& input) -> vector<double>
        {   
            vector<double> output(outputSize, 0.0);
            return output;
        }

    private:
        vector<vector<double>> weights;
        vector<double> biases;
        int inputSize;
        int outputSize;

        auto sigmoid(double x) -> double
        {
            return 0;
        }
};

int main(int argv, char**argc)
{ 
    vector<double> input = {0.5, 0.3, 0.8};

    FullyConnectedLayer fcLayer(3, 2);

    vector<double> output = fcLayer.forward(input);

    vector<double> expected_output = {0.5, 0.5};
    assert(output == expected_output);

    return 0;
}