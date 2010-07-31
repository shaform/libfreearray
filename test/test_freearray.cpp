/**
 * IM-Tester
 *
 * A simple program to test an input method.
 */
/**
 * test.cpp
 * Copyright (c) 2010
 * 	Yong-Siang Shih (Shaform) <shaform@gmail.com>
 *
 * IM-Tester is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Im-tester is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with im-tester.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See the file "COPYING" for information on usage and redistribution
 * of this file.
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>
#include <locale.h>

extern "C" {
#include "faft.h"
}
/**
 * Define key symbol codes.
 * Basically borrowed from ibus.
 */
#define IM_TESTER_BackSpace 0xff08
#define IM_TESTER_Tab 0xff09
#define IM_TESTER_Return 0xff0d
#define IM_TESTER_Escape 0xff1b
#define IM_TESTER_Delete 0xffff

/* Modifier keys */
#define IM_TESTER_Shift_L 0xffe1
#define IM_TESTER_Shift_R 0xffe2
#define IM_TESTER_Control_L 0xffe3
#define IM_TESTER_Control_R 0xffe4
#define IM_TESTER_Alt_L 0xffe9
#define IM_TESTER_Alt_R 0xffea

/* Movement */
#define IM_TESTER_Home 0xff50
#define IM_TESTER_Left 0xff51
#define IM_TESTER_Up 0xff52
#define IM_TESTER_Right 0xff53
#define IM_TESTER_Down 0xff54
#define IM_TESTER_Page_Up 0xff55
#define IM_TESTER_Page_Down 0xff56
#define IM_TESTER_End 0xff57

/* Locks */
#define IM_TESTER_Num_Lock 0xff7f
#define IM_TESTER_Caps_Lock 0xffe5
#define IM_TESTER_Shift_Lock 0xffe6


/* Keypad */
#define IM_TESTER_KP_Space 0xff80
#define IM_TESTER_KP_Tab 0xff89
#define IM_TESTER_KP_Enter 0xff8d
#define IM_TESTER_KP_F1 0xff91
#define IM_TESTER_KP_F2 0xff92
#define IM_TESTER_KP_F3 0xff93
#define IM_TESTER_KP_F4 0xff94
#define IM_TESTER_KP_Home 0xff95
#define IM_TESTER_KP_Left 0xff96
#define IM_TESTER_KP_Up 0xff97
#define IM_TESTER_KP_Right 0xff98
#define IM_TESTER_KP_Down 0xff99
#define IM_TESTER_KP_Prior 0xff9a
#define IM_TESTER_KP_Page_Up 0xff9a
#define IM_TESTER_KP_Next 0xff9b
#define IM_TESTER_KP_Page_Down 0xff9b
#define IM_TESTER_KP_End 0xff9c
#define IM_TESTER_KP_Begin 0xff9d
#define IM_TESTER_KP_Insert 0xff9e
#define IM_TESTER_KP_Delete 0xff9f
#define IM_TESTER_KP_Equal 0xffbd
#define IM_TESTER_KP_Multiply 0xffaa
#define IM_TESTER_KP_Add 0xffab
#define IM_TESTER_KP_Separator 0xffac
#define IM_TESTER_KP_Subtract 0xffad
#define IM_TESTER_KP_Decimal 0xffae
#define IM_TESTER_KP_Divide 0xffaf
#define IM_TESTER_KP_0 0xffb0
#define IM_TESTER_KP_1 0xffb1
#define IM_TESTER_KP_2 0xffb2
#define IM_TESTER_KP_3 0xffb3
#define IM_TESTER_KP_4 0xffb4
#define IM_TESTER_KP_5 0xffb5
#define IM_TESTER_KP_6 0xffb6
#define IM_TESTER_KP_7 0xffb7
#define IM_TESTER_KP_8 0xffb8
#define IM_TESTER_KP_9 0xffb9

/* Function Keys */
#define IM_TESTER_F1 0xffbe
#define IM_TESTER_F2 0xffbf
#define IM_TESTER_F3 0xffc0
#define IM_TESTER_F4 0xffc1
#define IM_TESTER_F5 0xffc2
#define IM_TESTER_F6 0xffc3
#define IM_TESTER_F7 0xffc4
#define IM_TESTER_F8 0xffc5
#define IM_TESTER_F9 0xffc6
#define IM_TESTER_F10 0xffc7
#define IM_TESTER_F11 0xffc8
#define IM_TESTER_F12 0xffc9


/* Key Masks */
#define IM_TESTER_SHIFT_MASK	0x1
#define IM_TESTER_CONTROL_MASK	0x2
#define IM_TESTER_ALT_MASK	0x4
#define IM_TESTER_RELEASE_MASK	0x8



