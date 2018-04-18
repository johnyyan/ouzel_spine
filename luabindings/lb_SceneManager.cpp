//
//  lb_SceneManager.cpp
//  ouzel_spine
//
//  Created by john on 4/18/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_SceneManager.hpp"
#include <ouzel.hpp>

using namespace ouzel;
using namespace ouzel::scene;

void lb_SceneManager(sol::table &lua)
{
    sol::usertype<SceneManager> sceneManagerType(
                                                 "draw", &SceneManager::draw,
                                                 "setScene", sol::overload(static_cast<void (SceneManager::*)(Scene* scene)>(&SceneManager::setScene)),
                                                 "removeScene", &SceneManager::removeScene,
                                                 "getScene", &SceneManager::getScene
                                                 );
    
    lua.set_usertype("SceneManager", sceneManagerType);
}
