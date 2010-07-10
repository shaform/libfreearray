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

#include "code.h"

namespace freearray {
	struct Word {
		int type;

		wch_t ch;

		char c_code;
		ArrayCode a_code;
	};



	Variety;
	Factory;
	PhrasingModule;

	class KeyCodeBuffer
	{
		public:
			explicit KeyCodeBuffer(int size = ARRAYCODE_MAX_LEN) : max_len(size) {}

			void push_back(KeyCode key) { if (!is_full()) buffer.push_back(key); }

			void clear() { buffer.clear(); }
			void pop() { buffer.pop_back(); }

			bool is_full() { return buffer.size() >= max_len; }
			bool is_empty() { return buffer.empty(); }
			bool get_length() { return buffer.size(); }

			ArrayCode get_code() { return keytocode(buffer); }
			Keycode &get_key(int n) { return buffer.at(n); }
			KeyCode &back() { return buffer.back(); }


			KeyCode &operator[](int n) { return buffer[n]; }


		private:
			vector<KeyCode> buffer;
			const int max_len;
	};

	class PhrasedCharBuffer
	{
	};

	class CharBuffer
	{
		public:
			unsigned char buffer;


			void set_max_length(size_t);


			std::string get_string(size_t);
			std::string get_string(size_t, size_t);
			std::string get_string();


			std::string get_vector(size_t);
			std::string get_vector(size_t, size_t);
			std::string get_vector();

			erase(size_t);
			erase(size_t, size_t);
			void clear();

			bool is_full();
			bool is_overflowed();

		private:
			size_t cursor;
	};

	class LookupTable
	{
		public:
			LookupTable (int page_size = 10);
			void set_candidate_labels (const std::vector<WideString> &labels);
			WideString get_candidate_label (int page_index) const;
			void set_page_size (int page_size); 
			int get_page_size () const;
			int get_current_page_size () const;
			int get_current_page_start () const;
			bool is_page_size_fixed () const;
			int get_cursor_pos () const;
			int get_cursor_pos_in_current_page () const;
			bool page_up ();
			bool page_down ();
			bool cursor_up ();
			bool cursor_down ();
			void set_cursor_pos (int pos);
			void set_cursor_pos_in_current_page (int pos);
			WideString get_candidate_in_current_page (int page_index) const;

		public:
			virtual WideString get_candidate (int index) const = 0;
			virtual uint32 number_of_candidates () const = 0;
			virtual void clear () = 0;
	};

	class LookUpTable {
		public:
			typedef size_t size_type;
			typedef;


			// Page mover
			bool next();
			bool prev();

			// Iterators
			iterator begin();
			iterator end();
			iterator page_begin();
			iterator page_end();

			// Information
			size_type get_page_size();
			size_type get_page_number();
			size_type get_page();
			size_type get_max_page_size();
			size_type get_total_size();
	};
	class WordBuffer {
		public:
			iterator;
			size_t size() { return buffer.size() }

			vector<string> get_vector();
			string get_string();

			/*
			   size_t get_cursor();
			   cursor_up();
			   cursor_down();
			 */
		private:
			vector<Word> buffer;
	};

	string WordBuffer::get_string()
	{
		string s;
		for (vector<Word>::iterator it = buffer.begin(); it != buffer.end(); ++it)
			s += reinterpret_cast<char *>(it->ch.s);

		return s;
	}

	vector<string> WordBuffer::get_vector()
	{
		vector<string> vec_s;

		for (vector<Word>::iterator it = buffer.begin(); it != buffer.end(); ++it)
			vec_s.push_back(reinterpret_cast<char *>(it->ch.s));

		return vec_s;
	}
}
