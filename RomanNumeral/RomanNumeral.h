#ifndef ROMANNUMERAL_H_
#define ROMANNUMERAL_H_

#include <string>
using namespace std;

class RomanNumeral
{
public:
    RomanNumeral();
    RomanNumeral(string roman);
    RomanNumeral(int value);
    ~RomanNumeral();

    string getRoman()   const;
    int    getDecimal() const;

    // Overload the arithmetic operators.
    RomanNumeral operator +(const RomanNumeral& other);
    RomanNumeral operator -(const RomanNumeral& other);
    RomanNumeral operator *(const RomanNumeral& other);
    RomanNumeral operator /(const RomanNumeral& other);

    // Overload the equality operators.
    bool operator ==(const RomanNumeral& other);
    bool operator !=(const RomanNumeral& other);

    // Overload the stream >> and << operators.
    friend istream& operator >>(istream& in, RomanNumeral& numeral);
    friend ostream& operator <<(ostream& out, const RomanNumeral& numeral);

private:
    string roman;      // Roman numeral as a string
    int    decimal;    // decimal value of the Roman numeral

    void toRoman();    // calculate string from decimal value
    void toDecimal();  // calculate decimal value from string
};

#endif /* ROMANNUMERAL_H_ */
