/**
 * 
 * Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.
 * 
 * For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24].
 * If our input was [3, 2, 1], the expected output would be [2, 3, 6].
 * 
 * Follow-up: what if you can't use division?
 */

#include <vector>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <cstring>

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

std::vector<int64> ProductArray(const std::vector<int64> InArray)
{
    /**
     * Iterate over all elements, and multiply them to get the total product.
     * Then, iterate over all the elements again, dividing that element out.
     * 
     * Complexity is O(N).
     */
    std::vector<int64> OutArray = InArray;

    if (OutArray.size() == 0)
    {
        return OutArray;
    }

    std::vector<int64> FoundZeros;
    int64 TotalProduct = 1;
    for (int32 i = 0; i < OutArray.size(); ++i)
    {
        if (OutArray[i] == 0)
        {
            FoundZeros.push_back(i);

            if (FoundZeros.size() > 1)
            {
                break;
            }
        }
        else
        {
            TotalProduct *= OutArray[i];
        }
    }

    if (FoundZeros.size() >= 1)
    {
        // First, set everything to zero.
        memset(OutArray.data(), 0, sizeof(int64) * OutArray.size());

        // If there's only one zero element, then it will be the only element
        // that is non zero (because we exclude it from the product).
        if (FoundZeros.size() == 0)
        {
            OutArray[FoundZeros[0]] = TotalProduct;
        }
    }
    else
    {
        for (int64& Elem : OutArray)
        {
            Elem = TotalProduct / Elem;
        }
    }

    return OutArray;
}

std::vector<int64> ProductArray_NoDivision_Brute(const std::vector<int64>& InArray)
{
    std::vector<int64> OutArray(1, InArray.size());

    for (int32 i = 0; i < OutArray.size(); ++i)
    {
        for (int32 j = 0; j < OutArray.size(); ++j)
        {
            if (i != j)
            {
                OutArray[i] *= InArray[j];
            }
        }
    }

    return OutArray;
}