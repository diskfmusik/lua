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
// _hp : �h�䑤��hp
// _power : �U������power
// *_name : �U������name
//---------------------------------------------------------------------------------------
void attack(int &_hp, const int _power, const char *_name)
{
	// Lua�X�e�[�g�I�u�W�F�N�g�̍쐬
	lua_State *L = luaL_newstate();

	// Lua�̕W�����C�u������ǂݍ���
	luaL_openlibs(L);// lua_State *L

	// �R���[�`�����g����悤�ɐݒ肷��
	luaopen_base(L);

	// Lua�t�@�C�����J���Ď��s
	if (luaL_dofile(L, "attack.lua"))
	{// �߂�l int
		printf("%s\n", lua_tostring(L, lua_gettop(L)));// �G���[�\��
		lua_close(L);
		getchar();
		return;
	}

	// attack �֐����X�^�b�N�ɐς�
	lua_getglobal(L, "attack");// (hp, attack)

	// �������X�^�b�N�ɐς�
	lua_pushnumber(L, _hp);
	lua_pushnumber(L, _power);
	lua_pushstring(L, _name);

#if 0
	/* �X�^�b�N�ɐς܂�Ă��邩�̊m�F�p*/
	double a = lua_tonumber(L, -3);
	printf("-003 : %f\n", a);
	a = lua_tonumber(L, -2);
	printf("-002 : %f\n", a);
	getchar();
	const char *str = lua_tostring(L, -1);
	printf("-001 : %s\n", str);
#endif

	// Lua�֐������s
	// int lua_pcall(
	// lua_State *L,    // Lua�X�e�[�g
	// int nargs,       // �����̐�
	// int nresults,    // �߂�l�̐�
	// int errfunc      // �G���[�n���h���֐��̃X�^�b�NID
	//	);
	if (lua_pcall(L, 3, 1, 0))
	{
		printf("%s\n", lua_tostring(L, lua_gettop(L)));// �G���[�\��
		lua_close(L);
		getchar();
		return;
	}

	// �X�^�b�N�ɐς܂ꂽ�Ԃ�l������Ă��āA
	// ���ۂ�hp�����炷
	_hp = (int)lua_tonumber(L, -1);


	// Lua�X�e�[�g�I�u�W�F�N�g�����
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
