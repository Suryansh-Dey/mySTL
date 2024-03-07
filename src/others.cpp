#include "../mySTL.hpp"
template <typename type>
void MyStl::print1D(type array1D)
{
    for (auto element : array1D)
        std::cout << element << ' ';
}
template <typename type>
void MyStl::print1D(type array1D, size_t size)
{
    for (size_t i = 0; i < size; i++)
        std::cout << array1D[i] << ' ';
}
std::pair<uint32_t, uint32_t> MyStl::firstDifferenceFile(const char *outputFilePath, const char *testFilePath)
{
    std::ifstream outputFile(outputFilePath), testFile(testFilePath);
    if (!outputFile.is_open())
        throw std::runtime_error("MyStl::firstDifferenceFile(const char *outputFilePath, const char *testFilePath) failed.\nNo file found of passed outputFilePath");
    if (!testFile.is_open())
        throw std::runtime_error("MyStl::firstDifferenceFile(const char *outputFilePath, const char *testFilePath) failed.\nNo file found of passed testFilePath");
    uint32_t lineNo = 0;
    std::string outputLine, testLine;
    bool outputEOF = false, testEOF = false;
    while (!testEOF && !outputEOF)
    {
        if (testLine.size() != outputLine.size() && (testLine.size() + 1 != outputLine.size() || outputLine[outputLine.size() - 1] >= '0'))
            return std::make_pair(lineNo + 1, outputLine.size());
        for (uint32_t colNo = 0; colNo < outputLine.size(); colNo++)
        {
            if (outputLine[colNo] != testLine[colNo] && colNo != outputLine.size() - 1 && outputLine[outputLine.size() - 1] >= '0')
                return std::make_pair(lineNo + 1, colNo + 1);
        }
        lineNo++;
        outputEOF = bool(getline(outputFile, outputLine));
        testEOF = bool(getline(testFile, testLine));
    }
    if (outputEOF || testEOF)
        return std::make_pair(lineNo, 0);
    return std::make_pair(0, 0);
}