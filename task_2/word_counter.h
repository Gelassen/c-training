#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "file_utils.h"

class WordCounter {

    public:
        
        void execute(std::string filename);

        void reset() {
            m_fileName = "";
            m_countedWords.clear();
        };

    private:

        std::string m_fileName;
        std::map<std::string, int> m_countedWords;

        void countWord(std::string text);

        std::vector<std::string> splitOnTokens(std::string text);

        void printResults();

    };

#endif