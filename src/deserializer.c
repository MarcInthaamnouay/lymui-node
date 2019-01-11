//
//  deserializer.c
//  lymui
//
//  Created by Marc Intha on 24/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <node_api.h>
#include "deserializer.h"
#include "binding_util.h"
#include "binding_error.h"
#include "deserializer_opts.h"

// Global varaible referencing the napi_env
napi_env envglobal;

/**
 * @brief Set Bridge Opt Field
 * @param obj napi_value
 * @param br * BridgeObj
 * @void
 */
static void setBridgeOptField(napi_value obj, BridgeObj *br) {
    OptField *opt = getOptField(envglobal, obj, "profile");
    if (opt == NULL) {
        return;
    }
    
    if (opt->has) {
        char *value = getStringValue(envglobal, opt->field, MAX_LEN_TYPE);
        br->matrix = value;
    }

    free(opt);
    
    OptField *clamp = getOptField(envglobal, obj, "clamp");
    if (clamp == NULL) {
        return;
    }
    
    if (clamp->has) {
        double clampValue = getDoubleValue(envglobal, clamp->field);
        br->clamp = clampValue;
    }

    free(clamp);

    OptField *scale = getOptField(envglobal, obj, "scale");
    if (scale == NULL) {
        return;
    }

    if (scale->has) {
        char *value = getStringValue(envglobal, opt->field, MAX_LEN_TYPE);
        br->matrix = value;
    }

    free(scale);
}

BridgeObj *deserialize(napi_env env, napi_value obj) {
    envglobal = env;
    BridgeObj *br = malloc(sizeof(BridgeObj));
    if (br == NULL) {
        return NULL;
    }
    
    char *inputProps = "input:output";
    napi_value params[2];
    
    if (!hasPropInJSObj(env, obj, inputProps, CONVERT_BASIC_LEN)) {
        br->error = ARG_NB_ERR;
        return br;
    }
    
    // retrieve the param of the function
    getNamedPropArray(env, inputProps, obj, CONVERT_BASIC_LEN, params);
    if (!hasPropInJSObj(env, params[0], RGB_PROPS, MIN_LEN_TYPE)) {
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

    // set the struct
    br->color  = params[0];
    br->output = validator->output;
    br->error  = NULL;
    br->matrix = NULL;
    br->clamp  = 0.0;

    free(validator);
    setBridgeOptField(obj, br);
    
    return br;
}
