https://leetcode.com/problems/sort-characters-by-frequency/description/

/*
===========================================================================================
SORT CHARACTERS BY FREQUENCY - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 451 / CodeStoryWithMIK (YouTube)
Companies: Google, Amazon, Oracle, Zoho

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Given a string `s`, sort it in decreasing order based on the frequency of the characters.
The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.

Example:
Input:  s = "tree"
Output: "eert" (or "eetr")
Explanation: 'e' appears twice, 'r' and 't' both appear once. 
             So 'e' must appear before 'r' and 't'.

-------------------------------------------------------------------------------------------
APPROACH: Frequency Counting & Custom Sorting
Logic:
1. We need to store both the character and its frequency.
2. Since characters are ASCII, we can use a vector of pairs of size 123 (to cover 'z' which is 122).
3. First, iterate through the string to count the frequency of each character.
   - We use `vec[ch]` to store the pair `{character, frequency}`.
4. Use a custom comparator (Lambda function) to sort the vector in descending order 
   based on the frequency (`p1.second > p2.second`).
5. After sorting, iterate through the sorted vector. For each character with frequency > 0, 
   append it to the result string as many times as its frequency.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
Sorting by Freq  | O(N + K log K)  | O(K)             | N = length of string.
                                                        K = Number of unique chars (fixed).
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Typedef for cleaner pair usage
    typedef pair<char, int> P;

    string frequencySort(string s) {
        // Size 123 covers all common ASCII characters including 'z' (122)
        vector<P> vec(123);

        // Step 1: Count frequency and store char information
        for(char &ch : s){
            int freq = vec[ch].second;
            vec[ch] = {ch, freq + 1};
        }

        // Step 2: Custom sorting lambda for descending order of frequency
        auto lamda = [&](P &p1, P &p2){
            return p1.second > p2.second;
        };
        
        sort(vec.begin(), vec.end(), lamda);

        // Step 3: Build the result string
        string result = "";
        for(int i = 0; i <= 122; i++){
            if(vec[i].second > 0){
                char ch = vec[i].first;
                int freq = vec[i].second;
                // Append character 'ch', 'freq' times
                string temp = string(freq, ch);
                result += temp;
            }
        }

        return result;
    }
};

/*

There is other solution too with priorityqueue
-------------------------------------------------------------------------------------------
DRY RUN:
Input: s = "raae"

1. Frequency Counting:
   'r': 1, 'a': 2, 'e': 1
   vec[97] = {'a', 2}, vec[114] = {'r', 1}, vec[101] = {'e', 1}

2. After Sorting (Lambda):
   Index 0: {'a', 2}
   Index 1: {'r', 1}  (Order of 'r' and 'e' could vary)
   Index 2: {'e', 1}

3. Building String:
   i=0: result += "aa"
   i=1: result += "r"
   i=2: result += "e"

Final Output: "aare"
-------------------------------------------------------------------------------------------
*/