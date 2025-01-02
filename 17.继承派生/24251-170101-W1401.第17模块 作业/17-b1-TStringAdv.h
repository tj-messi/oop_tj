/*2351114 Öì¿¡Ôó ´óÊý¾Ý*/
#include "17-b1-TString.h"

const int SUBSTRMAXNUM = 2147483600;

class TStringAdv : public TString {
public:
    // Constructors
    TStringAdv();
    TStringAdv(const char* s);
    TStringAdv(const TString& s);
    TStringAdv(const TStringAdv& s);

    // Assign methods
    TStringAdv& assign(const TStringAdv& ts2);
    TStringAdv& assign(const char* s);

    // Append methods
    TStringAdv& append(const TStringAdv& ts2);
    TStringAdv& append(const char* s);
    TStringAdv& append(const char& c);

    // Insert methods
    TStringAdv& insert(const TStringAdv& ts2, int pos);
    TStringAdv& insert(const char* s, int pos);
    TStringAdv& insert(const char& c, int pos);

    // Erase methods
    TStringAdv& erase(const TStringAdv& ts2);
    TStringAdv& erase(const char* s);
    TStringAdv& erase(const char& c);

    // Substring method
    TStringAdv substr(const int pos, const int len = SUBSTRMAXNUM) const;

    // Access character method
    char& at(const int n);

    
};
// Length function equivalent
int TStringAdvLen(const TString& obj);
