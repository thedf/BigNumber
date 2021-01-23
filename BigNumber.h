#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class BigNumber
{
private:
    string numberInString;
    int sign = 1;

public:
    BigNumber();
    BigNumber(string number);
    BigNumber(int number);
    ~BigNumber();

    string getString()
    {
        if (sign == -1)
            return "-" + numberInString;
        else
            return numberInString;
    };
    BigNumber add(BigNumber other);
    BigNumber sous(BigNumber other);
    BigNumber multiply(BigNumber other);
    BigNumber shift(int numberOfZeros);

    bool equals(const BigNumber &other);
    int getSign() { return sign; };
    BigNumber addMod(const BigNumber &other, BigNumber &modNumber);
    BigNumber sousMod(const BigNumber &other, BigNumber &modNumber);
    BigNumber multiMod(const BigNumber &other, BigNumber &modNumber);
    BigNumber inverteSign()
    {
        this->sign = -this->sign;
        return *this;
    };
    int size() { return numberInString.size(); };
    friend bool operator==(BigNumber first, const BigNumber &other);
    friend bool operator>(BigNumber first, const BigNumber &other);
    friend bool operator<(BigNumber first, const BigNumber &other);
    friend bool operator>=(BigNumber first, const BigNumber &other);
    friend bool operator<=(BigNumber first, const BigNumber &other);
    friend BigNumber operator+(BigNumber first, const BigNumber &other);
    friend BigNumber operator-(BigNumber first, const BigNumber &other);
    friend BigNumber operator*(BigNumber first, const BigNumber &other);
    friend BigNumber operator*(int first, const BigNumber &other);
    BigNumber &operator=(const BigNumber &other);
};
