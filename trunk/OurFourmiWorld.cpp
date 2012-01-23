
#include "OurFourmiWorld.h"

OurFourmiWorld::OurFourmiWorld()
{
 linkcellules();
 initcellules();
 morefood(Xnest-40, Ynest+40, 13, 5);
 morefood(Xnest-55, Ynest-55, 13, 5);
 morefood(Xnest+70, Ynest-70, 13, 5);
 morefood(Xnest+85, Ynest+85, 13, 5);
 dothepalette();
 screen1 = create_bitmap(InitPlayfield::ScrW, InitPlayfield::ScrH);
}

OurFourmiWorld::~OurFourmiWorld()
{
 destroy_bitmap(screen1);
}


// Init palette colors

void  OurFourmiWorld::dothepalette()
{
int c=0;

      palette[0].r = 0;
      palette[0].g = 0;
      palette[0].b = 0;

      palette[1].r = 255;
      palette[1].g = 255;
      palette[1].b = 255;

      palette[2].r = 0;
      palette[2].g = 255;
      palette[2].b = 0;

      palette[3].r = 255;
      palette[3].g = 255;
      palette[3].b = 0;



   for (c=4; c<256; c++)
   {
      palette[c].r = c-3;
      palette[c].g = 0;
      palette[c].b = 0;
   }

 set_palette(palette);
}

// Init the cellz

void OurFourmiWorld::initcellules()
{
struct Cellule *cellz;
int i,j,k;

for(i=0; i<Wgrille; i++)
 for(j=0; j<Hgrille; j++)
  {
  cellz=&field[j*Wgrille+i];

  cellz->nbfood=0;
  cellz->nbpherofood=0;
  cellz->pherotemp=0;
  cellz->nbpheronest = (int)(((i-Xnest)*(i-Xnest) + (j-Ynest)*(j-Ynest)) );
  }
}



// link the cellules

void OurFourmiWorld::linkcellules()
{
struct Cellule *cellz;
int lig, col;

cellz=&field[0];                     // en haut a gauche
cellz->H  = 0;
cellz->HG = 0;
cellz->HD = 0;
cellz->G  = 0;
cellz->D  = &field[1];
cellz->B  = &field[Wgrille];
cellz->BG = &field[Wgrille+1];
cellz->BD = 0;

cellz=&field[Wgrille-1];            // en haut a droite
cellz->H  = 0;
cellz->HG = 0;
cellz->HD = 0;
cellz->G  = &field[Wgrille-2];
cellz->D  = 0;
cellz->B  = &field[2*Wgrille-1];
cellz->BG = &field[2*Wgrille-2];
cellz->BD = 0;

cellz=&field[Wgrille*(Hgrille-1)];  // en bas a gauche
cellz->H  = &field[Wgrille*(Hgrille-2)];
cellz->HG = 0;
cellz->HD = &field[Wgrille*(Hgrille-2)+1];
cellz->G  = 0;
cellz->D  = &field[Wgrille*(Hgrille-1)+1];
cellz->B  = 0;
cellz->BG = 0;
cellz->BD = 0;

cellz=&field[Wgrille*Hgrille-1];    // en bas a droite
cellz->H  = &field[Wgrille*(Hgrille-1)-1];
cellz->HG = &field[Wgrille*(Hgrille-1)-2];
cellz->HD = 0;
cellz->G  = &field[Wgrille*Hgrille-2];
cellz->D  = 0;
cellz->B  = 0;
cellz->BG = 0;
cellz->BD = 0;


lig=0;                             // ligne du haut
for(col=1; col<Wgrille-1; col++)
{
cellz=&field[lig*Wgrille+col];
cellz->H  = 0;
cellz->HG = 0;
cellz->HD = 0;
cellz->G  = &field[lig*Wgrille+col-1];
cellz->D  = &field[lig*Wgrille+col+1];
cellz->B  = &field[(lig+1)*Wgrille+col];
cellz->BG = &field[(lig+1)*Wgrille+col-1];
cellz->BD = &field[(lig+1)*Wgrille+col+1];
}

col=0;                            // ligne a gauche
for(lig=1; lig<Hgrille-1; lig++)
{
cellz=&field[lig*Wgrille];
cellz->H  = &field[(lig-1)*Wgrille];
cellz->HG = 0;
cellz->HD = &field[(lig-1)*Wgrille+1];
cellz->G  = 0;
cellz->D  = &field[lig*Wgrille+1];
cellz->B  = &field[(lig+1)*Wgrille];
cellz->BG = 0;
cellz->BD = &field[(lig+1)*Wgrille+1];
}

lig=Hgrille-1;                         // ligne du bas
for(col=1; col<Wgrille-1; col++)
{
cellz=&field[lig*Wgrille+col];
cellz->H  = &field[(lig-1)*Wgrille+col];
cellz->HG = &field[(lig-1)*Wgrille+col-1];
cellz->HD = &field[(lig-1)*Wgrille+col+1];
cellz->G  = &field[lig*Wgrille+col-1];
cellz->D  = &field[lig*Wgrille+col+1];
cellz->B  = 0;
cellz->BG = 0;
cellz->BD = 0;
}

col=Wgrille-1;                         // ligne a droite
for(lig=1; lig<Hgrille-1; lig++)
{
cellz=&field[lig*Wgrille+col];
cellz->H  = &field[(lig-1)*Wgrille+col];
cellz->HG = &field[(lig-1)*Wgrille+col-1];
cellz->HD = 0;
cellz->G  = &field[lig*Wgrille+col-1];
cellz->D  = 0;
cellz->B  = &field[(lig+1)*Wgrille+col];
cellz->BG = &field[(lig+1)*Wgrille+col-1];
cellz->BD = 0;
}

for(col=1; col<Wgrille-1; col++)        // the middle cellz
 for(lig=1; lig<Hgrille-1; lig++)
 {
 cellz=&field[lig*Wgrille+col];
 cellz->H  = &field[(lig-1)*Wgrille+col];
 cellz->HG = &field[(lig-1)*Wgrille+col-1];
 cellz->HD = &field[(lig-1)*Wgrille+col+1];
 cellz->G  = &field[lig*Wgrille+col-1];
 cellz->D  = &field[lig*Wgrille+col+1];
 cellz->B  = &field[(lig+1)*Wgrille+col];
 cellz->BG = &field[(lig+1)*Wgrille+col-1];
 cellz->BD = &field[(lig+1)*Wgrille+col+1];
 }

}


// Some extra food

void OurFourmiWorld::morefood(int xcentre, int ycentre, int rayon, int density)
{
struct Cellule *cellz;
int lig, col;
float f;

 for(lig=ycentre-rayon; lig<ycentre+rayon; lig++)
  for(col=xcentre-rayon; col<xcentre+rayon; col++)
  {
   f =(xcentre-col)*(xcentre-col) + (ycentre-lig)*(ycentre-lig);
   if( f <rayon*rayon)
   {
    cellz=&field[lig*Wgrille+col];
    if((rand()%density)==1) cellz->nbfood=nbfoodcellz;
   }
  }

}

