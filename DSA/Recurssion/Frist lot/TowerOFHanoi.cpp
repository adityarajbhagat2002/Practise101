/*
===========================================================================================
TOWER OF HANOI - RECURSIVE STORY
===========================================================================================
Source: CodeStoryWithMIK (YouTube)
Complexity: Time O(2^n) | Space O(n)

-------------------------------------------------------------------------------------------
PROBLEM DESCRIPTION:
- 3 Rods: Source (From), Destination (To), Auxiliary (Aux).
- Goal: Move N disks from 'From' to 'To' using 'Aux'.
- Rules: 
    1. Only one disk can be moved at a time.
    2. A larger disk cannot be placed on a smaller disk.

-------------------------------------------------------------------------------------------
THE RECURSIVE STORY (Story to Code): [00:08:45]
1. Task 1: Move the top (n-1) disks from 'From' to 'Aux'.
   - We use 'To' as the helper rod for this sub-task.
2. Task 2: Move the remaining 1 largest disk (nth disk) from 'From' to 'To'.
   - This is 1 direct move.
3. Task 3: Move the (n-1) disks currently on 'Aux' to the final 'To' rod.
   - We use 'From' as the helper rod for this sub-task.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS: [00:19:30]
- Time Complexity: O(2^n)
    Recurrence Relation: T(n) = 2T(n-1) + 1
    This simplifies to 2^n - 1 total moves.
- Space Complexity: O(n)
    This is the Auxiliary Space used by the System Recursion Stack.
    The depth of the recursion tree is exactly 'n'.
===========================================================================================
*/

#include <iostream>
using namespace std;

class Solution {
public:
    // Parameters: n (disks), from (Source), to (Destination), aux (Helper)
    long long towerOfHanoi(int n, int from, int to, int aux) {
        // Base Case: If no disks are left to move [00:15:58]
        if (n == 0) {
            return 0;
        }

        // Base Case: If only 1 disk is left, move it directly [00:16:22]
        if (n == 1) {
            cout << "move disk " << n << " from rod " << from << " to rod " << to << endl;
            return 1;
        }

        long long moves = 0;

        // STEP 1: Move n-1 disks from 'from' to 'aux' using 'to' as helper [00:14:14]
        moves += towerOfHanoi(n - 1, from, aux, to);

        // STEP 2: Move the nth (largest) disk from 'from' to 'to' [00:14:41]
        cout << "move disk " << n << " from rod " << from << " to rod " << to << endl;
        moves += 1;

        // STEP 3: Move n-1 disks from 'aux' to 'to' using 'from' as helper [00:15:28]
        moves += towerOfHanoi(n - 1, aux, to, from);

        return moves;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN EXAMPLE (n=3):
1. Move 2 disks (1,2) from Source to Aux.
2. Move disk 3 from Source to Destination.
3. Move 2 disks (1,2) from Aux to Destination.
Total Moves: 2^3 - 1 = 7.
-------------------------------------------------------------------------------------------
*/