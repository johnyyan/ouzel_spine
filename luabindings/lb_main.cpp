//
//  lb_main.cpp
//  ouzel_spine
//
//  Created by john on 4/17/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_main.hpp"
#include <ouzel.hpp>

#include "lb_Component.hpp"
#include "lb_Camera.hpp"
#include "lb_FileSystem.hpp"
#include "lb_ActorContainer.hpp"
#include "lb_Actor.hpp"
#include "lb_Vector2.hpp"
#include "lb_Layer.hpp"
#include "lb_Scene.hpp"
#include "lb_SceneManager.hpp"
#include "lb_Engine.hpp"
#include "lb_Sprite.hpp"

void lb_main(sol::state &lua)
{
    // init base
    lua.open_libraries();

    // oz namespace
    sol::table oz = lua.create_named_table("oz");
    
    // init ouzel bindings
    lb_FileSystem(oz);
    lb_ActorContainer(oz);
    lb_Component(oz);
    lb_Camera(oz);
    lb_Vector2(oz);
    lb_Layer(oz);
    lb_Actor(oz);
    lb_SceneManager(oz);
    lb_Scene(oz);
    lb_Engine(oz);
    lb_Sprite(oz);
    
    // global engine
    lua.set("engine", ouzel::engine);
}
