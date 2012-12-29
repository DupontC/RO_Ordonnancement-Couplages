//
//  diagramme.cpp
//  reecherche_operationel
//
//  Created by Cyril_Dupont on 16/11/12.
//
//

#include "diagramme.h"

using namespace std;

//construteur
Diagramme::Diagramme(){}

/**
 * \fn split
 * \param s String
 * \param delim String
 * \param elems liste d'elements
 * \brief Fonction pour spliter une string
 */
std::vector<std::string> &split2(const std::string &s, char delim, std::vector<std::string> &elems) {
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
std::vector<std::string> split2(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split2(s, delim, elems);
}

Tache Diagramme::getHighLevel(){
    std::string highLevelTache="alpha";
    int level=0;
    std::map<std::string, Tache>::iterator it;
    
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache tache = it->second;
        if(tache.level>level){
            highLevelTache=tache.name;
            level=tache.level;
        }
    }
    Tache t= getTache(highLevelTache);
    return t;
}

void Diagramme::tacheLevel(int level){
    std::map<std::string, Tache>::iterator it;
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache &tache = it->second;
        if(tache.level==level){
            ressourceForTache(tache);
        }
    }
}

void Diagramme::addOmega(){
    int cost=0,nb_succ=0;
    Tache tache=getHighLevel();
    std::vector<std::string> next;
    std::vector<std::string> previous;
    std::map<std::string, Tache>::iterator it;
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache &t=it->second;
        next=seachNext(t.name);
        if(next.empty()){
            previous.push_back(t.name);
            nb_succ=nb_succ+1;
        }
        next.clear();
    }
    
    Tache omega("omega",cost,nb_succ,tache.level+1,previous);
    omega.critique=true;
    TacheList.insert(pair<std::string, Tache>("omega", omega));
    cout <<"add omega"<<endl;
    
}

void Diagramme::addAlpha(){
    std::vector<std::string> previous;
    std::map<std::string, Tache>::iterator it;
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache &tache=it->second;
        if(tache.succ==0){
            cout <<"add alpha" <<endl;
            tache.succ=1;
            (tache.previous).push_back("alpha");
        }
    }
    Tache alpha("alpha",0,0,0,previous);
    alpha.marge=0;
    alpha.critique=true;
    TacheList.insert(pair<std::string, Tache>("alpha", alpha));
}

Tache Diagramme::getTache(std::string key){
    std::map<std::string, Tache>::iterator it;
    it = TacheList.find(key);
    if(it != TacheList.end())
        return it->second;
}

Tache& Diagramme::getTache2(std::string key){
    std::map<std::string, Tache>::iterator it;
    it = TacheList.find(key);
    if(it != TacheList.end())
        return it->second;
}

Ressource& Diagramme::getRessource(std::string key){
    std::map<std::string, Ressource>::iterator it;
    it = ressources.find(key);
    if(it != ressources.end())
        return it->second;
}

void Diagramme::updateLevel() {
    std::map<std::string, Tache>::iterator it;
    std::vector<std::string>::iterator it2;
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache &tache = it->second;
        for(it2=tache.previous.begin();it2 != tache.previous.end();it2++){
            Tache t=getTache(*it2);
            if(t.level>=tache.level){
                tache.level=t.level+1;
            }
        }
    }
}


void Diagramme::updateAllLevel(){
    updateLevel();
    updateLevel();
    updateLevel();
}

std::vector<std::string> Diagramme::seachNext(std::string t0){
    std::vector<std::string> next;
    std::map<std::string, Tache>::iterator it;
    std::vector<std::string>::iterator it2;
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache t1=it->second;
        for(it2=t1.previous.begin();it2 != t1.previous.end();it2++){
            if(t0.compare(*it2)==0){
                next.push_back(t1.name);
            }
        }
    }
    return next;
}

void Diagramme::updateEarlyDate(std::string name){
    std::vector<std::string> next;
    std::string alpha="alpha";
    std::vector<std::string>::iterator it;
    Tache courant=getTache(name);
    next=seachNext(courant.name);
    for(it=next.begin();it != next.end();it++){
        Tache &t=getTache2(*it);
        if(t.earlyDate<=courant.earlyDate){
            t.earlyDate=courant.earlyDate+courant.cost;
            updateEarlyDate(t.name);
        }else if(courant.earlyDate+courant.cost>=t.earlyDate){
            t.earlyDate=courant.earlyDate+courant.cost;
            updateEarlyDate(t.name);
        }
    }
    
}

void Diagramme::updateLateDate(std::string name){
    Tache &courant=getTache2(name);
    std::vector<std::string>::iterator it;
    for(it=(courant.previous).begin();it != (courant.previous).end();it++){
        Tache &tmp=getTache2(*it);
        tmp.lateDate=courant.lateDate-tmp.cost;
        tmp.marge=tmp.lateDate-tmp.earlyDate;
        if(tmp.marge==0){
            tmp.critique=true;
        }
        updateLateDate(tmp.name);
    }
}



