#include <lua.hpp>

#include <psl1ght/lv2.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <sysmodule/sysmodule.h>
extern int luaopen_sock(lua_State *L);
int main (int argc, char* argv[])
{
    SysLoadModule(SYSMODULE_FS);
    lua_State *L = lua_open();
    luaL_openlibs(L);
    if(!luaL_dofile(L, "/dev_usb000/app.lua") == 0)
        fprintf(stderr, "Failed to load file /dev_usb000/app.lua");
    return 0;
}
