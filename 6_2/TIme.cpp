#include "Time.h"
#include <stdexcept>

uint16_t Time::getHours() const {
    return hours;
}

void Time::setHours(uint16_t hours) {
    if (hours > 23) throw std::runtime_error("Invalid hours");
    Time::hours = hours;
}

uint16_t Time::getMinutes() const {
    return minutes;
}

void Time::setMinutes(uint16_t minutes) {
    if (minutes > 59) throw std::runtime_error("Invalid minutes");
    Time::minutes = minutes;
}

uint16_t Time::getSeconds() const {
    return seconds;
}

void Time::setSeconds(uint16_t seconds) {
    if (seconds > 59) throw std::runtime_error("Invalid seconds");
    Time::seconds = seconds;
}

Time::Time(std::uint16_t h, std::uint16_t m, std::uint16_t s) {
    if (h > 23) throw std::runtime_error("Invalid hours");
    if (m > 59) throw std::runtime_error("Invalid minutes");
    if (s > 59) throw std::runtime_error("Invalid seconds");

    hours = h;
    minutes = m;
    seconds = s;
}

bool Time::operator>(Time another) const {
    if (hours > another.hours) return true;
    else if (hours < another.hours) return false;

    if (minutes > another.minutes) return true;
    else if (minutes < another.minutes) return false;

    if (seconds > another.seconds) return true;
    else if (seconds < another.seconds) return false;
}

std::ostream& operator<<(std::ostream& os, Time t) {
    return os << (t.hours < 10 ? "0" : "") << t.hours << ':' << (t.minutes < 10 ? "0" : "") << t.minutes << ':' << (t.seconds < 10 ? "0" : "") << t.seconds;
}
