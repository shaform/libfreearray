/** 
 * @file frontend.h
 * @brief Keyboard Interface
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
#ifndef FREEARRAY_FRONTEND_H
#define FREEARRAY_FRONTEND_H
namespace freearray {
	/* FreeArrayKeyboardInterface */
	class KeyboardInterface {
			virtual int handle_shift(char) = 0;
			virtual int handle_ctrl(char) = 0;
			virtual int handle_numlock() = 0;
			virtual int handle_capslock() = 0;
			virtual int handle_end() = 0;
			virtual int handle_home() = 0;
			virtual int handle_pagedown() = 0;
			virtual int handle_pageup() = 0;
			virtual int handle_default(char) = 0;
			virtual int handle_space() = 0;
			virtual int handle_tab() = 0;
			virtual int handle_esc() = 0;
			virtual int handle_enter() = 0;
			virtual int handle_delete() = 0;
			virtual int handle_backspace() = 0;
			virtual int handle_tab() = 0;
			virtual int handle_shiftleft() = 0;
			virtual int handle_shiftright() = 0;
			virtual int handle_left() = 0;
			virtual int handle_right() = 0;
			virtual int handle_up() = 0;
			virtual int handle_down() = 0;
	};

	// State type for the FreeArrayFrontEnd
	// Any implentation could inherit this type to define its own behavour of the frontend 
	class FrontEndState : public KeyboardInterface {
		public:
			virtual int handle_shift(char);
			virtual int handle_ctrl(char);
			virtual int handle_numlock();
			virtual int handle_capslock();
			virtual int handle_end();
			virtual int handle_home();
			virtual int handle_pagedown();
			virtual int handle_pageup();
			virtual int handle_default(char);
			virtual int handle_space();
			virtual int handle_tab();
			virtual int handle_esc();
			virtual int handle_enter();
			virtual int handle_delete();
			virtual int handle_backspace();
			virtual int handle_tab();
			virtual int handle_shiftleft();
			virtual int handle_shiftright();
			virtual int handle_left();
			virtual int handle_right();
			virtual int handle_up();
			virtual int handle_down();
			virtual int handle_space();
		protected:
			FrontEndState(FreeArrayFrontEnd &);

			FreeArrayFrontEnd &instance;
	};

	/* An adapter transforming keyboard input to FreeArray Instance */
	// It only contains interface, all implemtation should goes elsewhere
	class FreeArrayFrontEnd : public FreeArrayKeyboardInterface {
		public:
			FreeArrayFrontEnd(freearray::FreeArrayInstance &in, FrontEndState *s);

			/* Keyboard interface */

			int handle_shift(char );
			int handle_ctrl(char );
			int handle_numlock();
			int handle_capslock();
			int handle_end();
			int handle_home();
			int handle_pagedown();
			int handle_pageup();
			int handle_default(char);
			int handle_default(char);
			int handle_space();
			int handle_tab();
			int handle_esc();
			int handle_enter();
			int handle_delete();
			int handle_backspace();
			int handle_tab();
			int handle_shiftleft();
			int handle_shiftright();
			int handle_left();
			int handle_right();
			int handle_up();
			int handle_down();


			/* Helper methods */

			/* settings */

			int set_attritube(freearray::KbType);
			int set_attritube(freearray::Shape);
			int set_attritube(freearray::Variety);


			/* gets */

			string get_preedit_string();
			string get_buffer_string();
			string get_cand_string_first();
			string get_cand_string_next();

			int get_cursor_pos();

			int get_cand_total();
			int get_cand_per_page();



			/* register */
			bool register_commit(void (*f)());
			bool register_signtable(void (*f)());
			bool register_phrase(void (*f)());
			bool register_(void (*f)());
			bool register_commit(void (*f)());

		protected:
			class FreeArrayFrontEndImpl;
			FreeArrayInstance *freearray;
			FrontEndState *state;
			FreeArrayFrontEndImpl *impl;
	};
};
#endif
