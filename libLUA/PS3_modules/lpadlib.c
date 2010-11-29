#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <io/pad.h>

#define lpadlib_c
#define LUA_LIB

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

PadInfo padinfo;
PadData paddata;

int CheckPad(int pad)
{
    ioPadGetInfo(&padinfo);
    if(pad <= MAX_PADS) {
        if(padinfo.status[pad]){
            ioPadGetData(pad, &paddata);
                return 1;
        }
    }
    return 0;
}

static int pad_init(lua_State *L){
    int ret = ioPadInit(luaL_checkint(L, 1));
    lua_pushnumber(L, ret);
    return 1;
}

static int pad_end(lua_State *L){
    int ret = ioPadEnd();
    lua_pushnumber(L, ret);
    return 1;
}

static int pad_setsixaxis(lua_State *L)
{
    int pad = luaL_checkint(L, 1);
    int enable = luaL_checkint(L, 2);
    ioPadSetSensorMode(pad, enable);
    return 0;
}

static int pad_UpPressed(lua_State *L){
    int pad = luaL_checkint(L, 1);

    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_UP);
        return 1;
    }
    return 0;
}

static int pad_DownPressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_DOWN);
        return 1;
    }
    return 0;
}

static int pad_LeftPressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_LEFT);
        return 1;
    }
    return 0;
}

static int pad_RightPressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_RIGHT);
        return 1;
    }
    return 0;
}

static int pad_TrianglePressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_TRIANGLE);
        return 1;
    }
    return 0;
}

static int pad_SquarePressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_SQUARE);
        return 1;
    }
    return 0;
}

static int pad_CirclePressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_CIRCLE);
        return 1;
    }
    return 0;
}

static int pad_CrossPressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_CROSS);
        return 1;
    }
    return 0;
}

static int pad_R1Pressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_R1);
        return 1;
    }
    return 0;
}

static int pad_R2Pressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_R2);
        return 1;
    }
    return 0;
}

static int pad_R3Pressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_R3);
        return 1;
    }
    return 0;
}

static int pad_L1Pressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_L1);
        return 1;
    }
    return 0;
}

static int pad_L2Pressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_L2);
        return 1;
    }
    return 0;
}


static int pad_L3Pressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_L3);
        return 1;
    }
    return 0;
}

static int pad_StartPressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_START);
        return 1;
    }
    return 0;
}

static int pad_SelectPressed(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.BTN_SELECT);
        return 1;
    }
    return 0;
}

static int pad_LeftAnalogX(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.ANA_L_H);
        return 1;
    }
    return 0;
}

static int pad_LeftAnalogY(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.ANA_L_V);
        return 1;
    }
    return 0;
}

static int pad_RightAnalogX(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.ANA_R_H);
        return 1;
    }
    return 0;
}

static int pad_RightAnalogY(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.ANA_R_V);
        return 1;
    }
    return 0;
}

static int pad_SensorX(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.SENSOR_X);
        return 1;
    }
    return 0;
}

static int pad_SensorY(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.SENSOR_Y);
        return 1;
    }
    return 0;
}

static int pad_SensorZ(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.SENSOR_Z);
        return 1;
    }
    return 0;
}

static int pad_SensorG(lua_State *L){
    int pad = luaL_checkint(L, 1);
    if(CheckPad(pad)){
        lua_pushnumber(L, paddata.SENSOR_G);
        return 1;
    }
    return 0;
}

static const luaL_Reg padlib[] = {
  {"init", pad_init},
  {"endPad", pad_end},
  {"setsixaxis", pad_setsixaxis},
  {"up", pad_UpPressed},
  {"down", pad_DownPressed},
  {"left", pad_LeftPressed},
  {"right", pad_RightPressed},
  {"triangle", pad_TrianglePressed},
  {"square", pad_SquarePressed},
  {"circle", pad_CirclePressed},
  {"cross", pad_CrossPressed},
  {"R1", pad_R1Pressed},
  {"R2", pad_R2Pressed},
  {"R3", pad_R3Pressed},
  {"L1", pad_L1Pressed},
  {"L2", pad_L2Pressed},
  {"L3", pad_L3Pressed},
  {"start", pad_StartPressed},
  {"select", pad_SelectPressed},
  {"LanalogX", pad_LeftAnalogX},
  {"LanalogY", pad_LeftAnalogY},
  {"RanalogX", pad_RightAnalogX},
  {"RanalogY", pad_RightAnalogY},
  {"Xaxis", pad_SensorX},
  {"Yaxis", pad_SensorY},
  {"Zaxis", pad_SensorZ},
  {"Gaxis", pad_SensorG},
  {NULL, NULL}
};

LUALIB_API int luaopen_pad (lua_State *L) {
    luaL_register(L, LUA_PADLIBNAME, padlib);
    lua_pushnumber(L, MAX_PADS);
    lua_setfield(L, -2, "maxpads");
    return 1;
}
