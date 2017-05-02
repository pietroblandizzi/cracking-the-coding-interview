/*****************************************************************************
Copyright (c) [2017] [Blandizzi Pietro]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*********************************************************************************/

#include <iostream>
#include <map>
#include <string>
#include <cctype>

using std::string;
bool isPalPerm (const string& s);
bool isPalPermOpt (const string& s);
bool isPalPermBit (const string& s);

int main()
{
    string s = "Tact Coa";
    std::cout << "This is the string: " << s << std::endl;
    if (isPalPermBit(s))
        std::cout << "Yes" << std::endl;
     else
        std::cout << "No" << std::endl;

    return 0;
}


bool isPalPerm (const string& s)
{
    std::map<char,int> charset;
    typedef string::const_iterator s_it;
    for (s_it it = s.begin();it != s.end(); ++it) {
        if (!isspace((*it))) {
            charset[tolower((*it))]++;
        }
    }
    bool n_odd = false;

    typedef std::map<char,int>::iterator m_it;
    for (m_it it = charset.begin();it != charset.end(); ++it) {

        if ((it->second % 2) != 0 ) {
            if (n_odd) {return false;}
            else {n_odd = true;}
        }
    }
    return true;
}


bool isPalPermOpt (const string& s)
{
    int n_odd = 0;
    std::map<char,int> charset;
    typedef string::const_iterator s_it;
    for (s_it it = s.begin();it != s.end(); ++it) {
        if (!isspace((*it))) {
            charset[tolower((*it))]++;
            if ((charset[tolower((*it))] % 2) !=0 )  {
                n_odd ++;
            }
            else {
                n_odd --;
            }
        }
    }
    return n_odd <= 1;
}


bool isPalPermBit (const string& s)
{
    int bitVec = 0;
    typedef string::const_iterator s_it;
    for (s_it it = s.begin();it != s.end(); ++it) {
        if (!isspace((*it))) {
            int val = (*it) -'a';
            int mask = 1 << val;
            if (( bitVec & mask) == 0 ) {
                bitVec |= mask;
            }
            else {
                bitVec &= ~mask;
            }
        }
    }
    return bitVec == 0 || (bitVec & (bitVec-1)) == 0;
}
