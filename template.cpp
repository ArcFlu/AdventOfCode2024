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

int main()
{
    std::ifstream input("sample.txt");
    // std::ifstream input("real.txt");

    std::string line;

    if (input.is_open())
    {
        while (std::getline(input, line))
        {
            std::cout << line << std::endl;
        }
    }
}
