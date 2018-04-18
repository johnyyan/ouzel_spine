//
//  lb_Camera.cpp
//  ouzel_spine
//
//  Created by john on 4/17/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_Camera.hpp"
#include <ouzel.hpp>

using namespace ouzel::scene;

void lb_Camera(sol::table &lua)
{
    sol::usertype<Camera> cameraType(
                                     "setType", &Camera::setType,
                                     "getType", &Camera::getType,
                                     
                                     "setFOV", &Camera::setFOV,
                                     "getFOV", &Camera::getFOV,
                                     
                                     "setNearPlane", &Camera::setNearPlane,
                                     "getNearPlane", &Camera::getNearPlane,
                                     
                                     "setFarPlane", &Camera::setFarPlane,
                                     "getFarPlane", &Camera::getFarPlane,
                                     
                                     "getProjection", &Camera::getProjection,
                                     "getViewProjection", &Camera::getViewProjection,
                                     "getRenderViewProjection", &Camera::getRenderViewProjection,
                                     "getInverseViewProjection", &Camera::getInverseViewProjection,
                                     
                                     "convertNormalizedToWorld", &Camera::convertNormalizedToWorld,
                                     "convertWorldToNormalized", &Camera::convertWorldToNormalized,
                                     
                                     "checkVisibility", &Camera::checkVisibility,
                                     
                                     "setViewport", &Camera::setViewport,
                                     "getViewport", &Camera::getViewport,
                                     "getRenderViewport", &Camera::getRenderViewport,
                                     
                                     "setScaleMode", &Camera::setScaleMode,
                                     "getScaleMode", &Camera::getScaleMode,
                                     
                                     "setTargetContentSize", &Camera::setTargetContentSize,
                                     "getTargetContentSize", &Camera::getTargetContentSize,
                                     
                                     "getContentSize", &Camera::getContentSize,
                                     "getContentScale", &Camera::getContentScale,
                                     "getContentPosition", &Camera::getContentPosition,
                                     
                                     "setRenderTarget", &Camera::setRenderTarget,
                                     "getRenderTarget", &Camera::getRenderTarget,
                                     
                                     "getDepthWrite", &Camera::getDepthWrite,
                                     "setDepthWrite", &Camera::setDepthWrite,
                                     "getDepthTest", &Camera::getDepthTest,
                                     "setDepthTest", &Camera::setDepthTest,
                                     
                                     "getWireframe", &Camera::getWireframe,
                                     "setWireframe", &Camera::setWireframe,
                                     
                                     // base
                                     sol::base_classes, sol::bases<Component>()
                                     );
    
    lua.set_usertype("Camera", cameraType);
}
