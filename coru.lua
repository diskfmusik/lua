function foo ()
	coroutine.yield("1回目の中断")
	coroutine.yield("2回目の中断")
	return "終了"
end

-- wrap関数 関数をコルーチンとして機能させる。
-- 作成するだけで、実行はしない。

co = coroutine.wrap(foo)


print(co())
print(co())
print(co())
print(co())
