#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>  // 소수점 자릿수 조정을 위한 헤더 추가

using namespace std;

class FullyConnectedLayer
{
    public:
        FullyConnectedLayer(int inputSize, int outputSize)
        {
            // 테스트 위한 임시 생성된 weight
            weights = {{0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}};
            biases = {0.7, 0.8};
        }

        auto forward(vector<double>& input, int outputSize) -> vector<double>
        {   
            vector<double> output(outputSize);

            for(int i = 0; i < outputSize; i++)
            {
                double cur_output = 0.0;
                for(int j = 0; j < input.size(); j++)
                    cur_output += input[j] * weights[i][j];
                output[i] = sigmoid(cur_output + biases[i]);

            }

            return output;
        }

    private:
        vector<vector<double>> weights;
        vector<double> biases;

        auto sigmoid(double x) -> double
        {   
            return 1.0 / (1.0 + exp(-x));
        }
};

int main(int argv, char**argc)
{ 
    vector<double> input = {0.5, 0.3, 0.8};
    int outputSize = 2;

    FullyConnectedLayer fcLayer(input.size(), outputSize);

    vector<double> output = fcLayer.forward(input, outputSize);

    vector<double> expected_output = {0.740775, 0.83617};

    // 부동소숫점으로 인해 오찻값 0.000001범위 내에서 테스트
    for(int i = 0; i<output.size(); i++)
        assert(abs(output[i] - expected_output[i]) < 0.000001);

    return 0;
}