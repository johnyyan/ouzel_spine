// Copyright (C) 2017 Elviss Strazdins

#include "SpineSample.hpp"

#define SOL_CHECK_ARGUMENTS 1
#include <sol/sol.hpp>

std::string DEVELOPER_NAME = "elnormous";
std::string APPLICATION_NAME = "Spine sample";

std::unique_ptr<SpineSample> sample;

void ouzelMain(const std::vector<std::string>& args)
{
    OUZEL_UNUSED(args);
    
    //lua state
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::coroutine);

    int x = 0;
    lua.set_function("beep", [&x]{ ++x; });
    lua.script("beep()");
    lua.script("print('dddd')");
    
//    sample.reset(new SpineSample());
}
