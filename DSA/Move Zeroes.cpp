https://leetcode.com/problems/move-zeroes/description/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int lastnonzeroindex=0;

        for(int i=0; i< nums.size();i++){
            if(nums[i] != 0 ){
                swap(nums[lastnonzeroindex++] , nums[i])
            }
        }
        
    }
};







