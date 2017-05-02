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
#include <stdlib.h>

using std::string;
using std::vector;

bool oneway (const string & a, const string& b);
bool onewayV2 (const string & a, const string& b);

int main()
{
    string a = "pele";
    string b = "pale";
    if (onewayV2(a,b)) {

        std::cout << "true!" << std::endl;
    }
    else
    std::cout << "false!" << std::endl;
    return 0;
}


bool oneway (const string & a, const string& b)
{
    if (abs(a.size()-b.size())>1)
        return false;
    vector<int> v(128);

    for (int i=0; i<a.size();++i) {
        v[a[i]]++;
    }
    for (int i=0; i<b.size();++i) {
        v[b[i]]++;
    }
    int error = 0;

    for (int i=0; i<128;++i) {
        if (v[i]==1)
            error++;
    }
    if (error>1)
        return false;

    return true;
}


bool onewayV2 (const string & a, const string& b)
{
    if (abs(a.size()-b.size())>1)
        return false;
    string s1,s2;
    int i = 0, j = 0;
    bool error = false;

    s1 = a.size() > b.size() ? a : b;
    s2 = a.size() > b.size() ? b : a;


    while ( i < s1.size() && j < s2.size()) {
        if (s1[i] != s2[j]) {
            if (error) return false;
            error = true;

            if (s1.size()== s2.size())
                j++;
        }
        else {
            j++;
        }

        i++;
    }
    return true;
}
