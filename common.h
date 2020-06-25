/*
Copyright (c) 2012 Radoslav Gerganov <rgerganov@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdbool.h>

enum modifier {
    MOD_L_CTRL    = 1,
    MOD_L_SHIFT   = 2,
    MOD_L_OPTION  = 4, // ALT
    MOD_L_COMMAND = 8, // SUPER

    MOD_R_CTRL    = 16,
    MOD_R_SHIFT   = 32,
    MOD_R_OPTION  = 64,
    MOD_R_COMMAND = 128,
};

enum mouse_button {
    BTN_L_MOUSE = 1, // left
    BTN_R_MOUSE = 2, // right
    BTN_M_MOUSE = 4, // middle
    BTN_D_MOUSE = 8, // double
};

bool parse_modifier(const char *, enum modifier *);
bool parse_mouse_button(const char *, enum mouse_button *);

bool encode_string(const char *, unsigned char *);
bool encode_key(const char *, unsigned char *);

const char * decode_byte(unsigned char);

#endif
