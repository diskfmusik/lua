#include <lua.hpp>


void main()
{
	// Lua�X�e�[�g�I�u�W�F�N�g�̍쐬
	lua_State *L = luaL_newstate();

	// Lua�X�e�[�g�I�u�W�F�N�g�����
	lua_close(L);

	getchar();
}