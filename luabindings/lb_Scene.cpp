//
//  lb_Scene.cpp
//  ouzel_spine
//
//  Created by john on 4/17/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_Scene.hpp"
#include <ouzel.hpp>

using namespace ouzel;
using namespace ouzel::scene;

void lb_Scene(sol::table &lua)
{
    sol::usertype<Scene> sceneType(
                                   "draw", &Scene::draw,
                                   
                                   "addLayer", sol::overload(static_cast<void (Scene::*)(Layer* layer)>(&Scene::addLayer)),
                                   "removeLayer", sol::overload(static_cast<bool (Scene::*)(Layer* layer)>(&Scene::removeLayer)),
                                   
                                   "removeAllLayers", &Scene::removeAllLayers,
                                   
                                   "hasLayer", &Scene::hasLayer,
                                   "getLayers", &Scene::getLayers,
                                   "recalculateProjection", &Scene::recalculateProjection,
                                   
                                   "pickActor", &Scene::pickActor,
                                   "pickActors", sol::overload(static_cast<std::vector<Actor*> (Scene::*)(const std::vector<Vector2>& edges, bool renderTargets) const>(&Scene::pickActors))
                                   );
    
    lua.set_usertype("Scene", sceneType );
}
