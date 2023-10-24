#include <sstream>
#include <iostream>
#include <algorithm>
#include "FileProperties.h"


namespace fs = std::filesystem;
uint32_t FileProperties::countLine(std::ifstream& fs)
{
    if(fs.is_open() == false)
    {
        std::cout << "Error opening file\n"; 
    }
    fs.seekg(0, std::ios::beg);
    uint32_t numLine = std::count(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>(), '\n');
    fs.clear(); 
    return numLine;
}

uint32_t FileProperties::countChar(std::ifstream& fs)
{
    if(fs.is_open() == false)
    {
        std::cout << "Error opening file\n"; 
    }
    fs.seekg(0, std::ios::beg);
    int numChar = 0;
    char c; 
    uint32_t rCount = 0;
    uint32_t nCount = 0;
    if(fs.is_open())
    {
        while(fs.get(c))
        {
            if (c == '\r')
            {
                rCount++;
            }
            else if(c == '\n')
            {
                nCount++;
            }
            else if(c == EOF)
            {
                break; 
            }
            numChar++;
        }
    }
    fs.clear(); 
    return numChar; 
}
uint32_t FileProperties::countWord(std::ifstream& fs)
{
    if(fs.is_open() == false)
    {
        std::cout << "Error opening file\n"; 
    }
    int numWord = 0; 
    fs.seekg(0, std::ios::beg);
    std::string line;
    while(std::getline(fs, line))
    {
        std::stringstream ss(line);
        std::string word;
        while(ss >> word)
        {
            numWord++;
        }
    }
    fs.clear(); 
    return numWord;
}
uint32_t FileProperties::countByte(std::ifstream& fs)
{
    int numByte = 0;
    fs.seekg(0, std::ios::beg);
    fs.seekg(0, std::ios::end);
    numByte = fs.tellg();
    fs.clear(); 
    return numByte;

}
void FileProperties::readFile(fs::path path)
{
    int numLine = 0;
    int numWord = 0; 
    int numChar = 0; 
    int numByte = 0;
    std::string line; 
    std::string pathString = path.string();
    
    std::ifstream fs(path, std::ios::binary);
    numChar = countChar(fs);
    numByte = countByte(fs);
    numLine = countLine(fs);
    numWord = countWord(fs);
    fs.close(); 
    byteCount[pathString] = numByte;
    wordCount[pathString] = numWord;
    lineCount[pathString] = numLine;
    charCount[pathString] = numChar;    
}


uint32_t FileProperties::getWordCount(fs::path path)
{
    std::string pathString = path.string();
    return wordCount[pathString]; 
}

uint32_t FileProperties::getLineCount(fs::path path)
{
    std::string pathString = path.string();
    return lineCount[pathString]; 
}

uint32_t FileProperties::getCharCount(fs::path path)
{
    std::string pathString = path.string();
    return charCount[pathString]; 
}
uint32_t FileProperties::getByteCount(fs::path path)
{
    std::string pathString = path.string();
    return byteCount[pathString]; 
}

