#include <iostream>
#include <vector>

using namespace std;

class Backtrack{
    public:
        Backtrack(vector<int> nums, int target)
        {
            this->nums = nums;
            this->target = target;
        }

        auto findSubsets() -> vector<int>
        {
            vector<int> ans;

            return ans;
        }

    private:
    vector<int> nums;
    int target;


};

int main()
{
    vector<int> nums = {2, 4, 6, 8};
    int target = 10;
    
    Backtrack backtrack = Backtrack(nums, target);

    cout << "주어진 배열에서 합이 " << target << "이 되는 부분집합을 찾습니다." << endl;
    vector<int> res = {2, 8};
    assert(backtrack.findSubsets() == res);

    return 0;
}