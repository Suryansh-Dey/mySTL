#include "../mySTL.hpp"

MyStl::BitArray::BitArray(uint32_t size) noexcept : size(size), bits(size / elementSize + size % elementSize != 0)
{
}
void MyStl::BitArray::set(uint32_t index)
{
    this->bits[index / elementSize] |= 1ULL << (index % elementSize);
}
void MyStl::BitArray::unset(uint32_t index)
{
    this->bits[index / elementSize] &= ~(1ULL << (index % elementSize));
}
bool MyStl::BitArray::get(uint32_t index)
{
    return this->bits[index / elementSize] & (1ULL << (index % elementSize));
}
void MyStl::BitArray::operator|=(BitArray &bitArray) noexcept
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] |= bitArray.bits[elementNo];
}
void MyStl::BitArray::operator&=(BitArray &bitArray) noexcept
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] &= bitArray.bits[elementNo];
}
void MyStl::BitArray::operator^=(BitArray &bitArray) noexcept
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] ^= bitArray.bits[elementNo];
}
void MyStl::BitArray::bitwiseNot() noexcept
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size(); elementNo++)
        this->bits[elementNo] = ~(this->bits[elementNo]);
}
MyStl::BitArray MyStl::BitArray::operator~() const noexcept
{
    BitArray bitArray = *this;
    for (uint32_t elementNo = 0; elementNo < bitArray.bits.size(); elementNo++)
        bitArray.bits[elementNo] = ~(bitArray.bits[elementNo]);
    return bitArray;
}
void MyStl::BitArray::print() const noexcept
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size(); elementNo++)
    {
        for (uint32_t bitNo = 0; bitNo < elementSize && bitNo + elementSize * elementNo < this->getSize(); bitNo++)
        {
            if (bitNo == 8)
                printf(" ");
            printf("%c ", bool(this->bits[elementNo] & (1ULL << bitNo)));
        }
    }
}
uint32_t MyStl::BitArray::getSize() const noexcept
{
    return this->size;
}