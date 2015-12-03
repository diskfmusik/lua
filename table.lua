Character = {

    New = function(_name, _hp, _power)
        -- テーブルをreturnで返す
        return {
        name = _name,
        hp = _hp,
        power = _power,

        Draw = function(_this)
            print(_this.name, _this.hp, _this.power)
        end
        }
    end
}

player = Character.New("player", 100, 10)
enemy = Character.New("enemy", 50, 5)

player.Draw(player)
-- シンタックスシュガー
-- テーブルに登録した関数を呼び出すときに『:』を使うと、
-- テーブル自体を第1引数に渡す事が出来る
enemy:Draw()
