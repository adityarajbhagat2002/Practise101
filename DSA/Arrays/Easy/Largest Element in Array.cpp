class Solution {
  public:
    int largest(vector<int> &arr) {
        int maxnum = INT_MIN;
        
        for(int i=0;i<arr.size();i++){
            if(arr[i]>maxnum){
                maxnum=arr[i];
            }
            
        }
        
        return maxnum;
        
    }
};


