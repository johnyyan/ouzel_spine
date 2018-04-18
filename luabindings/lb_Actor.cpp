//
//  lb_Actor.cpp
//  ouzel_spine
//
//  Created by john on 4/17/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_Actor.hpp"
#include <ouzel.hpp>

using namespace ouzel;
using namespace ouzel::scene;

void lb_Actor(sol::table &lua)
{
    sol::usertype<Actor> actorType(
                                   "visit", &Actor::visit,
                                   "draw", &Actor::draw,
                                   
                                   "setPosition", sol::overload(static_cast<void (Actor::*)(const Vector2& newPosition)>(&Actor::setPosition),
                                                                static_cast<void (Actor::*)(const Vector3& newPosition)>(&Actor::setPosition)),
                                   "getPosition", &Actor::getPosition,
                                   
                                   "setOrder", &Actor::setOrder,
                                   "getOrder", &Actor::getOrder,
                                   
                                   "setRotation", sol::overload(static_cast<void (Actor::*)(const Quaternion& newRotation)>(&Actor::setRotation),
                                                                static_cast<void (Actor::*)(const Vector3& newRotation)>(&Actor::setRotation),
                                                                static_cast<void (Actor::*)(float newRotation)>(&Actor::setRotation)),
                                   "getRotation", &Actor::getRotation,
                                   
                                   "setScale", sol::overload(static_cast<void (Actor::*)(const Vector2& newScale)>(&Actor::setScale),
                                                             static_cast<void (Actor::*)(const Vector3& newScale)>(&Actor::setScale)),
                                   "getScale", &Actor::getScale,
                                   
                                   "setFlipX", &Actor::setFlipX,
                                   "getFlipX", &Actor::getFlipX,
                                   
                                   "setFlipY", &Actor::setFlipY,
                                   "getFlipY", &Actor::getFlipY,
                                   
                                   "setPickable", &Actor::setPickable,
                                   "isPickable", &Actor::isPickable,
                                   
                                   "isCullDisabled", &Actor::isCullDisabled,
                                   "setCullDisabled", &Actor::setCullDisabled,
                                   
                                   "setHidden", &Actor::setHidden,
                                   "isHidden", &Actor::isHidden,
                                   "isWorldHidden", &Actor::isWorldHidden,
                                   
                                   "pointOn", &Actor::pointOn,
                                   "shapeOverlaps", &Actor::shapeOverlaps,
                                   
                                   "getLocalTransform", &Actor::getLocalTransform,
                                   "getTransform", &Actor::getTransform,
                                   "getInverseTransform", &Actor::getInverseTransform,
                                   
                                   "getWorldPosition", &Actor::getWorldPosition,
                                   "getWorldOrder", &Actor::getWorldOrder,
                                   
                                   "convertWorldToLocal", &Actor::convertWorldToLocal,
                                   "convertLocalToWorld", &Actor::convertLocalToWorld,
                                   
                                   "getParent", &Actor::getParent,
                                   "removeFromParent", &Actor::removeFromParent,
                                   
                                   "addComponent", sol::overload(static_cast<void (Actor::*)(Component* component)>(&Actor::addComponent)),
                                   "removeComponent", sol::overload(static_cast<bool (Actor::*)(Component* component)>(&Actor::removeComponent)),
                                   
                                   "removeAllComponents", &Actor::removeAllComponents,
                                   "getComponents", sol::overload(static_cast<const std::vector<Component*>& (Actor::*)() const>(&Actor::getComponents),
                                                                  static_cast<std::vector<Component*> (Actor::*)(uint32_t type) const>(&Actor::getComponents)
                                                                  ),
                                   "getBoundingBox", &Actor::getBoundingBox
                                   );
    
    lua.set_usertype("Actor", actorType);
}
