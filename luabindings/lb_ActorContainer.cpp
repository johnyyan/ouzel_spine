//
//  lb_ActorContainer.cpp
//  ouzel_spine
//
//  Created by john on 4/18/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_ActorContainer.hpp"
#include <ouzel.hpp>

using namespace ouzel;
using namespace ouzel::scene;

void lb_ActorContainer(sol::table &lua)
{
    sol::usertype<ActorContainer>
    actorContainerType(
                       "addChild", sol::overload(static_cast<void (ActorContainer::*)(Actor* actor)>(&ActorContainer::addChild)),
                       "removeChild", sol::overload(static_cast<bool (ActorContainer::*)(Actor* actor)>(&ActorContainer::removeChild)),
                       
                       "moveChildToBack", &ActorContainer::moveChildToBack,
                       "moveChildToFront", &ActorContainer::moveChildToFront,
                       "removeAllChildren", &ActorContainer::removeAllChildren,
                       "hasChild", &ActorContainer::hasChild,
                       "getChildren", &ActorContainer::getChildren,
                       "getLayer", &ActorContainer::getLayer,
                       "findActors",
                       sol::overload(
                                     static_cast<void (ActorContainer::*)(const Vector2& position, std::vector<std::pair<Actor*, Vector3>>& actors)const>(&ActorContainer::findActors),
                                     static_cast<void (ActorContainer::*)(const std::vector<Vector2>& edges, std::vector<Actor*>& actors)const>(&ActorContainer::findActors)
                                     )
                       );
    
    lua.set_usertype("ActorContainer", actorContainerType);
}
