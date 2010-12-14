#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>

#include <lua.hpp>
#include "lunar.h"

#include "sockets.h"

const char *sockets::className = "socket";

Lunar<sockets>::RegType sockets::methods[] = {
  LUNAR_DECLARE_METHOD(sockets, socket),
  LUNAR_DECLARE_METHOD(sockets, gethostbyname),
  LUNAR_DECLARE_METHOD(sockets, setport),
  LUNAR_DECLARE_METHOD(sockets, connect),
  LUNAR_DECLARE_METHOD(sockets, send),
  LUNAR_DECLARE_METHOD(sockets, read),
  LUNAR_DECLARE_METHOD(sockets, listen),
  LUNAR_DECLARE_METHOD(sockets, accept),
  LUNAR_DECLARE_METHOD(sockets, bind),
  LUNAR_DECLARE_METHOD(sockets, setaddr),
  {0,0}
};

extern "C"
{
    LUALIB_API int luaopen_sock(lua_State *L) {
        Lunar<sockets>::Register(L);

        lua_pushnumber(L, AF_INET);
        lua_setfield(L, LUA_GLOBALSINDEX, "AF_INET");
        lua_pushnumber(L, SOCK_STREAM);
        lua_setfield(L, LUA_GLOBALSINDEX, "SOCK_STREAM");
        lua_pushnumber(L, IPPROTO_TCP);
        lua_setfield(L, LUA_GLOBALSINDEX, "IPPROTO_TCP");
        lua_pushnumber(L, IPPROTO_UDP);
        lua_setfield(L, LUA_GLOBALSINDEX, "IPPROTO_UDP");
        lua_pushnumber(L, INADDR_ANY);
        lua_setfield(L, LUA_GLOBALSINDEX, "INADDR_ANY");

        return 1;
    }
}