#define MSGB_ROW 8
#define PREEB_ROW 2


/* Windows */
WINDOW *commit_box;
WINDOW *info_box;
WINDOW *cand_box;
WINDOW *aux_box;
WINDOW *message_box;
WINDOW *preedit_box;

/* im-tester routines */
int im_tester_init(IMEngine *);
void im_tester_exit(IMEngine *);
int im_tester_get_input(unsigned int *keysym, unsigned int *keycode, unsigned int *modifiers);

void im_tester_print_aux_string(const char *);
void im_tester_print_message(const char *);
void im_tester_print_commit(const char *);

void im_tester_clear_lookup_table();
void im_tester_print_cand(const char *);

void im_tester_refresh_windows();
void im_tester_resize_windows();

/* im-tester im methods */
int im_tester_init_im(IMEngine *);
void im_tester_exit_im(IMEngine *);
void im_tester_update(IMEngine *);
void im_tester_commit(IMEngine *);
void im_tester_update_lookup_table(IMEngine *);
void im_tester_update_preedit_string(IMEngine *);
void im_tester_update_aux_string(IMEngine *);
void im_tester_update(IMEngine *);
void im_tester_refresh_info(IMEngine *);
int im_tester_process_key_event(IMEngine *engine, unsigned int keysym, unsigned int keycode, unsigned int modifiers);




int main() {
	/* Init */
	IMEngine engine;
	if(!im_tester_init(&engine))
		return 1;

	/* Get input and process it */
	unsigned int keysym, keycode, modifiers;
	while (im_tester_get_input(&keysym, &keycode, &modifiers)) {
		if (im_tester_process_key_event(&engine, keysym, 0, modifiers))
			im_tester_print_message("Key processed!\n");
		else {
			im_tester_print_message("Key passed!\n");
			if (isprint(keysym)) {
				char ci_str[] = {keysym, '\0'};
				im_tester_print_commit(ci_str);
			}
		}
		im_tester_refresh_windows();
	}

	/* Exit */
	im_tester_exit(&engine);

	return 0;
}







/* IM-Tester routines */

