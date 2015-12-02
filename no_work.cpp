#include <lua.hpp>


void main()
{
	// Luaステートオブジェクトの作成
	lua_State *L = luaL_newstate();

	// Luaステートオブジェクトを閉じる
	lua_close(L);

	getchar();
}