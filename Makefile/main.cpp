#include <iostream>
#include "LetterCount.h"
#include "WordCount.h"
#include "LineCount.h"

int main() {
    std::string filename = "test.txt"; // Make sure this file exists

    LetterCount letterCounter;
    WordCount wordCounter;
    LineCount lineCounter;

    int letters = letterCounter.countLetters(filename);
    int words = wordCounter.countWords(filename);
    int lines = lineCounter.countLines(filename);

    if (letters == -1 || words == -1 || lines == -1) {
        std::cerr << "Error: Could not open the file.\n";
        return 1;
    }

    std::cout << "Letters: " << letters << std::endl;
    std::cout << "Words: " << words << std::endl;
    std::cout << "Lines: " << lines << std::endl;

    return 0;
}
