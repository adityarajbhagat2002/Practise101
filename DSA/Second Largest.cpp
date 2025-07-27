https://www.geeksforgeeks.org/problems/second-largest3735/1

class Solution {
  public:
    int getSecondLargest(vector<int> &arr) {
        int maxnum=INT_MIN;
        int secondmax=INT_MIN;
        
        for(int i=0; i<arr.size(); i++){
             
        if(arr[i]>maxnum){
            
            secondmax =maxnum;
            maxnum=arr[i];
        
        }
        else if(arr[i]>secondmax && arr[i]!=maxnum)
        secondmax = arr[i];
       
        }
            
        return (secondmax== INT_MAX) ? -1 : secondmax;
        

    }
};