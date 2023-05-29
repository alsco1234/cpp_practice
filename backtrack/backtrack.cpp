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
            vector<int> subset;
            vector<int> ans = backtrack(subset, 0, 0);
            return ans;
        }

    private:
        vector<int> nums;
        int target;

        auto backtrack(vector<int>& subset, int start, int sum) -> vector<int>
        {
            if (sum == target) {
                return subset;
            }

            // start 포인트부터 시작
            for (int i = start; i < nums.size(); i++) {
                if (sum + nums[i] <= target) {
                    subset.push_back(nums[i]);
                    return backtrack(subset, i + 1, sum + nums[i]);
                    subset.pop_back();
                }
            }
        }   
};


int main()
{
    vector<int> nums = {2, 4, 6, 8};
    int target = 10;

    Backtrack backtrack(nums, target);

    cout << "주어진 배열에서 합이 " << target << "이 되는 부분집합을 찾습니다." << endl;
    vector<int> res = {2, 8};
    assert(backtrack.findSubsets() == res);

    return 0;
}