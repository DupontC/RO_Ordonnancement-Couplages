/**
 * \file tache.h
 * \author  Cyril Dupont Jérémy Euvrard
 * \date    16/11/12
 * \brief Declaration de la class Taches avec le prototype des fonctions
 */

#ifndef reecherche_operationel_tache_h
#define reecherche_operationel_tache_h

#include <iostream> // pour std::cout
#include <string>   // pour std::string
#include <vector>
#include <fstream>
#include "ressource.h"

/**
 * \class Tache. Permet de crée une tache composer de ressource possible. Cette classe est utilisé pour la création des objets Diagramme
 */
class Tache{
public:
    std::string name;
    int cost;
    int succ;
    int level;
    int earlyDate;
    int lateDate;
    int marge;
    bool critique;
    std::vector<std::string> previous;
    std::vector<Ressource> ressourceDispo;
    std::string ressourceAffecter;

   
    Tache(std::string,int,int,int);
    Tache(std::string,int,int,int,std::vector<std::string>);
    void addPrevious(std::string);
    void display(std::string );
    void displayForGraphviz();
    void configForm();
};

#endif