void Diagramme::diplayCritiqueWay(std::string fileOut){
    std::map<std::string, Tache>::iterator it;
    ofstream fichier(fileOut.c_str(), ios::out|ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    if(fichier)
    {
        Tache &omega=getTache2("omega");
        fichier<<"-----------------------------------"<<endl;
        fichier<<"CRITICAL PATH"<<endl;
        fichier<<"-----------------------------------"<<endl<<endl;
        for(int i=0;i<=omega.level;i++){
            for(it = TacheList.begin() ; it != TacheList.end(); it++){
                Tache t=it->second;
                if(t.level==i && t.critique==true){
                    //cout <<t.name<<" "<<t.level<<endl;
                    fichier <<t.name<<" - ";
                }
            }
        }
        fichier<<endl<<endl;
        fichier.close();
    }else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
}

void Diagramme::display(std::string fileOut){
    std::map<std::string, Tache>::iterator it;
    
    diplayCritiqueWay(fileOut);
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache t=it->second;
        t.display(fileOut);
    }
}

void Diagramme::closeFileGraphviz(){
    ofstream fichier("graphviz.dot", ios::out|ios::app);  // ouverture en écriture avec effacement du fichier ouvert
    if(fichier)
    {
        fichier<<"}";
    }else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void Diagramme::linkForGraphviz(Tache &t1, Tache &t2){
    ofstream fichier("graphviz.dot", ios::out|ios::app);  // ouverture en écriture avec effacement du fichier ouvert
    t2.displayForGraphviz();
    if(fichier)
    {
        fichier <<" -> ";
        fichier.close();
        t1.displayForGraphviz();
        fichier.open("graphviz.dot", ios::out|ios::app);
        fichier <<"[style=bold];"<<endl;
        fichier.close();
        
    }else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
}

void Diagramme::displayForGraphviz(){
    std::map<std::string, Tache>::iterator it;
    std::vector<std::string>::iterator it2;
    ofstream fichier("graphviz.dot", ios::out|ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    if(fichier)
    {
        fichier <<"digraph G{"<<endl;
        fichier <<"rankdir = LR;"<<endl;
        fichier <<"make_string [label=\"nomTache(plutot,plutard,marge)\",color=\".7 .3 1.0\"];"<<endl;
        fichier.close();
        
    }else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        (it->second).configForm();
    }
    
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache &courant=it->second;
        if(courant.succ>0){
            for(it2=(courant.previous).begin();it2 != (courant.previous).end();it2++){
                Tache &previous=getTache2(*it2);
                linkForGraphviz(courant, previous);
            }
        }
    }
    closeFileGraphviz();
}

void Diagramme::loadRessource(std::string fileRessource){
    std::ifstream text;
    std::string name;
    int nb;
    std::string ress;
    text.open(fileRessource.c_str());
    cout << "ressource file" <<endl;
    
    if(text.is_open())
    {
        std::string line = "";
        
        //on recupere le nombre de tache
        getline(text, line);
        std::vector<std::string> nbRess=split2(line, ' ');
        std::vector<std::string>::iterator itnbRess;
        for (itnbRess = nbRess.begin() ; itnbRess < nbRess.end(); itnbRess++)
        {
            if(itnbRess - nbRess.begin() == 0)
            {
                std::stringstream ss;
                ss << *itnbRess;
                ss >> nb;
            }
        }
        //on crée les ressources pour le diagramme
        for(int i=1;i<=nb;i++){
            std::stringstream ss;
            ss << i;
            ss >> ress;
            //cout << ress <<endl;
            Ressource r(ress,false);
            ressources.insert(pair<std::string, Ressource>(ress,r));
        }
        
        //ensuite on regardes les couplages possible entre les taches et les ressources
        while(text.good())
        {
            //on recupere chaque ligne du fichier
            getline(text, line);
            if(line.length() != 0)
            {
                //on recupere les arguments de la ligne
                cout << line << endl;
                std::vector<std::string> x = split2(line, ' ');
                std::vector<std::string>::iterator it;
                //on parcour les différents elements
                for (it = x.begin() ; it < x.end(); it++)
                {
                    if(it - x.begin() == 0)
                    {
                        //name of tache
                        name = *it;
                        Tache &tache=getTache2(name);
                    }else{
                        Ressource r(*it,false);
                        Tache &tache=getTache2(name);
                        //cout << "tache "<< tache.name <<endl;
                        tache.ressourceDispo.push_back(r);
                    }
                }
            }
        }
        text.close();
    }else{
        cout << "can't open the resources file" <<endl;
    }
}

bool ressourceDispo(std::string name){
    
}

int nombreRessourceForTache(Tache t){
    std::vector<Ressource>::iterator it;
    int nbRessource=0;
    for(it = t.ressourceDispo.begin() ; it != t.ressourceDispo.end(); it++){
        nbRessource++;
    }
    return nbRessource;
}

std::string Diagramme::getRessourceLibre(Tache t){
    std::vector<Ressource>::iterator it;
    for(it = t.ressourceDispo.begin() ; it != t.ressourceDispo.end(); it++){
        Ressource &r=getRessource((*it).name);
        if(r.freeDate<=t.earlyDate)
            return r.name;
    }
    return "";
}

