#ifndef OUT_OF_RANGE_EXCEPTION
#define OUT_OF_RANGE_EXCEPTION
#include <iostream>
using namespace std;
/*
    Author: Ky Lam
    Date: October 29, 2023
    Description: This class helps control and run when the exception appears.
*/
class OutOfRangeExcept:public exception
{
    public:
        const char* what() const throw()
        {
            return "An empty list or invalid position";
        }
};

#endif