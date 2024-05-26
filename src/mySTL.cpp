#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

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
        return "";
    return std::string_view(str.data() + index, str.size());
}
int main(int argc, char *argv[])
{
    std::vector<std::string> sourceContent;
    std::string destinationPath, line;
    // processing arguments
    if (argc <= 1)
        throw std::runtime_error("Too few arguments");
    else if (argc == 2)
    {
        if (argv[1][0] == '-')
        {
            std::string flag = std::string(argv[1] + 1);
            if (flag == "-version")
                std::cout << "This is mySTL version 1.0\n"
                          << "Author: Suryansh Dey\n"
                          << "This is free library;\n"
                          << "There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.";
            else if (flag == "-help")
                std::cout << "It removes first line of your code and adds the whole source code of mySTL library only.\n"
                          << "Arguments:\n- It takes two command line argument, your_source_file_path output_file_path\n- If only one argument of source_file_path provided, the default output_file_name is choosen to be MYSTL_source_file_name and stored at source_file_directory\n"
                          << "\nFor further help visit:\nhttps://github.com/suryansh-dey/mystl";
            else
                throw std::runtime_error("Flag " + flag + " is unrecognized");
            exit(0);
        }
        else
            destinationPath = std::string("mySTL_") + argv[1];
    }
    else if (argc == 3)
        destinationPath = argv[2];
    else
        throw std::runtime_error("Too many arguments");
    std::string basePath = std::filesystem::path(argv[0]).parent_path().parent_path().string() + '\\';
    // opening and checking files
    std::ifstream sourceFile((argv[1])), header(basePath + "mySTL.hpp");
    if (not header.is_open())
        throw std::runtime_error("Cannot find mySTL.hpp at expected path: " + basePath);
    if (not sourceFile.is_open())
        throw std::runtime_error("Cannot open source file of given path");
    std::getline(sourceFile, line);
    if (std::filesystem::equivalent(argv[1], destinationPath))
    {
        while (std::getline(sourceFile, line))
            sourceContent.emplace_back(line);
    }
    std::ofstream destinationFile(destinationPath);
    if (not destinationFile.is_open())
        throw std::runtime_error("Cannot open destination file of given path");
    // copying header ignoring comments
    std::getline(header, line);
    bool multilineComment = false;
    while (std::getline(header, line) && line != "// MYSTL_END")
    {
        std::string_view removedSpaces = removeLeadingWhiteSpace(line);
        if (!removedSpaces.size())
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
        std::getline(libFile, line);
        while (std::getline(libFile, line))
            destinationFile << line << '\n';
    }
    // copying source files
    if (not std::filesystem::equivalent(argv[1], destinationPath))
    {
        while (std::getline(sourceFile, line))
            destinationFile << line << '\n';
    }
    else
    {
        for (std::string &line : sourceContent)
            destinationFile << line << '\n';
    }
    return 0;
}