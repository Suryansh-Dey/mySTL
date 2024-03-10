#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <filesystem>
#include <regex>
std::vector<std::string> getFilenamesInDirectory(const std::string &directoryPath)
{
    std::vector<std::string> filenames;
    for (const auto &entry : std::filesystem::directory_iterator(directoryPath))
    {
        if (std::filesystem::is_regular_file(entry.path()))
        {
            std::string filename = entry.path().filename().string();
            if (filename != "mySTL.cpp")
                filenames.push_back(filename);
        }
    }
    return filenames;
}
std::string_view removeLeadingWhiteSpace(const std::string &str)
{
    size_t index = str.find_first_not_of(" \t\n\r\f\v");
    if (index == std::string::npos)
    {
        return "";
    }
    return std::string_view(str.data()+index, str.size());
}
int main(int argc, char *argv[])
{
    // processing arguments
    std::string destinationPath;
    if (argc <= 1)
        throw std::runtime_error("Too few arguments");
    else if (argc == 2)
        destinationPath = std::string("mySTL_") + argv[1];
    else if (argc == 3)
        destinationPath = argv[2];
    else
        throw std::runtime_error("Too many arguments");
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
    // opening and checking files
    std::ifstream sourceFile((argv[1])), header(basePath + "mySTL.hpp");
    if (not header.is_open())
        throw std::runtime_error("Cannot find mySTL.hpp at expected path");
    if (not sourceFile.is_open())
        throw std::runtime_error("Cannot open source file of given path");
    std::ofstream destinationFile(destinationPath);
    if (not destinationFile.is_open())
        throw std::runtime_error("Cannot open destination file of given path");
    // copying header ignoring comments
    std::string line;
    std::getline(header, line);
    bool multilineComment = false;
    while (std::getline(header, line) && line != "// MYSTL_END")
    {
        std::string_view removedSpaces = removeLeadingWhiteSpace(line);
        if (removedSpaces == "")
            continue;
        if (multilineComment)
        {
            if (removedSpaces[0] == '*' && removedSpaces[1] == '/')
                multilineComment = false;
            continue;
        }
        else if (removedSpaces[0] == '/')
        {
            if (removedSpaces[1] == '/')
                continue;
            else if (removedSpaces[1] == '*')
            {
                multilineComment = true;
                continue;
            }
        }
        destinationFile << line << '\n';
    }
    // copying lib files
    std::vector<std::string> libFiles = getFilenamesInDirectory(basePath + "src");
    for (std::string libFileName : libFiles)
    {
        std::ifstream libFile(basePath + "src\\" + libFileName);
        if (not libFile.is_open())
            throw std::runtime_error("Cannot find " + libFileName + " at expected path");
        std::getline(libFile, line);
        while (std::getline(libFile, line))
            destinationFile << line << '\n';
    }
    // copying source files
    std::getline(sourceFile, line);
    while (std::getline(sourceFile, line))
        destinationFile << line << '\n';
    return 0;
}