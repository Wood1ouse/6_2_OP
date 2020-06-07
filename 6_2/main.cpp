#include <iostream>
#include "smooth_sort.h"
#include "HexNumber.h"
#include "Time.h"

#include <string>
int main() {
    char* arrString[] = { (char*)"dbc", (char*)"bbb", (char*)"aaa", (char*)"123", (char*)"321" };
    smoothSort(arrString);
    for (auto&& i : arrString) std::cout << i << '\n';
    std::cout << '\n';

    HexNumber arrHex[] = { "faa", "100", "5a", "bb", "9f" };
    smoothSort(arrHex);
    for (auto&& i : arrHex) std::cout << i << '\n';
    std::cout << '\n';

    Time arrTime[] = { {20, 40, 10}, {18, 45, 15}, {17, 22, 12}, {17, 22, 10}, {23, 12, 2}, {14, 3, 12} };
    smoothSort(arrTime);
    for (auto&& i : arrTime) std::cout << i << '\n';
    return 0;
}
