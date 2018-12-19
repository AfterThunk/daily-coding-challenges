/**
 * This problem was recently asked by Google.
 * 
 * Given a list of numbers and a number k, return whether any two numbers from the list add up to k.
 * For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
 * 
 * Bonus: Can you do this in one pass? 
 * 
 * Compilation instructions:
 *  `clang -lstdc++ -o SumInList SumInList.cpp`
 */

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <cstdio>

// This may not actually be true in certain systems / architectures.
// But, barring an actual platform framework, it'll be OK for shorthand.
using int64 = long long int;
using int32 = int;

static void DumpVector(const std::vector<int64>& List)
{
    std::cout << "{";
    if (List.size() > 0)
    {
        printf("%lli", List[0]);

        for (int32 i = 1; i < List.size(); ++i)
        {
            printf(", %lli", List[i]);
        }
    }
    std::cout << "}";
}

static const bool SumInList(const std::vector<int64>& List, const int64 DesiredSum)
{
    /**
     * Pretty straightforward answer here.
     * Loop over every element in the list, and add it to every other element.
     * If we find a match, we're done.
     * 
     * We care about *combinations* and not *permutations* (i.e., order doesn't matter).
     * Therefore, if we check List[0] + List[1], then we don't need to check List[1] + List[0].
     * We also don't need to check an element against itself.
     * 
     * This is why we loop Outer = 0 ~ N - 1 and Outer + 1 ~ N.
     * 
     * As for complexity...
     * The outer loop will iterate a total of 9 times (N - 1).
     * On the first iteration, the inner loop will loop 9 times (1 ~ N)
     * On the second iteration, the inner loop will loop 8 times (2 ~ N)
     * On the third iteration, the inner loop will loop 7 times (3 ~ N)
     * And so on until we hit the last iteration where the inner loop will loop 1 time (N~N).
     * So, the number of loops is effectively the Sum of Numbers between 1 and N - 1.
     * The formula of the sum of numbers between 1 and X is (X*(X+1)) / 2, and so:
     * 
     * = O(((N-1)*(N-1+1))/2) = O(((N-1)*N))/2) = O((N^2 - N)/2) = O(N^2)
     * 
     * Complexity = Complexity(Outer Loop) * Complexity(Inner Loop)
     *              = O(N - 1) * O(Sum(1 ... N-1))
     *              = O(N - 1) * O((N^2 + N)/2)
     *              = O(N - 1) * O(N^2 + N) *
     */ 
    const int32 ListSize = List.size();
    for (int32 Outer = 0; Outer < ListSize - 1; ++Outer)
    {
        for (int32 Inner = Outer + 1; Inner < ListSize; ++Inner)
        {
            if (DesiredSum == List[Inner] + List[Outer])
            {
                std::cout << "(List[" << Inner << "] = " << List[Inner] << ") + (List[" << Outer << "] = " << List[Outer] << ") = " << List[Inner] + List[Outer] << std::endl;
                return true;
            }
        }
    }

    return false;
}

static const bool SumInList_Bonus(const std::vector<int64>& List, const int64 DesiredSum)
{
    /**
     * First sort the list, and then work our way in from the front and the back until we find a match.
     * 
     * Given that the list is in ascending order:
     * Increasing the index of either i or j would mean either the sum stays the same or increases.
     * Decreasing the index of either i or j would mean either the sum stays the same or decreases.
     * 
     * We will limit incrementing to i (starts at 0) and decrementing to j (starts at N - 1, where N = number of elements).
     * In that way, any time we adjust either i or j, we will never consider elements outside of the bounds i < x < j again,
     * and therefore we can conceptually think of this as removing those elements from the list.
     * 
     * TODO: Write a proof that shows this works :).
     *      The gist of the proof would likely hinge on 3 cases:
     *          1. Min(List) <= DesiredSum <= Max(List).
     *              In this case, we'd keep popping elements off of the end of the list until:
     *                  a. i == j
     *                      Would happen if all elements were the same, or if Min(List) <= DesiredSum <= NextMin(List).
     * 
     *                  b. Min(List) <= Max(List) <= DesiredSum.
     *                      Devolves into case 3 (see below).
     *                      Note, that case handles the terminal case.
     * 
     *          2. DesiredSum <= Min(List) <= Max(List).
     *              In this case, we'd keep popping elements off of the start of the list until:
     *                  a. i == j
     *                      See logic for 1.a.
     * 
     *                  b. Min(List) <= Max(List) <= DesiredSum.
     *                      See logic for 1.b.
     * 
     * Complexity = Complexity(Sort) + Complexity(Iteration) = O(N log (N)) + O(N) = O(N log (N))
     * 
     * Note, the assumption is made that the *best* case complexity for a sort is O(N log (N)).
     * This is generally accepted as true, and there are entropy theories that dictate sorts *can't* be
     * better than this.
     */
    if (List.size() <= 1)
    {
        return false;
    }

    int32 i = 0;
    int32 j = List.size() - 1;
    int32 Sum = 0;

    // We could just assert that the input list is sorted and avoid copying.
    std::vector<int64> MyList = List;
    std::sort(MyList.begin(), MyList.end());

    while (true)
    {
        if (i == j)
        {
            return false;
        }

        Sum = MyList[i] + MyList[j];
        if (DesiredSum == Sum)
        {
            return true;
        }
        else if (DesiredSum > Sum)
        {
            ++i;
        }
        else
        {
            --j;
        }
    }


    return false;
}

static void DisplayCase(const std::vector<int64>& List, const int64 DesiredSum)
{
    const bool bSumInListResult = SumInList(List, DesiredSum);
    const bool bSumInListBonusResult = SumInList_Bonus(List, DesiredSum);

    std::cout << "List = ";
    DumpVector(List);
    std::cout << std::endl;
    std::cout << "Desired Sum = " << DesiredSum << std::endl;
    std::cout << "SumInList = " << bSumInListResult << std::endl;
    std::cout << "SumInList_Bonus = " << bSumInListBonusResult << std::endl;

    if (bSumInListResult != bSumInListBonusResult)
    {
        std::cerr << "Inconsistent Results!" << std::endl;
    }
}

int main(int32 argc, char* argv[])
{
    {
        std::vector<int64> List = {10, 15, 3, 7};
        for (int32 i = 0; i < 40; ++i)
        {
            DisplayCase(List, i);
        }
    }

    {
        std::vector<int64> List = {-1, -2, -10, -3, -20};
        for (int32 i = -40; i < 0; ++i)
        {
            DisplayCase(List, i);
        }
    }

    {
        std::vector<int64> List = {};
        DisplayCase(List, 0);
    }

    {
        std::vector<int64> List = {1,2,3,4,5,10,20,30,40,50,80,99};
        for (int32 i = 0; i < 200; ++i)
        {
            DisplayCase(List, i);
        }
    }

    return 0;
}