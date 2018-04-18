
__G__TRACKBACK__ = function(msg)
    local msg = debug.traceback(msg, 3)
    print(msg)
    return msg
end


local function main()
    -- local fs = engine:getFileSystem()

    -- dump(getmetatable(fs), "fs")
    -- -- print(fs.getPath, "aaaa")
    -- print(fs:getTempDirectory())

    -- engine:getRenderer():setClearColor(Color(64, 0, 0))

    local testPath = engine:getFileSystem():getPath("main.lua", true)
    print(testPath)

    local scene = oz.Scene.new()

    local cameraActor = oz.Actor.new()

    local spriteActor = oz.Actor.new()

    local camera = oz.Camera.new()

    local layer = oz.Layer.new()

    cameraActor:addComponent(camera)

    layer:addChild(cameraActor)
    layer:addChild(spriteActor)
    scene:addLayer(layer)

    local char = oz.Sprite.new()
    local pv = oz.Vector2.new(0.5, 0.5)
    char:init("run.json", true, 1, 1, pv)
    char:setAnimation("", true)
    char:play()

    spriteActor:addComponent(char)
    spriteActor:setScale(oz.Vector2.new(2, 2))

    local sceneManager = engine:getSceneManager()
    sceneManager:setScene(scene)

    local tmpVec2 = oz.Vector2.new(1, 1)
    local tmpVec3 = oz.Vector2.new(1, 1)
    local tmpVec4 = tmpVec2 + tmpVec3
    dump(getmetatable(tmpVec2))
    dump(tmpVec4, "tmpVec4")
    print(tmpVec4.x, tmpVec4.y)
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end





