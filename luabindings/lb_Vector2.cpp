//
//  lb_Vector2.cpp
//  ouzel_spine
//
//  Created by john on 4/18/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_Vector2.hpp"
#include <ouzel.hpp>

using namespace ouzel;

void lb_Vector2(sol::table &lua)
{
    sol::usertype<Vector2>
    vec2Type(
             sol::constructors<Vector2(),
             Vector2(float initX, float initY),
             Vector2(const Vector2& p1, const Vector2& p2),
             Vector2(const Vector2& copy),
             Vector2(const Vector3& vec),
             Vector2(const Vector4& vec)>(),

             "isZero", &Vector2::isZero,
             "isOne", &Vector2::isOne,
             "angle", &Vector2::angle,
             "add", sol::overload(static_cast<void (Vector2::*)(const Vector2& vec)>(&Vector2::add)),
             "clamp", sol::overload(static_cast<void (Vector2::*)(const Vector2& min, const Vector2& max)>(&Vector2::clamp)),
             
             "distance", &Vector2::distance,
             "distanceSquared", &Vector2::distanceSquared,
             
             "dot", sol::overload(static_cast<float (Vector2::*)(const Vector2& vec) const>(&Vector2::dot)),
             "length", &Vector2::length,
             "lengthSquared", &Vector2::lengthSquared,
             "negate", &Vector2::negate,
             "normalize", &Vector2::normalize,
             "scale", sol::overload(static_cast<void (Vector2::*)(float scalar)>(&Vector2::scale),
                                    static_cast<void (Vector2::*)(const Vector2& scale)>(&Vector2::scale)),
             
             "rotate", sol::overload(static_cast<void (Vector2::*)(float angle)>(&Vector2::rotate),
                                     static_cast<void (Vector2::*)(const Vector2& point, float angle)>(&Vector2::rotate)),
             
             "set", sol::overload(static_cast<void (Vector2::*)(float newX, float newY)>(&Vector2::set),
                                  static_cast<void (Vector2::*)(const Vector2& p1, const Vector2& p2)>(&Vector2::set)),
             
             "subtract", sol::overload(static_cast<void (Vector2::*)(const Vector2& vec)>(&Vector2::subtract)),
             
             "smooth", &Vector2::smooth,
             "getMin", &Vector2::getMin,
             "getMax", &Vector2::getMax,
             "getAngle", &Vector2::getAngle,

             sol::meta_function::addition, &Vector2::operator+,
             sol::meta_function::subtraction, sol::overload(static_cast<Vector2 (Vector2::*)(const Vector2& vec) const>(&Vector2::operator-),
                                  static_cast<Vector2 (Vector2::*)() const>(&Vector2::operator-)),
             sol::meta_function::multiplication, &Vector2::operator*,
             sol::meta_function::division, &Vector2::operator/,
             sol::meta_function::equal_to, &Vector2::operator==,
             sol::meta_function::less_than, &Vector2::operator<,
             
             "x", sol::readonly(&Vector2::x),
             "y", sol::readonly(&Vector2::y)
             );
    
    lua.set_usertype("Vector2", vec2Type);
}
