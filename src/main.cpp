
/**
 * \file main.cpp
 * \author  Cyril Dupont
 * \date    16/11/12
 * \brief Fichier qui lance le tp de recherche operationel (chargement du graph et recherche des taches aux plus tot et au plus tard )
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
    if(argc>0)
        readFile(argv,diag);
    else{
        cout << "no file name in argument"<<endl;
        return 0;
    }
    if(argv[2]){
        diag.init(argv[2],argv[3]);
    }else{
        cout << "no file name for file out"<<endl;
    }
    return 1;
}

