/**
 * \file ressource.h
 * \author  Cyril Dupont Jérémy Euvrard
 * \date    16/11/12
 * \brief Declaration de la class Ressource avec le prototype des fonctions
 */

#ifndef ____ressource__
#define ____ressource__

#include <iostream> // pour std::cout
#include <string>   // pour std::string
#include <vector>
#include <fstream>

/**
 * \class Ressource. Permet de crée une ressource utilisée par les taches et le diagramme.
 */
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
