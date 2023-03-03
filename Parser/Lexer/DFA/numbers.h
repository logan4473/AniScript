#ifndef NUMBERS_H
#define NUMBERS_H

bool numbers(std::string& tokenString) {

    std::string::iterator it = tokenString.begin();

    if(*it=='+' || *it=='-') it++;

    if(it==tokenString.end()) return false;

    while(it!=tokenString.end() && isdigit(*it)) it++;

    if(it==tokenString.end()) return true;

    if(*it=='.') it++;

    if(it==tokenString.end()) return false;

    while(it!=tokenString.end() && isdigit(*it)) it++;

    return (it==tokenString.end());
}

#endif