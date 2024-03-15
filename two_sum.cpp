#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;

vector<int> twosum (vector<int> & nums, int target) {
    unordered_map <int, int> hash;
    for (int i=0; i<nums.size(); i++) {
        int complement = target - nums[i];
        if (hash.count(complement)) {
            return {hash[i], i};
        }
        hash[nums[i]] = complement;
    }
    return {};
}

int main() {
    vector <int> nums;
    vector <int> result;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(15);

    result= twosum(nums, 11);
    for (const int &i: result) {
        cout << "results "<< i << endl;
    }
    return 0;
}
