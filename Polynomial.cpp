/*
 *  Polynomial.cpp
 *
 *  Polynomial Calculator
 *
 *  10/6/2016
 *  Dongpeng Xia
 */

#include <iostream>
#include <stdexcept>
#include <climits>
#include "Polynomial.h"

using std::ostream;
using std::istream;
using std::cout;
using std::endl;
using std::bad_alloc;



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                     class Node implementation                          **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

/****************************************************************************
 *        Node class default constructor/constructor with parameters        *
 ****************************************************************************/

Node::Node(Term t, Node* nextNode): info(t), next(nextNode)
{
    
} //END constructor with parameters for Node class





/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                  class Polynomial implementation                       **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

/****************************************************************************
 *         Polynomial class overloaded stream insertion operator            *
 ****************************************************************************/

ostream& operator<<(ostream &os, const Polynomial &linkList)
{
    Node *current = linkList.head;
    
    if(current != NULL)
    {
        os << current->info;
        current = current->next;
    }
    while(current != NULL)
    {
        os << " + ";
        os << current->info;
        current = current->next;
    }
    
    return os;
    
} //END overloaded stream insertion operator for Polynomial class



/****************************************************************************
 *         Polynomial class overloaded stream extraction operator           *
 ****************************************************************************/

istream& operator>>(istream &is, Polynomial &p1)
{
    Term t1;
    
    while(is >> t1)
    {
        p1.push_back(t1);
    }
    
    return is;
    
} //END overloaded stream extraction operator for Polynomial class



/****************************************************************************
 *            Polynomial class overloaded addition operator                 *
 ****************************************************************************/

Polynomial operator+(const Polynomial &p1, const Polynomial &p2)
{
    Polynomial result;
    Node* p1Current = p1.head;
    Node* p2Current = p2.head;
    
    while(p1Current && p2Current) //if both are not NULL
    {
        if (p1Current->info > p2Current->info)
        {
            //p1 current term exponent > p2 current term exponent
            result.push_back(p1Current->info);
            p1Current = p1Current->next;
        }
        else if (p1Current->info < p2Current->info)
        {
            //p1 current term exponent < p2 current term exponent
            result.push_back(p2Current->info);
            p2Current = p2Current->next;
        }
        else
        {
            //p1 current term exponent == p2 current term exponent
            Term sum = p1Current->info + p2Current->info;
            p1Current = p1Current->next;
            p2Current = p2Current->next;
            
            if(sum.getCoefficient() != 0)
            {
                result.push_back(sum);
            }
        }
    }
    while(p1Current)
    {
        //Polynomial p1 still has terms left, but all of p2's terms have been processed
        result.push_back(p1Current->info);
        p1Current = p1Current->next;
    }
    while(p2Current)
    {
        //Polynomial p2 still has terms left, but all of p1's terms have been processed
        result.push_back(p2Current->info);
        p2Current = p2Current->next;
    }
    return result;
    
} //END overloaded addition operator for Polynomial class



/****************************************************************************
 *            Polynomial class overloaded subtraction operator              *
 ****************************************************************************/

Polynomial operator-(const Polynomial &p1, const Polynomial &p2)
{
    Polynomial result;
    Node* p1Current = p1.head;
    Node* p2Current = p2.head;
    Term negativep2;
    
    while(p1Current && p2Current) //if both are not NULL
    {
        if (p1Current->info > p2Current->info)
        {
            //p1 current term exponent > p2 current term exponent
            result.push_back(p1Current->info);
            p1Current = p1Current->next;
        }
        else if (p1Current->info < p2Current->info)
        {
            //p1 current term exponent < p2 current term exponent
            negativep2.setTerm((p2Current->info.getCoefficient())*-1,p2Current->info.getExponent());
            result.push_back(negativep2);
            
            p2Current = p2Current->next;
        }
        else
        {
            //p1 current term exponent == p2 current term exponent
            negativep2.setTerm((p2Current->info.getCoefficient())*-1,p2Current->info.getExponent());
            Term sum = p1Current->info + negativep2;
            
            p1Current = p1Current->next;
            p2Current = p2Current->next;
            
            if(sum.getCoefficient() != 0)
            {
                result.push_back(sum);
            }
        }
    }
    while(p1Current)
    {
        //Polynomial p1 still has terms left, but all of p2's terms have been processed
        result.push_back(p1Current->info);
        p1Current = p1Current->next;
    }
    while(p2Current)
    {
        //Polynomial p2 still has terms left, but all of p1's terms have been processed
        negativep2.setTerm((p2Current->info.getCoefficient())*-1,p2Current->info.getExponent());
        result.push_back(negativep2);
        p2Current = p2Current->next;
    }
    return result;
    
} //END overloaded subtraction operator for Polynomial class



