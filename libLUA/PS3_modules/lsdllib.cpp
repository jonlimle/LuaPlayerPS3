#include <lua.hpp>
#include "lunar.h"
#include "sdl.h"

const char *surface::className = "surface";
SDL_Surface *Screen;
#define PITCH (Screen->pitch / 4)

SDL_Surface *Font;

static int InitFont(lua_State *L)
{
  SDL_Surface *temp = SDL_LoadBMP("/dev_usb000/font.bmp");
  Font = SDL_ConvertSurface(temp, Screen->format, SDL_SWSURFACE);
  SDL_FreeSurface(temp);
}

void DrawChar(int x, int y, int character)
{
  if (character == 32)
    return;

  character -= 33;
  int i, j;
  for (i = 0; i < Font->w; i++)
  {
    int screenofs = x + (y + i) * PITCH;
    int charofs = (i + character * Font->w) * (Font->pitch / 4);
    for (j = 0; j < Font->w; j++)
    {
      ((unsigned int*)Screen->pixels)[screenofs] =
        ((unsigned int*)Font->pixels)[charofs];
      screenofs++;
      charofs++;
    }
  }
}

static int DrawText(lua_State *L)
{
    int x = luaL_checkint(L, 1);
    int y = luaL_checkint(L, 2);
    const char *s = luaL_checkstring(L, 3);

    while (*s != 0)
    {
        DrawChar(x, y, *s);
        s++;
        x += Font->w;
    }
}

int surface::LoadIMG(lua_State *L)
{
    const char *arg1 = luaL_checkstring(L, 1);
    if(arg1 != NULL){
        NewSurface = SDL_LoadBMP(arg1);
        printf("Loading %s\n", arg1);
    }
    return 0;
}

int surface::DisplayFormat(lua_State *L)
{
    NewSurface = SDL_DisplayFormat(NewSurface);
    return 0;
}
int surface::getRes(lua_State *L)
{
    lua_pushnumber(L, NewSurface->w);
    lua_pushnumber(L, NewSurface->h);
    return 2;
}

int surface::setRectPos(lua_State *L)
{
    int arg1 = luaL_checkint(L, 1);
    int arg2 = luaL_checkint(L, 2);
    NewRect.x = arg1;
    NewRect.y = arg2;
    return 0;
}

Lunar<surface>::RegType surface::methods[] = {
  LUNAR_DECLARE_METHOD(surface, LoadIMG),
  LUNAR_DECLARE_METHOD(surface, getRes),
  LUNAR_DECLARE_METHOD(surface, setRectPos),
  LUNAR_DECLARE_METHOD(surface, DisplayFormat),
  {0,0}
};

static int InitGFX(lua_State *L)
{
    SDL_setenv("SDL_VIDEODRIVER", "psl1ght", 1);
    int arg1 = luaL_checkint(L, 1);
    int arg2 = luaL_checkint(L, 2);
    SDL_Init(SDL_INIT_VIDEO);
    Screen = SDL_SetVideoMode(arg1, arg2, 32, SDL_FULLSCREEN|SDL_HWSURFACE|SDL_DOUBLEBUF);
    return 0;
};

static int endGFX(lua_State *L)
{
    SDL_Flip(Screen);
    return 0;
};

static int screenRes(lua_State *L)
{
    lua_pushnumber(L, Screen->w);
    lua_pushnumber(L, Screen->h);
    return 2;
};

static int BlitToScreen(lua_State *L)
{
    surface *arg1 = Lunar<surface>::check(L, 1);
    SDL_BlitSurface(arg1->getSurface(), 0, Screen, arg1->getRect());
    return 0;
};

static int beginGFX(lua_State *L)
{
    SDL_FillRect(Screen, NULL, 0xFFFFFF);
    return 0;
};

extern "C"
{
    LUALIB_API int luaopen_SDL(lua_State *L) {
        Lunar<surface>::Register(L);

        lua_pushcfunction(L, InitGFX);
        lua_setglobal(L, "InitGFX");

        lua_pushcfunction(L, endGFX);
        lua_setglobal(L, "endGFX");

        lua_pushcfunction(L, screenRes);
        lua_setglobal(L, "screenRes");

        lua_pushcfunction(L, BlitToScreen);
        lua_setglobal(L, "BlitToScreen");

        lua_pushcfunction(L, beginGFX);
        lua_setglobal(L, "beginGFX");

        lua_pushcfunction(L, InitFont);
        lua_setglobal(L, "InitFont");

        lua_pushcfunction(L, DrawText);
        lua_setglobal(L, "DrawText");

        return 1;
    }
}
