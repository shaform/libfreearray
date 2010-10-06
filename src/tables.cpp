/** 
 * @file tables.cpp
 * @brief 
 *
 */

/**
 * FreeArray Input Method Library
 * 
 * Copyright (c) 2009-2010
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
#include <sqlite3.h>
#include <string>
#include <vector>
#include <utility>
#include "code.h"
#include "tables.h"
namespace freearray {
	using std::string;
	using std::vector;
	using std::pair;

	SQLiteTable::SQLiteTable(const char *dp, const char *tn) : db(0), qc_stmt(0), qw_stmt(0)
	{
		if (open_db(dp))
			open_table(tn);
	}
	bool SQLiteTable::open_db(const char *dp)
	{
		if (db)
			close_db();

		if (sqlite3_open_v2(dp, &db, SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX, 0) == SQLITE_OK)
			return true;
		else {
			close_db();
			return false;
		}
	}
	void SQLiteTable::close_db()
	{
		close_table();
		if (db)
			sqlite3_close(db);
		db = 0;
	}
	bool SQLiteTable::open_table(const char *tn)
	{
		if (db && sqlite3_prepare_v2(db,
					("SELECT code, word FROM "+string(tn)+" WHERE code=?").c_str(),
					-1,
					&qc_stmt, 0) == SQLITE_OK
				&& sqlite3_prepare_v2(db,
					("SELECT code, word FROM "+string(tn)+" WHERE word=?").c_str(),
					-1,
					&qw_stmt, 0) == SQLITE_OK)
			return true;
		else {
			close_table();
			return false;
		}
	}
	void SQLiteTable::close_table()
	{
		if (qc_stmt)
			sqlite3_finalize(qc_stmt);
		if (qw_stmt)
			sqlite3_finalize(qw_stmt);
		qc_stmt = qw_stmt = 0;
	}

	BufferedResult *SQLiteTable::query(string s) {
		vector<pair<ArrayCode, string> > vec;

		sqlite3_reset(qw_stmt);
		if (sqlite3_bind_text(qw_stmt, 1, s.c_str(), -1, SQLITE_TRANSIENT) == SQLITE_OK) {
			while (sqlite3_step(qw_stmt) == SQLITE_ROW) {
				vec.push_back(pair<ArrayCode, string>(
							sqlite3_column_int(qw_stmt, 0),
							reinterpret_cast<const char *>(
								sqlite3_column_text(qw_stmt, 1))));
			}
		}
		return new BufferedResult(vec);
	}
	BufferedResult *SQLiteTable::query(ArrayCode ac) {
		vector<pair<ArrayCode, string> > vec;

		sqlite3_reset(qc_stmt);
		if (sqlite3_bind_int(qc_stmt, 1, ac) == SQLITE_OK) {
			while (sqlite3_step(qc_stmt) == SQLITE_ROW) {
				vec.push_back(pair<ArrayCode, string>(
							sqlite3_column_int(qc_stmt, 0),
							reinterpret_cast<const char *>(
								sqlite3_column_text(qc_stmt, 1))));
			}
		}
		return new BufferedResult(vec);
	}

	static SQLiteTable sqdtchar(PKGDATADIR "/data/freearray.db", "TC_CHAR");
	Table &dtchar = sqdtchar;
}
