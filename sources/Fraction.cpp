#include "Fraction.hpp"
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace ariel;

// Helper function to check for integer overflow
bool check_overflow(int a, int b, int &result, char op) {
    bool overflow = false;

    switch (op) {
        case '+':
            overflow = __builtin_add_overflow(a, b, &result);
            break;
        case '-':
            overflow = __builtin_sub_overflow(a, b, &result);
            break;
        case '*':
            overflow = __builtin_mul_overflow(a, b, &result);
            break;
        default:
            break;
    }

    return overflow;
}

int Fraction::getNumerator() const
{
    return this->numerator;
};

int Fraction::getDenominator() const
{
    return this->denominator;
};

void Fraction::setNumerator(int numerator)
{
    ariel::Fraction::numerator = numerator;
};

void Fraction::setDenominator(int denominator)
{
    ariel::Fraction::denominator = denominator;
};

void Fraction::print()
{
    cout << ariel::Fraction::numerator << "/" << ariel::Fraction::denominator << endl;
};




Fraction Fraction::operator+(const Fraction &other) {
    int resultNum;
    int resultDenom;

    if (check_overflow(numerator * other.denominator, other.numerator * denominator, resultNum, '+')) {
        throw std::overflow_error("Integer overflow in addition operation");
    }

    if (check_overflow(denominator, other.denominator, resultDenom, '*')) {
        throw std::overflow_error("Integer overflow in addition operation");
    }

    Fraction temp = Fraction(resultNum, resultDenom);
    temp.reduction();
    return temp;
}


Fraction ariel::operator+(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);
    int numerator = (num1.numerator * other.denominator) + (other.numerator * num1.denominator);
    int denominator = num1.denominator * other.denominator;
    Fraction result = Fraction(numerator, denominator);
    result.reduction();
    return result;
}

Fraction Fraction::operator-(const Fraction &other) {
    int resultNum;
    int resultDenom;

    if (check_overflow(numerator * other.denominator, other.numerator * denominator, resultNum, '-')) {
        throw std::overflow_error("Integer overflow in subtraction operation");
    }

    if (check_overflow(denominator, other.denominator, resultDenom, '*')) {
        throw std::overflow_error("Integer overflow in subtraction operation");
    }

    Fraction tmp = Fraction(resultNum, resultDenom);
    tmp.reduction();
    return tmp;
}


Fraction ariel::operator-(double value, const Fraction &other)
{

    Fraction num1 = Fraction(value);
    num1.reduction();

    int resultNumerator = (num1.numerator * other.denominator) - (other.numerator * num1.denominator);
    int resultDenominator = num1.denominator * other.denominator;


    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduction();
    return result;
}

Fraction ariel::operator*(int num, const Fraction &other)
{
    Fraction result = Fraction(num * other.numerator, other.denominator);
    result.reduction();

   
    return result;
}

Fraction Fraction::operator*(const Fraction &other) {
    int resultNumerator;
    int resultDenominator;

    if (check_overflow(numerator, other.numerator, resultNumerator, '*')) {
        throw std::overflow_error("Integer overflow in multiplication operation");
    }

    if (check_overflow(denominator, other.denominator, resultDenominator, '*')) {
        throw std::overflow_error("Integer overflow in multiplication operation");
    }

    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduction();
    return result;
}

Fraction ariel::operator*(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);
    int resultNumerator = static_cast<int>(num1.numerator * other.numerator);
    int resultDenominator = static_cast<int>(num1.denominator * other.denominator);

    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduction();

    return result;
};

Fraction Fraction::operator/(const Fraction &other) {
    if (other.numerator == 0) {
        throw std::runtime_error("Division by zero");
    }

    int resultNumerator;
    int resultDenominator;

    if (check_overflow(numerator, other.denominator, resultNumerator, '*')) {
        throw std::overflow_error("Integer overflow in division operation");
    }

    if (check_overflow(denominator, other.numerator, resultDenominator, '*')) {
        throw std::overflow_error("Integer overflow in division operation");
    }

    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduction();
    return result;
}

Fraction ariel::operator/(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);
    int resultNumerator = static_cast<int>(num1.numerator * other.denominator);
    int resultDenominator = static_cast<int>(num1.denominator * other.numerator);

    Fraction result = Fraction(resultNumerator, resultDenominator);
    result.reduction();
    return result;
};

// bool Fraction::operator>(const Fraction& other) const{
//     return (numerator * other.denominator) > (other.numerator * denominator);
// };

