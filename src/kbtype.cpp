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
namespace {
	using std::string;
	using std::vector;
}
namespace freearray {
	class KbType::Impl {
		public:
			typedef vector<string> conv_vec;
			conv_vec convert_strings;
			const string name;
			Impl(const string &s) : name(s) {}
	};
	KbType::KbType(const string &kbtype) : impl(new Impl(kbtype)) {}
	KbType::~KbType() { delete impl; }

	string KbType::get_kbtype_string() const
	{
		//In fact, impl should never be NULL
		if (impl)
			return impl->name;
		else
			return string();
	}

	inline void KbType::add_convert_string(const string &s)
	{
		//In fact, impl should never be NULL
		if (impl)
			impl->convert_strings.push_back(s);
	}



	KeyCode KbType::get_kc(char c) const
	{
		if (impl)
			for (Impl::conv_vec::size_type i=0; i < impl->convert_strings.size(); ++i) {
				string::size_type found = impl->convert_strings[i].find(c);
				if (found != string::npos)
					return found + 1;
			}

		return KEYCODE_ERROR;
	}
	int KbType::get_char(KeyCode kc) const
	{
		// Check if conversion is possible
		if (valid_kc(kc) && impl && !impl->convert_strings.empty()) {
			// Set the search position for kc
			Impl::conv_vec::size_type pos = kc;
			--pos;

			// Search for the first convert_string which is able to convert kc
			for (Impl::conv_vec::size_type i=0; i < impl->convert_strings.size(); ++i)
				if (pos < impl->convert_strings[i].size())
					return impl->convert_strings[i][pos];
		}

		return EOF;
	}

	int KbType::convert(char c, const KbType &from) const
	{
		int kc = from.get_kc(c);
		if (kc != KEYCODE_ERROR)
			return get_char(kc);
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
	KbTypeDefault::KbTypeDefault() : KbType(string("USA_Default"))
	{
		add_convert_string(string("qwertyuiopasdfghjkl;zxcvbnm,./"));
		add_convert_string(string("QWERTYUIOPASDFGHJKL:ZXCVBNM<>?"));
	}
	KbTypeDefault *KbTypeDefault::get_type()
	{
		static KbTypeDefault kbt;
		return kbt;
	}

	/* USA Dvorak Keyboard */
	KbTypeDvorak::KbTypeDvorak() : KbType(string("USA_Dvorak"))
	{
		add_convert_string(string("',.pyfgcrlaoeuidhtns;qjkxbmwvz"));
		add_convert_string(string("\"<>PYFGCRLAOEUIDHTNS:QJKXBMWVZ"));
	}

	KbTypeDvorak *KbTypeDvorak::get_type()
	{
		static KbTypeDvorak kbt;
		return kbt;
	}
}
