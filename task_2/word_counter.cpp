#include "word_counter.h"

void WordCounter::execute(std::string filename) {
    m_fileName = filename;

    FileUtils fileUtils;
    std::string text = fileUtils.readFile(filename);
    
    this->countWord(text);

    this->printResults();
}

void WordCounter::countWord(std::string text) {
    std::vector<std::string> tokens = this->splitOnTokens(text);

    for (auto& word : tokens) {
        m_countedWords[word]++; 
    }
}

std::vector<std::string> WordCounter::splitOnTokens(std::string text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    char delimeter = ' ';
    std::string token;

    while (std::getline(ss, token, delimeter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void WordCounter::printResults() {
    for (auto& item : this->m_countedWords) {
        std::cout << item.first << " " << item.second << "\n";
    }
}