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
#include "code.h"
#include "tables.h"
#include "imengine_component.h"

namespace freearray {
	class FreeArrayIM;

	/* This should be a state */
	class FreeArrayIM::Variety {
		private:
			friend class FreeArrayIM;

			Variety(const std::string &ln, const std::string &sn) : data(new Data(ln, sn)) {}

		public:
			Variety() : data(0) {}
			Variety(const Variety &rhs) : data(rhs.data) { incr_use(); }
			~Variety() { decr_use(); }


			const std::string get_long_name() const
			{
				return data==0 ? std::string() : data->long_name;
			}
			const std::string get_short_name() const
			{
				return data==0 ? std::string() : data->short_name;
			}


			Variety &operator=(const Variety &rhs)
			{
				if (&rhs != this) {
					decr_use();
					data = rhs.data;
					incr_use();
				}
				return *this;
			}
			bool operator==(const Variety &rhs) const
			{
				return rhs.data == data;
			}
			bool operator!=(const Variety &rhs) const
			{
				return rhs.data != data;
			}


		private:

			void decr_use();
			void incr_use();

			class Data;

			Data *data;
	};

	class FreeArrayIM::Variety::Data {
		friend class Variety;

		int count;
		std::string long_name;
		std::string short_name;
		Data(const std::string &ln, const std::string &sn) : long_name(ln), short_name(sn), count(1) {}
	};

	inline void FreeArrayIM::Variety::decr_use()
	{
		if (data && --data->count == 0)
			delete data;
	}
	inline void FreeArrayIM::Variety::incr_use()
	{
		if (data) ++data->count;
	}

	








	/**
	 * Main FreeArray IM class
	 *
	 */
	class FreeArrayIM {
		public:
			size_t get_max_ac_size();
			class Variety;
			enum {
				EVENT_ACCEPTED,
				EVENT_IGNORED,
				EVENT_PASSED,
			};


		public:
			// Input
			//int input_sign(char);
			int input_key(KeyCode);
			int input_key(char);

			// Commit
			/*
			int commit_char();
			int commit_array_sign();
			int commit_phrase();

			int commit_buffer();
			int commit_all();

			int commit_short(int);
			*/

			// Character Buffer
			/*
			int cursor_up();
			int cursor_down();
			int cursor_front();
			int cursor_end();
			int cursor_remove();
			*/

			//void clear_buffer();
			void clear_keys();
			void pop_key();
			void clear_aux();
			//void clear();
			//void reset();

			/*
			bool cursor_lookup();

			symbol_table();
			break_point();
			*/


			// Getter
			/*
			bool get_buffer(std::string &);
			bool get_buffer(std::vector<std::string> &);

			bool get_commit(std::string &);
			bool get_commit(std::vector<std::string> &);

			bool get_auxiliary(std::string &);
			bool get_auxiliary(std::vector<std::string> &);


			LookupTable get_cands();
			get_();
			*/



			/* Setter */
			/*
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


			*/

			/* Attributes */

			/*
			shape toggle_shape();
			shape get_shape();
			*/

			const Variety set_variety(Variety = Variety());
			const Variety get_variety() const { return v_current; }

			const Variety get_eng_variety() const { return v_eng; }
			const Variety get_tc_variety() const { return v_tc; }
			const Variety get_sc_variety() const { return v_sc; }

			/*
			kbtype toggel_kbtype();
			kbtype get_kbtype();
			*/

			bool set_auto_clear_mode(bool = !m_auto_clear);
			bool set_auto_input_mode(bool = !m_auto_input);
			bool set_back_choose_mode(bool = !m_back_choose);
			bool set_pre_input_mode(bool = !pre_input);
			bool set_short_mode(bool = !m_short);
			bool set_phrase_mode(bool = !m_phrase);
			bool set_array_sign_mode(bool = !m_array_sign);
			bool set_easy_symbol_mode(bool = !m_easy_symbol);



			bool is_key_buffer_full() { return kcb.is_full(); }
			bool is_key_buffer_empty() { return kcb.is_empty(); }

			/*
			   int buffer_size() const;
			   int buffer_capacity() const;
			   int keycode_buffer_size() const;
			   int keycode_buffer_capacity() const;

			   void reset();
			 */

		public:
			FreeArrayIM()
				: v_eng("English","EN"), v_tc("Traditional Chinese", "TC"), v_sc("Simplified Chinese", "SC")
			{}
			~FreeArrayIM();

		private:
			// implementation
			

			/* ArrayCode, KeyCodes, KeyCode string */
			KeyCodeBuffer key_buffer;
			CharBuffer char_buffer;

			/* Auxiliary string */
			std::string aux;


			/* For Phrasing & Lookup */

		private:

			/* Varieties */
			const Variety v_eng, v_tc, v_sc;

			/* Settings */
			bool m_auto_clear;
			bool m_auto_input;
			bool m_back_choose;
			bool m_pre_input;
			bool m_short;
			bool m_phrase;
			bool m_array_sign;
			bool m_easy_symbol;


			/* States */
			bool s_lookup;
			bool s_;
	};


	inline void FreeArrayIM::clear_keys()
	{
		key_buffer.clear();
	}
	inline void FreeArrayIM::pop_key()
	{
		key_buffer.pop();
	}
	inline void FreeArrayIM::clear_aux()
	{
		aux.clear();
	}
	inline bool set_auto_clear_mode(bool m)
	{
		return m_auto_clear = m;
	}
	inline bool set_auto_input_mode(bool m)
	{
		return m_auto_input = m;
	}
	inline bool set_back_choose_mode(bool m)
	{
		return m_auto_back_choose = m;
	}
	inline bool set_pre_input_mode(bool m)
	{
		return m_pre_input = m;
	}
	inline bool set_short_mode(bool m)
	{
		return m_short = m;
	}
	inline bool set_phrase_mode(bool m)
	{
		return m_phrase = m;
	}
	inline bool set_array_sign_mode(bool m)
	{
		return m_array_sign = m;
	}
	inline bool set_easy_symbol_mode(bool m)
	{
		return m_easy_symbol = m;
	}

	extern FreeArrayIM freearray_im;
}

#endif