int im_tester_init(IMEngine *im)
{
	setlocale(LC_ALL, "");
	/* Initiate ncurses */
	initscr();
	if (has_colors()) {
		start_color();

		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		init_pair(2, COLOR_YELLOW, COLOR_BLACK);
		init_pair(3, COLOR_BLUE, COLOR_WHITE);
		init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
		init_pair(5, COLOR_WHITE, COLOR_BLACK);
	}

	raw();
	noecho();

	commit_box = newwin(0, 0, 0, 0);
	info_box = newwin(0, 0, 0, 0);
	cand_box = newwin(0, 0, 0, 0);
	aux_box = newwin(0, 0, 0, 0);
	message_box = newwin(0, 0, 0, 0);
	preedit_box = newwin(0, 0, 0, 0);

	keypad(preedit_box, TRUE);

	if (has_colors()) {
		bkgd(COLOR_PAIR(5));
		wbkgd(commit_box, COLOR_PAIR(5));
		wbkgd(info_box, COLOR_PAIR(2));
		wbkgd(cand_box, COLOR_PAIR(3));
		wbkgd(aux_box, COLOR_PAIR(3));
		wbkgd(message_box, COLOR_PAIR(1));
		wbkgd(preedit_box, COLOR_PAIR(4));
	}

	if (commit_box && info_box && cand_box && aux_box && message_box && preedit_box) {
		scrollok(message_box, TRUE);
		scrollok(commit_box, TRUE);
		im_tester_resize_windows();

		return im_tester_init_im(im);
	} else
		return 0;
}
void im_tester_resize_windows()
{
	int row, col;

	getmaxyx(stdscr, row, col);

	wresize(commit_box, row-(MSGB_ROW+PREEB_ROW+3), col);
	wresize(info_box, 1, col);
	wresize(cand_box, 1, col);
	wresize(aux_box, 1, col);
	wresize(message_box, MSGB_ROW, col);
	wresize(preedit_box, PREEB_ROW, col);

	mvwin(aux_box, row-MSGB_ROW-PREEB_ROW-3, 0);
	mvwin(cand_box, row-MSGB_ROW-PREEB_ROW-2, 0);
	mvwin(preedit_box, row-MSGB_ROW-PREEB_ROW-1, 0);
	mvwin(info_box, row-MSGB_ROW-1, 0);
	mvwin(message_box, row-MSGB_ROW, 0);

	refresh();
	im_tester_refresh_windows();
}
void im_tester_refresh_windows()
{
	wrefresh(info_box);
	wrefresh(cand_box);
	wrefresh(aux_box);
	wrefresh(message_box);
	wrefresh(commit_box);
	wrefresh(preedit_box);
}
void im_tester_exit(IMEngine *engine)
{
	delwin(commit_box);
	delwin(info_box);
	delwin(cand_box);
	delwin(aux_box);
	delwin(message_box);
	delwin(preedit_box);
	endwin();
	im_tester_exit_im(engine);
}
int im_tester_get_input(unsigned int *keysym, unsigned int *keycode, unsigned int *modifiers)
{
	im_tester_print_message("Wating for input...\n"
			"^q : quit, "
			"^o : ctrl-l, "
			"^n : ctrl-r, "
			"^e : shift-l, "
			"^t : shift-r, "
			"^u : alt-l, "
			"^h : alt-r, "

			"^d : delete, "

			"^f : pagedown, "
			"^b : pageup, "
			//"^k : numpad, "


			"^s : shift-mask, "
			"^c : ctrl-mask, "
			"^a : alt-mask.\n"
			);

	int ch;
	int shift_mask = 0, ctrl_mask = 0, alt_mask = 0;
	*keysym = 0;
	while (!(*keysym)) {

		if (shift_mask || ctrl_mask || alt_mask) {
			im_tester_print_message("Mask:");
			if (shift_mask)
				im_tester_print_message(" shift,");
			if (ctrl_mask)
				im_tester_print_message(" ctrl,");
			if (alt_mask)
				im_tester_print_message(" alt");

			im_tester_print_message("\n");
		}
		while (!(*keysym)) {
			ch = wgetch(preedit_box);

			switch (ch) {
				case KEY_RESIZE:
					im_tester_resize_windows();
					continue;
					break;

				case '':
					*keysym = IM_TESTER_Control_L;
					break;
				case '':
					*keysym = IM_TESTER_Control_R;
					break;
				case '':
					*keysym = IM_TESTER_Shift_L;
					break;
				case '':
					*keysym = IM_TESTER_Shift_R;
					break;
				case '':
					*keysym = IM_TESTER_Alt_L;
					break;
				case '':
					*keysym = IM_TESTER_Alt_R;
					break;
				case KEY_BACKSPACE:
					*keysym = IM_TESTER_BackSpace;
					break;
				case '':
					*keysym = IM_TESTER_Escape;
					break;
				case '':
					*keysym = IM_TESTER_Delete;
					break;

				case '':
					*keysym = IM_TESTER_Page_Up;
					break;
				case '':
					*keysym = IM_TESTER_Page_Down;
					break;



				case KEY_HOME:
					*keysym = IM_TESTER_Home;
					break;
				case KEY_LEFT:
					*keysym = IM_TESTER_Left;
					break;
				case KEY_UP:
					*keysym = IM_TESTER_Up;
					break;
				case KEY_RIGHT:
					*keysym = IM_TESTER_Right;
					break;
				case KEY_DOWN:
					*keysym = IM_TESTER_Down;
					break;
				case KEY_END:
					*keysym = IM_TESTER_End;

				case '\t':
					*keysym = IM_TESTER_Tab;
					break;
				case '\n':
					*keysym = IM_TESTER_Return;
					break;

					/* Masks: */
				case '':
					shift_mask = !shift_mask;
					break;
				case '':
					ctrl_mask = !ctrl_mask;
					break;
				case '':
					alt_mask = !alt_mask;
					break;
				case '':
					*keysym = '';
					break;
				default:
					if (isprint(ch)) {
						*keysym = ch;
						break;
					} else
						continue;

			}
			break;
		}

	}

	if (*keysym == '')
		return 0;

	*modifiers = 0u;
	if (shift_mask)
		*modifiers |= IM_TESTER_SHIFT_MASK;
	if (ctrl_mask)
		*modifiers |= IM_TESTER_CONTROL_MASK;
	if (alt_mask)
		*modifiers |= IM_TESTER_ALT_MASK;


	return 1;
}
void im_tester_print_aux_string(const char *str)
{
	mvwaddstr(aux_box, 0, 0, str);
	wrefresh(aux_box);
}
void im_tester_print_message(const char *msg)
{
	waddstr(message_box, msg);
	wrefresh(message_box);
}
void im_tester_print_commit(const char *ci)
{
	waddstr(commit_box, ci);
	wrefresh(commit_box);
}












/* IM-Tester IM methods */
int im_tester_init_im(IMEngine *im)
{
	if (im->context) {

		/* Default Settings */

		im_tester_refresh_info(im);
		return 1;
	} else
		return 0;
}
void im_tester_exit_im(IMEngine *engine)
{
}
void im_tester_refresh_info(IMEngine *engine)
{
	FAFTContext *context = engine->context;

	char shape[5], variety[4];

	if (faft_context_get_shape(context) == FAFT_SHAPE_FULL)
		strcpy(shape, "Full");
	else
		strcpy(shape, "Half");

	if (faft_context_get_variety(context) == FAFT_VARIETY_ENG)
		strcpy(variety, "Eng");
	else
		strcpy(variety, "Chi");

	mvwprintw(info_box, 0, 0, "Variety: %s, Shape: %s\n", variety, shape);
	wrefresh(info_box);
}

