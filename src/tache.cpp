//
//  tache.cpp
//  reecherche_operationel
//
//  Created by Cyril_Dupont on 16/11/12.
//
//

#include "tache.h"
using namespace std;

//construteur de tache
Tache::Tache(string name,int cost,int succ,int level,std::vector<std::string> previous)
{
    this->name=name;
    this->cost=cost;
    this->succ=succ;
    this->level=level;
    this->previous=previous;
    this->critique=false;
    this->earlyDate=0;
    this->lateDate=0;
    this->marge=0;
}

Tache::Tache(string name,int cost,int succ,int level)
{
    this->name=name;
    this->cost=cost;
    this->succ=succ;
    this->level=level;
    this->critique=false;
    this->earlyDate=0;
    this->lateDate=0;
    this->marge=0;
}

void Tache::addPrevious(std::string nameNext){
    this->previous.push_back(nameNext);
}

void Tache::display(std::string fileOut){
    ofstream fichier(fileOut.c_str(), ios::out|ios::app);  // ouverture en écriture
    std::string resCritique="false";
    if(critique==1)
        resCritique="true";
        
    if(fichier)
    {
        fichier << endl<<"-----------------------------------" <<endl;
        fichier <<"Nom tache : " << name <<endl;
        fichier <<"  cost :" << cost <<endl;
        fichier <<"  level :" << level <<endl;
        fichier <<"  earlyDate :" << earlyDate <<endl;
        fichier <<"  lateDate :"<< lateDate << endl;
        fichier <<"  marge :"<< marge<<endl;
        fichier <<"  Critical :"<<resCritique << endl;
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
}
void Tache::configForm(){
    ofstream fichier("graphviz.dot", ios::out|ios::app);  // ouverture en écriture
    if(fichier)
    {
        displayForGraphviz();
        if(critique==true)
            fichier << "[color=red]";
        fichier<<"[shape=box];"<<endl;
    }
}

void Tache::displayForGraphviz(){
    ofstream fichier("graphviz.dot", ios::out|ios::app);  // ouverture en écriture
    if(fichier)
    {
        fichier<<"\""<<name<<"("<<earlyDate<<" , "<<lateDate<<" , "<<marge<<")"<<"\"";
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;

}
