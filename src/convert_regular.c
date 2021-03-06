//
//  convert_regular.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdlib.h>
#include <node_api.h>
#include "convert_regular.h"
#include "binding_error.h"
#include "factory_regular.h"
#include "factory_space.h"
#include "factory_common.h"
#include "factory_operation.h"
#include "deserializer.h"
#include "bridge.h"

/**
 * @brief Generate the napi_value containing the color type
 * @param bridge BridgeObj
 * @return napi_value
 */
static napi_value generateTypeJSObj(napi_env env, BridgeObj *bridge) {
    Rgb *rgb = getRGBFromJSObj(env, bridge->color);
    if (rgb == NULL) {
        return NULL;
    }
    
    switch (bridge->output) {
        case hex:
            return HexJSObjFactory(env, rgb);
        case hsl:
            return HslJSObjFactory(env, rgb, bridge->clamp);
        case hsv:
            return HsvJSObjFactory(env, rgb, bridge->clamp);
        case cymk:
            return CymkJSObjFactory(env, rgb, bridge->clamp);
        case ycbcr:
            return YcbcrJSObjFactory(env, rgb);
        case yuv:
            return YuvJSObjFactory(env, rgb, bridge->clamp);
        case xyz:
            return XyzJSObjFactory(env, rgb, bridge->matrix, bridge->clamp);
        case hwb:
            return HwbJSObjFactory(env, rgb, bridge->clamp);
        case tsl:
            return TslJSObjFactory(env, rgb, bridge->clamp);
        case grasycale:
            return GrayScaleJSObjFactory(env, rgb, bridge->matrix);
        case tint:
            return TintFactory(env, rgb);
        case shade:
            return ShadeFactory(env, rgb);
        default:
            return NULL;
    }
}

/**
 *  JS API
 *  const xyz = async fromRGB({
 *    input: {
 *      r: 100,
 *      g: 10,
 *      b: 200
 *    },
 *    output: 'xyz',
 *    profile: 'adobeRgb', (optional) <string> only use for xyz
 *    clamp: 1000, (optional) <double>
 *    scale: 'Lightness', (optional) <string> only use for grayscale
 *  })
 *
 */
napi_value fromRGB(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value promise;
    napi_deferred def;
    napi_value JSObject;
    
    status = napi_create_promise(env, &def, &promise);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, PROMISE_ERR);
        return NULL;
    }
    
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (status != napi_ok) {
        napi_reject_deferred(env, def, BuildPromiseError(env, CB_INFO_ERR));
        return promise;
    }
    
    if (argc < 1) {
        napi_reject_deferred(env, def, BuildPromiseError(env, ARG_NB_ERR));
        return promise;
    }
    
    BridgeObj *bridge = deserialize(env, argv[0]);
    if (bridge == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, DESERIALIZE_ERR));
        return promise;
    }
    
    if (bridge->error != NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, bridge->error));
        free(bridge);
        return promise;
    }
    
    JSObject = generateTypeJSObj(env, bridge);
    if (JSObject == NULL) {
        napi_reject_deferred(env, def, BuildPromiseError(env, CREATE_VALUE_ERR));
        free(bridge);
        return promise;
    }
    
    free(bridge);
    napi_resolve_deferred(env, def, JSObject);
    
    return promise;
}
