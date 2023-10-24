// wc.cpp : Defines the entry point for the application.

#include <filesystem>
#include <string> 
#include <fstream>
#include <vector> 

#include "wc.h"

using namespace std;
namespace fs = std::filesystem;

string readFile(fs::path path)
{
	ifstream file(path, std::ios::in | std::ios::binary);
	const auto sz = fs::file_size(path);
	string result(sz, '\0');
	file.read(result.data(), sz);
	return result; 
}

// Note only works for ascii characters
// need to add support for utf-8 locales and windows 
int main(int argc, char** argv)
{
	uint8_t bitFlag = 0; 
	bool flagExist = false; 
	vector<fs::path> inputFiles; 
	if(argc <= 1)
	{
		cout << "Error no arguments given\n" << endl;
		return -1; 
	}
	else 
	{
		for(int i = 1; i < argc; i++)
		{
			if(string(argv[i]) == "-c")
			{
				bitFlag |= 0x01;
				continue;
			}
			else if(string(argv[i]) == "-l")
			{
				bitFlag |= 0x01 << 1;
				continue;

			}
			else if(string(argv[i]) == "-w")
			{
				bitFlag |= 0x01 << 2;
				continue;
			}
			else if(string(argv[i]) == "-m")
			{
				bitFlag |= 0x01 << 3;
				continue;
			}
			inputFiles.push_back(fs::path(string(argv[i])));
		}
	}

	FileProperties fileProperties;
	for(auto filePath : inputFiles)
	{
		//auto filePath = fs::path(file);
		if(fs::exists(filePath))
		{
			fileProperties.readFile(filePath);
		}
		else 
		{
			cout << "Error: " << filePath.string() << " does not exist" << endl;
			exit(-1); 
		}
	}
	uint64_t totalLine = 0;
	uint64_t totalChar = 0;
	uint64_t totalByte = 0;
	uint64_t totalWord = 0;
	for(auto input : inputFiles)
	{
		if(bitFlag & 0x01)
		{
			auto tmp = fileProperties.getByteCount(input);
			std::cout << tmp << " " << input.string() << std::endl;
			totalByte += tmp;
		}
		else if(bitFlag & (0x01 << 1))
		{
			auto tmp = fileProperties.getLineCount(input);
			std::cout << tmp << " " << input.string() << std::endl;
			totalLine += tmp;
		}
		else if(bitFlag & (0x01 << 2))
		{
			auto tmp = fileProperties.getWordCount(input);
			std::cout << tmp << " " << input.string() << std::endl;
			totalWord += tmp;
		}
		else if(bitFlag & (0x01 << 3))
		{
			auto tmp = fileProperties.getCharCount(input);
			std::cout << tmp << " " << input.string() << std::endl;
			totalChar += tmp;
		}
		else 
		{
			std::cout << fileProperties.getLineCount(input) << " " << fileProperties.getWordCount(input) << " " << fileProperties.getByteCount(input) << " " << input.string() << std::endl;

			totalByte += fileProperties.getByteCount(input);
			totalChar += fileProperties.getCharCount(input);
			totalLine += fileProperties.getLineCount(input);
			totalWord += fileProperties.getWordCount(input);	
		}
	}
	if(inputFiles.size() > 1)
	{
		if(bitFlag & 0x01)
		{
			std::cout << totalByte << " total" << std::endl;
		}
		else if(bitFlag & (0x01 << 1))
		{
			std::cout << totalLine << " total" << std::endl;
		}
		else if(bitFlag & (0x01 << 2))
		{
			std::cout << totalWord << " total" << std::endl;
		}
		else if(bitFlag & (0x01 << 3))
		{
			std::cout << totalChar << " total" << std::endl;
		}
		else 
		{
			std::cout << totalLine << " " << totalWord << " " << totalByte << " total" << std::endl;
		}
	}



	return 0;
}