/****************************************************************************
 *         Polynomial class overloaded multiplication operator              *
 ****************************************************************************/

Polynomial operator*(const Polynomial &p1, const Polynomial &p2)
{
    Polynomial result;
    Node* p1Current = p1.head;
    Node* p2Current = p2.head;
    
    while(p1Current) //while p1Current is not NULL
    {
        p2Current = p2.head;
        while(p2Current)
        {
            Term mult = (p1Current->info)*(p2Current->info);
            result.push_back(mult);
            
            p2Current = p2Current->next;
        }
        p1Current = p1Current->next;
    }
    
    result.selectionSort();
    result = result.simplify();
    
    return result;
    
} //END overloaded multiplication operator for Polynomial class



/****************************************************************************
 *                  Polynomial class copyList function                      *
 ****************************************************************************/

void Polynomial::copyList(const Polynomial &listToCopy)
{
    try
    {
        //if listToCopy is nonempty
        if(listToCopy.count > 0)
        {
            Node *current = listToCopy.head;
            head = new Node(current->info, NULL);
            tail = head;
            
            while(current->next != NULL)
            {
                this->push_back(current->next->info);
                current = current->next;
            }
            
            count = listToCopy.size();
        }
        //if listToCopy is empty
        else
        {
            head = NULL;
            tail = NULL;
            count = 0;
        }
        
    }//end try block
    
    catch(bad_alloc ba)
    {
        throw;
        
    }//end catch block
    catch(...)
    {
        throw;
        
    }//end catch block
    
} //END Polynomial class private function copyList



/****************************************************************************
 *                   Polynomial class default constructor                   *
 ****************************************************************************/

Polynomial::Polynomial(): count(0), head(NULL), tail(NULL)
{
    //see member initialization list above
    
} //END default constructor for Polynomial class



/****************************************************************************
 *                  Polynomial class destructor                             *
 ****************************************************************************/

Polynomial::~Polynomial()
{
    //call the clear function to remove all objects and update count to 0
    this->clear();
    
} //END destructor for Polynomial class



/****************************************************************************
 *                  Polynomial class copy constructor                       *
 ****************************************************************************/

Polynomial::Polynomial(const Polynomial &otherPolynomial)
{
    try
    {
        this->copyList(otherPolynomial);
    }//end try block
    
    catch(bad_alloc ba)
    {
        throw;
        
    }//end catch block
    catch(...)
    {
        throw;
        
    }//end catch block
    
} //END copy constructor for Polynomial class



/****************************************************************************
 *           Polynomial class overloaded assignment operator                *
 ****************************************************************************/

Polynomial Polynomial::operator=(const Polynomial &rhsObj)
{
    try
    {
        //check against self assignment
        if(this != &rhsObj)
        {
            //destroy current linked list
            this->clear();
            this->copyList(rhsObj);
        }
        
        return rhsObj;
    }//end try block
    
    catch(bad_alloc ba)
    {
        throw;
        
    }//end catch block
    catch(...)
    {
        throw;
        
    }//end catch block
    
} //END overloaded assignment operator for Polynomial class



/****************************************************************************
 *               Polynomial class push_back member function                 *
 ****************************************************************************/

