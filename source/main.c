#include <tiny3d.h>
#include <libfont.h>

#include <io/pad.h>

#include "font_stuff.h"

#define BTN_LEFT       32768
#define BTN_DOWN       16384
#define BTN_RIGHT      8192
#define BTN_UP         4096
#define BTN_START      2048
#define BTN_R3         1024
#define BTN_L3         512
#define BTN_SELECT     256  
#define BTN_SQUARE     128
#define BTN_CROSS      64
#define BTN_CIRCLE     32
#define BTN_TRIANGLE   16
#define BTN_R1         8
#define BTN_L1         4
#define BTN_R2         2
#define BTN_L2         1

padInfo padinfo;
padData paddata;

unsigned get_button_pressed()
{
	int i_for_pad_num;

	ioPadGetInfo(&padinfo);

	for(i_for_pad_num = 0; i_for_pad_num < MAX_PADS; i_for_pad_num++){

		if(padinfo.status[i_for_pad_num]){
			ioPadGetData(i_for_pad_num, &paddata);
			return (paddata.button[2] << 8) | (paddata.button[3] & 0xff);

		}
		
	}
	return 0;
}

void drawScene()
{
	float x, y;

    tiny3d_Project2D(); // change to 2D context (remember you it works with 848 x 512 as virtual coordinates)
    
    DrawBackground2D(0x0040ffff) ; // light blue 

    SetFontSize(18, 32);
    
    x= 0.0; y = 0.0;

    
    SetFontColor(0xffffffff, 0x0);
    x = DrawString(x, y,"wat da duce");

    
    SetFontColor(0x00ff00ff, 0x0);
    x = DrawString(x, y, "Hermes ");

    
    SetFontColor(0xffffffff, 0x0);
    x = DrawString(x, y, "and this is one sample working with captured TTF fonts.");
    
    x = 0; y += 40;
    
    DrawString(x, y, "I am using 3 fonts:");
    
    
    y += 40;
    SetFontColor(0xffffffff, 0x00a000ff);
    DrawFormatString(x, y, "Font 0 is one TTF array capture of 224 chars 32 x 32 pix and texture size %i KB", 224 * 32 * 32 * 2 / 1024);

    
    y += 40;
    SetFontColor(0xffffffff, 0xa00000ff);
    DrawFormatString(x, y, "Font 1 is one TTF array capture of 224 chars 32 x 32 pix and texture size %i KB", 224 * 32 * 32 * 2 / 1024);

    
    y += 40;
    SetFontColor(0x000000ff, 0xffff00ff);
    DrawFormatString(x, y, "Font 2 is the Font 1 captured as 64 x 64 pix and texture size %i KB", 224 * 64 * 64 * 2 / 1024);

    y += 48;
    
    SetFontSize(32, 64);
    SetFontColor(0xffffffff, 0x000000ff);
    SetFontAutoCenter(1);
    DrawString(0, y, "You can resize letters with SetFontSize()");
    SetFontAutoCenter(0);

    SetFontSize(18, 32);
    SetFontColor(0xffffffff, 0x00000000);
    y += 72;

    SetFontAutoNewLine(848);
    x = DrawString(0, y, "change the color, background color and center the text with ");

    SetFontColor(0x00ff00ff, 0x00000000);
    x = DrawString(x, GetFontY(), "SetFontAutoCenter()");

    
    SetFontColor(0xffffffff, 0x00000000);

    x = DrawString(x, GetFontY(), ". This txt is displayed using ");

    SetFontColor(0x00ff00ff, 0x00000000);
    x = DrawString(x, GetFontY(), "SetFontAutoNewLine()");
    SetFontColor(0xffffffff, 0x00000000);

    x = DrawString(x, GetFontY(), " option. ");

    DrawString(x, GetFontY(), "TTF captured as bitmap is a good compromise between speed and quality fonts without using one big "
    "surface (1920 x 1080 x 4 bytes) to maintain the quality in all video resolutions and "
    "using the CPU to render the fonts instead of using the RSX for it.\n"
    "Remember you always to test the result at 480/576P video modes .");
    
    SetFontAutoNewLine(0);

    y = GetFontY();
    x = 0;
}

s32 main(s32 argc, const char* argv[])
{
	
	tiny3d_Init(1024*1024);

	ioPadInit(7);

	// Load texture

    LoadTexture();

	
	// Ok, everything is setup. Now for the main loop.
	while(1) {
	if(get_button_pressed() & BTN_CROSS){
		return 0;
	}

        /* DRAWING STARTS HERE */

        // clear the screen, buffer Z and initializes environment to 2D

        tiny3d_Clear(0xff000000, TINY3D_CLEAR_ALL);
        

        // Enable alpha Test
        tiny3d_AlphaTest(1, 0x10, TINY3D_ALPHA_FUNC_GEQUAL);

        // Enable alpha blending.
        tiny3d_BlendFunc(1, TINY3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA | TINY3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
            TINY3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA | TINY3D_BLEND_FUNC_DST_ALPHA_ZERO,
            TINY3D_BLEND_RGB_FUNC_ADD | TINY3D_BLEND_ALPHA_FUNC_ADD);

        drawScene(); // Draw


        /* DRAWING FINISH HERE */

        tiny3d_Flip();
		
	}

	return 0;
}

