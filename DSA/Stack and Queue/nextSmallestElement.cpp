//Same logic as the next greated  eleemt

class Solution {
public:
    vector<int> nextSmallerEle(vector<int>& arr) {

        int n = arr.size(); 
        // n stores number of elements in array

        stack<int> st;      
        // stack to keep potential next smaller elements
        // it will store elements in increasing order from bottom to top

        vector<int> ans(n); 
        // result array of size n to store NSE for each index

        // Traverse array from right to left
        // because NSE must be on the right side
        for(int i = n-1; i >= 0; i--){

            // Remove all elements from stack that are
            // greater than or equal to current element
            // because they cannot be the next smaller element
            while(!st.empty() && st.top() >= arr[i]){
                st.pop();
            }

            // If stack becomes empty, no smaller element exists on right
            if(st.empty()){
                ans[i] = -1;
            }
            // Otherwise, the top of stack is the next smaller element
            else{
                ans[i] = st.top();
            }

            // Push current element to stack
            // so it can act as NSE for elements on the left
            st.push(arr[i]);
        }

        // Return the result vector
        return ans;
    }
};