void Polynomial::push_back(Term a)
{
    try
    {
        if(head == NULL)
        {
            //linked list is empty, add one Node to beginning
            head = new Node(a);
            tail = head;
        }
        
        else
        {
            tail->next = new Node(a);
            tail = tail->next;
        }
        
        //increment count
        count++;
        
    }//end try block
    catch(bad_alloc ba)
    {
        throw;
        
    }//end catch block
    catch(...)
    {
        throw;
        
    }//end catch block
    
} //END Polynomial class member function push_back



/****************************************************************************
 *                 Polynomial class insert member function                  *
 ****************************************************************************/

void Polynomial::insert(Term a)
{
    try
    {
        Node *current;
        //make sure we're not adding a zero term in
        if(a.getCoefficient() != 0)
        {
            if(head == NULL)
            {
                //add 1 node to empty list
                head = new Node(a, NULL);
                tail = head;
                count++;
            }
            
            //list is not empty
            else if(a > head->info)
            {
                //inserting a node at the head of linked list
                head = new Node(a, head);
                count++;
            }
            else if(a == head->info)
            {
                Term t = a + head->info;
                if(t.getCoefficient() == 0)
                {
                    //summation brings first term to zero, move head forward and delete
                    current = head;
                    head = head->next;
                    delete current;
                    count--;
                    
                    if(head == NULL)
                    {
                        tail = NULL;
                        count = 0;
                    }
                }
                else
                {
                    head->info = t;
                }
            }
            
            //inserting a node in the body of a non-empty ordered list (head > a)
            else
            {
                Node *trailCurrent = head;
                Node *current = head->next;
                
                //short circuit evaluation prevents access errors
                while(current != NULL && current->info > a)
                {
                    trailCurrent = current;
                    current = current->next;
                }
                if(!current) //if current is NULL, a is the new smallest
                {
                    trailCurrent->next = new Node(a, NULL);
                    tail = trailCurrent->next;
                    count++;
                }
                //current does exist, a >= current
                else if(a == current->info)
                {
                    Term sum = a + current->info;
                    if(sum.getCoefficient() == 0)
                    {
                        if(current == tail)
                        {
                            tail = trailCurrent;
                        }
                        trailCurrent->next = current->next;
                        delete current;
                        current = NULL;
                        count--;
                    }
                    else
                    {
                        current->info = sum;
                    }
                }
                else if(a > current->info)
                {
                    trailCurrent->next = new Node(a,current);
                    count++;
                }
            }
        }
        
    }//end try block
    catch(bad_alloc ba)
    {
        throw;
        
    }//end catch block
    catch(...)
    {
        throw;
        
    }//end catch block
    
    
} //END Polynomial class member function insert



/****************************************************************************
 *                Polynomial class pop_back member function                 *
 ****************************************************************************/

void Polynomial::pop_back()
{
    //if there are at least two nodes in linked list
    if(count > 1)
    {
        Node *current = head;
        while(current->next->next != NULL)
        {
            current = current->next;
        }
        delete (current->next);
        current->next = NULL;
        tail = current;
        
        //decrement count
        count--;
    }
    
    //if exactly one node in linked list
    else if(count == 1)
    {
        delete head;
        head = NULL;
        tail = NULL;
        
        //update count
        count = 0;
    }
    
} //END Polynomial class member function pop_back



/****************************************************************************
 *                   Polynomial class clear member function                 *
 ****************************************************************************/

void Polynomial::clear()
{
    Node *current = head;
    
    while(head != NULL)
    {
        head = head->next;
        delete current;
        current = head;
    }
    
    current = head = tail = NULL;
    count = 0;
    
} //END Polynomial class member function clear



/****************************************************************************
 *                    Polynomial class at member function                   *
 ****************************************************************************/

Term& Polynomial::at(unsigned long ndx) const
{
    indexOutOfRange indexError;
    
    try
    {
        //if ndx is within range
        if(ndx < count)
        {
            Node *current = head;
            for(unsigned long i = 0; i < ndx; i++ )
            {
                current = current->next;
            }
            return current->info;
        }
        else
        {
            //ndx is out of range
            throw indexError;
        }
    }//end try block
    catch(indexOutOfRange iError)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }
    
} //END Polynomial class member function at



/****************************************************************************
 *            Polynomial class selectionSort member function                *
 ****************************************************************************/

