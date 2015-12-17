#include <lua.hpp>
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>

#include <time.h>

void hoge(const int num)
{
	printf("%d\n", num);
}

class piyo
{
public:
	int n_;

	piyo() : n_(0)
	{
		printf("コンストラクタ\n");
	}
	~piyo()
	{
		printf("デストラクタ\n");
	}
};

int main(int argc, char* argv[])
{
	// Luaを開く
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// luabindを開く
	luabind::open(L);
	luabind::module(L)
	[
		luabind::def("hoge", &hoge),

		luabind::class_<piyo>("piyo")
		.def(luabind::constructor<>())
		.def_readwrite("n_", &piyo::n_)
	];

	// Luaスクリプトを開く
	if (luaL_loadfile(L, "test.lua") || lua_pcall(L, 0, 0, 0)) {
		perror(lua_tostring(L, -1));
	}
	if (luaL_loadfile(L, "test2.lua") || lua_pcall(L, 0, 0, 0)) {
		perror(lua_tostring(L, -1));
	}

	clock_t first = clock();

	luabind::call_function<piyo>(L, "GetP");

	clock_t second = clock();

	// Luaを閉じる
	lua_close(L);

	// スクリプトでコンストラクタを呼んでメモリを確保した場合、
	// Lua を閉じたときに解放される。

	printf("sec : %f", (float)(second - first) / CLOCKS_PER_SEC);

	getchar();
	return 0;
}