#include "Utils.h"
#include <iomanip>

std::string nformat_time(const std::chrono::system_clock::time_point& time_point, time_type type){
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    std::ostringstream oss;
    oss.imbue(std::locale("en_US.UTF-8"));
    switch (type) {
    case TIME_COMPLETE:
        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        break;
    case TIME_NO_DATE:
        oss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
        break;
    default:
        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        break;
    }

    return oss.str();
}

size_t nHashString(std::string str){
    return std::hash<std::string>{}(str);
}