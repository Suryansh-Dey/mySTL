#include "../mySTL.hpp"
using namespace MyStl;
BitArray::BitArray(uint32_t size) : size(size), bits(size / elementSize + size % elementSize != 0)
{
}
void BitArray::set(uint32_t index)
{
    this->bits[index / elementSize] |= 1UL << (index % elementSize);
}
BitArray BitArray::operator|=(BitArray bitArray)
{
    for (uint32_t elementNo = 0; elementNo < bits.size(); elementNo++)
        this->bits[elementNo] |= bitArray.bits[elementNo];
    return *this;
}
void BitArray::print() const
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size(); elementNo++)
    {
        for (uint32_t bitNo = 0; bitNo < elementSize && bitNo + elementSize * elementNo < this->getSize(); bitNo++)
        {
            if(bitNo == 8)
                std::cout << ' ';
            std::cout << bool(this->bits[elementNo] & (1UL << bitNo));
        }
    }
}
uint32_t BitArray::getSize() const
{
    return this->size;
}