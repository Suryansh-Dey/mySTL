#include "../mySTL.hpp"

template <typename type>
void MyStl::print1D(type array1D) noexcept
{
    for (auto element : array1D)
        std::cout << element << ' ';
    std::cout << '\n';
}
template <typename type>
void MyStl::print1D(type array1D, size_t size) noexcept
{
    for (size_t i = 0; i < size; i++)
        std::cout << array1D[i] << ' ';
    std::cout << '\n';
}
std::pair<uint32_t, uint32_t> MyStl::fileFirstDifference(const char *outputFilePath, const char *testFilePath)
{
    std::ifstream outputFile(outputFilePath), testFile(testFilePath);
    if (!outputFile.is_open())
        throw std::runtime_error("MyStl::firstDifferenceFile(const char *outputFilePath, const char *testFilePath) failed.\nNo file found of passed outputFilePath");
    if (!testFile.is_open())
        throw std::runtime_error("MyStl::firstDifferenceFile(const char *outputFilePath, const char *testFilePath) failed.\nNo file found of passed testFilePath");
    uint32_t lineNo = 0;
    std::string outputLine, testLine;
    while (not(testFile.eof() || outputFile.eof()))
    {
        std::getline(outputFile, outputLine);
        std::getline(testFile, testLine);
        if (outputLine[outputLine.size() - 1] == ' ')
            outputLine.pop_back();
        if (testLine.size() != outputLine.size())
            return std::make_pair(lineNo + 1, std::min(outputLine.size(), testLine.size()) + 1);
        for (uint32_t colNo = 0; colNo < outputLine.size() - 1; colNo++)
        {
            if (outputLine[colNo] != testLine[colNo])
                return std::make_pair(lineNo + 1, colNo + 1);
        }
        lineNo++;
    }
    if (!outputFile.eof())
    {
        std::getline(outputFile, outputLine);
        if (not(outputLine == "" || outputLine == " "))
            return std::make_pair(lineNo + 1, 0);
    }
    if (!testFile.eof())
        return std::make_pair(lineNo + 1, 0);
    return std::make_pair(0, 0);
}