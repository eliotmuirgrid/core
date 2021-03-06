-- $Id: pptest.lua,v 1.10 2004/08/15 19:38:11 bsunshin Exp $

permtable = { 1234 } 

perms = { [coroutine.yield] = 1, [permtable] = 2 }

twithmt = {}
setmetatable( twithmt, { __call = function() return 21 end } )

function testfenv()
	return abc
end

setfenv(testfenv, { abc = 456 })

function fa(i)
	local ia = i + 1
	return fb(ia)
end

function fb(i)
	local ib = i + 1
	ib = ib + fc(ib)
	return ib
end

function fc(i)
	local ic = i + 1
	coroutine.yield()
	return ic*2
end

function func()
	return 4
end

thr = coroutine.create(fa)
coroutine.resume(thr, 2)

testtbl = { a = 2, [2] = 4 }

function funcreturningclosure(n)
	return function()
		return n
	end
end

function nestedfunc(n)
	return (function(m) return m+2 end)(n+3)
end

testloopa = {}
testloopb = { testloopa = testloopa }
testloopa.testloopb = testloopb

sharedref = {}
refa = {sharedref = sharedref}
refb = {sharedref = sharedref}

sptable = { a = 3 }

setmetatable(sptable, { 
	__persist = function(tbl)
		local a = tbl.a
		return function()
			return { a = a+3 }
		end
	end 
})

literaludata = boxinteger(71)

function booleanpersist(udata)
	local b = unboxboolean(udata)
	return function()
		return boxboolean(b)
	end
end

function makecounter()
	local a = 0
	return {
		inc = function() a = a + 1 end,
		cur = function() return a end
	}
end

rootobj = {
	testfalse = false,
	testtrue = true,
	testseven = 7,
	testfoobar = "foobar",
	testfuncreturnsfour = func,
	testnil = nil,
	testthread = thr,
	testperm = permtable,
	testmt = twithmt,
	testtbl = testtbl,
	testfenv = testfenv,
	testclosure = funcreturningclosure(11),
	testnilclosure = funcreturningclosure(nil),
	testnest = nestedfunc,
	testludata = createludata(),
	testlooptable = testloopa,
	testsharedrefa = refa,
	testsharedrefb = refb,
	testsptable = sptable,
	testliteraludata = literaludata,
	testspudata1 = boxboolean(true),
	testspudata2 = boxboolean(false),
	testsharedupval = makecounter()
}

buf = pluto.persist(perms, rootobj)

outfile = io.open("test.plh", "wb")
outfile:write(buf)
outfile:close()
