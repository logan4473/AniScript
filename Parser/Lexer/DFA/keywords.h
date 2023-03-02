#ifndef KEYWORDS_H
#define KEYWORDS_H

int keyword(std::string& tokenString) {

    if(tokenString=="exit") return tok_exit;
    
    if(tokenString=="if") return tok_if;

    if(tokenString=="else") return tok_else;

    return 0;
}

#endif