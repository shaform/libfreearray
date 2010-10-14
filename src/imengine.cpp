/** 
 * @file imengine.cpp
 * @brief A generic IMEngine instance.
 *
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

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "kbtype.h"
#include "code.h"
#include "imengine.h"

#define MAX_UTF8_SIZE 6


using std::string;
using std::vector;
typedef union {
	unsigned char s[ MAX_UTF8_SIZE + 1];
	wchar_t wch;
} wch_t;

enum {
	HALF_SIGN,
	FULL_SIGN,
	TC_CHAR,
	TC_SIGN,
	SC_CHAR,
	SC_SIGN
};
namespace {

}

namespace freearray {

#if 0
	class PhrasingModule {
		IntervalString is[];
		Interval its[];
	};
#endif
	FreeArrayIM::~FreeArrayIM()
	{
	}

	int FreeArrayIM::input_key(KeyCode key)
	{
		// All varieties: ENG/TC/SC/UC
		if (get_variety() == get_eng_variety() || is_lookup_table_shown() || !is_key_valid(key))
			return IGNORED;

		if (is_key_buffer_full() && is_auto_clear_mode() && is_key_error())
			clear_keys();

		if (is_key_buffer_full() && is_auto_input_mode())
			commit_char();

		if (is_key_buffer_full())
			return IGNORED;

		key_buffer.push_back(key);

		set_key_updated();

		return ACCEPTED;
	}


#if 0
	void FreeArrayIM::call_phrasing()
	{
		break_points = user_break_points;
		/* then phrasing */
		Phrasing( 
				&( pgdata->phrOut ), pgdata->phoneSeq, pgdata->nPhoneSeq,
				pgdata->selectStr, pgdata->selectInterval, pgdata->nSelect, 
				pgdata->bArrBrkpt, pgdata->bUserArrCnnct );

		/* and then make prefer interval */
		MakePreferInterval( pgdata );
	}
#endif



	int FreeArrayIM::commit_char()
	{
		// return get_variety()->commit_char();

		if (get_variety() == get_eng_variety() || is_lookup_table_shown() || get_key_size() == 0)
			return IGNORED;


		ArrayCode code = key_buffer.get_code();

		if (dtchar.query(code)) {
			key_buffer.clear();

			char_buffer.insert(code);
			cursor_down();

			//			call_phrasing();

			return ACCEPTED;
		} else {
			/* The KeyCode sequence cannot match any characters */
			if (is_key_error() && is_auto_clear_mode()) {
				clear_keys();
			}

			set_key_error();
			return IGNORED;
		}

	}
#if 0
	int FreeArrayIM::commit_symbol(int keysym)
	{
		/* Skip special keys */
		if (keysym & 0xFF00)
			return IGNORED;

	}
#endif

#if 0
	const string &FreeArrayIM::get_buffer_string()
	{
		return get_buffer().get_string();
	}
	const vector<string> &FreeArrayIM::get_buffer_vector()
	{
		return get_buffer().get_vector();
	}
#endif

	FreeArrayIM freearray_im;
}
