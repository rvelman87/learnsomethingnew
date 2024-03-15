#include<iostream>
#include<vector>
#include<map>
#include<unordered_set>
using namespace std;

bool ContainsDuplicate (vector<int> & nums) {
    unordered_set <int> Set;
    for (int i=0; i<nums.size(); i++) {
        if (Set.count(nums[i])) {
            return true;
        }
        Set.insert(nums[i]);
    }
    return false;
}

int main() {
    vector <int> nums;
    bool result;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
 
    result = ContainsDuplicate (nums);
    cout << "results "<< result << endl;
    //clear the vector 
    nums.clear();
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(1);
    

    result = ContainsDuplicate (nums);
    cout << "results "<< result << endl;
    
    return 0;
}
