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
		printf("�R���X�g���N�^\n");
	}
	~piyo()
	{
		printf("�f�X�g���N�^\n");
	}
};

int main(int argc, char* argv[])
{
	// Lua���J��
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// luabind���J��
	luabind::open(L);
	luabind::module(L)
	[
		luabind::def("hoge", &hoge),

		luabind::class_<piyo>("piyo")
		.def(luabind::constructor<>())
		.def_readwrite("n_", &piyo::n_)
	];

	// Lua�X�N���v�g���J��
	if (luaL_loadfile(L, "test.lua") || lua_pcall(L, 0, 0, 0)) {
		perror(lua_tostring(L, -1));
	}
	if (luaL_loadfile(L, "test2.lua") || lua_pcall(L, 0, 0, 0)) {
		perror(lua_tostring(L, -1));
	}

	clock_t first = clock();

	luabind::call_function<piyo>(L, "GetP");

	clock_t second = clock();

	// Lua�����
	lua_close(L);

	// �X�N���v�g�ŃR���X�g���N�^���Ă�Ń��������m�ۂ����ꍇ�A
	// Lua ������Ƃ��ɉ�������B

	printf("sec : %f", (float)(second - first) / CLOCKS_PER_SEC);

	getchar();
	return 0;
}