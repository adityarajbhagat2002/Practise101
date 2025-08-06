https://leetcode.com/problems/max-consecslackutive-ones/description/


class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int prevcount =0;
        int maxcount=0;
        for(int i=0; i<nums.size();i++){

            if(nums[i]==1){
                prevcount++;
                maxcount=max(prevcount , maxcount);
            }else{
                prevcount=0;
            }
        }
        return max(maxcount , prevcount );

        
        
    }
};