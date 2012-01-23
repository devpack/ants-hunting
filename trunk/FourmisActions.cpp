#include <math.h>
#include "FourmisActions.h"
#include "stdio.h"

// init fourmi

void FourmisActions::initfourmi()
{
struct Fourmi *fourmiz;
int j=0;

 for(j=0; j<Maxfourmi; j++)
 {
  fourmiz=&tbfourmi[j];

  fourmiz->xpos=Xnest;
  fourmiz->ypos=Ynest;
  fourmiz->state=0;              // seek
  fourmiz->rndstatetime=0;
  fourmiz->whichway=rand()%8;    // one way
  fourmiz->nbfood=0;
 }

}


void FourmisActions::Fourmirndmove(int j)
{
struct Fourmi *fourmiz;

 fourmiz=&tbfourmi[j];

  switch(fourmiz->whichway)
  {
   case 0: // Up Left
   if(fourmiz->xpos>1 && fourmiz->ypos>1)
   { fourmiz->xpos--; fourmiz->ypos--; }
   break;

   case 1: // Up
   if(fourmiz->ypos>1)
   fourmiz->ypos--;
   break;

   case 2: // Up Right
   if(fourmiz->xpos+1<Wgrille-1 && fourmiz->ypos>1)
   { fourmiz->xpos++; fourmiz->ypos--; }
   break;

   case 3: // Right
   if(fourmiz->xpos+1<Wgrille-1)
   fourmiz->xpos++;
   break;

   case 4: // Down Right
   if(fourmiz->xpos+1<Wgrille-1 && fourmiz->ypos+1<Hgrille-1)
   { fourmiz->xpos++; fourmiz->ypos++; }
   break;

   case 5: // Down
   if(fourmiz->ypos+1<Hgrille-1)
   fourmiz->ypos++;
   break;

   case 6: // Down Left
   if(fourmiz->xpos>1 && fourmiz->ypos+1<Hgrille-1)
   { fourmiz->xpos--; fourmiz->ypos++; }
   break;

   case 7: // Left
   if(fourmiz->xpos>1)
   fourmiz->xpos--;
   break;

  } // end of switch

 fourmiz->whichway=rand()%8;
}


void FourmisActions::Fourmimaxpheromove(int j)
{
struct Cellule *cellz;
struct Fourmi *fourmiz;
int x, y;

 fourmiz=&tbfourmi[j];
 x=fourmiz->xpos;  y=fourmiz->ypos;
 cellz=&field[y*Wgrille+x];

 // x max phero move
 if( cellz->G->nbpherofood < cellz->D->nbpherofood)
 fourmiz->xpos++;
 if( cellz->G->nbpherofood > cellz->D->nbpherofood)
 fourmiz->xpos--;

 // y max phero move
 if( cellz->H->nbpherofood < cellz->B->nbpherofood)
 fourmiz->ypos++;
 if( cellz->H->nbpherofood > cellz->B->nbpherofood)
 fourmiz->ypos--;

}


