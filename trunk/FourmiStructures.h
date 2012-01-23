#ifndef __FOURMITRUCTURES_H_
#define __FOURMITRUCTURES_H_

const int   Nbfourmicellz = 26;

//////////////////////////////////////////////////////////////////////
///                         STRUCTURES                             ///
//////////////////////////////////////////////////////////////////////

// state: food taken or not

struct Fourmi{
int state;     // 0=allé (cherche food) & 1=retour (ramene food)
int type;      // exploratrice ou classique
int movetime;  // time to go straight
int lastmove;
};

// type cellule pour la grille

struct Cellule{
int active;
int nbfourmi;
int nbfood;
float nbphero;
struct Fourmi fourmiz[Nbfourmicellz];
struct Cellule *H;
struct Cellule *B;
struct Cellule *G;
struct Cellule *D;
struct Cellule *HD;
struct Cellule *HG;
struct Cellule *BD;
struct Cellule *BG;
};

#endif
