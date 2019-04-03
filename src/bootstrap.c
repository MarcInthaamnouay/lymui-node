//
//  node_rgb.c
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <node_api.h>
#include "binding_error.h"
#include "convert_space.h"
#include "convert_regular.h"
#include "convert_rgb.h"
#include "convert_xyz.h"


#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }

/**
 *  Initialization of our NodeJS module
 */
napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    
    // define the methods here
    napi_property_descriptor desc[] = {
        // Normal color
        DECLARE_NAPI_METHOD("fromRGB", fromRGB),
        DECLARE_NAPI_METHOD("toRGB", toRGB),
        // Color Space
        DECLARE_NAPI_METHOD("fromXYZ", fromXYZ),
        DECLARE_NAPI_METHOD("toXYZ", toXYZ)
    };
    
    status = napi_define_properties(env, exports, sizeof(desc) / sizeof(*desc), desc);
    
    if (status != napi_ok) {
        napi_throw_error(env, NULL, BINDING_ERR);
    }
    
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
