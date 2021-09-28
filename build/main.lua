function buildout (text)
   os.execute("echo "..text)
end   

function request (cmd)
   local D = io.popen(cmd)
   local R = D:read("*a")
   D:close()
   return R
end

function latestHash() 
   return request("git log --max-count=1 --all --pretty=format:\"%H\"") 
end

function latestDescription() 
   return request("git log --max-count=1 --all --pretty=format:\"%H:%s - %an \"") 
end


buildout("GIT watcher current status: "..latestDescription())
local Hash = latestHash()
local NewHash = Hash
while true do 
   request("git pull --all")
   NewHash = latestHash()
   if Hash ~= NewHash then
      buildout("new commit deteced!")
      buildout(latestDescription())
   end
   Hash = NewHash
end

