/*
 *  Term.cpp
 *
 *  Polynomial Calculator
 *
 *  10/6/2016
 *  Dongpeng Xia
 */

#include <iostream>
#include <climits>
#include "Term.h"

using std::ostream;
using std::istream;



//function pow calculates x to the expo exponent and returns the result
long pow(long x, unsigned long expo)
{
    long result = 1;
    long copy;
    overFlowException error;
    
    try
    {

        while(expo > 0)
        {
            if(expo % 2)
            {
                //expo is odd, expo % 2 = 1
                copy = result; //copy for overflow testing
                result *= x;
                
                //check overflow
                if(x != 0 && result/x != copy) //short circuit evaluation to prevent /0
                {
                    throw error;
                }
            }
        
            copy = x; //copy for overflow testing
            x = x * x;
        
            //check overflow
            if(expo > 1 && copy != 0 && x/copy != copy) //short circuit evaluation to prevent /0
            {
                throw error;
            }
        
            expo /= 2;
            
        }//end while
    }//end try
    catch(overFlowException error)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }
    
    return result;
}//end pow function



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                 class Term implementation code                         **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

/****************************************************************************
 *        Term class default constructor/constructor with parameters        *
 ****************************************************************************/

Term::Term(long coeff, unsigned long expon)
{
    setTerm(coeff, expon);
    
} //END constructor with parameters for Term class



/****************************************************************************
 *            Term class overloaded stream insertion operator               *
 ****************************************************************************/

ostream& operator<<(ostream &os, const Term &t)
{
    os << t.coefficient << "x^" << t.exponent;
    return os;
    
} //END overloaded stream insertion operator for Term class



/****************************************************************************
 *            Term class overloaded stream extraction operator              *
 ****************************************************************************/

istream& operator>>(istream &in, Term &t)
{
    in >> t.coefficient; //extract and store the coefficient
    in >> t.exponent; //extract and store the exponent
    return in;
    
} //END overloaded stream extraction operator for Term class



/****************************************************************************
 *              Term class overloaded addition operator                     *
 ****************************************************************************/

Term operator+(const Term &t1, const Term &t2)
{
    try
    {
        //exponents must be equal to add two terms
        if(t1.exponent == t2.exponent)
        {
            //overflow testing
            if((t1.coefficient > 0 && t2.coefficient > 0 && LONG_MAX - t1.coefficient <
                t2.coefficient)||
               (t1.coefficient < 0 && t2.coefficient < 0 && LONG_MIN - t1.coefficient >
                t2.coefficient))
            {
                overFlowException overflow;
                throw overflow;
            }
            
            return Term(t1.coefficient + t2.coefficient, t1.exponent);
        }
        else
        {
            //exponents are not equal
            termAdditionError error;
            throw error;
        }
    }//end try block
    catch(termAdditionError error)
    {
        throw;
    }
    catch(overFlowException overflow)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }//end catch all block
    
} //END overloaded addition operator for Term class



/****************************************************************************
 *           Term class overloaded multiplication operator                  *
 ****************************************************************************/

Term operator*(const Term &t1, const Term &t2)
{
    try
    {
        //overflow testing
        long result = t1.coefficient * t2.coefficient;
        if((t1.coefficient != 0 && result/t1.coefficient != t2.coefficient) ||
            ULONG_MAX - t1.exponent < t2.exponent)
        {
            overFlowException overflow;
            throw overflow;
        }
        
        return Term(t1.coefficient * t2.coefficient, t1.exponent + t2.exponent);
    }
    catch(overFlowException overflow)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }//end catch all block

} //END overloaded multiplication operator for Term class



/****************************************************************************
 *              Term class overloaded subtraction operator                  *
 ****************************************************************************/

Term operator-(const Term &t1, const Term &t2)
{
    try
    {
        //exponents must be equal to subtract
        if(t1.exponent == t2.exponent)
        {
            //overflow testing
            if((t1.coefficient > 0 && t2.coefficient < 0 && LONG_MAX + t2.coefficient <
                t1.coefficient)||
               (t1.coefficient < 0 && t2.coefficient > 0 && LONG_MIN + t2.coefficient >
                t1.coefficient))
            {
                overFlowException overflow;
                throw overflow;
            }
            
            return Term(t1.coefficient - t2.coefficient, t1.exponent);
        }
        else
        {
            //exponents are not equal
            termSubtractionError error;
            throw error;
        }
    }//end try block
    catch(termSubtractionError error)
    {
        throw;
    }
    catch(overFlowException error)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }//end catch all block
    
} //END overloaded subtraction operator for Term class



/****************************************************************************
 *                    Term class copy constructor                           *
 ****************************************************************************/

Term::Term(const Term &t):coefficient(t.coefficient), exponent(t.exponent)
{
    //member initialization list used above
    
} //END copy constructor for Term class



/****************************************************************************
 *         Term class member function setTerm(int, unsigned int)            *
 ****************************************************************************/

void Term::setTerm(long coeff, unsigned long expon)
{
    coefficient = coeff;
    exponent = expon;
    
} //END member function Term::setTerm(int, unsigned int)



/****************************************************************************
 *               Term class member function setTerm(const Term&)            *
 ****************************************************************************/

void Term::setTerm(const Term &t)
{
    coefficient = t.coefficient;
    exponent = t.exponent;
    
} //END member function Term::setTerm(const Term&)



/****************************************************************************
 *              Term class overloaded assignment operator                   *
 ****************************************************************************/

Term Term::operator=(const Term &t)
{
    //check against self assigment
    if(this != &t)
    {
        coefficient = t.coefficient;
        exponent = t.exponent;
    }
    
    return t;
    
} //END overloaded assignment operator for Term class



/****************************************************************************
 *                      Term class evaluate function                        *
 ****************************************************************************/

long Term::evaluate(long x)
{
    try
    {
        long result = pow(x, exponent);
    
        long copy = result;//copy for overflow testing
        result *= coefficient;
    
        //overflow testing
        if(coefficient != 0 && result/coefficient != copy)
        {
            overFlowException error;
            throw error;
        }
    
        return result;
    }
    catch(overFlowException error)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }
    
} //END evaluate function for Term class



/****************************************************************************
 *                      Term class power function                           *
 ****************************************************************************/

void Term::power(unsigned long a)
{
    try
    {
        coefficient = pow(coefficient,a);
        
        unsigned long copy = exponent; //copy for overflow testing
        exponent *= a;
        
        //overflow testing
        if(a != 0 && exponent/a != copy)
        {
            overFlowException error;
            throw error;
        }
    }
    catch(overFlowException error)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }
    
} //END power function for Term class