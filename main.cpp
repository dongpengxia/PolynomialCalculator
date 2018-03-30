/*
 *  main.cpp
 *
 *  Polynomial Calculator
 *
 *  10/6/2016
 *  Dongpeng Xia
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>
#include "Term.h"
#include "Polynomial.h"

using std::string;
using std::stringstream;
using std::fstream;
using std::cout;
using std::endl;

//exception classes
class fileOpenError{};
class tooFewArguments{};

//loadPolynomials reads input file data into two polynomials
void loadPolynomials(string, Polynomial&, Polynomial&);

//displayOutput prints program output
void displayOutput(Polynomial&, Polynomial&);

//global constant
const string OVERFLOW_ERROR = "Overflow Detected";



int main(int argc, const char * argv[])
{
    try
    {
        if(argc > 1)
        {
            string filePath = string(argv[1]); //fileNameAndPath passed in
            
            Polynomial p1;
            Polynomial p2;
        
            loadPolynomials(filePath, p1, p2);
            displayOutput(p1,p2);
        }
        else
        {
            //error: not enough arguments
            tooFewArguments error;
            throw error;
        }
        
    }//END try block
    catch(overFlowException error)
    {
        cout << OVERFLOW_ERROR << endl;
    }
    catch(tooFewArguments error)
    {
        cout << "ERROR: Not enough arguments. Need file name and path." << endl;
    }
    catch(termAdditionError error)
    {
        cout << "ERROR: Can not add two terms with different exponents." << endl;
    }
    catch(termSubtractionError error)
    {
        cout << "ERROR: Can not subtract two terms with different exponents." << endl;
    }
    catch(indexOutOfRange error)
    {
        cout << "ERROR: Attempted to use at function to access invalid position" << endl;
    }
    catch(bad_alloc error)
    {
        cout << "ERROR: Failed to allocate dynamic memory" << endl;
    }
    catch(fileOpenError error)
    {
        cout << "ERROR: Input file failed to open." << endl;
    }
    catch( ... )
    {
        cout << "ERROR: UNKNOWN ERROR CAUGHT IN MAIN" << endl;
        
    } //END catch all block
    
    return 0;
    
}//END function main()



//function loadPolynomials opens fileNameAndPath and loads Polynomials p1 and p2 from input data
void loadPolynomials(string fileNameAndPath, Polynomial &p1, Polynomial &p2)
{
    try
    {
        fstream inFileStream;
        
        //Open file name and path
        inFileStream.open(fileNameAndPath.c_str());
    
        //If the input data file failed to open
        if(!inFileStream)
        {
            fileOpenError fileError;
            throw fileError;
        }
        else
        {
            //fileNameAndPath opened correctly
            string str;
            stringstream stream;
            
            //Get polynomial 1
            getline(inFileStream,str);
            stream << str;
            stream >> p1;
            
            stream.str(""); //set string stream to blank
            stream.clear(); //clear string stream
            
            //Get polynomial 2
            getline(inFileStream,str);
            stream << str;
            stream >> p2;
        }
        
        inFileStream.close();
        
        p1.selectionSort();
        p1 = p1.simplify();
        p2.selectionSort();
        p2 = p2.simplify();
    }
    catch(fileOpenError error)
    {
        throw;
    }
    catch( ... )
    {
        throw;
    }
} //end loadPolynomials function



//function displayOutput displays the output for polynomials 1 and 2 from the input file
void displayOutput(Polynomial &p1, Polynomial &p2)
{
    Polynomial result;
    
    cout << "Polynomial 1: f(x): " << p1 << endl;
    try
    {
        cout << "f(1) = ";
        cout << p1.evaluate(1) << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
    }
    try
    {
        cout << "f(2) = ";
        cout << p1.evaluate(2) << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
    }
    try
    {
        cout << "f(3) = ";
        cout << p1.evaluate(3) << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
    }
    try
    {
        cout << "f(10) = ";
        cout << p1.evaluate(10) << endl << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl << endl;
    }
    
    
    cout << "Polynomial 2: g(x): " << p2 << endl;
    try
    {
        cout << "g(1) = ";
        cout << p2.evaluate(1) << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
    }
    try
    {
        cout << "g(2) = ";
        cout << p2.evaluate(2) << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
    }
    try
    {
        cout << "g(3) = ";
        cout << p2.evaluate(3) << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
    }
    try
    {
        cout << "g(10) = ";
        cout << p2.evaluate(10) << endl << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl << endl;
    }
    
    
    bool firstCalcOverflow = false; //flag for whether result (f(x) + g(x)) is overflowed
    try
    {
        cout << "f(x) + g(x) = ";
        result = p1 + p2;
        cout << result << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
        firstCalcOverflow = true; //result did not calculate properly, so no further evaluations
    }
    if(firstCalcOverflow)
    {
        cout << "(f + g)(1) = " << OVERFLOW_ERROR << endl;
        cout << "(f + g)(2) = " << OVERFLOW_ERROR << endl;
        cout << "(f + g)(3) = " << OVERFLOW_ERROR << endl;
        cout << "(f + g)(10) = " << OVERFLOW_ERROR << endl << endl;
    }
    else
    {
        //p1 + p2 did not overflow
        try
        {
            cout << "(f + g)(1) = ";
            cout << result.evaluate(1) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f + g)(2) = ";
            cout << result.evaluate(2) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f + g)(3) = ";
            cout << result.evaluate(3) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f + g)(10) = ";
            cout << result.evaluate(10) << endl << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl << endl;
        }
    }
    
    
    firstCalcOverflow = false; //reset flag, now doing p1 - p2
    try
    {
        cout << "f(x) - g(x) = ";
        result = p1 - p2;
        cout << result << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
        firstCalcOverflow = true;
    }
    if(firstCalcOverflow) //result overflowed, so the next 4 calculations will also have errors
    {
        cout << "(f - g)(1) = " << OVERFLOW_ERROR << endl;
        cout << "(f - g)(2) = " << OVERFLOW_ERROR << endl;
        cout << "(f - g)(3) = " << OVERFLOW_ERROR << endl;
        cout << "(f - g)(10) = " << OVERFLOW_ERROR << endl << endl;
    }
    else
    {
        //p1 - p2 did not overflow, proceed to evaluations
        try
        {
            cout << "(f - g)(1) = ";
            cout << result.evaluate(1) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f - g)(2) = ";
            cout << result.evaluate(2) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f - g)(3) = ";
            cout << result.evaluate(3) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f - g)(10) = ";
            cout << result.evaluate(10) << endl << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl << endl;
        }
    }
    
    
    firstCalcOverflow = false; //reset flag, now on p1 * p2
    try
    {
        cout << "f(x) * g(x) = ";
        result = p1 * p2;
        cout << result << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
        firstCalcOverflow = true;
    }
    if(firstCalcOverflow) //result overflowed, so the next 4 calculations will also have errors
    {
        cout << "(f * g)(1) = " << OVERFLOW_ERROR << endl;
        cout << "(f * g)(2) = " << OVERFLOW_ERROR << endl;
        cout << "(f * g)(3) = " << OVERFLOW_ERROR << endl;
        cout << "(f * g)(10) = " << OVERFLOW_ERROR << endl << endl;
    }
    else
    {
        try
        {
            cout << "(f * g)(1) = ";
            cout << result.evaluate(1) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f * g)(2) = ";
            cout << result.evaluate(2) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f * g)(3) = ";
            cout << result.evaluate(3) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
        try
        {
            cout << "(f * g)(10) = ";
            cout << result.evaluate(10) << endl << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl << endl;
        }
    }
    
    
    Polynomial p1Copy = p1; //make a copy for exponentiation
    
    firstCalcOverflow = false;
    try
    {
        cout << "f^5(x) = ";
        p1Copy.expon(5);
        cout << p1Copy << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
        firstCalcOverflow = true; //f^5 overflowed
    }
    
    
    try
    {
        cout << "f(x)^(g(5)) = ";
        result = p1; //copy p1 into result
        result.expon(p2.evaluate(5));
        cout << result << endl;
    }
    catch(overFlowException)
    {
        cout << OVERFLOW_ERROR << endl;
    }
    
    
    if(firstCalcOverflow)
    {
        //f^5 overflowed, no evaluation necessary
        cout << "(f^5)(2) = " << OVERFLOW_ERROR << endl;
    }
    else
    {
        //f^5 is valid, use pre-computed f^5 stored in p1Copy
        try
        {
            cout << "(f^5)(2) = ";
            cout << p1Copy.evaluate(2) << endl;
        }
        catch(overFlowException)
        {
            cout << OVERFLOW_ERROR << endl;
        }
    }
} //end displayOutput function