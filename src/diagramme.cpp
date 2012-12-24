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
    int i=0;
    std::map<std::string, Tache>::iterator it;
    ofstream fichier(fileOut.c_str(), ios::out|ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    if(fichier)
    {
        Tache &omega=getTache2("omega");
        fichier<<"-----------------------------------"<<endl;
        fichier<<"CRITICAL PATH"<<endl;
        fichier<<"-----------------------------------"<<endl<<endl;
        for(i;i<=omega.level;i++){
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

void Diagramme::init(std::string fileout){
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
    //gestion des fichiers de sorties
    display(fileout);
    displayForGraphviz();
    //affichage des diagrammes .dot si Graphviz est présent sous Unix
    cout << "Affichage du diagrammes de potentiel-taches dans un terminal x11 et géneration du diagramme en format png " <<endl;
    cout << "ATTENTION MESSAGES D'ERREUR SI GRAPHVIZ EST PAS INSTALLÉ SUR LA MACHINE UNIX --> A NE PAS PRENDRE EN COMPTE DANS CE CAS" <<endl;
    system("dot -Tx11 graphviz.dot");
    system("dot -Tpng graphviz.dot > diagramme_perte.png");
}
