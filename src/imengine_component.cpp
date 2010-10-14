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

#include "imengine_component.h"
using namespace std;

namespace freearray {

	CharBuffer::CharBuffer()
		: cursor(begin())
	{
	}
	void CharBuffer::insert(Iterator pos, CharType type, ArrayCode code, char ckey, wch_t sym)
	{
		/* shift the selectInterval */
		break_points.insert(break_points.begin() + pos, false);
		user_break_points.insert(user_break_points.begin() + pos, false);
		user_connect_points.insert(user_connect_points.begin() + pos, false);

		/* insert all symbols */
		code_buffer.insert(code_buffer.begin() + pos, code);
		type_buffer.insert(type_buffer.begin() + pos, type);
		buffer.insert(buffer.begin() + pos, sym);
		ckey_buffer.insert(ckey_buffer.begin() + pos, ckey);
	}
	const string CharBuffer::get_string() const
	{
		string output;
		for (vector<string>::const_iterator it=output_buffer.begin(); it != output_buffer.end(); ++it)
			output += *it;
		return output;
	}
}
