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

using std::string;

bool IsSubstring (const string& , const string&);
bool StringRotation (const string& , const string&);
bool StringRotationV2 (const string& , const string&);
int main()
{
    string s1 = "waterbottle";
    string s2 = "wrbottlewat";

    if (StringRotationV2 (s1,s2)) {
        std::cout << "Yes" << std::endl;
    }
    else         std::cout << "No" << std::endl;
    return 0;
}



bool StringRotation (const string& s1, const string& s2)
{
    if (s1.size()!= s2.size()) return false;

    string rot = "";
    int start = 0;

    for (int i = 0; i < s1.size(); i++) {
        if (s1[i]==s2[0]){
            //found the start point of rotation
            start = i;
            break;
        }
        rot.push_back (s1[i]);
    }
    //no rotation
    if (start==0 || start==s1.size())
        return false;

    for (int i = start; i <s1.size(); i++) {
        if (s1[i]!= s2[i-start])
            return false;
    }
    if (IsSubstring (s2,rot))
        return true;

     return false;
}

bool StringRotationV2 (const string& s1, const string& s2)
{
    if (s1.size()!= s2.size()) return false;
    string conc = s2+s2;
    if (IsSubstring(conc,s1))
        return true;
    return false;
}

bool IsSubstring (const string& s1, const string& s2)
{
    if (s1.find(s2) != std::string::npos)
        return true;

    return false;
}

