#include "HexNumber.h"


HexNumber::HexNumber(const std::string& num) {
    hexValue = std::stoi(num, 0, 16);
}

HexNumber::HexNumber(const char* num) {
    hexValue = std::stoi(num, 0, 16);
}

std::ostream& operator<<(std::ostream& os, HexNumber h) {
    return os << std::hex << h.hexValue << std::dec;
}

bool HexNumber::operator>(HexNumber another) const {
    return hexValue > another.hexValue;
}

void HexNumber::set(const std::string& num) {
    hexValue = std::stoi(num, 0, 16);
}
