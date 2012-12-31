/**
 * \file tache.cpp
 * \author  Cyril Dupont Jérémy Euvrard
 * \date    16/11/12
 * \brief Fichier contenent l'enssemble des methodes liées à la class Tache 
 */

#include "tache.h"
using namespace std;

/**
 * \fn Tache
 * \param name String. Nom de la tahce
 * \param cost int. Cout pour réaliser la tache
 * \param succ int. Nombre de succeseur.
 * \param vecteur String. Nom des taches qui la précéde
 */
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

/**
 * \fn Tache
 * \param name String. Nom de la tahce
 * \param cost int. Cout pour réaliser la tache
 * \param succ int. Nombre de succeseur.
 * \param level int. Niveau de la tache dans le graph
 */
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

/**
 * \fn addPrevious
 * \param nameNext String. Permet d'ajouter un voisin (nameNext) a la tache courante.
 */
void Tache::addPrevious(std::string nameNext){
    this->previous.push_back(nameNext);
}

/**
 * \fn display
 * \param fileOut String. Nom du fichier de sortie (resultat).
 */
void Tache::display(std::string fileOut){
    std::string monFichier="./resultats/"+fileOut;
    ofstream fichier(monFichier.c_str(), ios::out|ios::app);  // ouverture en écriture
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
        fichier <<"  ressource :" << ressourceAffecter <<endl;
        fichier <<"  Critical :"<<resCritique << endl;
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
}

/**
 * \fn configForm
 */
void Tache::configForm(){
    ofstream fichier("./resultats/graphviz.dot", ios::out|ios::app);  // ouverture en écriture
    if(fichier)
    {
        displayForGraphviz();
        if(critique==true)
            fichier << "[color=red]";
        fichier<<"[shape=box];"<<endl;
    }
}

/**
 * \fn displayForGraphviz
 */
void Tache::displayForGraphviz(){
    ofstream fichier("./resultats/graphviz.dot", ios::out|ios::app);  // ouverture en écriture
    if(fichier)
    {
        fichier<<"\""<<name<<"("<<earlyDate<<" , "<<lateDate<<" , "<<marge<<")"<<"\"";
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;

}
