#include <iostream>
#include <vector>
#include <sstream>

/// <summary>
/// Get the last occurrence of a loop in a sequence of commands.
/// </summary>
/// <param name="commands"> Sequence of commands. Needs to be U | R | D | L</param>
/// <returns>A string with the command of the last loop</returns>
std::string getLastLoop(const std::string& commands)
{
    std::string valid_loop_a = "URDL";
    std::string valid_loop_b = "RDLU";
    std::string valid_loop_c = "DLUR";
    std::string valid_loop_d = "LURD";

    std::vector<std::pair<char, int>> converted;

    // convert UUDDDLLLUUUU into the following sequential pairs -> 2U | 3D | 3L | 4U
    for (int i = 0; i < commands.size(); i++)
    {
        // check if all letter are valid
        if (!(commands[i] == 'U' || commands[i] == 'R' || commands[i] == 'D' || commands[i] == 'L'))
        {
            return "Invalid input";
        }
        if (converted.empty() || converted.back().first != commands[i])
        {
            converted.push_back(std::make_pair(commands[i], 0));
        }
        converted.back().second++;
    }

    std::stringstream ss("A Loop does not exist in this sequency of commands");

    if (converted.size() < 4)
    {
        return ss.str();
    }

    std::string path = "";
    for (int i = 0; i < converted.size() - 3; i++)
    {
        if (converted[i].second >= converted[i + 2].second && converted[i + 3].second >= converted[i + 1].second)
        {
            // verify if the current 4 commands form a loop
            path = std::move(std::string() + converted[i].first + converted[i+1].first + converted[i+2].first + converted[i+3].first);
            if (path.compare(valid_loop_a) == 0|| path.compare(valid_loop_b) == 0 || path.compare(valid_loop_c) == 0 || path.compare(valid_loop_d) == 0)
            {
                ss.str("");
                ss.clear();
                ss << std::string(converted[i + 2].second, converted[i].first) << std::string(converted[i + 1].second, converted[i + 1].first)
                    << std::string(converted[i + 2].second, converted[i + 2].first) << std::string(converted[i + 1].second, converted[i + 3].first);
            }
        }
    }
    return ss.str();
}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Execute de software using as follow: X.exe Y\n Where:\n X : Name of the compiled software \n Y : Sequence of performed commands \n Y needs to be composed only of the characters URDL. All of then in uppercase." << std::endl;
    }
    else
    {
        std::cout << getLastLoop(std::string(argv[1]));
    }
    return 0;
}