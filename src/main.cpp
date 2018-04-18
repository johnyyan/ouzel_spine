// Copyright (C) 2017 Elviss Strazdins

#include "SpineSample.hpp"

#define SOL_CHECK_ARGUMENTS 1
#include <sol/sol.hpp>
#include "lb_main.hpp"

std::string DEVELOPER_NAME = "elnormous";
std::string APPLICATION_NAME = "Spine sample";

std::unique_ptr<SpineSample> sample;

using namespace ouzel;

//global lua state
sol::state lua;

void ouzelMain(const std::vector<std::string>& args)
{
    OUZEL_UNUSED(args);
    
    lb_main(lua);
    
    //load lua dump
    std::string dumpPath = engine->getFileSystem()->getPath("dump.lua");
    lua.do_file(dumpPath);
    
    //execute main
    std::string mainPath = engine->getFileSystem()->getPath("main.lua");
    lua.do_file(mainPath);

    // sample.reset(new SpineSample());
}