void FourmisActions::Fourminestmove(int j)
{
struct Cellule *cellz;
struct Fourmi *fourmiz;
int    x, y;

 fourmiz=&tbfourmi[j];
 x=fourmiz->xpos;  y=fourmiz->ypos;
 cellz=&field[y*Wgrille+x];

 // back to the nest?
 if(x==Xnest && y==Ynest)
 {
 fourmiz->rndstatetime=0;
 fourmiz->state=0;
 nbfoodback += fourmiz->nbfood;
 fourmiz->nbfood=0;
 }

 // If too far -> rnd move
 if(cellz->nbpheronest > Nestlimit)
 {
 fourmiz->rndstatetime=0;
 fourmiz->state=0;
 }

 // put some pheromone
 if(fourmiz->nbfood!=0)
 {
 // first cell
 cellz->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->nbpherofood>nbmaxphero) cellz->nbpherofood=nbmaxphero;

 //petite couronne
 cellz->HG->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->HG->nbpherofood>nbmaxphero) cellz->HG->nbpherofood=nbmaxphero;

 cellz->H->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->H->nbpherofood>nbmaxphero) cellz->H->nbpherofood=nbmaxphero;

 cellz->HD->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->HD->nbpherofood>nbmaxphero) cellz->HD->nbpherofood=nbmaxphero;

 cellz->D->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->D->nbpherofood>nbmaxphero) cellz->D->nbpherofood=nbmaxphero;

 cellz->BD->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->BD->nbpherofood>nbmaxphero) cellz->BD->nbpherofood=nbmaxphero;

 cellz->B->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->B->nbpherofood>nbmaxphero) cellz->B->nbpherofood=nbmaxphero;

 cellz->BG->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->BG->nbpherofood>nbmaxphero) cellz->BG->nbpherofood=nbmaxphero;

 cellz->G->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->G->nbpherofood>nbmaxphero) cellz->G->nbpherofood=nbmaxphero;

 // grande couronne
 cellz->H->H->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->H->H->nbpherofood>nbmaxphero) cellz->H->H->nbpherofood=nbmaxphero;

 cellz->B->B->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->B->B->nbpherofood>nbmaxphero) cellz->B->B->nbpherofood=nbmaxphero;

 cellz->D->D->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->D->D->nbpherofood>nbmaxphero) cellz->D->D->nbpherofood=nbmaxphero;

 cellz->G->G->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->G->G->nbpherofood>nbmaxphero) cellz->G->G->nbpherofood=nbmaxphero;

 cellz->HG->G->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->HG->G->nbpherofood>nbmaxphero) cellz->HG->G->nbpherofood=nbmaxphero;

 cellz->HG->HG->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->HG->HG->nbpherofood>nbmaxphero) cellz->HG->HG->nbpherofood=nbmaxphero;

 cellz->HG->H->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->HG->H->nbpherofood>nbmaxphero) cellz->HG->H->nbpherofood=nbmaxphero;

 cellz->HD->H->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->HD->H->nbpherofood>nbmaxphero) cellz->HD->H->nbpherofood=nbmaxphero;

 cellz->HD->HD->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->HD->HD->nbpherofood>nbmaxphero) cellz->HD->HD->nbpherofood=nbmaxphero;

 cellz->HD->D->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->HD->D->nbpherofood>nbmaxphero) cellz->HD->D->nbpherofood=nbmaxphero;

 cellz->BD->D->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->BD->D->nbpherofood>nbmaxphero) cellz->BD->D->nbpherofood=nbmaxphero;

 cellz->BD->BD->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->BD->BD->nbpherofood>nbmaxphero) cellz->BD->BD->nbpherofood=nbmaxphero;

 cellz->BD->B->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->BD->B->nbpherofood>nbmaxphero) cellz->BD->B->nbpherofood=nbmaxphero;

 cellz->BG->B->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->BG->B->nbpherofood>nbmaxphero) cellz->BG->B->nbpherofood=nbmaxphero;

 cellz->BG->BG->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->BG->BG->nbpherofood>nbmaxphero) cellz->BG->BG->nbpherofood=nbmaxphero;

 cellz->BG->G->nbpherofood += ((pherofood*fourmiz->nbfood)/25);
 if(cellz->BG->G->nbpherofood>nbmaxphero) cellz->BG->G->nbpherofood=nbmaxphero;

 }

 // x nest move
 if( cellz->G->nbpheronest > cellz->D->nbpheronest)
 fourmiz->xpos++;
 if( cellz->G->nbpheronest < cellz->D->nbpheronest)
 fourmiz->xpos--;

 // y nest move
 if( cellz->H->nbpheronest > cellz->B->nbpheronest)
 fourmiz->ypos++;
 if( cellz->H->nbpheronest < cellz->B->nbpheronest)
 fourmiz->ypos--;

}


void FourmisActions::Fourmifollowpheropiste(int j)
{
struct Cellule *cellz;
struct Fourmi *fourmiz;
float  ProbaGauche, ProbaHaut;
int x, y;

 fourmiz=&tbfourmi[j];
 x=fourmiz->xpos;  y=fourmiz->ypos;
 cellz=&field[y*Wgrille+x];

 // Enought phero ?
 if(cellz->nbpherofood<pheropistestop)
 {
  fourmiz->rndstatetime=0;
  fourmiz->state=0;
 }

 // Yes, follow the piste
 //else
 {

  if( cellz->G->nbpherofood > cellz->D->nbpherofood && fourmiz->xpos>1 &&
     cellz->G->nbpheronest>=cellz->D->nbpheronest)
    fourmiz->xpos--;

  if(cellz->G->nbpherofood < cellz->D->nbpherofood && fourmiz->xpos+1<Wgrille-1 &&
     cellz->G->nbpheronest<=cellz->D->nbpheronest)
    fourmiz->xpos++;

  if(cellz->H->nbpherofood > cellz->B->nbpherofood && fourmiz->ypos>1 &&
     cellz->H->nbpheronest>=cellz->B->nbpheronest)
    fourmiz->ypos--;

  if(cellz->H->nbpherofood < cellz->B->nbpherofood && fourmiz->ypos+1<Hgrille-1 &&
    cellz->H->nbpheronest<=cellz->B->nbpheronest)
    fourmiz->ypos++;

  // If no move => s'eloigne du nid

  if(x==fourmiz->xpos && y==fourmiz->ypos)
  {
   if(cellz->G->nbpheronest > cellz->D->nbpheronest && fourmiz->xpos>1)
   fourmiz->xpos--;

   if(cellz->G->nbpheronest < cellz->D->nbpheronest && fourmiz->xpos+1<Wgrille-1)
   fourmiz->xpos++;

   if(cellz->H->nbpheronest > cellz->B->nbpheronest && fourmiz->ypos>1)
   fourmiz->ypos--;

   if(cellz->H->nbpheronest < cellz->B->nbpheronest && fourmiz->ypos+1<Hgrille-1)
   fourmiz->ypos++;
  }


 } // end else follow the piste


}

