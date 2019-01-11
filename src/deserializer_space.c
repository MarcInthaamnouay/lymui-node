//
//  deserializer_space.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include "deserializer_space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "binding_error.h"
#include "binding_util.h"
#include "deserializer_opts.h"

// Global varaible referencing the napi_env
napi_env envglobal;

/**
 * @brief Set Bridge Opt Field
 * @param obj napi_value obj
 * @param br * BridgeObj
 */
static void setBridgeOptField(napi_value obj, BridgeSpaceObj *br) {
    OptField *clamp = getOptField(envglobal, obj, "clamp");
    if (clamp == NULL) {
        return;
    }
    
    if (clamp->has) {
        double clampValue = getDoubleValue(envglobal, clamp->field);
        br->clamp = clampValue;
    }
}

BridgeSpaceObj *deserializeSpace(napi_env env, napi_value obj) {
    envglobal = env;
    BridgeSpaceObj *br = malloc(sizeof(BridgeSpaceObj));
    if (br == NULL) {
        return NULL;
    }
    
    char *inputProps = "input:output";
    napi_value params[2];
    
    if (!hasPropInJSObj(env, obj, inputProps, CONVERT_BASIC_LEN)) {
        br->error = ARG_NB_ERR;
        return br;
    }
    
    getNamedPropArray(env, inputProps, obj, CONVERT_BASIC_LEN, params);
    if (!hasPropInJSObj(env, params[0], XYZ_PROPS, MIN_LEN_TYPE)) {
        br->error = ARG_TYPE_ERR;
        return br;
    }
    
    char *type = getStringValue(env, params[1], MAX_LEN_TYPE);
    if (type == NULL) {
        br->error = CONVERT_ERR;
        return br;
    }

    Validation *validator = getValidationProps(type);
    if (validator == NULL) {
        br->error = OTYPE_TYPE_ERR;
        return br;
    }

    free(type);
    
    br->color  = params[0];
    br->output = validator->output;
    br->error  = NULL;
    br->clamp  = 0.0;

    // set the optionals fields
    setBridgeOptField(obj, br);    
    free(validator);
    
    return br;
}
