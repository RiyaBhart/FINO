#include "WordCount.h"
#include <fstream>
#include <string>

WordCount::WordCount() {}

int WordCount::countWords(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return -1;

    std::string word;
    int count = 0;

    while (file >> word) {
        count++;
    }

    return count;
}
