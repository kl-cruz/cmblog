/*
 * Copyright (c) 2018, Karol Lasończyk
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CMBLOG_H_
#define _CMBLOG_H_

#include <stdint.h>

/**
 * @brief Pointer to function with output data as argument
 */
typedef void (*cmblog_out_t)(void *p, uint8_t size);

#if CMBLOG_DISABLE

#define cmblog_init(dev)                do {} while(0)
#define cmblog_deinit()                 do {} while(0)

#define cmblog_error(__format, ...)     do {} while(0)
#define cmblog_warn(__format, ...)      do {} while(0)
#define cmblog_info(__format, ...)      do {} while(0)
#define cmblog_debug(__format, ...)     do {} while(0)

#else

/**
 * @brief Log levels.
 */
typedef enum {
    CMBLOG_OFF =   0, /**< Log subsystem disabled. */
    CMBLOG_ERROR = 1, /**< Error log level*/
    CMBLOG_WARN =  2, /**< Warning log level*/
    CMBLOG_INFO =  3, /**< Info log level*/
    CMBLOG_DEBUG = 4, /**< Debug log level*/
} cmblog_level_t;

/**
 * @brief Log context structure
 */
typedef struct {
    cmblog_level_t severity; /**< The highest severity level of printable logs. */
    const char *   source;   /**< The name of the log source.*/
} cmblog_t;

/**
 * @brief Macro for declaring log system structure.
 *
 * @param _severity The highest severity level of printable logs.
 * @param _source   The name of the log source.
 */
#define CMBLOG_DECLARE_LOG(_severity, _source)       \
        static cmblog_t __CMBLOG_CTX__ = {           \
                .severity = _severity,               \
                .source = (const char []){(_source)} \
        };

/**
 * @brief Macro for declaring log system structure with filename as a source.
 *
 * @param _severity The highest severity level of printable logs.
 */
#define CMBLOG_DECLARE_FILE_LOG(_severity) CMBLOG_DECLARE_LOG(_severity, __FILE__)

/**
 * @brief Macro for printing log text with particular severity level.
 *
 * @param _severity Severity level of the log.
 * @param _format   Text to print.
 * @param ...       Arguments.
 */
#define cmblog_print_log(_severity, _format, ...) do {                                   \
        if (__CMBLOG_CTX__.severity >= _severity)                                        \
        {                                                                                \
            cmblog_printf(&__CMBLOG_CTX__, _severity, __LINE__, _format, ##__VA_ARGS__); \
        }                                                                                \
    } while (0)

/**
 * @brief Macro for printing log text with error severity level.
 *
 * @param _format   Text to print.
 * @param ...       Arguments.
 */
#define cmblog_error(_format, ...) cmblog_print_log(CMBLOG_ERROR, _format, ##__VA_ARGS__)

/**
 * @brief Macro for printing log text with warning severity level.
 *
 * @param _format   Text to print.
 * @param ...       Arguments.
 */
#define cmblog_warn(_format, ...)  cmblog_print_log(CMBLOG_WARN,  _format, ##__VA_ARGS__)

/**
 * @brief Macro for printing log text with info severity level.
 *
 * @param _format   Text to print.
 * @param ...       Arguments.
 */
#define cmblog_info(_format, ...)  cmblog_print_log(CMBLOG_INFO,  _format, ##__VA_ARGS__)

/**
 * @brief Macro for printing log text with debug severity level.
 *
 * @param _format   Text to print.
 * @param ...       Arguments.
 */
#define cmblog_debug(_format, ...) cmblog_print_log(CMBLOG_DEBUG, _format, ##__VA_ARGS__)

/**
 * @brief cmblog_init Function for initializing the log output function.
 *
 * @param p_out_fun Pointer to function with output data.
 */
void cmblog_init(cmblog_out_t p_out_fun);

/**
 * @brief cmblog_printf Function for processing text data. Executes output data function internally.
 *
 * @param p_log Structure with log context.
 * @param level Severity level.
 * @param line  Line in file.
 * @param fmt   Text to process.
 */
void cmblog_printf(cmblog_t *p_log, cmblog_level_t level, uint16_t line, char * fmt, ...);

#endif

#endif // _CMBLOG_H_
