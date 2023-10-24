#pragma once 

#include <fstream> 
#include <iostream>
#include <string> 
#include <filesystem>
#include <unordered_map> 

namespace fs = std::filesystem;

class FileProperties
{
    public: 
        explicit FileProperties(){
             std::locale::global(std::locale("C"));
        }; 
        void readFile(fs::path path);
        uint32_t getWordCount(fs::path path);
        uint32_t getLineCount(fs::path path);
        uint32_t getCharCount(fs::path path);
        uint32_t getByteCount(fs::path path);
        
    private: 
        uint32_t countLine(std::ifstream& fs); 
        uint32_t countWord(std::ifstream& fs);
        uint32_t countChar(std::ifstream& fs);
        uint32_t countByte(std::ifstream& fs);

        std::unordered_map<std::string, uint32_t> wordCount;
        std::unordered_map<std::string, uint32_t> lineCount;
        std::unordered_map<std::string, uint32_t> charCount;
        std::unordered_map<std::string, uint32_t> byteCount;
};
