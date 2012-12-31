
/**
 * \file main.cpp
 * \author  Cyril Dupont
 * \date    16/11/12
 * \brief Fichier qui lance le tp de recherche operationel (chargement du graph et recherche des taches aux plus tot et au plus tard )
 */

/*! \mainpage Index Page
 
 * \section intro_0 Référence
 http://www710.univ-lyon1.fr/~bonnev/TP3.html
 * \section intro_1 Potentiel-tâche et couplage
 *
 * Pour en terminer avec les graphes, l'idée est de combiner les 2 problèmes.
    On suppose que pour chaque tâche, il faut une ressource choisie parmi un sous-ensemble. Chaque ressource est unique et non partageable (ce peut-être un chef-d'équipe spécialisé si on fait un chantier, un processeur (ou noeud de supercalculateur) particulier si les tâches sont des processus, une machine particulière si c'est pour une manufacture, ....). Une fois affectée à une tâche, une ressource ne peut pas être préemptée (elle est conservée par la tâche jusqu'à sa terminaison).
 *
 * \section intro_2 Résultat attendu
 *À l'issu des calculs, 2 situations possibles :
 
 pas d'ordonnancement possible compatible avec les contraintes de couplage : un simple message signifiant l'échec est le minimum attendu; la situation de blocage peut aussi être précisée (tâches et ressources impliquées ainsi que les dates utiles).
 
 il existe un ordonnancement compatible avec les contraintes : un ordonnacement possible a donc été trouvé, il doit être affiché. Ainsi pour chaque tâche, seront affichées les informations suivantes :
 
 date prévue de démarrage,
 marge restante,
 ressource affectée,
 éventuellement la date de fin
 En l'absence d'autres critères, nous nous contenterons de la première solution trouvée.
 
 * \section intro_3 Variantes
 
 Suivant les situations, de nombreuses variantes existes et certaines hypothèses remises en causes. Par exemple, il est possible d'imaginer que les ressources sont préemptibles et les tâches interruptibles (ce peut être le cas par exemple si on considère des affectations de processus sur des ressources particulières), mais souvent il y a des coûts associés (prise en compte du surcoût du à l'interruption, coût et délais si un processus est déplacé d'un processeur à un autre, ...) et les modèles deviennent encore plus complexe.
 
 De même, sur ce problème simple, la dimension économique peut aussi être prise en compte, si on considére des pénalités pour le retard et des coûts associés au ressources : faut-il augmenter le nombre de ressource, si oui pour quelles tâches, ou payer des pénalités, ou combiner ?
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include "diagramme.h"
#define MAX 100

using namespace std;

/**
 * \fn split
 * \param s String
 * \param delim String
 * \param elems liste d'elements
 * \brief Fonction pour spliter une string
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

/**
 * \fn split
 * \param s String
 * \param delim String
 * \brief Fonction pour spliter une string
 */
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}



/**
 * \fn readFile
 * \param fileName String
 * \param diag Diagramme
 * \brief Lit un fichier passer en parametre afin de crée le diagramme associé
 */
int readFile(char ** fileName, Diagramme &diag){
    std::ifstream text;
    text.open(fileName[1]);
    if(text.is_open())
    {
        cout << "reding the file" << endl;
        while(text.good())
        {
            std::string line = "";
            //on recupere chaque ligne du fichier
            getline(text, line);
            if(line.length() != 0)
            {
                std::string name;
                std::vector<std::string> previous;
                int cost;
                int nbNext;
                //on recupere les arguments de la ligne
                cout << line << endl;
                std::vector<std::string> x = split(line, ' ');
                std::vector<std::string>::iterator it;
                
                //on parcour les différents elements
                for (it = x.begin() ; it < x.end(); it++)
                {
                    if(it - x.begin() == 0)
                    {
                        //name of tache
                        name = *it;
                    }
                    else if(it - x.begin() == 1)
                    {
                        //cost of the tache
                        std::stringstream ss;
                        //cast the char to int
                        ss << *it;
                        ss >> cost;
                    }
                    else if(it - x.begin() == 2)
                    {
                        //nunber of @param
                        std::stringstream ss;
                        //cast the char to int
                        ss << *it;
                        ss >> nbNext;
                    }
                    else
                    {
                        //next tache
                        previous.push_back(*it);
                    }
                }
                
                //new tache
                Tache tache(name,cost,nbNext,1,previous);
                //add tache at the diagramme
                diag.TacheList.insert(pair<std::string, Tache>(name, tache));
                //clean
                name.clear();
                previous.clear();
                cost=0;
                nbNext=0;
            }
        }//end of file
        //we close the file
        text.close();
    }else{
        cout << "can't open the file" <<endl;
    }
}


/**
 * \fn main
 * \param fileName String
 * \param outFile String
 * \brief Fonction de lancement du tp
 */
int main(int argc, char** argv) {
    Diagramme diag;
    diag.couplage=true;
    if(argc>0)
        readFile(argv,diag);
    else{
        cout << "(1)no file name in argument"<<endl;
        return 0;
    }
    if(argv[2]){
        diag.init(argv[2],argv[3]);
    }else{
        cout << "(2)no file name for file out"<<endl;
    }
    return 1;
}

