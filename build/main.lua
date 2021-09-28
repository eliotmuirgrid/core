local D = io.popen("echo hi")
-- local R = D:read("*a")
-- print(R)
local R = "Eliot"
os.execute("echo "..R)

-- os.execute("CURL https://www.interfaceware.com/")
-- os.execute("echo hello")
-- local D = io.popen("CURL https://www.interfaceware.com/")
-- local R = D:read('*a')
-- D:close()

-- local f = io.open('cmd_out', 'w')
-- f:write(R)
-- f:close()