#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void printArray(std::vector<std::string> arr)
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

int main()
{
    std::ifstream input("day1_input.txt");
    std::string word;
    std::vector<std::string> arr1;
    std::vector<std::string> arr2;
    bool flag = true;

    if (input.is_open())
    {
        while (input >> word)
        {
            if (flag)
            {
                arr1.push_back(word);
                flag = !flag;
            }
            else
            {
                arr2.push_back(word);
                flag = !flag;
            }
        }
    }

    printArray(arr1);
    printArray(arr2);
}