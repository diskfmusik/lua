function foo ()
	coroutine.yield("1��ڂ̒��f")
	coroutine.yield("2��ڂ̒��f")
	return "�I��"
end

-- wrap�֐� �֐����R���[�`���Ƃ��ċ@�\������B
-- �쐬���邾���ŁA���s�͂��Ȃ��B

co = coroutine.wrap(foo)


print(co())
print(co())
print(co())
print(co())
