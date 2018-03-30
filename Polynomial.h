/*
 *  Polynomial.h
 *
 *  Polynomial Calculator
 *
 *  10/6/2016
 *  Dongpeng Xia
 */

#ifndef Polynomial_h
#define Polynomial_h

#include "Term.h"

using std::ostream;
using std::istream;
using std::cout;
using std::endl;
using std::bad_alloc;

//exception classes
class indexOutOfRange{};



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                     class Node declaration                             **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class Node
{
public:
    Term info;
    Node *next;
    Node(Term = Term(), Node* = NULL);
    
};//END class Node declaration





/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                   class Polynomial declaration                         **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class Polynomial
{
    friend ostream& operator<<(ostream&, const Polynomial&);
    //Postcondition: The polynomial linked list is output to the stream
    
    friend istream& operator>>(istream&, Polynomial&);
    //Postcondition: Extracts values for each data member from the input stream.
    
    friend Polynomial operator+(const Polynomial&, const Polynomial&);
    //Postcondition: Polynomials are added, sum is returned.
    
    friend Polynomial operator-(const Polynomial&, const Polynomial&);
    //Postcondition: Right polynomial is subtracted from left polynomial, result is returned.
    
    friend Polynomial operator*(const Polynomial&, const Polynomial&);
    //Postcondition: Polynomials are multiplied, result is returned.
    
private:
    unsigned long count;
    Node* head;
    Node* tail;
    
    void copyList(const Polynomial &listToCopy);
    //copyList is a private function called by both copy constructor and overloaded = operator
    //must ensure deep copy
    
public:
    Polynomial();
    
    ~Polynomial();
    //destructor, must ensure memory is deallocated
    
    Polynomial(const Polynomial&);
    //copy constructor
    
    Polynomial operator=(const Polynomial&);
    //overloaded = operator
    
    void push_back(Term);
    //member function push_back results in a Node object being added to the end of the linked
    //list polynomial, requires dynamic allocation of memory
    
    void insert(Term);
    //member function insert results in a Node object being inserted
    
    void pop_back();
    //member function pop_back removes the last list object and deallocates memory
    
    void clear();
    //member function clear removes all objects from the list and deallocates memory
    
    unsigned long size() const { return count; }
    //member function size returns number of objects on the polynomial linked list
    
    Term& at(unsigned long ndx) const;
    //member function at, returns node at index ndx (starting at head with index 0)
    
    void selectionSort();
    //sorts linked list polynomial in descending order
    
    Polynomial simplify();
    //combines terms with the same exponent in an ordered polynomial, eliminates terms with 0 coeff
    
    void expon(unsigned long);
    //returns polynomial to a nonnegative exponent
    
    long evaluate(long);
    //returns evaluation of polynomial given value of x
    
};//END class Polynomial declaration

#endif