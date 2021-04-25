#pragma once
#include <iostream>
#include <string>
#include <map>


using std::map;
#define Infinity ((double)(42.0 / 0.0))

namespace ariel {

    class NumberWithUnits{
    public:

        std::string unit;
        double amount;
        NumberWithUnits(const double& a, const std::string& str);
        
        static void read_units(std::istream&);
        friend NumberWithUnits operator + (const NumberWithUnits& a,const NumberWithUnits& b ) ;
        friend NumberWithUnits operator - (const NumberWithUnits& a,const NumberWithUnits& b ) ;
        friend NumberWithUnits operator += (const NumberWithUnits& a,const NumberWithUnits& b);
        friend NumberWithUnits operator -= (const NumberWithUnits& a,const NumberWithUnits& b);


        friend bool operator < (const NumberWithUnits& a, const NumberWithUnits& b) ;
        friend bool operator <= (const NumberWithUnits& a, const NumberWithUnits& b) ;
        friend bool operator > (const NumberWithUnits& a, const NumberWithUnits& b) ;
        friend bool operator >= (const NumberWithUnits& a, const NumberWithUnits& b) ;
        friend bool operator != (const NumberWithUnits& a, const NumberWithUnits& b) ;
        friend bool operator == (const NumberWithUnits& a, const NumberWithUnits& b) ;


       NumberWithUnits& operator ++ ();
       NumberWithUnits& operator -- ();
       const NumberWithUnits operator ++ (int a);
       const NumberWithUnits operator -- (int a);


        friend NumberWithUnits operator * (const NumberWithUnits&, const double);
        friend NumberWithUnits operator * (const double , const NumberWithUnits&);

        friend std::ostream &operator << (std::ostream&, const NumberWithUnits&);
        friend std::istream &operator >> (std::istream&, NumberWithUnits&);


        const NumberWithUnits operator + () const {
            NumberWithUnits a = *this;
            a.amount *= +1;
            return a;
        } //unary

       const NumberWithUnits operator - () const {
            NumberWithUnits a = *this;
            a.amount *= -1;
            return a;

        } //unary
};
    
}
