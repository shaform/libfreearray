/** 
 * @file kbtype.cpp
 * @brief Defines the keyboard types that FreeArray library supports.
 *
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

#include <string>
#include <vector>
#include "kbtype.h"
#include "code.h"

using std::string;
using std::vector;
namespace {

	//Helper functions
	const vector<string> get_conv_str_default()
	{
		vector<string> vec;
		vec.push_back("qwertyuiopasdfghjkl;zxcvbnm,./");
		vec.push_back("QWERTYUIOPASDFGHJKL:ZXCVBNM<>?");
		return vec;
	}
	const vector<string> get_conv_str_dvorak()
	{
		vector<string> vec;
		vec.push_back("',.pyfgcrlaoeuidhtns;qjkxbmwvz");
		vec.push_back("\"<>PYFGCRLAOEUIDHTNS:QJKXBMWVZ");
		return vec;
	}
}

namespace freearray {
	class KbType::Data {
		friend class KbType;
		typedef vector<string> conv_vec;

		conv_vec convert_strings;
		const string name;
		int count;

		Data(const string &s, const conv_vec &vec) : name(s), convert_strings(vec), count(1) {}
	};

	KbType::KbType(const std::string &kbtype, const std::vector<std::string> &conv_strs)
		: data(new Data(kbtype, conv_strs))
	{
	}

	void KbType::decr_use()
	{
		if (data && --data->count == 0)
			delete data;
	}

	void KbType::incr_use()
	{
		if (data) ++data->count;
	}


	const string KbType::get_kbtype_string() const
	{
		if (data)
			return data->name;
		else
			return string();
	}

	inline void KbType::add_convert_string(const string &s)
	{
		if (data)
			data->convert_strings.push_back(s);
	}



	KeyCode KbType::get_key(char c) const
	{
		if (data)
			for (Data::conv_vec::size_type i=0; i < data->convert_strings.size(); ++i) {
				string::size_type found = data->convert_strings[i].find(c);
				if (found != string::npos)
					return found + 1;
			}

		return KEYCODE_ERROR;
	}

	int KbType::get_char(KeyCode key) const
	{
		// Check if conversion is possible
		if (is_key_valid(key) && data && !data->convert_strings.empty()) {
			// Set the search position for key
			Data::conv_vec::size_type pos = key;
			--pos;

			// Search for the first convert_string which is able to convert key
			for (Data::conv_vec::size_type i=0; i < data->convert_strings.size(); ++i)
				if (pos < data->convert_strings[i].size())
					return data->convert_strings[i][pos];
		}

		return EOF;
	}

	int KbType::convert(char c, const KbType &from) const
	{
		int key = from.get_key(c);
		if (key != KEYCODE_ERROR)
			return get_char(key);
		else
			return EOF;
	}

	int KbType::convert(string &dest, const string &source, const KbType &from) const
	{
		dest.clear();
		int i, converted;
		for (i=0; i != source.size(); ++i) {
			converted = convert(source[i], from);

			if (converted == EOF)
				break;
			else
				dest.push_back(converted);
		}
		// Return the converted length
		return i;
	}







	/* KbTypes */

	/* The first convert_string is for lowercase, and second is for uppercase */

	/* Default USA Qwerty Keyboard */
	extern const KbType kbt_default("USA_Default", get_conv_str_default());

	/* USA Dvorak Keyboard */
	extern const KbType kbt_dvorak("USA_Dvorak", get_conv_str_dvorak());

}
