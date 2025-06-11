https://www.geeksforgeeks.org/problems/union-of-two-sorted-arrays-1587115621/1

class Solution {
  public:
    // a,b : the arrays
    // Function to return a list containing the union of the two arrays.
    vector<int> findUnion(vector<int> &a, vector<int> &b) {
        int i = 0, j = 0;
    int n = a.size(), m = b.size();
    vector<int> result;

    while (i < n && j < m) {
        int val;
        if (a[i] < b[j]) val = a[i++];
        else if (a[i] > b[j]) val = b[j++];
        else val = a[i], i++, j++;

        if (result.empty() || result.back() != val)
            result.push_back(val);
    }

    while (i < n) {
        if (result.empty() || result.back() != a[i])
            result.push_back(a[i]);
        i++;
    }

    while (j < m) {
        if (result.empty() || result.back() != b[j])
            result.push_back(b[j]);
        j++;
    }

    return result;
        
    }
};