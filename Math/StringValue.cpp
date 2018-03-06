#include "stdafx.h"
#include "StringValue.h"
#include <assert.h>

StringValue::StringValue()
    : m_value("0")
{
    m_charVec.push_back('0');
}

StringValue::StringValue(const std::string& value)
    : m_value(value), m_charVec(value.begin(), value.end())
{
}

StringValue::StringValue(const StringValue& other)
    : m_value(other.m_value), m_charVec(other.m_charVec)
{
}

StringValue::StringValue(StringValue&& other)
    : m_value(std::move(other.m_value)), m_charVec(std::move(other.m_charVec))
{
}

StringValue::~StringValue()
{
}

StringValue& StringValue::operator=(const StringValue& other)
{
    if (this != &other)
    {
        m_value = other.m_value;
        m_charVec = other.m_charVec;
    }
    return *this;
}

StringValue& StringValue::operator=(StringValue&& other)
{
    if (this != &other)
    {
        this->m_charVec = std::move(other.m_charVec);
        this->m_value = std::move(other.m_value);
    }
    return *this;
}

StringValue StringValue::operator+(const StringValue& other)
{
    return Add(other);
}

StringValue& StringValue::operator+=(const StringValue& other)
{
    *this = *this + other;
    return *this;
}

StringValue StringValue::operator-(const StringValue& other)
{
    return Subtract(other);
}

StringValue& StringValue::operator-=(const StringValue& other)
{
    *this = *this - other;
    return *this;
}

StringValue StringValue::operator*(const StringValue& other)
{
    return Multiply(other);
}

StringValue & StringValue::operator*=(const StringValue & other)
{
    *this = *this * other;
    return *this;
}

bool StringValue::operator<(const StringValue& other)
{
    if (GetSize() < other.GetSize())
    {
        return true;
    }
    else if (GetSize() > other.GetSize())
    {
        return false;
    }
    else
    {
        // equal size.. check each digit
        int index = GetSize() - 1;
        for (int i = index; i >= 0; i--)
        {
            int digit1 = GetDigit(i);
            int digit2 = other.GetDigit(i);
            if (digit1 < digit2)
                return true;
            else if (digit1 > digit2)
                return false;
        }
    }
    
    return false;
}

bool StringValue::operator>(const StringValue& other)
{
    if (GetSize() > other.GetSize())
    {
        return true;
    }
    else if (GetSize() < other.GetSize())
    {
        return false;
    }
    else
    {
        // equal size.. check each digit
        int index = GetSize() - 1;
        for (int i = index; i >= 0; i--)
        {
            int digit1 = GetDigit(i);
            int digit2 = other.GetDigit(i);
            if (digit1 > digit2)
                return true;
            else if (digit1 < digit2)
                return false;
        }
    }

    return false;
}

bool StringValue::operator<=(const StringValue& other)
{
    return ((*this) < other) || ((*this) == other);
}

bool StringValue::operator>=(const StringValue& other)
{
    return ((*this) > other) || ((*this) == other);
}

bool StringValue::operator==(const StringValue& other)
{
    return (m_value == other.m_value);
}

const std::string& StringValue::GetValue() const
{
    return m_value;
}

inline int StringValue::GetSize() const
{
    return m_charVec.size();
}

StringValue StringValue::Add(const StringValue& other)
{
    std::string sum = "";
    int length = Max(GetSize(), other.GetSize());

    int carry = 0;
    for (int i = 0; i < length; i++)
    {
        int digit1 = GetDigit(i);
        int digit2 = other.GetDigit(i);

        int digitSum = digit1 + digit2 + carry;
        carry = (digitSum / 10) % 10;
        char newDigit = '0' + (digitSum % 10);
        sum += newDigit;
    }

    if (carry != 0)
        sum += '0' + carry;

    std::reverse(sum.begin(), sum.end());

    return StringValue(sum);
}

StringValue StringValue::Subtract(const StringValue& other)
{
    // this assumes first digit is greater..
    // maybe later will fix and change implementation
    std::string difference = "";
    //assert(GetSize() > other.GetSize());
    int length = Max(GetSize(), other.GetSize());

    int carry = 0;
    for (int i = 0; i < length; i++)
    {
        int digit1 = GetDigit(i) - carry;
        int digit2 = other.GetDigit(i);

        // borrow from next digit..
        carry = (digit1 < digit2) ? 1 : 0;

        int digitDiff = (digit1 + 10 * carry) - digit2;
        char newDigit = '0' + (digitDiff % 10);
        difference += newDigit;
    }

    difference.erase(difference.find_last_not_of('0') + 1, std::string::npos);

    std::reverse(difference.begin(), difference.end());

    return StringValue(difference);
}

StringValue StringValue::Multiply(const StringValue& other)
{
    int length = Max(GetSize(), other.GetSize());
    std::vector<StringValue> summations;
    summations.reserve(length);

    int numberOfAppendedZeroes = 0;
    for (int i = 0; i < GetSize(); i++)
    {
        int digit1 = GetDigit(i);
        std::string product = "";
        int carry = 0;
        for (int j = 0; j < other.GetSize(); j++)
        {
            int digit2 = other.GetDigit(j);
            int digitProduct = (digit1 * digit2) + carry;
            carry = (digitProduct / 10) % 10;
            char newDigit = '0' + (digitProduct % 10);
            product += newDigit;
        }

        if (carry != 0)
            product += '0' + carry;

        std::reverse(product.begin(), product.end());
        product.append(numberOfAppendedZeroes, '0');
        summations.emplace_back(std::move(product));

        numberOfAppendedZeroes++;
    }

    // add up all the summations
    StringValue result("0");
    for (const StringValue& sum : summations)
    {
        result += sum;
    }

    return result;
}

StringValue StringValue::Divide(const StringValue& other)
{

    return StringValue();
}

int StringValue::GetDigit(unsigned int index) const
{
    if (m_charVec.empty() || index > m_charVec.size())
        return 0;

    // index starts at end..
    auto digitIter = std::next(m_charVec.rbegin(), index);
    if (digitIter == m_charVec.rend())
        return 0;

    if (!std::isdigit(*digitIter))
        return 0;

    return *digitIter - '0';
}

void StringValue::SetValue(const std::string& value)
{
    m_value = value;
    m_charVec = std::vector<char>(value.begin(), value.end());
}

int StringValue::Max(int value1, int value2)
{
    if (value1 > value2)
        return value1;
    return value2;
}
