class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
    for(auto i = nums.begin(); i < nums.end(); ++i) {
        if(val == *i) {
            nums.erase(i);
            i = nums.begin();
        }
    }

    if(nums.empty()) {
        return nums.size();
    }

    if(*(nums.begin()) == val) {
        nums.erase(nums.begin());
    }

    return nums.size();
}
};
