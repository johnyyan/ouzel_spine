//
//  lb_Component.cpp
//  ouzel_spine
//
//  Created by john on 4/18/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_Component.hpp"
#include <ouzel.hpp>

using namespace ouzel;
using namespace ouzel::scene;

void lb_Component(sol::table &lua)
{
    sol::usertype<Component> componentType(
                                           "getType", &Component::getType,
                                           "draw", &Component::draw,
                                           
                                           "setBoundingBox", &Component::setBoundingBox,
                                           "getBoundingBox", &Component::getBoundingBox,

                                           "pointOn", &Component::pointOn,
                                           "shapeOverlaps", &Component::shapeOverlaps,
                                           "isHidden", &Component::isHidden,
                                           "setHidden", &Component::setHidden,
                                           "getActor", &Component::getActor,
                                           "removeFromActor", &Component::removeFromActor
                                           );
    
    lua.set_usertype("Component", componentType);
}
