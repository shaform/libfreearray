/** 
 * @file test_imengine.cpp
 * @brief 
 *
 */

/**
 * FreeArray Input Method Library
 * 
 * Copyright (c) 2010
 * 	Yong-Siang Shih (Shaform) <shaform@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See the file "COPYING" for information on usage and redistribution
 * of this file.
 */
#include <iostream>
#include <string>
using namespace std;

#include "imengine.h"
#include "kbtype.h"
#include "code.h"
using namespace freearray;

int main()
{

	string s;

	freearray_im.set_kbtype(kbt_dvorak);
	cout << "Type input sequences, separated by space: " << endl;
	while (cin >> s)
	{
		cout << "Type input sequences, separated by space: " << endl;

		for (int i=0; i != s.size(); ++i) {
			KeyCode key = kbt_dvorak.get_key(s[i]);
			freearray_im.input_key(key);
			cout << key << endl;
		}

		freearray_im.commit_char();

		cout << freearray_im.get_buffer_string() << endl;
	}
	return 0;
}
