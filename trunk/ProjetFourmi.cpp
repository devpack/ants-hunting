//////////////////////////////////////////////////////////////////////
//                                                                  //
//                ANTS                                              //
//                                                                  //
//                Pixel vert = nourriture                           //
//                Pixel blanc & jaune = fourmis                     //
//                Pixel rouge = phéromones                          //
//                                                                  //
//////////////////////////////////////////////////////////////////////


#include <allegro.h>
#include "InitPlayfield.h"
#include "OurFourmiWorld.h"
#include "FourmisActions.h"


// Constantes Class InitPlayfield

const int   InitPlayfield::ScrW = 800;
const int   InitPlayfield::ScrH = 600;
const int   InitPlayfield::GFXOPENARG = GFX_SAFE;//GFX_AUTODETECT;


// Constantes Class OurFourmiWorld

const int   OurFourmiWorld::nbfoodcellz = 11;           // quantite de food par cellule
const int   OurFourmiWorld::Xnest = Wgrille/2;
const int   OurFourmiWorld::Ynest = Hgrille/2;

// Constantes Class FourmisActions

const int   FourmisActions::Nestlimit = (int)((((Wgrille/2*Wgrille/2)+(Hgrille/2*Hgrille/2)) *85)/100);
const int   FourmisActions::fourmimaxfood = 3;

const int   FourmisActions::pherofood = 50*25/fourmimaxfood;
const int   FourmisActions::nbmaxphero = 255;
const int   FourmisActions::minphero = 3;
const int   FourmisActions::pheropistestart = 140;
const int   FourmisActions::pheropistestop = ( pheropistestart*85)/100;
const int   FourmisActions::pherocoefevapo = 999;
const int   FourmisActions::nothingfoundmaxtime = 1500;

//////////////////////////////////////////////////////////////////////
///                            MAIN                                ///
//////////////////////////////////////////////////////////////////////


int main() 
{
 FourmisActions *fourmiliere=new FourmisActions(InitPlayfield::GFXOPENARG, InitPlayfield::ScrW, InitPlayfield::ScrH);

 fourmiliere->initfourmi();

while(! key[KEY_ESC])
{
 fourmiliere->clearscreen1();

 fourmiliere->Fourmimotion();
 fourmiliere->Managepherofood();

 fourmiliere->plotscreen();
 fourmiliere->plotinfo();

 fourmiliere->blitscreen1();

 if (key[KEY_S])
  fourmiliere->svgbmp();
  
 vsync();
}

 delete fourmiliere;
 return 0;

}
END_OF_MAIN();
