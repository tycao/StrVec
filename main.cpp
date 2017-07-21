#include "strvec.h"

int main(int argc, char *argv[])
{
    StrVec s1;
    s1.push_back("Hi Mom!");
    s1.push_back("Hi Dad!");
    s1.push_back("Hi son!");
    cout << "s1.size() : " << s1.size() << endl;
    cout << "s1.capacity() : " << s1.capacity() << endl;
    cout << *(s1.begin()) << " " << *(s1.end()) << endl;

    StrVec s2(s1);
    cout << "s2.capacity() : " << s2.capacity() << endl;
    cout << *(s2.begin()) << endl;
    if (s2.end())
        cout << "*(s2.end()) not empty..." << endl;
}
