// 2017-10-29
#include <iostream> 
#include <vector>
#include <unordered_map>
#include <algorithm> 

using namespace std;

vector<int> twoSum(vector<int>& nums, int target);

int main() {
    vector<int> nums = {3,2,4};
    auto twoSumResult = twoSum(nums, 6);
    cout << twoSumResult[0] << " " << twoSumResult[1] << endl;

    return 0;
}

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> num2i;
    vector<int> indices;
    for(int i = 0; i < nums.size(); i++)
    {
        auto complement = num2i.find(target-nums[i]);
        if(complement != num2i.end())
        {
            indices.push_back((*complement).second);
            indices.push_back(i);
            return indices;
        }

        num2i[nums[i]] = i;        
    }

    return indices;
}