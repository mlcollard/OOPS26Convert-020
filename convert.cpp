/*
    convert.cpp

    Convert text with various conversions. E.g.,
        convert --upper "abcdefg"
*/

#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <cctype>
#include <unordered_map>

typedef void(*Convert)(char& c);

// convert to upper case
// @concerns std::toupper(), toUpper[out]
void toUpper(char& c) {
    c = std::toupper(c);
}

// convert to lower case
// @concerns std::tolower(), toLower[out]
void toLower(char& c) {
    c = std::tolower(c);
}

// map from option to the conversion function
const std::unordered_map<std::string_view, Convert> optionConversion{
    { "--upper", [](char& c) { c = std::toupper(c); } },
    { "--lower", [](char& c) { c = std::tolower(c); } },
};

int main(int argc, char* argv[]) {

    // requires conversion option and string
    // @concerns input format, argc, argv, error handling, std::cerr
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " <option> <string>\n";
        return 1;
    }

    // chosen options
    // @concerns input format, argv, std::string_view, option[out]
    std::string_view option(argv[1]);

    // text to convert
    // @concerns input format, argv, std::string, text[out]
    std::string text(argv[2]);

    // convert the string according to the option
    // @concerns "--upper", "--lower"
    // @concerns toUpper(), toLower()
    // @concerns error handling, std::cerr, option, conversion[out]
    Convert conversion = nullptr;
    if (option == "--upper") {

        conversion = toUpper;

    } else if (option == "--lower") {

        conversion = toLower;

    } else {

        std::cerr << "Invalid conversion option: " << option << '\n';
        return 1;
    }

    // convert using the current conversion
    // @concerns text, conversion, std::for_each
    std::for_each(text.begin(), text.end(), conversion);

    // output converted text
    // @concerns output format, text, iteration, std::cout
    for (auto pc = text.cbegin(); pc != text.cend(); ++pc)
        std::cout << *pc;
    std::cout << '\n';

    return 0;
}
