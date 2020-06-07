#ifndef SORT_HEXNUMBER_H
#define SORT_HEXNUMBER_H

#include <string>
#include <iostream>

class HexNumber {
    int hexValue;
public:
    HexNumber() = default;
    HexNumber(const std::string& num);
    HexNumber(const char* num);
    void set(const std::string& num);
    friend std::ostream& operator<<(std::ostream& os, HexNumber h);
    bool operator>(HexNumber another) const;
};


#endif //SORT_HEXNUMBER_H
