//
//  ressource.cpp
//  
//
//  Created by Cyril Dupont on 27/12/12.
//
//

#include "ressource.h"
using namespace std;

//construteur ressource
Ressource::Ressource(std::string name,bool busy)
{
    this->name=name;
    this->busy=busy;
}