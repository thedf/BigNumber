#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class BigNumber
{
private:
    numberInString;

public:
    BigNumber();
    BigNumber(string number);
    BigNumber(int number);
    ~BigNumber();

    string getString() { return numberInString; };
    BigNumber add(BigNumber other);
    BigNumber multiply(BigNumber other);

    bool equals(const BigNumber &other);

    friend bool operator==(BigNumber first, const BigNumber &other);
    friend bool operator>(BigNumber first, const BigNumber &other);
    friend bool operator<(BigNumber first, const BigNumber &other);
    friend bool operator>=(BigNumber first, const BigNumber &other);
    friend bool operator<=(BigNumber first, const BigNumber &other);
    friend BigNumber operator+(BigNumber first, const BigNumber &other);
    friend BigNumber operator*(BigNumber first, const BigNumber &other);
    BigNumber &operator=(const BigNumber &other);
};
