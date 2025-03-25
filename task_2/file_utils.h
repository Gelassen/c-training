#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class FileUtils {

    public:
    
        std::string readFile(const std::string& filename) {
            std::stringstream ss;
            std::ifstream file(filename);  // Open the file
        
            if (!file.is_open()) {  // Check if the file was successfully opened
                std::cerr << "Error opening file: " << filename << std::endl;
                return "";
            }
        
            std::string line;
            while (std::getline(file, line)) {  // Read file line by line
                ss << line << std::endl;  // Output the line to the console
            }
        
            file.close();  // Close the file
        
            return ss.str();
        };
};

#endif