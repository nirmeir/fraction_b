#pragma once
#include <iostream>
#include <stdio.h>


constexpr int MAX_DENOMINATOR = 1000;
using namespace std;
namespace ariel

{
    class Fraction{
        
    private:
        int numerator;
        int denominator;
        
    public:

        Fraction(int _numerator, int _denominator)  { //NOLINT

            if (_denominator == 0) {
                // throw runtime_error("Denominator cannot be zero");
                throw std::invalid_argument("Denominator cannot be zero");
            }


            if(_denominator<0 && _numerator<0){
                this->numerator=abs(_numerator);
                this->denominator=abs(_denominator);
                 this->reduction();
            }
            else if(_denominator<0 ) {

                this->numerator = abs(_numerator)*-1;
                this->denominator = abs(_denominator);         

               this->reduction();
            }
            else{

                this->numerator = _numerator;
                this->denominator = _denominator;
            }
          
    
                this->reduction();
        }//NOLINT

    
        Fraction(double frac): denominator(MAX_DENOMINATOR) {
        numerator = (int)(frac * denominator);
     
        }


        Fraction(): numerator(0), denominator(1) {};



        int getNumerator() const ;
        int getDenominator() const;
        void setNumerator(int numerator);
        void setDenominator(int denominator);
        void print();

        int gcd(int aaa, int bbb) {
        if (bbb == 0) {
            return aaa;
        }
        return gcd(abs(bbb), abs(aaa) % abs(bbb));
    }

        Fraction reduction() {

            int red = gcd(abs(numerator), abs(denominator)); // Calculate the greatest common divisor
            (numerator) /= abs(red); // Reduce the numerator
            denominator /= abs(red); // Reduce the denominator
            return *this;
        };

        Fraction operator+(const Fraction& other) ;
        friend Fraction operator+(double num, const Fraction& other);
        Fraction operator-(const Fraction& other) ;
        friend Fraction operator-(double num, const Fraction& other);

        friend Fraction operator*(int num, const Fraction& other) ;


        Fraction operator*(const Fraction& other) ;

        friend Fraction operator*( double num, const Fraction& other);
        Fraction operator/(const Fraction& other) ;
        friend Fraction operator/(double num,const Fraction& other) ;

        bool operator>(const Fraction& other) const;
        friend bool operator>(double num,const Fraction& other) ;


        bool operator>=(const Fraction& other) const;
        friend bool operator>=(double num,const Fraction& other) ;

        bool operator<(const Fraction& other) const;
        friend bool operator<(double num,const Fraction& other);

        bool operator<=(const Fraction& other) const;
        friend bool operator<=(double num,const Fraction& other);

        bool operator==(const Fraction& other) const;
        friend bool operator==(double num,const Fraction& other);

        bool operator!=(const Fraction& other) const;
        friend bool operator!=(double num ,const Fraction& other) ;

        Fraction operator++();
        Fraction operator++(int);
        Fraction operator--();
        Fraction operator--(int);

        friend std::ostream& operator<<(std::ostream& output, const Fraction& fraction);
        friend std::istream& operator>>(std::istream& input, Fraction& fraction);
    };

    }