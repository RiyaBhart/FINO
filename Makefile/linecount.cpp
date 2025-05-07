#include "LineCount.h"
#include <fstream>
#include <string>

LineCount::LineCount() {}

int LineCount::countLines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return -1;

    std::string line;
    int count = 0;

    while (std::getline(file, line)) {
        count++;
    }

    return count;
}
