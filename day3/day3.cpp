#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

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

std::vector<int> splitString(const std::string &str, char delimiter)
{
    std::vector<int> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        result.push_back(std::stoi(token));
    }

    return result;
}

void calcSumGivenMulStrings(std::vector<std::string> matches)
{
    // Parse matches and calculate sum
    int sum = 0;
    for (auto s : matches)
    {
        std::vector<int> intSplit = splitString(s.erase(0, s.find('(') + 1), ',');
        sum += intSplit[0] * intSplit[1];
    }

    std::cout << sum;
};

int main()
{
    // std::ifstream input("sample.txt");
    std::ifstream input("real.txt");

    std::string fileString;

    if (input.is_open())
    {
        std::stringstream buffer;
        buffer << input.rdbuf();
        fileString = buffer.str();
        // std::cout << fileString;

        // Approach: Use regex to find expressions in form mul(\d,\d)
        std::regex regularExpression("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");
        std::vector<std::string> matches;

        std::regex_iterator<std::string::iterator> it(fileString.begin(), fileString.end(), regularExpression);
        std::regex_iterator<std::string::iterator> end;

        while (it != end)
        {
            std::string match = it->str();
            matches.push_back(match);
            std::cout << match << std::endl;
            ++it;
        }

        // get rid of Dos and Donts
        bool doFlag = true;
        std::string doString = "do()";
        std::string dontString = "don't()";

        std::vector<std::string> mulMatches;

        for (int i = 0; i < matches.size(); i++)
        {
            std::string string = matches[i];

            if (string == doString)
            {
                doFlag = true;
                continue;
            }
            else if (string == dontString)
            {
                doFlag = false;
                continue;
            }

            if (doFlag)
            {
                mulMatches.push_back(string);
            }
        }

        calcSumGivenMulStrings(mulMatches);
    }
}
