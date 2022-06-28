#ifndef _FS_ASSETS_H__
#define _FS_ASSETS_H__

#include <stdbool.h>

#include "FS_Font.h"
#include "FS_Mesh.h"
#include "FS_Buffer.h"

bool Assets_LoadFile(Buffer *buffer, const char *filepath);
bool Assets_LoadFont(TrueTypeFont *font, float height, const char*filepath);

bool Assets_LoadTexture2D(Texture2D *texture, const char *filepath);
bool Assets_LoadBitmap2D(Bitmap2D *bitmap, const char *filepath);
bool Assets_LoadMesh(Mesh *mesh, const char *filepath);

void Assets_FreeAny(void *buffer);
void Assets_FreeFont(TrueTypeFont *font);
void Assets_FreeFile(Buffer *buffer);
void Assets_FreeBitmap(Bitmap2D *bitmap);
void Assets_FreeTexture2D(Texture2D *texture);

#endif // _FS_ASSETS_H__