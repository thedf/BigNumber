#include "BigNumber.h"

using namespace std;

BigNumber::BigNumber()
{
    numberInString = "0";
}
BigNumber::BigNumber(int number)
{
    numberInString = to_string(number);
    numberInString = numberInString.substr(numberInString.find_first_not_of('0'));
}
BigNumber::BigNumber(string number)
{
    numberInString = number;
    if (numberInString.size() > 0 && numberInString[0] == 0)
    {
        numberInString = numberInString.substr(numberInString.find_first_not_of('0'));
    }
}

BigNumber::~BigNumber()
{
}

bool BigNumber::equals(const BigNumber &other)
{
    return this->numberInString == other.numberInString;
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

BigNumber BigNumber::add(BigNumber other)
{
    string sum;

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
    // cout << biggestNumber.numberInString.size() << " + " << smallestNumber.numberInString.size() << endl;

    while (biggestNumber.numberInString.size() != smallestNumber.numberInString.size())
    {
        smallestNumber.numberInString.insert(smallestNumber.numberInString.begin(), '0');
    }

    int carry = 0;
    // cout << biggestNumber.numberInString << " + " << smallestNumber.numberInString << endl;

    for (int i = int(biggestNumber.numberInString.size() - 1); i >= 0; i--)
    {
        int sumOfOneIter = (biggestNumber.numberInString[i] - '0') + (smallestNumber.numberInString[i] - '0') + carry;
        // cout << biggestNumber.numberInString[i] << " + " << smallestNumber.numberInString[i] << " + " << carry << " = " << sumOfOneIter << endl;
        carry = 0;
        if (sumOfOneIter <= 9 || i == 0)
        {
            sum.insert(0, std::to_string(sumOfOneIter));
        }
        else
        {
            sum.insert(0, std::to_string(sumOfOneIter % 10));
            carry = 1;
        }
    }
    return BigNumber(sum);
}

BigNumber operator+(BigNumber first, const BigNumber &other)
{
    return first.add(other);
}

BigNumber &BigNumber::operator=(const BigNumber &other)
{
    this->numberInString = other.numberInString;
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
            // cout << biggestNumber.numberInString[k] << " * " << multiplier << " + " << carry << " = " << sumOfOneIter << endl;
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
        // cout << resultForOneIter << endl;
        BigNumber toBeAdded = BigNumber(resultForOneIter);
        prod = prod + toBeAdded;

        // cout << "Result : " << prod.getString() << endl;
        j++;
    }
    return prod;
}

BigNumber operator*(BigNumber first, const BigNumber &other)
{
    return first.multiply(other);
}