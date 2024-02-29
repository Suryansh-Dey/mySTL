#include "../mySTL.hpp"
using namespace MyStl;
BitArray::BitArray(uint32_t size) : size(size), bits(size / elementSize + size % elementSize != 0)
{
}
void BitArray::set(uint32_t index)
{
    this->bits[index / elementSize] |= 1ULL << (index % elementSize);
}
void BitArray::unset(uint32_t index)
{
    this->bits[index / elementSize] &= ~(1ULL << (index % elementSize));
}
bool BitArray::get(uint32_t index)
{
    return this->bits[index / elementSize] & (1ULL << (index % elementSize));
}
void BitArray::operator|=(BitArray &bitArray)
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] |= bitArray.bits[elementNo];
}
void BitArray::operator&=(BitArray &bitArray)
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] &= bitArray.bits[elementNo];
}
void BitArray::operator^=(BitArray &bitArray)
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] ^= bitArray.bits[elementNo];
}
void BitArray::bitwiseNot()
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size(); elementNo++)
        this->bits[elementNo] = ~(this->bits[elementNo]);
}
BitArray BitArray::operator~() const
{
    BitArray bitArray = *this;
    for (uint32_t elementNo = 0; elementNo < bitArray.bits.size(); elementNo++)
        bitArray.bits[elementNo] = ~(bitArray.bits[elementNo]);
    return bitArray;
}
void BitArray::print() const
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size(); elementNo++)
    {
        for (uint32_t bitNo = 0; bitNo < elementSize && bitNo + elementSize * elementNo < this->getSize(); bitNo++)
        {
            if (bitNo == 8)
                std::cout << ' ';
            std::cout << bool(this->bits[elementNo] & (1ULL << bitNo));
        }
    }
}
uint32_t BitArray::getSize() const
{
    return this->size;
}