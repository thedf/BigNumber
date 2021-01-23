#include "BigNumber.h"
#include <cmath>
using namespace std;

BigNumber::BigNumber()
{
    numberInString = "0";
}
BigNumber::BigNumber(int number)
{
    if (number < 0)
    {
        sign = -1;
        numberInString = to_string(-number);
    }
    else
        numberInString = to_string(number);
}
BigNumber::BigNumber(string number)
{
    const char c1 = '-';
    string s1{c1};
    if (number.substr(0, 1) == s1)
    {
        numberInString = number.substr(1);
        sign = -1;
    }
    else
    {
        numberInString = number;
        sign = 1;
    }

    if (numberInString.size() > 0 && numberInString[0] == '0')
    {
        numberInString = numberInString + "1";
        numberInString = numberInString.substr(numberInString.find_first_not_of("0"));
        if (numberInString == "1")
        {
            numberInString = "0";
        }
        else
        {
            numberInString = numberInString.substr(0, numberInString.size() - 1);
        }
    }
}

BigNumber::~BigNumber()
{
}

bool BigNumber::equals(const BigNumber &other)
{
    return this->numberInString == other.numberInString;
}

BigNumber BigNumber::shift(int numberOfZeros)
{
    BigNumber newOne = *this;
    for (int i = 0; i < numberOfZeros; i++)
    {
        newOne.numberInString += "0";
    }
    return newOne;
}

bool operator==(BigNumber first, const BigNumber &other)
{
    return first.equals(other);
}

bool operator>(BigNumber first, const BigNumber &other)
{

    if (first == other)
    {
        return false;
    }
    if (first.numberInString.size() > other.numberInString.size())
    {
        return true;
    }
    else if (other.numberInString.size() > first.numberInString.size())
    {
        return false;
    }
    else
    {
        for (unsigned int i = 0; i < first.numberInString.size(); i++)
        {
            if (first.numberInString[i] != other.numberInString[i])
            {
                return first.numberInString[i] > other.numberInString[i];
            }
        }
    }
    return false;
}

bool operator<(BigNumber first, const BigNumber &other)
{
    return !(first == other) && !(first > other);
}

bool operator>=(BigNumber first, const BigNumber &other)
{
    return first > other || first == other;
}

bool operator<=(BigNumber first, const BigNumber &other)
{
    return first < other || first == other;
}
BigNumber BigNumber::sous(BigNumber other)
{
    return this->add(other.inverteSign());
}

BigNumber BigNumber::add(BigNumber other)
{
    int whoIsBigger = other >= *this;
    string sum;

    BigNumber biggestNumber;
    BigNumber smallestNumber;
    if (whoIsBigger)
    {
        biggestNumber = other;
        smallestNumber = *this;
    }
    else
    {
        biggestNumber = *this;
        smallestNumber = other;
    }
    int signOfSum = biggestNumber.sign;
    int signOfSmallest = 1;
    int signOfBiggest = 1;
    if (biggestNumber.sign != smallestNumber.sign)
        signOfSmallest = -1;

    while (biggestNumber.numberInString.size() != smallestNumber.numberInString.size())
    {
        smallestNumber.numberInString.insert(smallestNumber.numberInString.begin(), '0');
    }

    int carry = 0;
    for (int i = int(biggestNumber.numberInString.size() - 1); i >= 0; i--)
    {
        int sumOfOneIter = (biggestNumber.numberInString[i] - '0') + signOfSmallest * (smallestNumber.numberInString[i] - '0') + carry;
        carry = 0;
        if (i == 0)
        {
            sum.insert(0, std::to_string(sumOfOneIter));
        }
        else if (sumOfOneIter < 0)
        {
            if (10 + sumOfOneIter < 0)
            {
                sum.insert(0, std::to_string(-10 - sumOfOneIter));
            }
            else
            {
                sum.insert(0, std::to_string(10 + sumOfOneIter));
            }
            carry = -1;
        }
        else if (sumOfOneIter <= 9)
        {
            sum.insert(0, std::to_string(sumOfOneIter));
        }
        else
        {
            sum.insert(0, std::to_string(sumOfOneIter % 10));
            carry = 1;
        }
    }
    if (signOfSum == -1)
    {
        return BigNumber("-" + sum);
    }
    return BigNumber(sum);
}

BigNumber operator+(BigNumber first, const BigNumber &other)
{
    return first.add(other);
}
BigNumber operator-(BigNumber first, const BigNumber &other)
{
    return first.sous(other);
}

BigNumber &BigNumber::operator=(const BigNumber &other)
{
    this->numberInString = other.numberInString;
    this->sign = other.sign;
    return *this;
}

BigNumber BigNumber::multiply(BigNumber other)
{
    BigNumber prod;

    BigNumber biggestNumber;
    BigNumber smallestNumber;

    if (other >= *this)
    {
        biggestNumber = other;
        smallestNumber = *this;
    }
    else
    {
        biggestNumber = *this;
        smallestNumber = other;
    }

    int j = 0;
    for (int i = int(smallestNumber.numberInString.size() - 1); i >= 0; i--)
    {

        string resultForOneIter;
        int carry = 0;

        int multiplier = (smallestNumber.numberInString[i] - '0');

        for (int k = int(biggestNumber.numberInString.size() - 1); k >= 0; k--)
        {
            int sumOfOneIter = (biggestNumber.numberInString[k] - '0') * multiplier + carry;
            carry = 0;
            if (sumOfOneIter <= 9 || k == 0)
            {
                resultForOneIter.insert(0, std::to_string(sumOfOneIter));
            }
            else
            {
                resultForOneIter.insert(0, std::to_string(sumOfOneIter % 10));
                carry = (sumOfOneIter - sumOfOneIter % 10) / 10;
            }
        }

        for (int l = 0; l < j; l++)
        {
            resultForOneIter.append("0");
        }
        BigNumber toBeAdded = BigNumber(resultForOneIter);
        prod = prod + toBeAdded;

        j++;
    }
    if (biggestNumber.sign * smallestNumber.sign == -1)
    {
        return prod.inverteSign();
    }
    return prod;
}

BigNumber operator*(BigNumber first, const BigNumber &other)
{
    return first.multiply(other);
}
BigNumber operator*(int first, const BigNumber &other)
{
    BigNumber firstBN = BigNumber(first);
    return firstBN.multiply(other);
}
BigNumber BigNumber::addMod(const BigNumber &other, BigNumber &modNum)
{
    BigNumber sum = this->add(other);
    int signOfSum = sum.getSign();
    int sizeDiff = sum.size() - modNum.size() - 1;
    while (sizeDiff >= 0)
    {
        BigNumber newMod = modNum.shift(sizeDiff);
        while (sum >= newMod || sum.sign == -1)
        {
            sum = sum - signOfSum * newMod;
        }
        sizeDiff = sum.size() - modNum.size() - 1;
    }

    return sum;
}

BigNumber BigNumber::sousMod(const BigNumber &other, BigNumber &modNum)
{
    BigNumber sum = this->sous(other);
    int signOfSum = sum.getSign();
    int sizeDiff = sum.size() - modNum.size() - 1;
    while (sizeDiff >= 0)
    {
        BigNumber newMod = modNum.shift(sizeDiff);
        signOfSum = sum.getSign();
        while (sum >= newMod || (sum < newMod && sum.sign == -1))
        {
            sum = sum - signOfSum * newMod;
        }
        sizeDiff = sum.size() - modNum.size() - 1;
    }

    return sum;
}
