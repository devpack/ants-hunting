#ifndef __FOURMISACTIONS_H_
#define __FOURMISACTIONS_H_

#include "InitPlayfield.h"
#include "OurFourmiWorld.h"

const int   Maxfourmi = 2000;

//////////////////////////////////////////////////////////////////////
///                   CLASS FourmisActions                         ///
//////////////////////////////////////////////////////////////////////

struct Fourmi{
int xpos;
int ypos;
int state;
int rndstatetime;
int whichway;
int nbfood;
};

// Fourmiliere type

class FourmisActions : public InitPlayfield, public OurFourmiWorld
{

private:
       char          buffer[50];
       int           nbfoodback;
       int           cycles;

private:
        struct Fourmi      tbfourmi[Maxfourmi];

        static const int   Nestlimit;
        static const int   pherofood;
        static const int   nbmaxphero;
        static const int   fourmimaxfood;
        static const int   minphero;
        static const int   pheropistestart;
        static const int   pheropistestop;
        static const int   pherocoefevapo;
        static const int   nothingfoundmaxtime;

public:
       FourmisActions(int GFXOPENARG, int ScrW, int ScrH)
       :InitPlayfield(GFXOPENARG, ScrW, ScrH) {}

       void initfourmi();
       void Fourmirndmove(int j);
       void Fourmimaxpheromove(int j);
       void Fourminestmove(int j);
       void Fourmifollowpheropiste(int j);
       void Fourmicheckfood(int j);
       void Checkfourmimotion(int j);
       void Fourmimotion();

       void Managepherofood();

       void plotscreen();
       void plotinfo();
	   void svgbmp();
       inline void countcycles() {cycles++;};
};

#endif
