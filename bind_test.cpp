#include <lua.hpp>
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>

void hoge(const int num)
{
     printf("%d\n", num);
}

enum STAGE
{
    FIRST,
    SECOND,
    THIRD,
};

class oya
{
public:
    int a_;

    oya() { a_ = 0; }
};

class ko : public oya
{
public:
    int b_;

    ko() { b_ = a_; }

    ko operator+(const int _s)
    {
        this->b_ += _s;
        return *this;
    }
};

void main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // luabindを開く
    luabind::open(L);

    luabind::module(L)
    [
        luabind::def("hoge", &hoge),

        luabind::class_<STAGE>("STAGE").enum_("constants")
        [
            luabind::value("FIRST", STAGE::FIRST),
            luabind::value("SECOND", STAGE::SECOND),
            luabind::value("THIRD", STAGE::THIRD)
        ],

        luabind::class_<ko>("ko")
        .def(luabind::constructor<>())
        .def_readwrite("a_", &ko::a_)
        .def_readwrite("b_", &ko::b_)
        .def(luabind::self + (const int()) )
    ];

    // Luaスクリプトを開く
    if (luaL_loadfile(L, "test.lua") || lua_pcall(L, 0, 0, 0))
    {
		perror(lua_tostring(L, -1));
    }

    lua_close(L);

    getchar();
}
