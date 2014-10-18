/***********************************************************************************************
 * Copyright (C) 2014 Qinsi Wang and Edmund M. Clarke.  All rights reserved.
 * By using this software the USER indicates that he or she has read, understood and will comply
 * with the following:
 *
 * 1. The USER is hereby granted non-exclusive permission to use, copy and/or
 * modify this software for internal, non-commercial, research purposes only. Any
 * distribution, including commercial sale or license, of this software, copies of
 * the software, its associated documentation and/or modifications of either is
 * strictly prohibited without the prior consent of the authors. Title to copyright
 * to this software and its associated documentation shall at all times remain with
 * the authors. Appropriated copyright notice shall be placed on all software
 * copies, and a complete copy of this notice shall be included in all copies of
 * the associated documentation. No right is granted to use in advertising,
 * publicity or otherwise any trademark, service mark, or the name of the authors.
 *
 * 2. This software and any associated documentation is provided "as is".
 *
 * THE AUTHORS MAKE NO REPRESENTATIONS OR WARRANTIES, EXPRESSED OR IMPLIED,
 * INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT
 * USE OF THE SOFTWARE, MODIFICATIONS, OR ASSOCIATED DOCUMENTATION WILL NOT
 * INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS OR OTHER INTELLECTUAL PROPERTY
 * RIGHTS OF A THIRD PARTY.
 *
 * The authors shall not be liable under any circumstances for any direct,
 * indirect, special, incidental, or consequential damages with respect to any
 * claim by USER or any third party on account of or arising from the use, or
 * inability to use, this software or its associated documentation, even if the
 * authors have been advised of the possibility of those damages.
 * ***********************************************************************************************/

// evaluate the +/-/*// expressions in the current rv file
// return the final version of rv file

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "evalrv.hpp"

using namespace std;


//compare the binding priorities between two operators
char cmp(char a,char b)
{
    switch(a)
    {
        case '#': // the lowest priority
            return ('#' == b)? '=' : '<';
            break;
            
        case '-':
        case '+':
        {
            if('*' == b || '/' == b || '(' == b)
            {
                return '<';
            }
            else
            {
                return '>';
            }
        }
            break;
            
        case '*':
        case '/':
        {
            return ('('==b)?'<':'>';
        }
            break;
            
        case '(':
            return (')'==b)?'=':'<';
            break;
        default:
            throw "error:unkown operator";
    }
}

//compute the results for "+,-,*,/" for reals
double calc(double a, double b, char op)
{
    switch(op)
    {
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            if(b == 0)
                throw "error: the divisor shoud not be negtive.";
            else
                return a/b;
        default:
            throw "error: unknown operator.";
    }
}

//tell whether the current char c is an operator
bool isoptr(char c)
{
    // legal operators
    static string optrs("+-*/()#");
    
    if(optrs.find(c) == string::npos)
    {
        if(isdigit(c))
            return false;
        else if(c == '.')
            return false;
        else
            throw "error: unknown char.";
    }
    return true;
}

//compute the value of expression e
double eval(std::string e)
{
    e += "#"; // # indicates the end of the expression
    stack<double> opnd;
    stack<char> optr;
    optr.push('#');
    int i = 0;  // starts with the init of e
    double num = 0;
    
    while(e[i] != '#' || optr.top() != '#')
    {
        
        if(!isoptr(e[i]))
        {
            stringstream ss;
            string s;
            while(!isoptr(e[i]))
            {
                ss << e[i];
                ++i;
            }
            ss >> s;
            const char * c = s.c_str();
            num = atof(c);
            //cout << num << endl;
            opnd.push(num);
        }
        
        else
        {
            if(optr.empty())
            {
                throw "error: optr is empty";
            }
            switch(cmp(optr.top(),e[i]))
            {
                case '<':
                    optr.push(e[i]);
                    ++i;
                    break;
              
                case '=':
                    optr.pop();
                    ++i;
                    break;
               
                case '>':
                    if(opnd.empty())
                    {
                        throw "error: opnd is empty.";
                    }
                    
                    double a = opnd.top();
                    //cout << a << endl;
                    opnd.pop();
                    if(opnd.empty())
                    {
                        throw "error: opnd is empty.";
                    }
                    
                    double b = opnd.top();
                    //cout << b << endl;
                    opnd.pop();
                    
                    opnd.push(calc(b, a, optr.top()));
                    optr.pop();
                    break;
            }
        }
    }
    return opnd.top();
}
