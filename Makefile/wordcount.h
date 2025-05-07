#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <string>

class WordCount {
public:
    WordCount();
    int countWords(const std::string& filename);
};

#endif
