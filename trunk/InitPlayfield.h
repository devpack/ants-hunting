#ifndef __INITPLAYFIELD_H_
#define __INITPLAYFIELD_H_


//////////////////////////////////////////////////////////////////////
///                   CLASS InitPlayfield                          ///
//////////////////////////////////////////////////////////////////////


// Init & Open screen type

class InitPlayfield
{
public:
       static const int   ScrW;
       static const int   ScrH;
       static const int   GFXOPENARG;

public:
       InitPlayfield(int GFXOPENARG, int ScrW, int ScrH);
       virtual ~InitPlayfield();
};

#endif
