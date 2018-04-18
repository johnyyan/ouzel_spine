//
//  lb_FileSystem.cpp
//  ouzel_spine
//
//  Created by john on 4/17/18.
//  Copyright © 2018 Bool Games. All rights reserved.
//

#include "lb_FileSystem.hpp"
#include <ouzel.hpp>

using namespace ouzel;

void lb_FileSystem(sol::table &lua)
{
    sol::usertype<FileSystem> fsType(
                                     "getStorageDirectory", &FileSystem::getStorageDirectory,
                                     "getTempDirectory", &FileSystem::getTempDirectory,
                                     
                                     "readFile", &FileSystem::readFile,
                                     "writeFile", &FileSystem::writeFile,
                                     
                                     "resourceFileExists", &FileSystem::resourceFileExists,
                                     "getPath", &FileSystem::getPath,
                                     "addResourcePath", &FileSystem::addResourcePath,
                                     "addArchive", &FileSystem::addArchive,
                                     
                                     "getExtensionPart", &FileSystem::getExtensionPart,
                                     "getFilenamePart", &FileSystem::getFilenamePart,
                                     "getDirectoryPart", &FileSystem::getDirectoryPart,
                                     "isAbsolutePath", &FileSystem::isAbsolutePath,
                                     
                                     "directoryExists", &FileSystem::directoryExists,
                                     "fileExists", &FileSystem::fileExists
                                     );
    
    lua.set_usertype("FileSystem", fsType);
}
