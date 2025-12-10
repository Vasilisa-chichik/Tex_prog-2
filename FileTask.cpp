#include "FileTask.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

bool startsWithVowel(const std::string &word)
{
    if (word.empty())
        return false;

    // Только английские гласные
    std::string eng = "aeiouAEIOU";

    char first = word[0];

    return eng.find(first) != std::string::npos;
}

void printWordsStartingWithVowelFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Не удалось открыть файл: " << filename << "\n";
        return;
    }

    std::string word;
    while (file >> word)
    {
        if (static_cast<unsigned char>(word[0]) > 127)
            continue;

        if (startsWithVowel(word))
            std::cout << word << "\n";
    }
}
