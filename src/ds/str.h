/*
BSD 3-Clause License

Copyright (c) 2024, Adwaith Rajesh

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// A simple string lib for loooka

/*
Usage

   #define _LOOOKA_STR_IMPLEMENTATION
   #include "str.h"

   int main() {
      String *str = str_create();
      ...
   }


define STR_MALLOC to avoid using malloc, realloc

Usage:
   #define STR_MALLOC(SZ)           malloc(SZ)
   #define STR_REALLOC(PTR, SZ)     realloc(PTR, SZ)
   #define STR_FREE(PTR)            free(PTR)

   #define _LOOOKA_STR_IMPLEMENTATION
   #include "str.h"

   int main() {
      String *str = str_create();
      ...
   }

*/

#ifndef _LOOOKA_STR_H
#define _LOOOKA_STR_H

#include <stddef.h>

#ifndef STRDEF
#ifdef STRDEF_STATIC
#define STRDEF static
#else
#define STRDEF extern
#endif  // STRDEF_STATIC
#endif  // STRDEF

typedef struct {
    char *str;
    size_t size;
} String;

/*
Create a String with the given size
*/
STRDEF String *str_create(size_t size);

/*
Create a String from c string.

Setting cstr == NULL, is equivalent to str_create(0);
*/
STRDEF String *str_create_cstr(const char *cstr);

#endif  // header

/*

########## Implementation s##########

*/

#ifdef _LOOOKA_STR_IMPLEMENTATION

#ifndef STR_MALLOC
#include <stdlib.h>
#define STR_MALLOC(SZ) malloc(SZ)
#define STR_REALLOC(PTR, SZ) realloc(PTR, SZ)
#define STR_FREE(PTR) free(PTR)
#endif

STRDEF String *str_create(size_t size) {
    String *new_str = STR_MALLOC(sizeof(String));
    new_str->str = STR_MALLOC(sizeof(char) * size);
    new_str->size = size;
    return new_str;
}

#endif
