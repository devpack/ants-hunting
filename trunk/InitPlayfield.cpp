#include <allegro.h>
#include "InitPlayfield.h"


InitPlayfield::InitPlayfield(int GFXOPENARG, int ScrW, int ScrH)
{
 allegro_init();
 set_color_depth(32);
 set_gfx_mode(GFXOPENARG, ScrW, ScrH, 0, 0);
 install_keyboard();
 srand(time(NULL));
}

InitPlayfield::~InitPlayfield()
{
 poll_keyboard();
 allegro_exit();
}

