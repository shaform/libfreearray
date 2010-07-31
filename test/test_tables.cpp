/** 
 * @file test_tables.cpp
 * @brief Testing DataTable abilities.
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
#include <vector>
using namespace std;


#include "kbtype.h"
#include "code.h"
#include "tables.h"

int main()
{

	using namespace freearray;
	KbType *kt_default = new KbTypeDefault,
	       *kt_dvorak = new KbTypeDvorak;
	string s;
	DataTable *tc2_table = new SQLiteTable("./data/freearray.db", "TC_CHAR");
	DataTable *tc_table = new SQLiteTable("./data/freearray.db", "TC_SIGN");

	cout << "Type input sequences, separated by space: " << endl;
	while (cin >> s)
	{
		cout << "Type input sequences, separated by space: " << endl;

		vector<KeyCode> kc_vec;
		kc_vec.clear();

		for (int i=0; i != s.size(); ++i) {
			KeyCode kc = kt_dvorak->get_kc(s[i]);
			kc_vec.push_back(kc);
			cout << kc << endl;
		}

		ArrayCode ac;
		ac = keytocode(kc_vec);
		cout << "Converted ArrayCode: " << ac << endl;
		if (tc_table->query(ac)) {
			cout << "Found: " << endl;
			string s;
			while (tc_table->get_next(&s))
				cout << s << endl;
		}
		cout << "End found." << endl;
	}
	delete kt_default;
	delete kt_dvorak;
	delete tc_table;

	return 0;
}
