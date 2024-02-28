#include "mySTL.hpp"
template <typename type>
void MyStl::printVector1D(std::vector<type> vect)
{
    for (type element : vect)
        std::cout << element << ' ';
}