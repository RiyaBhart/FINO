#ifndef LINECOUNT_H
#define LINECOUNT_H

#include <string>

class LineCount {
public:
    LineCount();
    int countLines(const std::string& filename);
};

#endif

