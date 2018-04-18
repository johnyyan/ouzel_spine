//
//  lb_Engine.cpp
//  ouzel_spine
//
//  Created by john on 4/17/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_Engine.hpp"
#include <ouzel.hpp>

using namespace ouzel;

void lb_Engine(sol::table &lua)
{
    sol::usertype<Engine> engineType(
                                     "init", &Engine::init,
                                     "getArgs", &Engine::getArgs,
                                     
                                     "getFileSystem", &Engine::getFileSystem,
                                     "getEventDispatcher", &Engine::getEventDispatcher,
                                     "getTimer", &Engine::getTimer,
                                     "getCache", &Engine::getCache,
                                     "getWindow", &Engine::getWindow,
                                     "getRenderer", &Engine::getRenderer,
                                     "getAudio", &Engine::getAudio,
                                     "getSceneManager", &Engine::getSceneManager,
                                     "getInput", &Engine::getInput,
                                     "getLocalization", &Engine::getLocalization,
                                     "getNetwork", &Engine::getNetwork,
                                     
                                     "getDefaultSettings", &Engine::getDefaultSettings,
                                     "getUserSettings", &Engine::getUserSettings,
                                     
                                     "run", &Engine::run,
                                     "start", &Engine::start,
                                     "pause", &Engine::pause,
                                     "resume", &Engine::resume,
                                     "exit", &Engine::exit,
                                     
                                     "isPaused", &Engine::isPaused,
                                     "isActive", &Engine::isActive,
                                     
                                     "scheduleUpdate", &Engine::scheduleUpdate,
                                     "unscheduleUpdate", &Engine::unscheduleUpdate,
                                     "executeOnUpdateThread", &Engine::executeOnUpdateThread,
                                     "update", &Engine::update,
                                     
                                     "executeOnMainThread", &Engine::executeOnMainThread,
                                     "openURL", &Engine::openURL,
                                     "setScreenSaverEnabled", &Engine::setScreenSaverEnabled,
                                     "isScreenSaverEnabled", &Engine::isScreenSaverEnabled
                                     );
    
    lua.set_usertype("Engine", engineType );
}
