#include <iostream>
#include "word_counter.h"

int main() {
    // Create an instance of WordCounter
    WordCounter wordCounter;
    
    // Define a sample text for testing
    std::string filename = "text.txt";

    wordCounter.execute(filename);

    return 0;
}
