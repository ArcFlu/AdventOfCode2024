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

bool isSafeReport(std::vector<int> arr);

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
                std::cout << word << std::endl;
            }

            printArray(arr);
            if (isSafeReport(arr))
            {
                std::cout << isSafeReport(arr);
                safeReports++;
            }
        }
    }

    std::cout << "Number of Safe Reports: " << safeReports << std::endl;
}

bool isSafeReport(std::vector<int> arr)
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

    return isIncreasing != isDecreasing && isSafeDiffer;
}