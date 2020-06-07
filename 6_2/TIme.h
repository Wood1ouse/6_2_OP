#ifndef SORT_TIME_H
#define SORT_TIME_H

#include <cstdint>
#include <iostream>

class Time {
    std::uint16_t hours = 0;
    std::uint16_t minutes = 0;
    std::uint16_t seconds = 0;
public:
    Time() = default;
    Time(std::uint16_t h, std::uint16_t m, std::uint16_t s);

    uint16_t getHours() const;
    void setHours(uint16_t hours);
    uint16_t getMinutes() const;
    void setMinutes(uint16_t minutes);
    uint16_t getSeconds() const;
    void setSeconds(uint16_t seconds);

    bool operator>(Time another) const;
    friend std::ostream& operator<<(std::ostream& os, Time t);
};


#endif //SORT_TIME_H
