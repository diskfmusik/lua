Character = {

    New = function(_name, _hp, _power)
        -- �e�[�u����return�ŕԂ�
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
-- �V���^�b�N�X�V���K�[
-- �e�[�u���ɓo�^�����֐����Ăяo���Ƃ��Ɂw:�x���g���ƁA
-- �e�[�u�����̂��1�����ɓn�������o����
enemy:Draw()
