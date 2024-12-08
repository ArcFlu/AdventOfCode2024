#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>

void printArray(std::vector<int> arr)
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        oss << arr[i];
        if (i != arr.size() - 1)
            oss << ", ";
    }
    oss << "]";

    std::cout << oss.str();
    std::cout << "\n";
}

// My failed attempt at implementing quicksort
// Segfaults and infinite loops === bruh moment
// void quickSort(std::vector<int> partitionArr, int leftPointer, int rightPointer)
// {
//     if (partitionArr.size() <= 1)
//         return;

//     int pivot = (partitionArr.size()) / 2;

//     while (leftPointer <= rightPointer)
//     {
//         while (partitionArr[leftPointer] < partitionArr[pivot] && leftPointer < partitionArr.size() - 1)
//         {
//             leftPointer++;
//         }
//         while (partitionArr[rightPointer] > partitionArr[pivot] && rightPointer > 0)
//         {
//             rightPointer--;
//         }
//         int temp = partitionArr[leftPointer];
//         partitionArr[leftPointer] = partitionArr[rightPointer];
//         partitionArr[rightPointer] = temp;
//     }

//     quickSort(partitionArr, 0, rightPointer);
//     quickSort(partitionArr, leftPointer, partitionArr.size() - 1);
//     return;
// };

// chatgpt to the rescue
void quickSort(std::vector<int> &partitionArr, int leftPointer, int rightPointer)
{
    if (leftPointer >= rightPointer)
    {
        return; // Base case: subarray of 1 or 0 elements
    }

    // Select the pivot as the middle element
    int pivotIndex = leftPointer + (rightPointer - leftPointer) / 2;
    int pivotValue = partitionArr[pivotIndex];

    // Partitioning
    int i = leftPointer;
    int j = rightPointer;

    while (i <= j)
    {
        // Move i to the right until an element larger than the pivot is found
        while (partitionArr[i] < pivotValue)
        {
            i++;
        }
        // Move j to the left until an element smaller than the pivot is found
        while (partitionArr[j] > pivotValue)
        {
            j--;
        }
        // Swap elements and adjust pointers
        if (i <= j)
        {
            std::swap(partitionArr[i], partitionArr[j]);
            i++;
            j--;
        }
    }

    // Recursively sort left and right subarrays
    quickSort(partitionArr, leftPointer, j);
    quickSort(partitionArr, i, rightPointer);
}

int main()
{
    std::ifstream input("day1_real.txt");
    // std::ifstream input("day1_input.txt");
    std::string word;
    std::vector<int> arr1;
    std::vector<int> arr2;
    bool flag = true;

    if (input.is_open())
    {
        while (input >> word)
        {
            if (flag)
            {
                arr1.push_back(std::stoi(word));
                flag = !flag;
            }
            else
            {
                arr2.push_back(std::stoi(word));
                flag = !flag;
            }
        }
    }

    quickSort(arr1, 0, arr1.size() - 1);
    printArray(arr1);
    quickSort(arr2, 0, arr2.size() - 1);
    printArray(arr2);

    // Calculate distances
    int sum = 0;
    for (int i = 0; i < arr1.size(); i++)
    {
        sum += abs(arr1[i] - arr2[i]);
    }

    std::cout << "Sum: " << sum << "\n";

    // Calculate similarities
    std::map<int, int> mapOfArr2;

    for (int value : arr2)
    {
        mapOfArr2[value]++; // Increment count for the value
    }

    int part2Sum = 0;
    for (int i : arr1)
    {
        int product = mapOfArr2[i] * i;
        std::cout << "Product: " << product << " ";
        part2Sum += product;
    }
    std::cout << "\nPart2Sum: " << part2Sum << "\n";
}