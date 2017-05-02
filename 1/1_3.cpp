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
#include <cctype>

using  std::string;
void URLfy (string& s, unsigned int l);
void URLfyV2 (string& s, int l);

int main()
{
    string s="Mr john smith        ";
    std::cout << "Before: " << s << std::endl;
    URLfyV2(s,13);
    std::cout << "After: " << s << std::endl;
    return 0;
}


void URLfy (string& s, unsigned int l)
{
    unsigned int newL = l;
    string::size_type i = 0;

    while (i < newL) {
            //i found a space in the middle of the string
        if (isspace(s[i])) {
            for (unsigned int j = newL; j > i; j--){
                // we know there is the space
                s[j+2] = s[j];
            }
            s[i++] = '%';
            s[i++] = '2';
            s[i] = '0';
            newL+= 2;
        }
        i++;
    }
}

void URLfyV2 (string& s, int l)
{
    int spaceCount = 0;
    int i = 0, index = 0;
    for (i = 0; i < l; i++) {
        if (isspace(s[i]))
            spaceCount++;
    }

    index = l + spaceCount*2;

    for (i = l-1;i >= 0;i--) {
        if (isspace(s[i])) {
            s[index-1] = '0';
            s[index-2] = '2';
            s[index-3] = '%';
            index = index - 3;
        }
        else {
        s[index-1] = s[i];
        index--;
       }
    }
}
