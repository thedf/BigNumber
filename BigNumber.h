#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class BigNumber
{
private:
    string numberInString;
    bool sign = false;

public:
    BigNumber();
    BigNumber(string number);
    BigNumber(int number);
    ~BigNumber();

    string getString() { return numberInString; };
    BigNumber add(BigNumber other);
    BigNumber sous(BigNumber other);
    BigNumber multiply(BigNumber other);

    bool equals(const BigNumber &other);
    BigNumber addMod(const BigNumber &other, const BigNumber &modNumber);

    friend bool operator==(BigNumber first, const BigNumber &other);
    friend bool operator>(BigNumber first, const BigNumber &other);
    friend bool operator<(BigNumber first, const BigNumber &other);
    friend bool operator>=(BigNumber first, const BigNumber &other);
    friend bool operator<=(BigNumber first, const BigNumber &other);
    friend BigNumber operator+(BigNumber first, const BigNumber &other);
    friend BigNumber operator-(BigNumber first, const BigNumber &other);
    friend BigNumber operator*(BigNumber first, const BigNumber &other);
    BigNumber &operator=(const BigNumber &other);
};
