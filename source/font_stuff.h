#ifndef FONT_STUFF_H_   /* Include guard */
#define FONT_STUFF_H_

int TTFLoadFont(char * path, void * from_memory, int size_from_memory);

void TTFUnloadFont();

void LoadTexture();

void DrawBackground2D(u32 rgba);

#endif // FONT_STUFF_H_