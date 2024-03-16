#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector <int> threesum(vector<int> nums, int  target) {
    //check the value is empty
    int left = 0;
    int right = 0;
    int i = 0, k=0;
    int prev;
    int threeSum = 0;
    vector<int> result;

    sort (nums.begin(), nums.end());
    for (i=0; i<nums.size(); i++) {

        if ((i >0) &&  nums[i] == nums[i-1]) {
            continue;
        }
        left = i;
        right = nums.size()-1;
        while (left<right) {
            threeSum = nums[i] + nums[left] + nums[right];
            if (threeSum > target) {
                right -=1;
            } else if (threeSum < target) {
                left +=1;
            } else {
                result.push_back(nums[i]);
                result.push_back(nums[left]);
                result.push_back(nums[right]);
                left +=1;
                while(nums[left] == nums[left -1] && left <right) {
                    left +=1;
                }
            }
        }

        // cout << nums[i] << " ";

    }
    cout <<endl;
    return result;

}

int main() {

    vector<int> nums;
    vector <int> result;
    nums.push_back(0);
    nums.push_back(1);
    nums.push_back(-1);
    result = threesum(nums, 0);
    for (auto & it: result) {

        cout << it << " ";

    }
    cout << endl;
    
    nums.clear();
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(0);
    result = threesum(nums, 0);
    for (auto & it: result) {

        cout << it << " ";

    }
    cout << endl;
    return 0;
}
