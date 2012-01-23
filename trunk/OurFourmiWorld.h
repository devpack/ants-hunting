#ifndef __OURFOURMIWORLD_H_
#define __OURFOURMIWORLD_H_

#include "InitPlayfield.h"
#include <allegro.h>

const int   Wgrille = 240;          // OurFourmiWorld grille size x
const int   Hgrille = 240;          // OurFourmiWorld grille size y

//////////////////////////////////////////////////////////////////////
///                   CLASS OurFourmiWorld                         ///
//////////////////////////////////////////////////////////////////////

// cell type

struct Cellule{
int    nbfood;
int    nbpherofood;
int    pherotemp;
int    nbpheronest;
struct Cellule *H;
struct Cellule *B;
struct Cellule *G;
struct Cellule *D;
struct Cellule *HD;
struct Cellule *HG;
struct Cellule *BD;
struct Cellule *BG;
};

// Our World grille type

class OurFourmiWorld
{
protected:
          PALETTE palette;
          BITMAP *screen1;
          struct Cellule field[Wgrille*Hgrille];

          static const int   Xnest;
          static const int   Ynest;

          static const int   nbfoodcellz;

public:
       OurFourmiWorld();
       virtual ~OurFourmiWorld();

       void linkcellules();
       void initcellules();
       void dothepalette();
       void morefood(int xcentre, int ycentre, int rayon, int density);
       inline void clearscreen1() { clear_bitmap(screen1); };
       inline void blitscreen1(){ blit(screen1, screen, 0, 0, 0, 0, screen1->w, screen1->h); };

};

#endif
