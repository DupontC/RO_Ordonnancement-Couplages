//
//  tache.h
//  reecherche_operationel
//
//  Created by Cyril_Dupont on 16/11/12.
//
//

#ifndef reecherche_operationel_tache_h
#define reecherche_operationel_tache_h

#include <iostream> // pour std::cout
#include <string>   // pour std::string
#include <vector>
#include <fstream>


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
   
    Tache(std::string,int,int,int);
    Tache(std::string,int,int,int,std::vector<std::string>);
    void addPrevious(std::string);
    void display(std::string );
    void displayForGraphviz();
    void configForm();
};

#endif
