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
#ifndef FREEARRAY_IMENGINE_H
#define FREEARRAY_IMENGINE_H

#include <string>
#include <vector>
#include <typeinfo>
#include "code.h"
#include "tables.h"

namespace freearray {
	class FreeArrayIM {
		public:
			static const unsigned int max_ac_size = ARRAYCODE_MAX_LEN;
			enum Variety {ENG, TC, SC};
			typedef KbType * kbtype;
			typedef Variety variety;


		public:
			// Input
			int input_sign(char);
			int input_keycode(KeyCode);
			int input_keycode(char);

			// Commit
			int commit_char();
			int commit_array_sign();
			int commit_phrase();
			int commit_buffer();
			commit_short();

			// Character Buffer
			int cursor_up();
			int cursor_down();
			int cursor_front();
			int cursor_end();
			int cursor_remove();
			int cursor_backremove();
			void clear_buffer();
			void clear_keycodes();
			void pop_back_keycode();
			void clear_aux();
			void clear();
			void reset();

			bool cursor_lookup();

			symbol_table();
			break_point();


			// Getter
			bool get_buffer(std::string &);
			bool get_buffer(std::vector<std::string> &);

			bool get_commit(std::string &);
			bool get_commit(std::vector<std::string> &);

			bool get_auxiliary(std::string &);
			bool get_auxiliary(std::vector<std::string> &);


			LookupTable get_cands();
			get_();



			/* Setter */
			void set_kbtype(kbtype);
			void set_array_sign_input();
			void set_array_easy_sign_input();
			void set_auto_clear_mode();


int faft_context_end_lookup_table(FAFTContext *);
int faft_context_show_lookup_table(FAFTContext *);

int faft_context_first_avail(FAFTContext *);
int faft_context_last_avail(FAFTContext *);
int faft_context_prev_avail(FAFTContext *);
int faft_context_next_avail(FAFTContext *);

int faft_context_first_page(FAFTContext *);
int faft_context_last_page(FAFTContext *);
int faft_context_prev_page(FAFTContext *);
int faft_context_next_page(FAFTContext *);

int faft_context_select_cand(FAFTContext *, int nth);
int faft_context_any_row_select(FAFTContext *, int keysym);
			


			/* Attributes */

			shape toggle_shape();
			shape get_shape();

			variety toggle_variety();
			variety get_variety();

			kbtype toggel_kbtype();
			kbtype get_kbtype();



			/*
			int buffer_size() const;
			int buffer_capacity() const;
			int keycode_buffer_size() const;
			int keycode_buffer_capacity() const;

			void reset();
			*/
		public:
			variety get_eng_variety();
			variety get_tc_variety();
			variety get_sc_variety();

		public:
			FreeArrayIM();
			~FreeArrayIM();

		private:
			class Impl;
			Impl &impl;



		private:
			/* Settings */
			bool m_auto_clear;
			bool m_auto_input;
			bool m_back_choose;
			bool m_pre_input;
			bool m_short;
			bool m_phrase;
			bool m_array_sign;
			bool m_easy_symbol;
	};
	
	extern FreeArrayIM freearray_im;
}

#endif
