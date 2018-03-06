#pragma once

#include <vector>
#include <ostream>
#include <iostream>
#include <string>
#include <cctype>

class StringValue
{
public:
    StringValue();
    StringValue(const std::string& value);
    StringValue(const StringValue& other);    // copy constructor
    StringValue(StringValue&& other);    // move constructor
    ~StringValue();

    // overloads
    StringValue& operator=(const StringValue& other);
    StringValue& operator=(StringValue&& other);
    StringValue operator+(const StringValue& other);
    StringValue& operator+=(const StringValue& other);
    StringValue operator-(const StringValue& other);
    StringValue& operator-=(const StringValue& other);
    StringValue operator*(const StringValue& other);
    StringValue& operator*=(const StringValue& other);
    bool operator<(const StringValue& other);
    bool operator>(const StringValue& other);
    bool operator<=(const StringValue& other);
    bool operator>=(const StringValue& other);
    bool operator==(const StringValue& other);

    friend std::ostream& operator<<(std::ostream& stream, const StringValue& value)
    {
        stream << value.GetValue();
        return stream;
    }

    // Getters
    const std::string& GetValue() const;
    inline int GetSize() const;
    int GetDigit(unsigned int index) const;

private:
    StringValue Add(const StringValue& other);
    StringValue Subtract(const StringValue& other);
    StringValue Multiply(const StringValue& other);
    StringValue Divide(const StringValue& other);

    void SetValue(const std::string& value);
    int Max(int value1, int value2);

private:
    std::string m_value;
    std::vector<char> m_charVec;
 
};

