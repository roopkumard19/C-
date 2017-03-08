#include <iostream>
#include <fstream>
#include <string>
#include "RomanNumeral.h"

using namespace std;

/**
 * Default constructor.
 */
RomanNumeral::RomanNumeral() : roman(""), decimal(0)
{
}

/**
 * Constructor.
 * @param str the Roman numeral string.
 */
RomanNumeral::RomanNumeral(string str) : roman(str)
{
    // Compute the decimal value.
    toDecimal();
}

/**
 * Constructor.
 * @param value the decimal value of the Roman numeral.
 */
RomanNumeral::RomanNumeral(int value) : decimal(value)
{
    // Compute the Roman numeral string.
    toRoman();
}

/**
 * Destructor.
 */
RomanNumeral::~RomanNumeral()
{
}

/**
 * @return the Roman numeral string.
 */
string RomanNumeral::getRoman() const
{
    return roman;
}

/**
 * @return the decimal value.
 */
int RomanNumeral::getDecimal() const
{
    return decimal;
}

/**
 * Overloaded operator to add two Roman numerals.
 * @param other the other numeral to add to this one.
 * @return the sum Roman numeral.
 */
RomanNumeral RomanNumeral::operator +(const RomanNumeral& other)
{
    int value = decimal + other.decimal;
    RomanNumeral sum(value);
    return sum;
}

/**
 * Overloaded operator to subtract two Roman numerals.
 * @param other the other numeral to subtract from this one.
 * @return the difference Roman numeral.
 */
RomanNumeral RomanNumeral::operator -(const RomanNumeral& other)
{
    int value = decimal - other.decimal;
    RomanNumeral diff(value);
    return diff;
}

/**
 * Overloaded operator to multiply two Roman numerals.
 * @param other the other numeral to multiply this one.
 * @return the product Roman numeral.
 */
RomanNumeral RomanNumeral::operator *(const RomanNumeral& other)
{
    int value = decimal*other.decimal;
    RomanNumeral prod(value);
    return prod;
}

/**
 * Overloaded operator to divide two Roman numerals (integer division).
 * @param other the other numeral to divide this one.
 * @return the quotient Roman numeral.
 */
RomanNumeral RomanNumeral::operator /(const RomanNumeral& other)
{
    int value = decimal/other.decimal;
    RomanNumeral quot(value);
    return quot;
}

/**
 * Overloaded operator for equality.
 * @param other the other numeral to compare to.
 * @return true if they're equal, otherwise true.
 */
bool RomanNumeral::operator ==(const RomanNumeral& other)
{
    return decimal == other.decimal;
}

/**
 * Overloaded operator for inequality.
 * @param other the other numeral to compare to.
 * @return true if they're unequal, otherwise true.
 */
bool RomanNumeral::operator !=(const RomanNumeral& other)
{
    return decimal != other.decimal;
}

/**
 * Overloaded operator construct a Roman numeral
 * by reading its string; e.g., MMXVI.
 * @param in the input stream.
 * @param numeral the constructed Roman numeral.
 * @return the input stream.
 */
istream& operator >>(istream& in, RomanNumeral& numeral)
{
    string str;
    in >> str;

    numeral.roman = str;
    numeral.toDecimal();

    return in;
}

/**
 * Overloaded operator to output a Roman numeral
 * in the form [string:value]; e.g., [2016:MMXVI]
 * @param out the output stream.
 * @param numeral the Roman numeral.
 * @return the output stream.
 */
ostream& operator <<(ostream& out, const RomanNumeral& numeral)
{
    out << "[" << numeral.decimal << ":" << numeral.roman << "]";
    return out;
}

/**
 * Compute the Roman numeral string from the decimal value.
 */
void RomanNumeral::toRoman()
{
    int temp = decimal;
    roman = "";

    // Append Roman numeral characters to the string
    // and subtract their corresponding values.

    while (temp >= 1000)
    {
        roman += "M";
        temp -= 1000;
    }

    if (temp >= 900)
    {
        roman += "CM";
        temp -= 900;
    }
    else if (temp >= 500)
    {
        roman += "D";
        temp -= 500;
    }
    else if (temp >= 400)
    {
        roman += "CD";
        temp -= 400;
    }

    while (temp >= 100)
    {
        roman += "C";
        temp -= 100;
    }

    if (temp >= 90)
    {
        roman += "XC";
        temp -= 90;
    }
    else if (temp >= 50)
    {
        roman += "L";
        temp -= 50;
    }
    else if (temp >= 40)
    {
        roman += "XL";
        temp -= 40;
    }

    while (temp >= 10)
    {
        roman += "X";
        temp -= 10;
    }

    if (temp >= 9)
    {
        roman += "IX";
        temp -= 9;
    }
    else if (temp >= 5)
    {
        roman += "V";
        temp -= 5;
    }
    else if (temp >= 4)
    {
        roman += "IV";
        temp -= 4;
    }

    while (temp >= 1)
    {
        roman += "I";
        temp--;
    }
}

/**
 * Compute the decimal value from the Roman numeral string.
 */
void RomanNumeral::toDecimal()
{
    int length = roman.length();
    decimal = 0;

    // Scan the Roman numeral string from left to right
    // and add the corresponding character values.
    for (int i = 0; i < length; i++)
    {
        switch (roman[i])
        {
            case 'M':
                decimal += 1000;
                break;

            case 'D':
                decimal += 500;
                break;

            case 'C':
                if (i+1 < length)
                {
                    switch (roman[i+1])
                    {
                        case 'D':  // CD
                            decimal += 400;
                            i++;
                            break;

                        case 'M':  // CM
                            decimal += 900;
                            i++;
                            break;

                        default:
                            decimal += 100;
                            break;
                    }
                }
                else decimal += 100;
                break;

            case 'L':
                decimal += 50;
                break;

            case 'X':
                if (i+1 < length)
                {
                    switch (roman[i+1])
                    {
                        case 'L':  // XL
                            decimal += 40;
                            i++;
                            break;

                        case 'C':  // XC
                            decimal += 90;
                            i++;
                            break;

                        default:
                            decimal += 10;
                            break;
                    }
                }
                else decimal += 10;
                break;

            case 'V':
                decimal += 5;
                break;

            case 'I':
                if (i+1 < length)
                {
                    switch (roman[i+1])
                    {
                        case 'V':  // IV
                            decimal += 4;
                            i++;
                            break;

                        case 'X':  // IX
                            decimal += 9;
                            i++;
                            break;

                        default:
                            decimal++;
                            break;
                    }
                }
                else decimal++;
                break;
        }
    }
}
