//
//  binding_error.h
//  lymui
//
//  Created by Marc Intha on 24/10/2018.
//  Copyright © 2018 Marc. All rights reserved.
//

#ifndef binding_error_h
#define binding_error_h

#define BINDING_ERR "Unable to bind lib methods"
#define DESERIALIZE_ERR "Unable to deserializing the value"
#define PARSE_ERR "Unable to parse the value"
#define CONVERT_ERR "Error while converting value to an other type"
#define ASSIGN_ERR "Unable to assign value to JS Object"
#define ARG_NB_ERR "Missing arguments"
#define ARG_TYPE_ERR "Wrong argument(s) type"
#define OBJ_MAKE_ERR "Error while creating JS Object"
#define PROP_NOT_FOUND_ERR "Property not found in JS Object"
#define CREATE_TYPE_ERR "An error occured when converting JS type to C type"
#define CREATE_VALUE_ERR "Error while creating JS Value"
#define CONVERSION_ERR "Error while converting from Type T to an other type"
#define ALLOCATION_ERR "Error while creating new type T of color"
#define PROMISE_ERR "Unable to create promise"
#define CB_INFO_ERR "Unable to retrieve data from method"
#define OTYPE_TYPE_ERR "Unable to retrieve the type of the color"
#define INVALID_TYPE "This color format is not supported by the library"

#endif /* binding_error_h */
