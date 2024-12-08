#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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

bool isSafeReport(std::vector<int> arr, bool isSecondPass);

int main()
{
    // std::ifstream input("day2_sample.txt");
    std::ifstream input("day2_real.txt");

    std::string line;
    int safeReports = 0;

    if (input.is_open())
    {
        while (std::getline(input, line))
        {
            std::cout << line << std::endl;

            std::stringstream lineInput(line);
            std::vector<int> arr;
            std::string word;

            while (lineInput >> word)
            {
                arr.push_back(std::stoi(word));
            }

            printArray(arr);
            std::cout << (isSafeReport(arr, false) ? "safe" : "unsafe") << std::endl
                      << std::endl;

            if (isSafeReport(arr, false))
            {
                safeReports++;
            }
        }
    }

    std::cout << "Number of Safe Reports: " << safeReports << std::endl;
}

bool isSafeReport(std::vector<int> arr, bool isSecondPass)
{
    if (arr.size() < 2)
    {
        return true;
    }
    int i = 0;
    int j = 1;
    bool isIncreasing = false;
    bool isDecreasing = false;
    bool isSafeDiffer = false;
    do
    {
        if (arr[i] > arr[j])
            isIncreasing = true;
        if (arr[i] < arr[j])
            isDecreasing = true;
        isSafeDiffer = 1 <= abs(arr[i] - arr[j]) && abs(arr[i] - arr[j]) <= 3;

        i++;
        j++;
    } while (isIncreasing != isDecreasing && isSafeDiffer && j < arr.size());

    bool result1 = isIncreasing != isDecreasing && isSafeDiffer;

    // For Tomorrow: which element to remove depending on increase/decrease.
    // Given an array of [0, i, j, 9], I need to check whether
    // [0, i, 9] or [0, j, 9] is valid
    // omg... i just delete the element bruh
    if (!result1 && j < arr.size() && !isSecondPass)
    {
        // Remove value at index i from arr2
        std::vector<int> arr2;
        std::vector<int> arr3;

        arr2.reserve(arr.size() - 1);
        for (int idx = 0; idx < arr.size(); ++idx)
        {
            if (idx != i)
            {
                arr2.push_back(arr[idx]);
            }
        }

        // Remove value at index j from arr3
        arr3.reserve(arr.size() - 1);
        for (int idx = 0; idx < arr.size(); ++idx)
        {
            if (idx != j)
            {
                arr3.push_back(arr[idx]);
            }
        }

        bool result2 = isSafeReport(arr2, true);
        bool result3 = isSafeReport(arr3, true);
        return result2 || result3;
    }

    return result1;
}