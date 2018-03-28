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

#include "cmblog.h"
#include "mini-printf.h"

#define PRE_BUF_SIZE 128
#define POST_BUF_SIZE 256

static cmblog_out_t m_p_out_fun;

static const char *m_log_levels[] = {
    "",
    "ERROR",
    "WARN ",
    "INFO ",
    "DEBUG"
};

/*
 * Log format to show logs:
 * SEVERITY:SOURCE:LINE:LOG_TEXT
 */
#define LOG_FORMAT "%s:%s:%d:%s\n"

void cmblog_init(cmblog_out_t p_out_fun)
{
    m_p_out_fun = p_out_fun;
}

void cmblog_printf(cmblog_t *p_log, cmblog_level_t level, uint16_t line, char * fmt, ...)
{
    static char m_int_pre_buffer[PRE_BUF_SIZE];
    static char m_int_post_buffer[POST_BUF_SIZE];

    va_list ap;

    mini_snprintf(m_int_pre_buffer,
                  PRE_BUF_SIZE,
                  LOG_FORMAT,
                  m_log_levels[level],
                  p_log->source,
                  line,
                  fmt);

    va_start(ap, fmt);
    int out_len = mini_vsnprintf(m_int_post_buffer, POST_BUF_SIZE, m_int_pre_buffer, ap);
    va_end(ap);

    m_p_out_fun(m_int_post_buffer, out_len);
}
