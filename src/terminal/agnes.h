/*
SPDX-License-Identifier: MIT

agnes
https://http://github.com/kgabis/agnes
Copyright (c) 2022 Krzysztof Gabis

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
#ifndef agnes_h
#define agnes_h


#ifdef __cplusplus
extern "C"
{
#endif

#define AGNES_VERSION_MAJOR 0
#define AGNES_VERSION_MINOR 2
#define AGNES_VERSION_PATCH 0

#define AGNES_VERSION_STRING "0.2.0"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern void *agnes_memcpy(void *dst, const void *src, int n);
extern void agnes_memset(void *dst, uint8_t c, int n);
extern void agnes_print(char *s);
extern void agnes_memmove(void *dst, const void *src, int n);
extern void *agnes_malloc(int n);
extern void agnes_free(void *p);
#define memcpy agnes_memcpy
#define memset agnes_memset
#define memmove agnes_memmove
#define malloc agnes_malloc
#define free agnes_free

static int strncmp(const char *s1, const char *s2, int n) {
    unsigned char u1, u2;

    while (n-- > 0) {
        u1 = (unsigned char) *s1++;
        u2 = (unsigned char) *s2++;
        if (u1 != u2) {
            return u1 - u2;
        }
        if (u1 == '\0') {
            return 0;
        }
    }
    return 0;
}

enum {
    AGNES_SCREEN_WIDTH = 256,
    AGNES_SCREEN_HEIGHT = 240
};

typedef struct {
    bool a;
    bool b;
    bool select;
    bool start;
    bool up;
    bool down;
    bool left;
    bool right;
} agnes_input_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} agnes_color_t;

typedef struct agnes agnes_t;
typedef struct agnes_state agnes_state_t;

agnes_t* agnes_make(void);
void agnes_destroy(agnes_t *agn);
bool agnes_load_ines_data(agnes_t *agnes, const void *data, size_t data_size);
void agnes_set_input(agnes_t *agnes, const agnes_input_t *input_1, const agnes_input_t *input_2);
size_t agnes_state_size(void);
void agnes_dump_state(const agnes_t *agnes, agnes_state_t *out_res);
bool agnes_restore_state(agnes_t *agnes, const agnes_state_t *state);
bool agnes_tick(agnes_t *agnes, bool *out_new_frame);
bool agnes_next_frame(agnes_t *agnes);

agnes_color_t agnes_get_screen_pixel(const agnes_t *agnes, int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* agnes_h */