void im_tester_update(IMEngine *engine)
{
	im_tester_update_lookup_table(engine);
	im_tester_update_preedit_string(engine);
	im_tester_commit(engine);
}
void im_tester_update_lookup_table(IMEngine *engine)
{
	FAFTContext *ctx = engine->context;

	wclear(cand_box);

	int i=0;
	char *candidate = NULL;

	int page_size = 0;
	if (faft_context_is_lookup_table_shown(ctx)) {
		page_size = faft_context_cand_page_size(ctx);
		faft_context_cand_enumerate(ctx);

		for(i=0; i < page_size; i++) {
			if (faft_context_cand_has_next(ctx)) {
				candidate = faft_context_cand_string(ctx);
				wprintw(cand_box, "%d: %s ", i+1, candidate);
				free(candidate);
			} else
				break;
		}

	} else if (faft_context_is_quick_input_updated(ctx)) {
		page_size = faft_context_quick_input_size(ctx);

		faft_context_quick_input_enumerate(ctx);
		for(i=0; i < page_size; i++) {
			if (faft_context_quick_input_has_next(ctx)) {
				candidate = faft_context_get_quick_input_string(ctx);
				wprintw(cand_box, "%d: %s ", i+1, candidate);
				free(candidate);
			} else
				break;
		}

	}
	faft_context_unset_lookup_table_updated(ctx);
	faft_context_unset_quick_input_updated(ctx);
	wrefresh(cand_box);
}
void im_tester_update_preedit_string(IMEngine *engine)
{
	char *buff_str = faft_context_get_buffer_string(engine->context);
	wclear(preedit_box);
	waddstr(preedit_box, buff_str);
	free(buff_str);

	FAFTKeyCode kc_buff[ARRAYCODE_MAX_LEN + 1];
	faft_acdata_get_unfinished(&(engine->context->data->acData), kc_buff);
	char *kc_str = keystostr(kc_buff);
	mvwaddstr(preedit_box, 1, 0, kc_str);
	free(kc_str);

	wrefresh(preedit_box);
}
void im_tester_commit(IMEngine *engine)
{
	FAFTContext *ctx = engine->context;

	if (faft_context_is_commit_string_updated(ctx)) {

		char *commit_string = faft_context_get_commit_string(ctx);
		if (commit_string && commit_string[0]) {
			im_tester_print_commit(commit_string);
			free(commit_string);
		}

		faft_context_unset_commit_string_updated(ctx);
	}
}

int im_tester_process_key_event(IMEngine *engine, unsigned int keysym, unsigned int keycode, unsigned int modifiers)
{
	/* Data */


	/* Ignore all release events */
	if (modifiers & IM_TESTER_RELEASE_MASK)
		return 0;




	unsigned keymask = modifiers & (IM_TESTER_SHIFT_MASK | IM_TESTER_CONTROL_MASK);

	/* A new key_event has happened */

	if (keymask == 0) {
		switch (keysym){
			case IM_TESTER_Return:
			case IM_TESTER_KP_Enter:
				break;
			case IM_TESTER_Escape:
				break;
			case IM_TESTER_BackSpace:
				break;
			case IM_TESTER_Delete:
			case IM_TESTER_KP_Delete:
				break;
			case ' ':
				break;
			case IM_TESTER_Page_Up: case IM_TESTER_KP_Page_Up:
				break;
			case IM_TESTER_Page_Down: case IM_TESTER_KP_Page_Down:
				break;

			case IM_TESTER_Left: case IM_TESTER_KP_Left:
				break;

			case IM_TESTER_Right: case IM_TESTER_KP_Right:
				break;



			case IM_TESTER_Up:
			case IM_TESTER_KP_Up:
				break;
			case IM_TESTER_Down:
			case IM_TESTER_KP_Down:
				break;
			case IM_TESTER_Home:
			case IM_TESTER_KP_Home:
				break;
			case IM_TESTER_End:
			case IM_TESTER_KP_End:
				break;
			case IM_TESTER_Tab:
			case IM_TESTER_KP_Tab:
				break;
			default:
				break;
		}
	} else if (keymask == IM_TESTER_SHIFT_MASK) {
		switch(keysym) {

			case ' ':
				break;
			case IM_TESTER_Return:
				break;
			default:
		}
	}

	im_tester_update();

	return 1;
}
