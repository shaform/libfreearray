/** 
 * @file test_code.cpp
 * @brief Testing ArrayCode.
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
#include <vector>
#include "kbtype.h"

using namespace freearray;
using namespace std;

int main()
{
	KbType kbt = kbt_default; 

	cout << kbt.get_kbtype_string() << endl;
	cout << "Input default characters to get KeyCode & Dvorak chars" << endl;
	char c;
	while (cin >> c) {
		cout << "Key: ";
		cout << kbt.get_key(c);
		cout << ", Dvoark char: ";
		cout << static_cast<char>(kbt_dvorak.convert(c, kbt)) << endl;
	}

	return 0;
}
