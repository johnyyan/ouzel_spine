//
//  lb_Sprite.cpp
//  ouzel_spine
//
//  Created by john on 4/18/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_Sprite.hpp"
#include <ouzel.hpp>

using namespace ouzel;
using namespace ouzel::scene;

void lb_Sprite(sol::table &lua)
{
    sol::usertype<Sprite>
    spriteType(
               sol::constructors<Sprite(),
               Sprite(const SpriteData& spriteData),
               Sprite(const std::string& filename, bool mipmaps, uint32_t spritesX, uint32_t spritesY, const Vector2& pivot),
               Sprite(std::shared_ptr<graphics::Texture> texture, uint32_t spritesX, uint32_t spritesY, const Vector2& pivot)>(),
               
               "init",
               sol::overload(static_cast<bool (Sprite::*)(const SpriteData& spriteData)>(&Sprite::init),
                             static_cast<bool (Sprite::*)(const std::string& filename, bool mipmaps, uint32_t spritesX, uint32_t spritesY, const Vector2& pivot)>(&Sprite::init),
                             static_cast<bool (Sprite::*)(std::shared_ptr<graphics::Texture> texture, uint32_t spritesX, uint32_t spritesY, const Vector2& pivot)>(&Sprite::init)
                             ),
               
               "update", &Sprite::update,
               "draw", &Sprite::draw,
               "getMaterial", &Sprite::getMaterial,
               "setMaterial", &Sprite::setMaterial,

               "getOffset", &Sprite::getOffset,
               "setOffset", &Sprite::setOffset,
               
               "play", &Sprite::play,
               "stop", &Sprite::stop,
               "reset", &Sprite::reset,
               "isPlaying", &Sprite::isPlaying,

               "getAnimations", &Sprite::getAnimations,
               "setCurrentFrame", &Sprite::setCurrentFrame,
               "getAnimation", &Sprite::getAnimation,
               "setAnimation", &Sprite::setAnimation,
               "addAnimation", &Sprite::addAnimation,

               // base
               sol::base_classes, sol::bases<Component>()
               );
    
    lua.set_usertype("Sprite", spriteType);
}
