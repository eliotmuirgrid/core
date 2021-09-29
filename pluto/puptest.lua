-- $Id: puptest.lua,v 1.10 2004/08/15 19:38:11 bsunshin Exp $

permtable = { 1234 } 

perms = { [1] = coroutine.yield, [2] = permtable }

function testcounter(counter)
	local a = counter.cur()
	counter.inc()
	return counter.cur() == a+1
end

function test(rootobj)
	local passed = 0
	local total = 0
	local dotest = function(name,cond)
		total = total+1
		if cond then
			print(name, "  PASSED")
			passed = passed + 1
		else
			print(name, "* FAILED")
		end
	end
		
	dotest("Boolean FALSE        ", rootobj.testfalse == false)
	dotest("Boolean TRUE         ", rootobj.testtrue == true)
	dotest("Number 7             ", rootobj.testseven == 7)
	dotest("String 'foobar'      ", rootobj.testfoobar == "foobar")
	dotest("Func returning 4     ", rootobj.testfuncreturnsfour() == 4)
	dotest("Nil value            ", rootobj.testnil == nil)
	dotest("Thread resume        ", coroutine.resume(rootobj.testthread) == true,14)
	dotest("Table                ", rootobj.testtbl.a == 2 and rootobj.testtbl[2] == 4);
	dotest("Permanent table      ", rootobj.testperm == permtable)
	dotest("Table metatable      ", rootobj.testmt() == 21)
	dotest("Function env         ", rootobj.testfenv() == 456)
	dotest("Lua closure          ", rootobj.testclosure() == 11)
	dotest("Nil in closure       ", rootobj.testnilclosure() == nil)
	dotest("Nested func          ", rootobj.testnest(1) == 6)
	dotest("Light userdata       ", checkludata(rootobj.testludata))
	dotest("Looped tables        ", 
		rootobj.testlooptable.testloopb.testloopa == 
		rootobj.testlooptable)
	dotest("Shared reference     ", rootobj.testsharedrefa.sharedref ==
		rootobj.testsharedrefb.sharedref)
	dotest("Identical tables     ", rootobj.testsharedrefa ~= 
		rootobj.testsharedrefb)
	dotest("Table special persist", rootobj.testsptable.a == 6)
	dotest("Udata literal persist", 
		unboxinteger(rootobj.testliteraludata) == 71)
	dotest("Udata special persist", 
		unboxboolean(rootobj.testspudata1) == true and
		unboxboolean(rootobj.testspudata2) == false)
	dotest("Shared upvalues      ",
		testcounter(rootobj.testsharedupval))
	print()
	if passed == total then
		print("All tests passed.")
	else
		print(passed .. "/" .. total .. " tests passed.")
	end
end

infile, err = io.open("test.plh", "rb")
if infile == nil then
	error("While opening: " .. (err or "no error"))
end

buf, err = infile:read("*a")
if buf == nil then
	error("While reading: " .. (err or "no error"))
end

infile:close()

rootobj = pluto.unpersist(perms, buf)

test(rootobj)
