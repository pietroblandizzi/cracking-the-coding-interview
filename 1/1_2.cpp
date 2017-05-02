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
#include <vector>
#include <string>
#include <algorithm>

using  std::string;
using  std::vector;
bool isPermutation (const string& a, const string& b);
bool isPermutationV2 (string a, string b);

int main()
{
    string a = "ciaociao";
    string b = "cioeoiac";

    if (isPermutationV2(a,b)) {
         std::cout << "yes" << std::endl;
    }
    else {
         std::cout << "no" << std::endl;
    }
    return 0;
}


// i cannot modify the strings
bool isPermutation (const string& a, const string& b)
{
    if (a.size() != b.size ())
        return false;

     vector<int>  charset(128); //assuming ASCII
     typedef string::size_type s_type;

    for (s_type i = 0; i < a.size(); ++i) {
        int val = a.at(i);
        charset[val]++;
    }

    for (s_type i = 0; i < b.size(); ++i) {
        int val = b.at(i);
        charset[val]--;
        if (charset[val] < 0)
            return false;
    }
    return true;
}
//i pass a copy of the string so i can modify it
bool isPermutationV2 (string a, string b)
{
    if (a.size() != b.size ())
        return false;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

     typedef string::size_type s_type;
    //the strings must have same length
    for (s_type i = 0; i < a.size(); ++i) {
        if (a[i]!=b[i])
            return false;
    }

    return true;
}