void Diagramme::ressourceForTache(Tache &t){
        std::string thisRessource;
        if(nombreRessourceForTache(t)==1){
            //si la tache peut etre coupler a une seule ressource alors on regardes si elle est disponible
            thisRessource=(t.ressourceDispo.at(0)).name;
            Ressource &r=getRessource(thisRessource);
            
            //on regarde si la ressource est disponible dés la date au plus tôt
            if(r.freeDate<=(t.earlyDate)){
                //la ressource disponible --> on l'affecte + on fixe la date de liberation de ressource
                (t.ressourceAffecter)=r.name;
                r.freeDate=(t.earlyDate)+(t.cost);
                
            }else if(r.freeDate<=t.lateDate){//on regarde si elle sera disponible sans retarder le projet
                //la ressource sera disponible --> on l'affecte + on fixe la date de liberation de ressource + modification earlyDate + modification marge
                t.ressourceAffecter=r.name;
                r.freeDate=t.earlyDate+t.cost;
                t.earlyDate=r.freeDate;
                t.marge=t.lateDate-t.earlyDate;
                
            }/*else{
              //imposible de liberer la ressource critique pour tache a partir de la date au plus tard --> retard dans le projet donc couplage imposible
              }
              */
        }else{//la tache peut etre couplée à plusieurs ressources
            //on regarde si une ressource est libre pour cette tache
            thisRessource=getRessourceLibre(t);
            if(thisRessource!=""){
                //on recupere la ressource concernet
                Ressource &r=getRessource(thisRessource);
                //on l'affecte + on fixe la date de liberation de ressource
                t.ressourceAffecter=r.name;
                r.freeDate=t.earlyDate+t.cost;
                
            }else{//si aucune des ses ressources sont libre on attends qu'une se libére
                //on parcours les ressources qui peuvent etre couplées à la tache , et on regarde si on peut l'affecter de façon à ce que le tps <= latedate
                std::vector<Ressource>::iterator iit;
                for(iit = t.ressourceDispo.begin() ; iit != t.ressourceDispo.end(); iit++){
                    Ressource &r=*iit;
                    if(r.freeDate<=t.lateDate && t.ressourceAffecter!=""){//on regarde si elle sera disponible sans retarder le projet
                        //la ressource sera disponible --> on l'affecte + on fixe la date de liberation de ressource + modification earlyDate + modification marge
                        t.ressourceAffecter=r.name;
                        r.freeDate=t.earlyDate+t.cost;
                        t.earlyDate=r.freeDate;
                        t.marge=t.lateDate-t.earlyDate;
                    }
                }
            }
        }
}

void Diagramme::affectationsRessource(){
    //on cherche le nombre de niveau dans le graph
    Tache omega=getTache("omega");
    int levelMax=omega.level;
    bool couplage;
    
    //on affecte les ressources au taches niveau par niveau
    for(int currentLevel=1 ;currentLevel<=levelMax;currentLevel++){
        tacheLevel(currentLevel);
    }
}

void Diagramme::init(std::string fileout, std::string ressources){
    //creation du graphe
    addAlpha();
    updateAllLevel();
    addOmega();
    
    std::map<std::string, Tache>::iterator it;
    std::vector<std::string>::iterator it2;
    
    int start=0;
    for(it = TacheList.begin() ; it != TacheList.end(); it++){
        Tache tache=it->second;
        for(it2=tache.previous.begin();it2 != tache.previous.end();it2++){
            if(start==0 && strcmp("alpha",(*it2).c_str())==0){
                updateEarlyDate(*it2);
                start=1;
            }
        }
    }
    
    Tache &omega=getTache2("omega");
    //gestion des date au plutot
    cout << "earlyDate"<<endl;
    omega.lateDate=omega.earlyDate;
    //gesttion des dates au plus tard
    cout << "lateDate"<<endl;
    updateLateDate("omega");
    cout << "marge & critical"<<endl;
    
    //gestion des ressources &  allocation
    loadRessource(ressources);
    affectationsRessource();
    
    std::map<std::string, Tache>::iterator iit;
    for(iit = TacheList.begin() ; iit != TacheList.end(); iit++){
        Tache &tache = iit->second;
        cout<<tache.name<<" --R--> "<<tache.ressourceAffecter<<endl;
    }
    
    //gestion des fichiers de sorties
    display(fileout);
    displayForGraphviz();
    //affichage des diagrammes .dot si Graphviz est présent sous Unix
    cout << "Affichage du diagrammes de potentiel-taches dans un terminal x11 et géneration du diagramme en format png " <<endl;
    cout << "ATTENTION MESSAGES D'ERREUR SI GRAPHVIZ EST PAS INSTALLÉ SUR LA MACHINE UNIX --> A NE PAS PRENDRE EN COMPTE DANS CE CAS" <<endl;
    system("dot -Tx11 graphviz.dot");
    system("dot -Tpng graphviz.dot > diagramme_perte.png");
}