void FourmisActions::Fourmicheckfood(int j)
{
struct Cellule *cellz;
struct Fourmi *fourmiz;
int f;
int x, y;

 fourmiz=&tbfourmi[j];
 x=fourmiz->xpos;  y=fourmiz->ypos;
 cellz=&field[y*Wgrille+x];

 for(f=0; f<nbfoodcellz; f++)
 {

  if(cellz->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->nbfood--;
  fourmiz->nbfood++;
  }

  if(cellz->HG->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->HG->nbfood--;
  fourmiz->nbfood++;
  }

  if(cellz->H->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->H->nbfood--;
  fourmiz->nbfood++;
  }

  if(cellz->HD->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->HD->nbfood--;
  fourmiz->nbfood++;
  }

  if(cellz->D->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->D->nbfood--;
  fourmiz->nbfood++;
  }

  if(cellz->BD->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->BD->nbfood--;
  fourmiz->nbfood++;
  }

  if(cellz->B->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->B->nbfood--;
  fourmiz->nbfood++;
  }

  if(cellz->BG->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->BG->nbfood--;
  fourmiz->nbfood++;
  }

  if(cellz->G->nbfood!=0 && fourmiz->nbfood<fourmimaxfood)
  {
  cellz->G->nbfood--;
  fourmiz->nbfood++;
  }

 } // end for


 if(fourmiz->nbfood==fourmimaxfood)
 {
 fourmiz->rndstatetime=0;
 fourmiz->state=2;
 }

}


void FourmisActions::Checkfourmimotion(int j)
{
struct Cellule *cellz;
struct Fourmi *fourmiz;
int x, y;

 fourmiz=&tbfourmi[j];
 x=fourmiz->xpos;  y=fourmiz->ypos;
 cellz=&field[y*Wgrille+x];

   // Seek state ?
   if(fourmiz->state==0)
   {
    if(cellz->nbpherofood>0 )
    {
     if(rand()%100<30)              // some rnd move
      Fourmirndmove(j);
     else
      Fourmimaxpheromove(j);        // seek phero piste

     // enought phero found ?
     if(cellz->nbpherofood>pheropistestart)
     {
      fourmiz->rndstatetime=0;
      fourmiz->state=1;            // follow phero piste move
     }

    }
    else // nbpherofood = 0
    {
     Fourmirndmove(j);             // No phero -> rnd move
     Fourmirndmove(j);             // No phero -> rnd move
     Fourmirndmove(j);             // No phero -> rnd move
    }
   }

   // follow phero piste move ?
   if(fourmiz->state==1)
   {
    if(rand()%100<15)                // some rnd move
     Fourmirndmove(j);
    else
     Fourmifollowpheropiste(j);
   }

   // Seek nest: nest move ?
   if(fourmiz->state==2)
   {
    if(rand()%100<20)                // some rnd move
     Fourmirndmove(j);
    else
     Fourminestmove(j);
   }

   // Check for food
   Fourmicheckfood(j);              // if food -> state=2 -> nest move

   // Non productive for too long ?
   if(fourmiz->state==0 && cellz->nbpherofood==0)
    fourmiz->rndstatetime++;
   if(fourmiz->rndstatetime>nothingfoundmaxtime)
   {
    fourmiz->rndstatetime=0;
    fourmiz->state=2;               // yes, go nest
   }

}

void FourmisActions::Fourmimotion()
{
struct Fourmi *fourmiz;
int j=0;

 for(j=0; j<Maxfourmi; j++)
  Checkfourmimotion(j);

}

