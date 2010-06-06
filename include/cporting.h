/** 
 * @file cporting.h
 * @brief C porting layer for libfreearray
 */

/**
 * FreeArray Input Method Library
 * 
 * Copyright (c) 2010
 * 	Yong-Siang Shih (Shaform) <shaform@gmail.com>
 *
 * FreeArray is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeArray is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeArray.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See the file "COPYING" for information on usage and redistribution
 * of this file.
 */
#ifndef FREEARRAY_CPROTING_H
#define FREEARRAY_CPROTING_H

#ifdef __cplusplus
extern "C" {
#endif 

/*
enum FREEARRAY_KBTYPE {};
enum FREEARRAY_SHAPE {};
enum FREEARRAY_VARIRITY {};
struct FreeArrayLink {
	int link_id;
};
int array_instances[id];
FreeArrayLink *get_freearray_link();
*/


/* process key events */

int freearray_handle_up(FreeArrayContext *ctx);
int freearray_handle_down(FreeArrayContext *ctx);
int freearray_handle_left(FreeArrayContext *ctx);
int freearray_handle_right(FreeArrayContext *ctx);

int freearray_handle_home(FreeArrayContext *ctx);
int freearray_handle_end(FreeArrayContext *ctx);

int freearray_handle_page_up(FreeArrayContext *ctx);
int freearray_handle_page_down(FreeArrayContext *ctx);

int freearray_handle_space(FreeArrayContext *ctx);
int freearray_handle_enter(FreeArrayContext *ctx);

int freearray_handle_esc(FreeArrayContext *ctx);
int freearray_handle_del(FreeArrayContext *ctx);
int freearray_handle_backspace(FreeArrayContext *ctx);

int freearray_handle_tab(FreeArrayContext *ctx);
int freearray_handle_capslock(FreeArrayContext *ctx);
int freearray_handle_shift_left(FreeArrayContext *ctx);
int freearray_handle_shift_right(FreeArrayContext *ctx);
int freearray_handle_shiftspace(FreeArrayContext *ctx);

int freearray_handle_default(FreeArrayContext *ctx, int key);
int freearray_handle_numlok(FreeArrayContext *ctx, int key);

/* FreeArray context management */

int freearray_init();
void freearray_terminate();

FreeArrayContext *freearray_new();
void freearray_delete(FreeArrayContext *ctx);
int freearray_reset(FreeArrayContext *ctx);

void freearray_free(void *);


int freearray_set_kbtype(FreeArrayContext *ctx, int kbtype);
int freearray_get_kbtype(FreeArrayContext *ctx);

char *freearray_get_kbtring(FreeArrayContext *ctx);
int freearray_kbstring_to_type(const char str[]);

void freearray_set_variety(FreeArrayContext *ctx, int mode);
int freearray_get_variety(FreeArrayContext *ctx);

void freearray_set_shape(FreeArrayContext *ctx, int mode);
int freearray_get_shape(FreeArrayContext *ctx);

void freearray_set_candPerPage(FreeArrayContext *ctx, int n);
int freearray_get_candPerPage(FreeArrayContext *ctx);

void freearray_set_max_buffer_size(FreeArrayContext *ctx, int n);
int freearray_get_max_buffer_size(FreeArrayContext *ctx);

/*
uint16 *freearray_get_keycodes(FreeArrayContext *ctx);
int freearray_get_keycode_length(FreeArrayContext *ctx);
*/

char *freearray_get_commit_string(FreeArrayContext *ctx);

char *freearray_get_buffer_string(FreeArrayContext *ctx);
int freearray_get_buffer_length(FreeArrayContext *ctx);

int freearray_get_cursor(FreeArrayContext *ctx);


#ifdef __cplusplus
}
#endif 

#endif
