//
//  main.c
//  reecherche_operationel
//
//  Created by Cyril_Dupont on 16/11/12.
//
//
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

//fonction pour spliter une string
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

//fonction pour spliter une string
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}




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


int main(int argc, char** argv) {
    Diagramme diag;
    if(argc>0)
        readFile(argv,diag);
    else{
        cout << "no file name in argument"<<endl;
        return 0;
    }
    if(argv[2]){
        diag.init(argv[2]);
    }else{
        cout << "no file name for file out"<<endl;
    }
    return 1;
}

