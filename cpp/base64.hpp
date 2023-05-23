#ifndef BASE_64_H
#define BASE_64_H
#include <string>
using namespace std;

string to_base64(unsigned char const*, unsigned int len);
string un_base64(string const& s);

#endif
