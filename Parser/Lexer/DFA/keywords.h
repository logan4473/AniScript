#ifndef KEYWORDS_H
#define KEYWORDS_H

int keyword(std::string& tokenString) {
    if(tokenString=="exit") return tok_exit;
    std::cout<<"Not a keyword"<<std::endl;
    return 0;
}

#endif