//
//  ressource.h
//  
//
//  Created by Cyril Dupont on 27/12/12.
//
//

#ifndef ____ressource__
#define ____ressource__

#include <iostream> // pour std::cout
#include <string>   // pour std::string
#include <vector>
#include <fstream>


class Ressource{
public:
    std::string name;
    int freeDate;
    bool busy;
    std::string owner;
    int level;
    
    Ressource(std::string,bool);
    
};
#endif /* defined(____ressource__) */
