#include <stdexcept>
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
int main(int argc, char *argv[])
{
    if (argc != 3)
        throw std::runtime_error("Can take only two argument");
    unsigned int nameLength = strlen(argv[0]);
    for (unsigned int i = nameLength; i >= 1; i--)
    {
        if (argv[0][i - 1] == '\\' or argv[0][i - 1] == '/')
        {
            argv[0][i] = '\0';
            break;
        }
    }
    std::string basePath = argv[0];

    std::ifstream sourceFile((argv[1])), header(basePath + "mySTL.hpp"), others(basePath + "src/others.cpp"), bitArray(basePath + "src/bitArray.cpp"), graph(basePath + "src/graph.cpp");
    if (not(header.is_open() && others.is_open() && bitArray.is_open() && graph.is_open()))
        throw std::runtime_error("Files of mySTL library is missing from expected location");
    if (not sourceFile.is_open())
        throw std::runtime_error("Cannot open source file of given path");
    std::ofstream destinationFile(argv[2]);
    if (not destinationFile.is_open())
        throw std::runtime_error("Cannot open destination file of given path");

    std::string line;
    while (std::getline(header, line) && line != "//lib files")
    {
        destinationFile << line;
        destinationFile << "\n";
    }
    std::getline(others, line);
    while (std::getline(others, line))
    {
        destinationFile << line;
        destinationFile << "\n";
    }
    std::getline(bitArray, line);
    while (std::getline(bitArray, line))
    {
        destinationFile << line;
        destinationFile << "\n";
    }
    std::getline(graph, line);
    while (std::getline(graph, line))
    {
        destinationFile << line;
        destinationFile << "\n";
    }
    std::getline(sourceFile, line);
    while (std::getline(sourceFile, line))
    {
        destinationFile << line;
        destinationFile << "\n";
    }
    return 0;
}