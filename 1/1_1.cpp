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
#include <string>
#include <vector>

using std::string;
using std::vector;


bool isunique (const string& s);
bool isuniqueV2 (const string& s);

int main()
{
    string s = "cciao";

    if (isuniqueV2(s))
        std::cout << "All characters are unique" << std::endl;
    else
        std::cout << "Characters not unique "<< std::endl;
    return 0;
}


bool isunique (const string& s)
{
    if (s.size() > 128)
        return false;
    //we are taking ASCII
    vector<bool> char_set(128);
    for (string::size_type i=0; i<s.size(); ++i) {
        int val = s.at(i);
        if (char_set[val])
            return false;

        char_set[val] = true;
    }
   return true;
}

bool isuniqueV2 (const string& s)
{
    if (s.size() > 128)
        return false;
    //we are taking ASCII
    int check = 0;
    for (string::size_type i=0; i<s.size(); ++i) {
        int val = s.at(i) - 'a';
        int a = 'a';
        std::cout << val << " a " <<  a << std::endl;
        if ( (check & (1 << val)) > 0  )
            return false;

        check |= (1 << val);
    }
   return true;
}
