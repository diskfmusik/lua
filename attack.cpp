#include <lua.hpp>

struct Character
{
	char *name;
	int hp;
	int power;
};

Character player = { "player", 100, 10 };
Character enemy = { "enemy", 50, 5 };


//---------------------------------------------------------------------------------------
// _hp : 防御側のhp
// _power : 攻撃側のpower
// *_name : 攻撃側のname
//---------------------------------------------------------------------------------------
void attack(int &_hp, const int _power, const char *_name)
{
	// Luaステートオブジェクトの作成
	lua_State *L = luaL_newstate();

	// Luaの標準ライブラリを読み込む
	luaL_openlibs(L);// lua_State *L

	// コルーチンを使えるように設定する
	luaopen_base(L);

	// Luaファイルを開いて実行
	if (luaL_dofile(L, "attack.lua"))
	{// 戻り値 int
		printf("%s\n", lua_tostring(L, lua_gettop(L)));// エラー表示
		lua_close(L);
		getchar();
		return;
	}

	// attack 関数をスタックに積む
	lua_getglobal(L, "attack");// (hp, attack)

	// 引数をスタックに積む
	lua_pushnumber(L, _hp);
	lua_pushnumber(L, _power);
	lua_pushstring(L, _name);

#if 0
	/* スタックに積まれているかの確認用*/
	double a = lua_tonumber(L, -3);
	printf("-003 : %f\n", a);
	a = lua_tonumber(L, -2);
	printf("-002 : %f\n", a);
	getchar();
	const char *str = lua_tostring(L, -1);
	printf("-001 : %s\n", str);
#endif

	// Lua関数を実行
	// int lua_pcall(
	// lua_State *L,    // Luaステート
	// int nargs,       // 引数の数
	// int nresults,    // 戻り値の数
	// int errfunc      // エラーハンドラ関数のスタックID
	//	);
	if (lua_pcall(L, 3, 1, 0))
	{
		printf("%s\n", lua_tostring(L, lua_gettop(L)));// エラー表示
		lua_close(L);
		getchar();
		return;
	}

	// スタックに積まれた返り値を取ってきて、
	// 実際にhpを減らす
	_hp = (int)lua_tonumber(L, -1);


	// Luaステートオブジェクトを閉じる
	lua_close(L);
}


void main()
{
	while (1)
	{
		printf("player_hp : %d\n", player.hp);
		printf("enemy_hp : %d\n", enemy.hp);
		getchar();

		attack(enemy.hp, player.power, player.name);
		printf("player_hp : %d\n", player.hp);
		printf("enemy_hp : %d\n", enemy.hp);
		getchar();

		attack(player.hp, enemy.power, enemy.name);
	}
}
