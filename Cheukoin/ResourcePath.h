//
//  ResourcePath.h
//  Cheukoin
//
//  Created by Corentin on 10/6/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__ResourcePath__
#define __Cheukoin__ResourcePath__

#include <string>

#ifdef __APPLE__
#include "ResourcePathOSX.hpp"
#else
inline std::string resourcePath(std::string fileName) {
    return "Resources/" + fileName;
}
#endif

#endif /* defined(__Cheukoin__ResourcePath__) */
