/***************************************************************
 * Name:      Common.cpp
 * Purpose:   Code for Common function
 * Author:     ()
 * Created:   2018-02-26
 * Copyright:  ()
 * License:
 **************************************************************/


 #include "Common.h"
 #include <sstream>
/**
Helper Function
**/
std::string Common::IntToStr(int num) {
    std::stringstream ss;
    ss << num;
    std::string str = ss.str();
    return str;
}
