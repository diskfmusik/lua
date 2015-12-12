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

	piyo() { n_ = 0; }
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
	piyo p;

	clock_t first = clock();

	/* luabind */
#if 1
	while (p.n_ < 100000)// 5273, 5513, 5370, 5464,	5490
	{
		luabind::call_function<void>(L, "update", boost::ref(p));
	}
#endif

	/* c++ */
#if 0
	while (p.n_ < 100000)// 3742, 3696,	3935, 3680,	3680
	{
		p.n_ = p.n_ + 1;
		greet(p.n_);
	}
#endif

	clock_t second = clock();

	// Luaを閉じる
	lua_close(L);

	printf("sec : %f", (float)(second - first) / CLOCKS_PER_SEC);

	getchar();
	return 0;
}