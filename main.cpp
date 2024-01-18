#include <iostream>

class Date {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    bool isOurEra;

public:
    
    Date() : year(1960), month(1), day(1), hour(0), minute(0), second(0), isOurEra(true) {}

    
    Date(int year, int month, int day, int hour, int minute, int second, bool isOurEra)
        : year(year), month(month), day(day), hour(hour), minute(minute), second(second), isOurEra(isOurEra) {}

    // Метод для проверки високосного года
    bool isLeapYear(int year) const;

    // Методы add и subtract
    Date add(int years, int months, int days, int hours, int minutes, int seconds) const;
    Date subtract(int years, int months, int days, int hours, int minutes, int seconds) const;

    // Перегрузка операторов
    Date& operator=(const Date& other);
    bool operator==(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    // Функция для определения количества дней в месяце
    int days_in_month(int year, int month) const;

    
};

bool Date::isLeapYear(int year) const {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    } else {
        return false;
    }
}

Date Date::add(int years, int months, int days, int hours, int minutes, int seconds) const {
    int new_year = year;
    int new_month = month;
    int new_day = day + days;
    int new_hour = hour + hours;
    int new_minute = minute + minutes;
    int new_second = second + seconds;

    if (new_second >= 60) {
        new_minute += new_second / 60;
        new_second %= 60;
    }

    if (new_minute >= 60) {
        new_hour += new_minute / 60;
        new_minute %= 60;
    }

    if (new_hour >= 24) {
        new_day += new_hour / 24;
        new_hour %= 24;
    }

    
    while (new_month <= 0) {
        new_year--;
        new_month += 12;
    }

    while (new_month > 12) {
        new_year++;
        new_month -= 12;
    }

    while (new_day <= 0) {
        if (--new_month == 0) {
            new_month = 12;
            new_year--;
        }
        new_day += days_in_month(new_year, new_month);
    }

    while (new_day > days_in_month(new_year, new_month)) {
        new_day -= days_in_month(new_year, new_month);
        if (++new_month == 13) {
            new_month = 1;
            new_year++;
        }
    }

    return Date(new_year, new_month, new_day, new_hour, new_minute, new_second, isOurEra);
}

Date Date::subtract(int years, int months, int days, int hours, int minutes, int seconds) const {
    int new_year = year;
    int new_month = month;
    int new_day = day - days;
    int new_hour = hour - hours;
    int new_minute = minute - minutes;
    int new_second = second - seconds;

    
    if (new_second < 0) {
        new_minute += new_second / 60 - 1;
        new_second = 60 + new_second % 60;
    }

    if (new_minute < 0) {
        new_hour += new_minute / 60 - 1;
        new_minute = 60 + new_minute % 60;
    }

    if (new_hour < 0) {
        new_day += new_hour / 24 - 1;
        new_hour = 24 + new_hour % 24;
    }

    
    while (new_month <= 0) {
        new_year--;
        new_month += 12;
    }

    while (new_month > 12) {
        new_year++;
        new_month -= 12;
    }

    while (new_day <= 0) {
        if (--new_month == 0) {
            new_month = 12;
            new_year--;
        }
        new_day += days_in_month(new_year, new_month);
    }

    while (new_day > days_in_month(new_year, new_month)) {
        new_day -= days_in_month(new_year, new_month);
        if (++new_month == 13) {
            new_month = 1;
            new_year++;
        }
    }

    return Date(new_year, new_month, new_day, new_hour, new_minute, new_second, isOurEra);
}

int Date::days_in_month(int year, int month) const {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return -1;
    }
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        
        year = other.year;
        month = other.month;
        day = other.day;
        hour = other.hour;
        minute = other.minute;
        second = other.second;
        isOurEra = other.isOurEra;
    }
    return *this;
}

bool Date::operator==(const Date& other) const {

    return true; 
}

bool Date::operator>(const Date& other) const {
    

    return true; 
}

bool Date::operator<(const Date& other) const {
    

    return true; 
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    
    os << "Date: (" << date.year << " year, " << date.month << " month, " << date.day << " day, ";
    os << date.hour << " hours, " << date.minute << " minutes, " << date.second << " sec., ";
    if (date.isOurEra) {
        os << "Our Era)";
    } else {
        os << "Previous Era)";
    }

    return os;
}

int main() {
    
    Date date1; 
    Date date2(2024, 1, 18, 12, 30, 0, true); 

    std::cout << date1 << std::endl;
    std::cout << date2 << std::endl;

    // Пример использования методов add и subtract
    Date newDate = date1.add(1, 0, 0, 0, 0, 0);
    std::cout << newDate << std::endl;

    newDate = date2.subtract(0, 1, 0, 0, 0, 0);
    std::cout << newDate << std::endl;

    if (date1 == date2) {
        std::cout << "Date 1 is equal to Date 2" << std::endl;
    } else if (date1 < date2) {
        std::cout << "Date 1 is before Date 2" << std::endl;
    } else {
        std::cout << "Date 1 is after Date 2" << std::endl;
    }

    return 0;
}
