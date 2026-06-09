#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Problem: Given an array of integers and a target sum,
// return indices of two numbers that add up to target.
// Example: nums = [2,7,11,15], target = 9 -> output: [0,1]

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // value -> index

    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];

        if (seen.count(complement)) {
            return {seen[complement], i};
        }

        seen[nums[i]] = i;
    }

    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> result = twoSum(nums, target);
    cout << "Indices: [" << result[0] << ", " << result[1] << "]\n";

    // Test 2
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> result2 = twoSum(nums2, target2);
    cout << "Indices: [" << result2[0] << ", " << result2[1] << "]\n";

    return 0;
}