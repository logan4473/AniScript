#ifndef LITERAL_H
#define LITERAL_H

bool literal(std::string& tokenString) {

    std::string::iterator it = tokenString.begin();

    if(*it!='\'') return false;
    ++it;
    
    while(isalnum(*it)) ++it;

    if(*it!='\'') return false;
    ++it;

    return (it==tokenString.end());
}

#endif