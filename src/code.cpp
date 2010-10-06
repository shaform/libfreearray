/** 
 * @file code.cpp
 * @brief Defines the KeyCode & ArrayCode
 */

/**
 * FreeArray Input Method Library
 * 
 * Copyright (c) 2007-2010
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

#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include "code.h"

using namespace freearray;
using std::string;
using std::vector;

namespace {
	const ArrayCode ARRAYCODE_MASK[5] = {63u << 24, 63u << 18, 63u << 12, 63u << 6, 63u};
}

namespace freearray {


	KeyCode get_key(ArrayCode code, int pos)
	{
		return (code & ARRAYCODE_MASK[pos]) >> 6*(ARRAYCODE_MAX_LEN - pos - 1);
	}


	ArrayCode set_key(ArrayCode code, KeyCode key, int pos)
	{
		code &= (~ARRAYCODE_MASK[pos]);
		return code | ((key << 6*(ARRAYCODE_MAX_LEN - pos - 1)) & ARRAYCODE_MASK[pos]);
	}


	bool is_code_valid(ArrayCode code)
	{
		KeyCode key = 0u;
		size_t i;

		// Check if all KeyCodes are valid and the ArrayCode is ended with a KEYCODE_END.
		for (i = 0; i < ARRAYCODE_MAX_LEN; ++i) {

			key = get_key(code, i);

			if (!is_key_valid(key))
				if (is_key_end(key))
					break;
				else
					return false;
		}


		// Check if all remaining KeyCodes are KEYCODE_ENDs.
		for (; i < ARRAYCODE_MAX_LEN; ++i)
			if (!is_key_end(get_key(code, i)))
				return false;

		// Return true if all tests were passed.
		return true;
	}


	bool is_code_valid(const KeyCodeVec &code)
	{
		if (code.size() > ARRAYCODE_MAX_LEN || code.empty())
			return false;
		for (KeyCodeVec::const_iterator it = code.begin(); it != code.end(); ++it) {
			if (!is_key_valid(*it))
				return false;
		}

		return true;
	}


	ArrayCode keytocode(const KeyCodeVec &keys)
	{
		ArrayCode code = 0u;
		size_t i=0;
		for (KeyCodeVec::const_iterator it = keys.begin(); it != keys.end() && i < ARRAYCODE_MAX_LEN; ++it, ++i) {
			if (is_key_valid(*it))
				code = set_key(code, *it, i);
			else {
				code = set_key(code, KEYCODE_ERROR, i);
				break;
			}
		}
		return code;
	}


	KeyCodeVec codetokey(ArrayCode code)
	{
		KeyCodeVec keys;
		for (int i=0; i<ARRAYCODE_MAX_LEN; ++i) {
			KeyCode key = get_key(code, i);
			if (is_key_valid(key))
				keys.push_back(key);
			else if (!is_key_end(key))
				keys.push_back(KEYCODE_ERROR);
			else
				break;
		}
		return keys;
	}


	string keytostr(KeyCode key)
	{
		if (is_key_valid(key)) {
			if (key >= 31) key -= 30;

			char temp[] = "^-v";
			char cstr[3];

			cstr[0] = '0'+(key%10);
			cstr[1] = temp[(key-1)/10];
			cstr[2] = '\0';

			return string(cstr);

		} else
			return string();
	}


	string keytostr(const KeyCodeVec &keys) {
		string s;
		for (vector<KeyCode>::const_iterator it=keys.begin(); it != keys.end(); ++it)
			if (is_key_valid(*it))
				s += keytostr(*it);
		return s;
	}


	string codetostr(ArrayCode code)
	{
		return keytostr(codetokey(code));
	}


	ArrayCode strtocode(string s)
	{
		return keytocode(strtokey(s));
	}


	KeyCodeVec strtokey(string s)
	{
		KeyCodeVec keys;
		for (int i=0; i*2+1 < s.size(); ++i) {

			int col;

			char c = s.at(i*2);
			if (c=='0')
				col = 10;
			else
				col = c - '0';

			if (col > 10 || col < 1)
				break;


			int row = 3;
			switch (s.at(i*2+1)) {
				case '^':
					row = 0;
					break;
				case '-':
					row = 1;
					break;
				case 'v':
					row = 2;
					break;
				default:
					break;
			}


			if (row==3) break;
			else
				keys.push_back(row*10 + col);
		}
		return keys;
	}
}