void FourmisActions::Managepherofood()
{
struct Cellule *cellz;
int i,j;
int Mainconvocoef =  1;
int Otherconvocoef = 1;

 // Convolution de nbpherofood dans pherotemp
 if(cycles%2==0)
 {
 for (j=1; j<Hgrille-2; j++)
  for (i=1; i<Wgrille-2; i++)
  {
  cellz=&field[j*Wgrille+i];

  cellz->pherotemp = ((Mainconvocoef*cellz->nbpherofood +
                      Otherconvocoef*cellz->HG->nbpherofood + Otherconvocoef*cellz->HD->nbpherofood +
                      Otherconvocoef*cellz->BG->nbpherofood + Otherconvocoef*cellz->BD->nbpherofood +
                      Otherconvocoef*cellz->H->nbpherofood + Otherconvocoef*cellz->B->nbpherofood +
                      Otherconvocoef*cellz->G->nbpherofood + Otherconvocoef*cellz->D->nbpherofood)/ (Mainconvocoef + 8*Otherconvocoef) );

  if(cellz->pherotemp<minphero) cellz->pherotemp=0;
  }

 // Copie de pherotemp->nbpherofood + evapo et clear pherotemp
 for (j=1; j<Hgrille-2; j++)
  for (i=1; i<Wgrille-2; i++)
  {
  cellz=&field[j*Wgrille+i];

  cellz->nbpherofood = (cellz->pherotemp*pherocoefevapo)/1000;
  cellz->pherotemp=0;

  if(cellz->nbpherofood<minphero) cellz->nbpherofood=0;
  }

  }
}

// gestion affichage

void FourmisActions::plotscreen()
{
struct Cellule *cellz;
struct Fourmi *fourmiz;
int w=0;
int h=0;
int j=0;
int pherocolor;
int fourmicolor=0;

 //vline(screen1, (ScrW-Wgrille)/2, (ScrH-Hgrille)/2, Hgrille+(ScrH-Hgrille)/2, makecol(255,255,255));
 //vline(screen1, Wgrille+(ScrW-Wgrille)/2, (ScrH-Hgrille)/2, Hgrille+(ScrH-Hgrille)/2, makecol(255,255,255));
 //hline(screen1, (ScrW-Wgrille)/2, (ScrH-Hgrille)/2, Wgrille+(ScrW-Wgrille)/2, makecol(255,255,255));
 //hline(screen1, (ScrW-Wgrille)/2, Hgrille+(ScrH-Hgrille)/2, Wgrille+(ScrW-Wgrille)/2, makecol(255,255,255));

 for(h=0; h<Hgrille; h++)
  for(w=0; w<Wgrille; w++)
  {
  cellz=&field[h*Wgrille+w];

  // Draw pheromones
  pherocolor=(int)cellz->nbpherofood;
  if(pherocolor>255) pherocolor=255;
  if(cellz->nbpherofood>minphero)
  putpixel(screen1, w+(ScrW-Wgrille)/2, h+(ScrH-Hgrille)/2, makecol(pherocolor,0,0));

  // Draw food
  if (cellz->nbfood!=0)
  putpixel(screen1, w+(ScrW-Wgrille)/2, h+(ScrH-Hgrille)/2, makecol(0, 255, 0));

 /*
 // Draw ants
 fourmicolor = 0;
 for(j=0; j<50; j++)
 {
  fourmiz=&tbfourmi[j*(rand()%((2000/50)-1))];
   if(fourmiz->xpos==w && fourmiz->ypos==h)
    fourmicolor += 70;
 }
  if(fourmicolor>255) fourmicolor = 255;

  if(fourmicolor!=0)
  {
  putpixel(screen1, w+(ScrW-Wgrille)/2, h+(ScrH-Hgrille)/2, makecol(fourmicolor,fourmicolor,fourmicolor));

  if(fourmiz->nbfood!=0)
  putpixel(screen1, w+(ScrW-Wgrille)/2, h+(ScrH-Hgrille)/2, makecol(fourmicolor,fourmicolor,0));
  }
 */
 } // all cellz

  for(j=0; j<Maxfourmi; j++)
 {
  fourmiz=&tbfourmi[j];

  putpixel(screen1, fourmiz->xpos+(ScrW-Wgrille)/2, fourmiz->ypos+(ScrH-Hgrille)/2, makecol(255,255,255));

  if(fourmiz->nbfood!=0)
  putpixel(screen1, fourmiz->xpos+(ScrW-Wgrille)/2, fourmiz->ypos+(ScrH-Hgrille)/2, makecol(255,255,0));
 }


}

void FourmisActions::svgbmp()
{
 sprintf(buffer, "Frame%i.bmp", cycles);
 save_bitmap(buffer, screen1, palette);
}

// plot info

void FourmisActions::plotinfo()
{
 countcycles();

 //sprintf(buffer, "Time:      %i", cycles);
 //textout(screen1, font, buffer, 50, 120, makecol(255,255,255));
 //sprintf(buffer, "Food Back: %i", nbfoodback);
 //textout(screen1, font, buffer, 50, 135, makecol(255,255,255));


}