void Polynomial::selectionSort()
{
    Term largestValue;
    bool madeChange = false;
    
    
    Node* openSlot = head;
    Node* replacementValue;
    Node* replacementPlaceHolder = NULL;
    
    
    while(openSlot != NULL)
    {
        madeChange = false;
        largestValue = openSlot->info;
        
        replacementValue = openSlot->next;
        
        while(replacementValue != NULL)
        {
            if(replacementValue->info > largestValue)
            {
                largestValue = replacementValue->info;
                replacementPlaceHolder = replacementValue;
                madeChange = true;
            }
            
            replacementValue = replacementValue->next;
        }
        
        if(madeChange)
        {
            replacementPlaceHolder->info = openSlot->info;
            openSlot->info = largestValue;
        }
        
        openSlot = openSlot->next;
    }
} //END member function Polynomial::selectionSort()



/****************************************************************************
 *               Polynomial class simplify member function                  *
 ****************************************************************************/

Polynomial Polynomial::simplify()
{
    Polynomial result;
    Node *p1Current = head;
    Term currentTerm;
    Term sum;
    
    while(p1Current)
    {
        currentTerm = p1Current->info;
        
        if(sum == currentTerm)
        {
            //sum and current term have the same exponent
            sum = sum + currentTerm;
        }
        
        else
        {
            //sum and current term have different exponents
            if(sum.getCoefficient() != 0)
                result.push_back(sum);
            sum = currentTerm;
        }
        
        p1Current = p1Current->next;
    }
    
    if(sum.getCoefficient() != 0)
    {
        result.push_back(sum);
    }
    
    return result;
    
} //END member function Polynomial::simplify()



/****************************************************************************
 *               Polynomial class expon member function                     *
 ****************************************************************************/

void Polynomial::expon(unsigned long n)
{
    Polynomial p1Copy = *this; //make a copy of current polynomial
    
    clear(); //clear current polynomial
    push_back(Term(1,0)); //set result to 1X^0 = 1
    
    while(n > 0)
    {
        if(n % 2)
        {
            //n is odd
            *this = *this * p1Copy;
            
        }
        p1Copy = p1Copy * p1Copy;
        n /= 2;
    }
    
} //END member function Polynomial::expon()



/****************************************************************************
 *             Polynomial class evaluate member function                    *
 ****************************************************************************/

long Polynomial::evaluate(long x)
{
    long value = 0;
    long cCoefficient;
    long cExponent;
    long copy; //used for overflow testing
    overFlowException overflow;
    
    unsigned long exponentDifference;
    
    
    if(count > 0)
    {
        try
        {
            //polynomial is not empty
            Node *current = head;
            while(current->next != NULL)
            {
                cCoefficient = current->info.getCoefficient();
                
                //overflow testing
                if((value > 0 && cCoefficient > 0 && LONG_MAX - value < cCoefficient) ||
                   (value < 0 && cCoefficient < 0 && LONG_MIN - value > cCoefficient))
                {
                    throw overflow;
                }
                
                value += cCoefficient;
                exponentDifference = current->info.getExponent()-current->next->info.getExponent();
                cExponent = pow(x,exponentDifference);
                
                copy = value; //copy value for overflow testing
                value *= cExponent;
                
                //overflow testing
                if(cExponent !=0 && value/cExponent != copy)
                {
                    throw overflow;
                }
                
                current = current->next;
            }
            
            
            cCoefficient = current->info.getCoefficient();
            
            //overflow testing
            if((value > 0 && cCoefficient > 0 && LONG_MAX - value < cCoefficient) ||
               (value < 0 && cCoefficient < 0 && LONG_MIN - value > cCoefficient))
            {
                throw overflow;
            }
            value += cCoefficient;
            
            cExponent = pow(x,current->info.getExponent());
            copy = value; //copy value for overflow testing
            value *= cExponent;
            
            //overflow testing
            if(cExponent != 0 && value/cExponent != copy)
            {
                throw overflow;
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
    }
    return value;
    
} //END member function Polynomial::evaluate()