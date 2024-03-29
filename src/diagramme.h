/**
 * \file diagramme.h
 * \author  Cyril Dupont
 * \date    16/11/12
 * \brief Declaration de la class Diagramme avec le prototype des fonctions
 */


#ifndef reecherche_operationel_diagramme_h
#define reecherche_operationel_diagramme_h

#include <iostream> // pour std::cout
#include <fstream>
#include <sstream>
#include <string>   // pour std::string
#include "ressource.h"
#include <map>
#include <vector>
#include <stdio.h>
#include "tache.h"
#include <fstream>

/**
 * \class Diagramme. Permet de crée un diagramme composer de taches et de ressources
 */
class Diagramme{
public:
    std::map<std::string,Tache> TacheList;
    std::map<std::string,Ressource> ressources;
    bool couplage;
    Diagramme();
    
    Tache getHighLevel();
    void addOmega();
    void addAlpha();
    Tache getTache(std::string);
    Tache& getTache2(std::string);
    Ressource& getRessource(std::string);
    void updateLevel();
    std::vector<std::string> seachNext(std::string );
    void tacheLevel(int );
    void updateAllLevel();
    void updateEarlyDateALL();
    void updateEarlyDate(std::string );
    void updateLateDate(std::string );
    void updateLateDate2(std::string);
    void diplayCritiqueWay(std::string);
    void display(std::string);
    void closeFileGraphviz();
    void linkForGraphviz(Tache &,Tache &);
    void displayForGraphviz();
    void loadRessource(std::string);
    std::string getRessourceLibre(Tache);
    void affectationsRessource();
    void init(std::string,std::string);
    void ressourceForTache(Tache &);
    
};

#endif
