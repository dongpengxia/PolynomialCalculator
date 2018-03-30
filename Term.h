/*
 *  Term.h
 *
 *  Polynomial Calculator
 *
 *  10/6/2016
 *  Dongpeng Xia
 */

#ifndef Term_h
#define Term_h

using std::ostream;
using std::istream;

//global constants
const long defaultCoefficient = 0;
const long defaultExponent = 0;

//exception classes
class termAdditionError{};
class termSubtractionError{};
class overFlowException{};

long pow(long, unsigned long); //integer exponent function

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                     class Term declaration                             **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class Term
{
    friend ostream& operator<<(ostream&, const Term&);
    //Postcondition: The term is output to the stream.

    friend istream& operator>>(istream&, Term&);
    //Postcondition: Extracts values for each data member from the input stream.
    
    friend Term operator+(const Term&, const Term&);
    //Precondition: Left term and right term have same exponents.
    //Postcondition: Left term and right term coefficients are added.
    
    friend Term operator*(const Term&, const Term&);
    //Postcondition: Left term and right term coefficients are multiplied, exponents are added.
    
    friend Term operator-(const Term&, const Term&);
    //Precondition: Left term and right term have same exponents
    //Postcondition: Right term coefficient subtracted from left term coefficient
    
private:
    long coefficient;
    unsigned long exponent;
    
public:
    Term(long = defaultCoefficient, unsigned long = defaultExponent);
    //Postcondition: Sets the values of coefficient and exponent
    //according to the values of the arguments passed in.
    //Default constructor if no values are passed
    
    Term(const Term&);
    //Postcondition: Passed by reference Term object is copied to construct a new Term object.
    
    void setTerm(long, unsigned long);
    //coefficient, exponent
    //Postcondition: Data members are set to the values of the respective arguments passed in.
    
    void setTerm(const Term&);
    //Postcondition: Data members are set to the values of the passed by reference Term object.
    
    long getCoefficient() const {return coefficient;}
    //Postcondition: Term coefficient returned.
    
    unsigned long getExponent() const {return exponent;}
    //Postcondition: Term exponent returned.
    
    Term operator=(const Term&);
    //Postcondition: The values of right Term's data members are copied to the data members
    //of the left Term.
    
    bool operator==(const Term &t) {return exponent == t.exponent;} //ONLY checks exponent
    //Postcondition: Boolean returned indicating if right Term's exponent value is equal
    //to left Term's exponent value
    
    bool operator!=(const Term &t) {return exponent != t.exponent;} //ONLY checks exponent
    //Postcondition: Boolean returned indicating if right Term's exponent value is different
    //from left Term's exponent value
    
    bool operator<=(const Term &t) {return exponent <= t.exponent;} //ONLY checks exponent
    //Postcondition: Boolean returned indicating if right Term has exponent equal to or greater
    //than the exponent of the left Term
    
    bool operator<(const Term &t) {return exponent < t.exponent;} //ONLY checks exponent
    //Postcondition: Boolean returned indicating if right Term has exponent greater
    //than the exponent of the left Term
    
    bool operator>=(const Term &t) {return exponent >= t.exponent;} //ONLY checks exponent
    //Postcondition: Boolean returned indicating if right Term has exponent equal to or less
    //than the exponent of the left Term
    
    bool operator>(const Term &t) {return exponent > t.exponent;} //ONLY checks exponent
    //Postcondition: Boolean returned indicating if right Term has exponent less
    //than the exponent of the left Term
    
    long evaluate(long);
    //Postcondition: Integer returned with value of term given the value of x
    
    void power(unsigned long);
    //Postcondition: Term raised to an integer exponent

}; //END class Term declaration

#endif