bool Fraction::operator>(const Fraction &other) const
{
    // Calculate the cross product of the fractions to compare their relative values
    int crossProduct = numerator * other.denominator - other.numerator * denominator;

    // Return true if the cross product is positive, indicating that 'this' fraction is greater
    return crossProduct > 0;
}

bool ariel::operator>(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);

    return (num1.numerator * other.denominator) > (other.numerator * num1.denominator);
};

// bool Fraction::operator>=(const Fraction& other) const{
//     cout<<"numerator: "<<numerator<<" denominator: "<<denominator<<endl;
//     cout<<"other.numerator: "<<other.numerator<<" other.denominator: "<<other.denominator<<endl;

//     return (*this < other);
// };

bool Fraction::operator>=(const Fraction &other) const
{
    cout << "######this is this" << *this << endl;
    cout << "######this is other" << other << endl;
    return (*this == other) || (*this > other);
}

bool ariel::operator>=(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);
    return !(num1 < other);
};

bool Fraction::operator<(const Fraction &other) const
{

    return (numerator * other.denominator) < (other.numerator * denominator);
};

bool ariel::operator<(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);
    return (num1.numerator * other.denominator) < (other.numerator * num1.denominator);
};

// bool ariel::operator<(double num, const Fraction& other) {
//     double fractionValue = static_cast<double>(other.numerator) / other.denominator;

//     if (other.denominator < 0) {
//         fractionValue *= -1; // Change sign of the fraction value
//     }

//     return num < fractionValue;
// }

bool Fraction::operator<=(const Fraction &other) const
{
    return !(*this > other);
};

bool ariel::operator<=(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);
    return !(num1 > other);
};

bool Fraction::operator==(const Fraction &other) const
{
    return (numerator * other.denominator) == (other.numerator * denominator);
};

bool ariel::operator==(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);
    return (num1.numerator * other.denominator) == (other.numerator * num1.denominator);
};

bool Fraction::operator!=(const Fraction &other) const
{
    return !(*this == other);
};

bool ariel::operator!=(double num, const Fraction &other)
{
    Fraction num1 = Fraction(num);
    return !(num1 == other);
};

Fraction Fraction::operator++()
{
    numerator += denominator;
    return *this;
};

Fraction ariel::Fraction::operator++(int)
{
    Fraction copy(*this);
    numerator += denominator;
    return copy;
};

Fraction Fraction::operator--()
{
    numerator -= denominator;
    return *this;
};

Fraction ariel::Fraction::operator--(int)
{
    Fraction copy(*this);
    numerator -= denominator;
    return copy;
};

// std::ostream& ariel::operator<<(std::ostream& output, const Fraction& fraction) {
//     output << fraction.numerator << "/" << fraction.denominator;
//     return output;
// }



ostream &ariel::operator<<(std::ostream &output, const Fraction &frac)
{

    if(frac.getDenominator()< 0){

        output << frac.getNumerator() * -1 << "/" << frac.getDenominator() * -1;
        return output;
    }
    
    // cout<<"numerator: "<<frac.getNumerator()<<" denominator: "<<frac.getDenominator()<<endl;

    // Fraction tmp = (frac);

    // cout<<"after TMP numerator: "<<frac.numerator<<" denominator: "<<frac.denominator<<endl;


    output << frac.getNumerator() << "/" << frac.getDenominator();

    return output;
};

//  std::istream& ariel::operator>>(std::istream& input, Fraction& fraction) {
        
//         std::string fractionStr;
//         std::getline(input, fractionStr);

//         // Replace any comma with a space for consistent parsing
//         std::replace(fractionStr.begin(), fractionStr.end(), ',', ' ');

//         std::istringstream iss(fractionStr);
        
//         int num, denom;
//         if (iss >> num >> denom) {
//             fraction.numerator = num;
//             fraction.denominator = denom;
//         } else {
//             // Check if the input is a single number
//             if (iss.fail() && !iss.eof()) {
//                 // Invalid input format, set the failbit for the input stream
//                 input.setstate(std::ios::failbit);
//             } else {
//                 // Input is a single number, throw an exception
//                 throw std::invalid_argument("Invalid input format. Expected numerator and denominator.");
//             }
//         }

//         return input;
//     }


std::istream& ariel::operator>>(std::istream& input, Fraction& fraction) {
    int num, denom;



    if (input >> num >> denom) {
        fraction.numerator = num;
        fraction.denominator = denom;
    } 
    else {
        // Invalid input format, set the failbit for the input stream
        input.setstate(std::ios::failbit);

        throw runtime_error("Invalid input format. Expected numerator and denominator.");
    }
     if(fraction.getDenominator()==0){
        throw runtime_error("denominator is 0");
    }


    return input;
}
