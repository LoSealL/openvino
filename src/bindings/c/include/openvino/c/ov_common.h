// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

/**
 * @brief This is a common header file for the C API
 *
 * @file ov_common.h
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifdef __cplusplus
#    define OPENVINO_C_API_EXTERN extern "C"
#else
#    define OPENVINO_C_API_EXTERN
#endif

#if defined(OPENVINO_STATIC_LIBRARY) || defined(__GNUC__) && (__GNUC__ < 4)
#    define OPENVINO_C_API(...) OPENVINO_C_API_EXTERN __VA_ARGS__
#    define OPENVINO_C_VAR(...) OPENVINO_C_API_EXTERN __VA_ARGS__
#    define OV_NODISCARD
#else
#    if defined(_WIN32)
#        define OPENVINO_C_API_CALLBACK __cdecl
#        ifdef openvino_c_EXPORTS
#            define OPENVINO_C_API(...) OPENVINO_C_API_EXTERN __declspec(dllexport) __VA_ARGS__ __cdecl
#            define OPENVINO_C_VAR(...) OPENVINO_C_API_EXTERN __declspec(dllexport) __VA_ARGS__
#        else
#            define OPENVINO_C_API(...) OPENVINO_C_API_EXTERN __declspec(dllimport) __VA_ARGS__ __cdecl
#            define OPENVINO_C_VAR(...) OPENVINO_C_API_EXTERN __declspec(dllimport) __VA_ARGS__
#        endif
#        define OV_NODISCARD
#    else
#        define OPENVINO_C_API(...) OPENVINO_C_API_EXTERN __attribute__((visibility("default"))) __VA_ARGS__
#        define OPENVINO_C_VAR(...) OPENVINO_C_API_EXTERN __attribute__((visibility("default"))) __VA_ARGS__
#        define OV_NODISCARD        __attribute__((warn_unused_result))
#    endif
#endif

#ifndef OPENVINO_C_API_CALLBACK
#    define OPENVINO_C_API_CALLBACK
#endif

/**
 * @enum ov_status_code_e
 * @brief This enum contains codes for all possible return values of the interface functions
 */
typedef enum {
    OK = 0,
    /*
     * @brief map exception to C++ interface
     */
    GENERAL_ERROR = -1,
    NOT_IMPLEMENTED = -2,
    NETWORK_NOT_LOADED = -3,
    PARAMETER_MISMATCH = -4,
    NOT_FOUND = -5,
    OUT_OF_BOUNDS = -6,
    /*
     * @brief exception not of std::exception derived type was thrown
     */
    UNEXPECTED = -7,
    REQUEST_BUSY = -8,
    RESULT_NOT_READY = -9,
    NOT_ALLOCATED = -10,
    INFER_NOT_STARTED = -11,
    NETWORK_NOT_READ = -12,
    INFER_CANCELLED = -13,
    /*
     * @brief exception in C wrapper
     */
    INVALID_C_PARAM = -14,
    UNKNOWN_C_ERROR = -15,
} ov_status_e;

/**
 * @enum ov_element_type_e
 * @brief This enum contains codes for element type.
 */
typedef enum {
    UNDEFINED = 0U,  //!< Undefined element type
    DYNAMIC,         //!< Dynamic element type
    BOOLEAN,         //!< boolean element type
    BF16,            //!< bf16 element type
    F16,             //!< f16 element type
    F32,             //!< f32 element type
    F64,             //!< f64 element type
    I4,              //!< i4 element type
    I8,              //!< i8 element type
    I16,             //!< i16 element type
    I32,             //!< i32 element type
    I64,             //!< i64 element type
    U1,              //!< binary element type
    U4,              //!< u4 element type
    U8,              //!< u8 element type
    U16,             //!< u16 element type
    U32,             //!< u32 element type
    U64,             //!< u64 element type
} ov_element_type_e;

/**
 * @enum ov_any_type_e
 * @brief Enum to define ov_any data type.
 */
typedef enum {
    BOOL = 0U,  //!< boolean data
    CHAR,       //!< char data
    INT32,      //!< int32 data
    UINT32,     //!< uint32 data
    INT64,      //!< int64 data
    UINT64,     //!< uint64 data
    ENUM,       //!< enum data, must define U32 data for enumeration
    FLOAT,      //!< float data
    DOUBLE,     //!< double data
} ov_any_type_e;

/**
 * @struct ov_any_t
 * @brief Represent a property value
 */
typedef struct {
    void* ptr;
    size_t size;
    ov_any_type_e type;
} ov_any_t;

/**
 * @brief Free ov_any data.
 * @param value The ov_any data will be freed.
 */
OPENVINO_C_API(void) ov_any_free(ov_any_t* value);

/**
 * @brief Print the error info.
 * @param ov_status_e a status code.
 */
OPENVINO_C_API(const char*) ov_get_error_info(ov_status_e status);

/**
 * @brief free char
 * @param content The pointer to the char to free.
 */
OPENVINO_C_API(void) ov_free(const char* content);
