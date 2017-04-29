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
