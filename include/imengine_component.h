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
#include <cstring>
#include <vector>
#include <string>
#define MAX_UTF8_SIZE 6

namespace freearray {

	union wch_t {
		char str[MAX_UTF8_SIZE + 1];
		wchar_t wch;
		wch_t() {}
		wch_t(const char s[]) { std::strcpy(str, s); }
		wch_t(wchar_t w) : wch(w) {}
	};

#if 0
	Variety;
	Factory;
	PhrasingModule;
#endif

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
			std::string get_string() { return keytostr(buffer); }
			KeyCode &get_key(int n) { return buffer.at(n); }
			KeyCode &back() { return buffer.back(); }


			KeyCode &operator[](int n) { return buffer[n]; }


		private:
			std::vector<KeyCode> buffer;
			const int max_len;
	};

	class PhrasedCharBuffer
	{
	};





	class CharBuffer
	{
		public:
			typedef size_t Iterator;
			typedef int CharType;
#if 0
			class Iterator {
				public:
					operator++
						operator++
						operator--
						operator--
						operator-=
						operator+=
						operator int() { return pos; }
				private:
					int pos;
			};
#endif
		public:
			CharBuffer();
		public:

#if 0
			AvailInfo availInfo;
			ChoiceInfo choiceInfo;
			PhrasingOutput phrOut;

			char selectStr[ MAX_PHONE_SEQ_LEN ][ MAX_PHONE_SEQ_LEN * MAX_UTF8_SIZE + 1 ];
			IntervalType selectInterval[ MAX_PHONE_SEQ_LEN ];

			IntervalType preferInterval[ MAX_INTERVAL ]; /* add connect points */
#endif

			/* store chars */
			std::vector<wch_t> buffer;
			/* store ArrayCodes */
			std::vector<ArrayCode> code_buffer;
			/* store output */
			std::vector<std::string> output_buffer;
			/* char keys */
			std::vector<char> ckey_buffer;


			/* phrasing breakpoints */
			std::vector<bool> break_points;
			/* user breakpoint */
			std::vector<bool> user_break_points;
			/* user connectpoints */
			std::vector<bool> user_connect_points;

			/* for use in phrasing / etc */
			std::vector<int> type_buffer;
			/* for output display */
			std::string bytestring;

			//void insert(wch_t, int pos);
			//void insert(ArrayCode, int pos);
			void set_max_length(size_t);

			const std::string get_string(Iterator) const;
			const std::string get_string(Iterator, Iterator) const;
			const std::string get_string() const;

			const std::string get_vector(Iterator) const;
			const std::string get_vector(Iterator, Iterator) const;
			const std::string get_vector() const;

			void erase(Iterator);
			void erase(Iterator, Iterator);
			void clear();

			bool is_full() const;
			bool is_overflowed() const;
		public:

			void insert(char ckey, wch_t sym = wch_t());

			void insert(ArrayCode code, wch_t sym = wch_t());

			void insert(CharType type, char ckey, wch_t sym = wch_t());

			void insert(CharType type, ArrayCode code, wch_t sym = wch_t());


			void insert(Iterator pos, char ckey, wch_t sym = wch_t());

			void insert(Iterator pos, ArrayCode code, wch_t sym = wch_t());

			void insert(Iterator pos, CharType type, char ckey, wch_t sym = wch_t());

			void insert(Iterator pos, CharType type, ArrayCode code, wch_t sym = wch_t());




			void insert(Iterator pos, CharType type, ArrayCode code, char ckey, wch_t sym = wch_t());
		public:
			Iterator current() { return cursor; }
			Iterator begin() { return Iterator(0); }
			Iterator end() { return Iterator(buffer.size()); }

			Iterator forward() { return ++cursor; }
			Iterator backward() { return --cursor; }
			Iterator seek(Iterator it) { return cursor = it; }
		private:
			Iterator cursor;
	};

	inline void CharBuffer::insert(char ckey, wch_t sym)
	{
		insert(current(), ckey, sym);
	}
	inline void CharBuffer::insert(ArrayCode code, wch_t sym)
	{
		insert(current(), code, sym);
	}
	inline void CharBuffer::insert(CharType type, char ckey, wch_t sym)
	{
		insert(current(), type, ckey, sym);
	}
	inline void CharBuffer::insert(CharType type, ArrayCode code, wch_t sym)
	{
		insert(current(), type, code, sym);
	}
	inline void CharBuffer::insert(Iterator pos, char ckey, wch_t sym)
	{
		insert(pos, 0, 0, ckey, sym);
	}
	inline void CharBuffer::insert(Iterator pos, ArrayCode code, wch_t sym)
	{
		insert(pos, 0, code, 0, sym);
	}
	inline void CharBuffer::insert(Iterator pos, CharType type, char ckey, wch_t sym)
	{
		insert(pos, type, 0, ckey, sym);
	}
	inline void CharBuffer::insert(Iterator pos, CharType type, ArrayCode code, wch_t sym)
	{
		insert(pos, type, code, 0, sym);
	}

	class LookUpTable {
		public:
			typedef size_t size_type;
			typedef size_t iterator;

			LookUpTable(size_t page_size = 10);

			bool choice_up();
			bool choice_down();

			bool page_up();
			bool page_down();

			bool cursor_up();
			bool cursor_down();

			// Iterators
			iterator begin();
			iterator end();
			iterator page_begin();
			iterator page_end();

			// Information
			size_type get_total_choice();
			size_type get_total_page();
			size_type get_total_cursor();

			size_type get_choice();
			size_type get_page();
			size_type get_cursor();

			size_type get_total_size();

			// Others
			void clear();
			void select();
			// Setter
			void set_page_size();
	};
}
