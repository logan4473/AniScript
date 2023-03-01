#ifndef NUMBERS_H
#define NUMBERS_H

bool numbers(std::string& tokenString) {

    std::string::iterator it = tokenString.begin();

    while(it!=tokenString.end() && isdigit(*it)) it++;

    return (it==tokenString.end());
}

#endif