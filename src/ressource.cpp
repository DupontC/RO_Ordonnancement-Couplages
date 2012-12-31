/**
 * \file ressource.cpp
 * \author  Cyril Dupont Jérémy Euvrard
 * \date    16/11/12
 * \brief Methode liée a la classe Ressource
 */

#include "ressource.h"
using namespace std;

/**
 * \fn Ressource
 * \param name String. Nom de la ressource.
 * \param busy boolean. Permet de savoir si la ressource est occupée.
 * \brief Contruteur de la classe Ressource
 */
Ressource::Ressource(std::string name,bool busy)
{
    this->name=name;
    this->busy=busy;
    this->freeDate=0;
    this->owner="";
    this->level=-1;
}