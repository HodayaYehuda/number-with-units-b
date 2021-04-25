#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include "NumberWithUnits.hpp"
#include <map>
#include <iterator>

using namespace std;
#include <float.h>
#define DBL_MAX __DBL_MAX__
const double lowest_double = DBL_MAX;

namespace ariel{

static map<std::string ,map<std::string, double>> convert_map;

NumberWithUnits::NumberWithUnits(const double& a,const string& str){

           if ( a < -DBL_MAX || a > DBL_MAX )  {
            throw std::invalid_argument( "invalid input" );
           }

           if (convert_map.count(str) == 0){
            throw std::invalid_argument( "doesnt was on file" );
           }
            amount = a;
            unit = str;
        }

void NumberWithUnits::read_units(istream& os){
//1 min = 60 sec
string unit_a;
string unit_b;
string x = "=";
double amount_b;
string line;
int one = 0;

while (getline(os, line)){
    stringstream g(line);

g >> one >> unit_a >> x >> amount_b >> unit_b;



convert_map[unit_a][unit_b] = amount_b;
convert_map[unit_b][unit_a] = 1/amount_b;

for(const auto &id1 : convert_map){
    if (id1.second.count(unit_a) > 0){
        std::map<std::string, double> t = id1.second;
        t.insert(pair<const std::string, double>(unit_b,amount_b/t.at(unit_a)));   
    }
 }

for(const auto &id1 : convert_map){
    if (id1.second.count(unit_b) > 0){
    std::map<std::string, double> t = id1.second;
    t.insert(pair<const std::string, double>(unit_a,1/amount_b));
}


}
 

 



// for(std::pair<const std::string, double> corrent : convert_map[unit_a]){
//     double val = amount_b/corrent.second;
//     //convert_map.at(corrent.first).insert(pair<const std::string, double>(unit_b,val))amount_b/corrent.second;   
//     convert_map.at(corrent.first).insert(pair<const std::string, double>(unit_a,val));
// }
// for(std::pair<const std::string, double> corrent : convert_map[unit_b]){
//     //double val = amount_b/corrent.second;
//     //convert_map.at(corrent.first).insert(pair<const std::string, double>(unit_b,val));   
// convert_map.at(corrent.first).insert(pair<const std::string, double>(unit_b,(corrent.second)/(amount_b)));
//}



}





// if (convert_map.count(unit_b) == 0 && convert_map.count(unit_a) > 0 ){
// for(std::pair<const std::string, double> corrent : convert_map[unit_a]){
//     double val = amount_b/corrent.second;
//     convert_map.at(corrent.first).insert(pair<const std::string, double>(unit_b,val));   
// }
// }


// if (convert_map.count(unit_a) == 0 && convert_map.count(unit_b) > 0){
// for(std::pair<const std::string, double> corrent : convert_map[unit_b]){
// double val = amount_a / (amount_b*corrent.second);
// convert_map.at(corrent.first).insert (pair<const std::string, double>(unit_a,val));   
// }
// }

// if (convert_map.count(unit_a) == 0 && convert_map.count(unit_b) == 0 ){
// convert_map[unit_a][unit_b] = amount_b/amount_a;
// convert_map[unit_b][unit_a] = amount_b/amount_a;

// }

}


NumberWithUnits operator + (const NumberWithUnits& a,const NumberWithUnits& b) {
    //same unit
    if (a.unit == b.unit){
        return NumberWithUnits(a.amount + b.amount, a.unit);
    }
    //not the same unit
    if (convert_map.at(b.unit).count(a.unit) == 0){
        throw std::invalid_argument( "not on map + " );
    }
    return NumberWithUnits(a.amount+(b.amount*convert_map[a.unit][b.unit]), a.unit);
}

NumberWithUnits operator - (const NumberWithUnits& a,const NumberWithUnits& b) {
    //same unit
    if (a.unit == b.unit){
        return NumberWithUnits(a.amount - b.amount, a.unit);
    }
    //not the same unit
    if (convert_map.count(a.unit) == 0 ||
        convert_map.at(a.unit).count(b.unit) == 0){
        throw std::invalid_argument( "not on map - " );
    }
    return NumberWithUnits(a.amount-(b.amount*convert_map[a.unit][b.unit]), a.unit);
}


NumberWithUnits operator += (const NumberWithUnits& a, const NumberWithUnits& b ){
    //same unit
    if (a.unit == b.unit){
        return NumberWithUnits(a.amount + b.amount, a.unit);
    }
    //not the same unit
    if (convert_map.at(a.unit).count(b.unit) == 0){
        throw std::invalid_argument( "different unit +=" );
    }

    return NumberWithUnits(a.amount+(b.amount/convert_map[a.unit][b.unit]), a.unit);



}
NumberWithUnits operator -= (const NumberWithUnits& a, const NumberWithUnits& b) {
     //same unit
    NumberWithUnits t = a;

    if (a.unit == b.unit){
        t.amount -= b.amount;
        return t;
    }
    //not the same unit
    if (convert_map.at(a.unit).count(b.unit) == 0 ){
        throw std::invalid_argument( "different unit -=" );
    }
    t.amount -= b.amount/convert_map[a.unit][b.unit];
        return t;
}



bool operator < (const NumberWithUnits& a, const NumberWithUnits& b) {
    //same unit
    if (a.unit == b.unit){
        return (a.amount < b.amount);
    }

    //not the same unit
    if ((convert_map.count(a.unit) == 0 ||
        convert_map.count(b.unit) == 0 ||
        convert_map.at(a.unit).count(b.unit) == 0 )){
            return false;
    }
     return(a.amount < b.amount/convert_map.at(a.unit).at(b.unit));
     }

bool operator > (const NumberWithUnits& a, const NumberWithUnits& b) {

    //same unit
    if (a.unit == b.unit){
         return(a.amount > b.amount);

    }
    //not the same unit
    if ((convert_map.count(a.unit) == 0 ||
        convert_map.count(b.unit) == 0 ||
        convert_map.at(a.unit).count(b.unit) == 0 )){
            return false;
    }
     if(a.amount > b.amount/convert_map[a.unit][b.unit]){
         return true;
     }
     return false;
     }

bool operator == (const NumberWithUnits& a, const NumberWithUnits& b) {
    //same unit
    if (a.unit == b.unit){
        return (a.amount == b.amount);
    }
    //not the same unit
    if ((convert_map.count(a.unit) == 0 ||
        convert_map.count(b.unit) == 0 ||
        convert_map.at(a.unit).count(b.unit) == 0 )){
            return false;
    }
     double t = b.amount/a.amount;
     return(convert_map.at(a.unit).at(b.unit) == t);
     }

bool operator <= (const NumberWithUnits& a, const NumberWithUnits& b) {
     return(a<b || a==b);
    }


bool operator >= (const NumberWithUnits& a, const NumberWithUnits& b) {
         return(a>b || a==b);

     }
bool operator != (const NumberWithUnits& a, const NumberWithUnits& b) {
     return ! (a == b);
     }
     


NumberWithUnits& NumberWithUnits::operator++ () {
    amount++;
    return *this;
} // ++a
NumberWithUnits& NumberWithUnits::operator -- () {
    amount--;
    return *this;
} // --a

const NumberWithUnits NumberWithUnits::operator ++ (int) {
     NumberWithUnits a = *this;
     a.amount++;
     return a;
} //a++

const NumberWithUnits NumberWithUnits::operator -- (int) {
     NumberWithUnits a = *this;
     a.amount--;
     return a;
} //a--





NumberWithUnits operator * (const NumberWithUnits& unit,const double num) {
    
     return NumberWithUnits(unit.amount*num , unit.unit);

}

NumberWithUnits operator * (const double num,const NumberWithUnits& unit) {
     return NumberWithUnits(unit.amount*num , unit.unit);

}

ostream& operator << (ostream &os, const NumberWithUnits &u){
return os<<u.amount<<"["<<u.unit<<"]";
}

//istream& operator >> (istream &is, NumberWithUnits &u){
// double new_amount;
// string new_unit;
// ios::pos_type startPos = is.tellg();

// if( ( !(is >> new_amount)) || 
//     (!(getchar() != '[')) ||
//     (!(is>>new_unit)) ||    
//      (!(getchar()!= ']')) ){

// auto errorState = is.rdstate();
// is.clear();
// is.seekg(startPos);
// is.clear(errorState);
//     }
//     else{
//         u.unit = new_unit;
//         u.amount = new_amount;
//     }

// return is;
// }



istream& operator>>(istream& istream, NumberWithUnits& a){
        double a_amount = 0;
        string line = " ";
        char b1 = '\0';
        char b2 = '\0';

        ios::pos_type startPosition = istream.tellg();
        istream >> a.amount >> b1 >> line;
        if (line.at(line.length()-1) == ']')
        {
            line = line.substr(0, line.length()-1);
        }
        else{
            istream >> b2;
        }
        if (convert_map.find(line) == convert_map.end())
        {
            throw invalid_argument("invalid argument");
        }

        a.amount = a_amount;
        a.unit = line;
        return istream;
    }
    

    // ostream& operator<<(ostream& ostream, const NumberWithUnits& a){
    //     return ostream<<a.amount<<"["<<a.Of_What<<"]";
    // }
};





