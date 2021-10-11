#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <queue>

/// <summary>
/// Contains the worlds to be used in the conversion of a given value in to words
/// Exception words: cem
/// Key = number
/// Value = number written in words
/// </summary>
std::unordered_map<int, std::string> Dictionary = {
    {1, "um"}, {2, "dois"}, {3, "tres"}, {4, "quatro"}, {5, "cinco"}, {6, "seis"}, {7, "sete"}, {8, "oito"}, {9, "nove"},
    {10, "dez"}, {11, "onze"}, {12, "doze"}, {13, "treze"}, {14, "quatorze"}, {15, "quinze"}, {16, "dezesseis"}, {17, "dezesete"}, {18, "dezoito"}, {19, "dezenove"},
    {20, "vinte"}, {30, "trinta"}, {40, "quarenta"}, {50, "cinquenta"}, {60, "sessenta"}, {70, "setenta"}, {80, "oitenta"}, {90, "noventa"},
    {100, "cento"}, {200, "duzentos"}, {300, "trezentos"}, {400, "quatrocentos"}, {500, "quinhentos"}, {600, "seiscentos"}, {700, "setecentos"}, {800, "oitocentos"}, {900, "novecentos"}
};

/// <summary>
/// Contains the words to be used to scale a given value. It's not define plural or singular.
/// Key = number of scale
/// Value = The scale written in words
/// </summary>
std::unordered_map<int, std::string> Scale = {
    {1, ""}, {2, "mil "}, {3, "milh"}, {4, "bilh"}
};

/// <summary>
/// Adds to a stringstream the conversion of a given value into words and also append the specific scale to it
/// </summary>
/// <param name="value">Value to be converted into words</param>
/// <param name="scale">Scale to be added at the end of the conversion</param>
/// <param name="ss">A StringStream reference which the conversion will be added</param>
void convert(const int& value, const std::string& scale, std::stringstream* ss)
{
    if (value == 0)
    {
        return;
    }

    if (value == 100)
    {
        *ss << "cem";
    }
    else
    {
        int remainder = value % 100;
        int hundred = value - remainder;
        if (hundred > 0)
        {
            *ss << Dictionary[hundred] << ((remainder == 0) ? "" : " e ");
        }

        if (1 <= remainder && remainder <= 19)
        {
            *ss << Dictionary[remainder];
        }
        else if (remainder > 19)
        {
            int unity = remainder % 10;
            int ten = remainder - unity;
            if (ten > 9)
            {
                *ss << Dictionary[ten];
            }
            if (unity > 0)
            {
                *ss << " e " << Dictionary[unity];
            }
        }
    }
    *ss << " " << scale;
}

/// <summary>
/// Put into a queue each group of three digits from right to left.
/// </summary>
/// <param name="value">The value to be grouped</param>
/// <returns>The queue that contains the grouped numbers</returns>
std::queue<int> GroupDigitsOfValueIntoQueue(const int& value)
{
    std::queue<int> q;
    std::string s_value(std::to_string(value));
    int unity = 0;
    int sum = 0;
    int key = 0;

    for (auto it = s_value.rbegin(); it != s_value.rend(); ++it)
    {
        unity = (int)((*it) - 48); // In ASCII code, numbers start from 48
        switch (++key)
        {
            case 1:
                sum += unity;
                break;
            case 2:
                sum += (unity * 10);
                break;
            default:
                sum += (unity * 100);
                key = 0;
                q.push(sum);
                sum = 0;
                break;
        }
    }
    if (key > 0)
    {
        q.push(sum);
    }
    return q;
}

/// <summary>
/// Builds a string that contains the amount of cents in words.
/// </summary>
/// <param name="cents">The amount of cents</param>
/// <returns>the amount of cents in words</returns>
std::string DefineCents(const int& cents)
{
    switch (cents)
    {
        case 0:
            return "";
        case 1:
            return "um centavo";
        default:
            std::stringstream ss;
            convert(cents, "centavos", &ss);
            return ss.str();
    }
}

/// <summary>
/// Builds a string that contains the amount of reais in words
/// </summary>
/// <param name="reais">The amount of reais</param>
/// <param name="cents">The amount of cents</param>
/// <returns>the amount of reais in words</returns>
std::string DefineReais(const int& reais, const int& cents)
{
    std::queue<int> q = GroupDigitsOfValueIntoQueue(reais);
    std::string result;
    std::string prefix = "";
    std::stringstream ss;
    int key = 1, current_value;


    if (!q.empty())
    {
        if (reais == 1)
        {
            ss << "real";
        }
        else if (reais % 1000000 == 0)
        {
            ss << "de reais";
        }
        else
        {
            ss << "reais";
        }
        ss << ((cents == 0) ? "" : " e ") << result;
        result = std::move(ss.str());
    }

    while (!q.empty())
    {
        ss.str("");
        ss.clear();
        current_value = q.front();
        q.pop();

        if (key > 2)
        {
            prefix = std::move((current_value == 1) ? "ao " : "oes ");
        }

        if (key == 2 && current_value == 1)
        {
            ss << Scale[key];
        }
        else
        {
            convert(current_value, Scale[key] + prefix, &ss);
        }
        ss << result;
        result = std::move(((!q.empty() && current_value > 0) ? "e " : "") + ss.str());
        key++;
    }
    return result;
}

/// <summary>
/// Convert and print the amount of reais and cents into words. To better understanding I have subdiveded this method and haven't treated the accentuation
/// </summary>
/// <param name="reais">The amount of reais</param>
/// <param name="cents">The amount of cents</param>
void convertAmount2Words(const int& reais, const int& cents)
{
    std::string r = DefineReais(reais, cents) + DefineCents(cents);
    r[0] = std::move(toupper(r[0]));
    std::cout << r << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Execute de software using as follow: X.exe Y Z\n Where:\n X : Name of the compiled software \n Y : Reais amount \n Z : Cents amount\n Y and Z needs to be number";
    }
    else
    {
        convertAmount2Words(atoi(argv[1]), atoi(argv[2]));
    }
    return 0;
}