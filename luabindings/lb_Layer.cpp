//
//  lb_Layer.cpp
//  ouzel_spine
//
//  Created by john on 4/17/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_Layer.hpp"
#include <ouzel.hpp>

using namespace ouzel;
using namespace ouzel::scene;

void lb_Layer(sol::table &lua)
{
    sol::usertype<Layer> layerType(
                                   "draw", &Layer::draw,
                                   "getCameras", &Layer::getCameras,
                                   "pickActor", &Layer::pickActor,
                                   "pickActors", sol::overload(static_cast<std::vector<Actor*> (Layer::*)(const std::vector<Vector2>& edges, bool renderTargets) const>(&Layer::pickActors)),

                                   "getOrder", &Layer::getOrder,
                                   "setOrder", &Layer::setOrder,
                                   
                                   "getScene", &Layer::getScene,
                                   "removeFromScene", &Layer::removeFromScene,
                                   
                                   // base
                                   sol::base_classes, sol::bases<ActorContainer>()
                                   );
    
    lua.set_usertype("Layer", layerType );
}
