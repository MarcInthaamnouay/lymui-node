//
//  factory.h
//  lymui
//
//  Created by Marc Intha on 01/11/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef factory_h
#define factory_h

#include <stdio.h>
#include <node_api.h>
#include "rgb.h"
#include "hex.h"
#include "cymk.h"
#include "ycbcr.h"
#include "hsl.h"
#include "hsv.h"
#include "yuv.h"
#include "hwb.h"
#include "tsl.h"
#include "grayscale.h"
#include "xyz.h"
#include "lab.h"
#include "lch.h"
#include "lchlab.h"
#include "luv.h"
#include "argb.h"
#include "srgb.h"
#include "xyy.h"

#define COLOR_SPACE_CLAMP 10000

/**
 * @brief struct use for handling promise error
 */
typedef struct JSError {
    char * error;
} JSError;


/**
 * @brief Factory creating Rgb Object on the fly
 * @param env napi_env
 * @param rgb Rgb struct pointer
 * @return napi_value
 */
napi_value RgbJSObjFactory(napi_env env, Rgb *rgb);

/**
 * @brief Factory creating a Hex JS Object
 * @param env napi_env
 * @param rgb Rgb struct pointer
 * @return napi_env
 */
napi_value HexJSObjFactory(napi_env env, Rgb *rgb);

/**
 * @brief Factory creating Cymk JS Object
 * @param env napi_env
 * @param rgb Rgb struct pointer
 * @param clamp double
 * @return napi_value
 */
napi_value CymkJSObjFactory(napi_env env, Rgb *rgb, double clamp);

/**
 * @brief Factory creating Ycbcr Object
 * @param env napi_env
 * @param rgb Rgbs struct pointer
 * @return napi_value
 */
napi_value YcbcrJSObjFactory(napi_env env, Rgb *rgb);

/**
 * @brief Factory creating Hsl Object
 * @param env napi_env
 * @param rgb Rgb struct pointer
 * @param clamp double
 * @return napi_value
 */
napi_value HslJSObjFactory(napi_env env, Rgb *rgb, double clamp);

/**
 * @brief Creating HSV JS Object
 * @param env napi_env
 * @param rgb struct Rgb pointer
 * @param clamp double
 * @return napi_value
 */
napi_value HsvJSObjFactory(napi_env env, Rgb *rgb, double clamp);

/**
 * @brief Creating YUV JS Object
 * @param env napi_env
 * @param rgb *Rgb
 * @param clamp double
 * @return napi_value
 */
napi_value YuvJSObjFactory(napi_env env, Rgb *rgb, double clamp);

/**
 * @brief Creating HSV JS Object
 * @param env napi_env
 * @param rgb Rgb struct
 * @param clamp double
 * @return napi_value
 */
napi_value HwbJSObjFactory(napi_env env, Rgb *rgb, double clamp);

/**
 * @brief Creating TSL JS Object
 * @param env napi_env
 * @param rgb Rgb
 * @param clamp double
 * @return napi_value
 */ 
napi_value TslJSObjFactory(napi_env env, Rgb *rgb, double clamp);

/**
 * @brief Creating a Grayscale JS Object
 * @param env napi_env
 * @param rgb Rgb
 * @return napi_value
 */
napi_value GrayScaleJSObjFactory(napi_env env, Rgb *rgb);

/**
 * @brief Creating Xyz JS Object
 * @param env napi_env
 * @param rgb *Rgb
 * @param clamp double
 * @return napi_value
 */
napi_value XyzJSObjFactory(napi_env env, Rgb *rgb, char *matrix, double clamp);

/**
 * @brief Create Xyz JS Object
 * @param env napi_env
 * @param xyz Xyz
 * @param clamp double
 * @return napi_value
 */
napi_value XyzJSObjFactoryNoInst(napi_env env, Xyz *xyz, double clamp);

/**
 * @brief Creating Lab JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @param clamp double
 * @return napi_value
 */
napi_value LabJSObjFactory(napi_env env, Xyz * xyz, double clamp);

/**
 * @brief Creating Lch JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @param clamp double
 * @return napi_value
 */
napi_value LchJSObjFactory(napi_env env, Xyz * xyz, double clamp);

/**
 * @brief Creating Lch Lab JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @param clamp double
 * @return napi_value
 */
napi_value LchLabJSObjFactory(napi_env env, Xyz * xyz, double clamp);

/**
 * @brief Creating Luv JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @param clamp double
 * @return napi_value
 */
napi_value LuvJSObjFactory(napi_env env, Xyz * xyz, double clamp);

/**
 * @brief Creating ARGB JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @param clamp double
 * @return napi_value
 */
napi_value ArgbJSObjFactory(napi_env env, Xyz *xyz, double clamp);

/**
 * @brief Creating Srgb JS Object
 * @param env napi_env
 * @param xyz * Xyz
 * @param clamp double
 * @return napi_value
 */
napi_value SrgbJSObjFactory(napi_env env, Xyz *xyz, double clamp);

/**
 * @brief Creating XYY JS Object
 * @param env napi_env
 * @param xyz Xyz
 * @param clamp double
 * @return napi_value
 */
napi_value XyyJSObjFactory(napi_env env, Xyz *xyz, double clamp);

/**
 * @brief Build Promise Error
 * @param env napi_env
 * @param error * char
 * @return napi_value
 */
napi_value BuildPromiseError(napi_env env, char * error);

#endif /* factory_h */
