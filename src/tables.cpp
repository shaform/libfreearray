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
#include "tables.h"
#include "code.h"


#define SIGN_CIN_FILE sign.data
#define TCHAR_CIN_FILE table.data
#define SCHAR_CIN_FILE
#define SPECIAL_CIN_FILE
#define SHORT_CIN_FILE

namespace {
	using std::string;
}

namespace freearray {
#if 0

	DataTable::DataTable(const char filename[])
	{
		ifstream cinfile;
		cinfile.open(filename, ios::in);
		ArrayCode ac;
		char as[99];
		WordVector wv;
		while (cinfile >> ac >> as) {
			map<ArrayCode, WordVector>::iterator iter = table.find(ac);
			if( iter == table.end() ) {
				wv.assign(1,Word(as));
				table.insert(make_pair(ac, wv));
			} else {
				iter->second.push_back(Word(as));
			}
		}
	}
	WordVector DataTable::fetch(ArrayCode ac, int max_size)
	{
		return table[ac];
	}

#endif
	class SQLiteTable::SQLiteTableImpl {
		public:
			sqlite3 *db;
			sqlite3_stmt *qw_stmt;
			sqlite3_stmt *qwr_stmt;
			sqlite3_stmt *next_stmt;
			string db_path;
			int total_items;
			string table_name;
			int ret;
	};

	SQLiteTable::SQLiteTable() : impl(new SQLiteTableImpl) {}
	SQLiteTable::SQLiteTable(const char *dp, const char *tn/*, OpenMode mode*/)
		: impl(new SQLiteTableImpl)
	{

		impl = new SQLiteTableImpl;
		if (open_db(dp/*, mode*/)) {
			open_table(tn);
		} else
			impl->db = NULL;

		impl->ret = SQLITE_DONE;
	}
	bool SQLiteTable::open_db(const char *dp/*, OpenMode mode*/)
	{
		impl->db_path = string(dp);
		if (sqlite3_open_v2(dp, &impl->db, SQLITE_OPEN_READONLY, NULL) == SQLITE_OK)
			return true;
		else
			return false;
	}
	bool SQLiteTable::open_table(const char *tn)
	{
		if (impl->db) {
			impl->table_name = tn;
			sqlite3_prepare_v2(impl->db, ("SELECT word FROM " + impl->table_name + " WHERE code=?").c_str(), -1, &impl->qw_stmt, NULL);
			sqlite3_prepare_v2(impl->db, ("SELECT code FROM " + impl->table_name + " WHERE word=?").c_str(), -1, &impl->qwr_stmt, NULL);
		}
		return true;
	}

	SQLiteTable::SQLiteTable(sqlite3 *sq3)
		: impl(new SQLiteTableImpl)
	{
		SQLiteTable();
		if (sq3) {
			impl->db_path = string();
			impl->db = sq3;
		}
	}

	bool SQLiteTable::query(string s) {
		sqlite3_reset(impl->qwr_stmt);
		sqlite3_bind_text(impl->qwr_stmt, 1, s.c_str(), -1, SQLITE_TRANSIENT);
		impl->ret = sqlite3_step(impl->qwr_stmt);

		if (impl->ret == SQLITE_ROW)
			return true;
		else
			return false;
	}
	bool SQLiteTable::query(ArrayCode ac) {
		sqlite3_reset(impl->qw_stmt);
		sqlite3_bind_int(impl->qw_stmt, 1, static_cast<int>(ac));
		impl->ret = sqlite3_step(impl->qw_stmt);

		if (impl->ret == SQLITE_ROW)
			return true;
		else
			return false;
	}
	SQLiteTable::~SQLiteTable()
	{
		sqlite3_reset(impl->qw_stmt);
		sqlite3_finalize(impl->qw_stmt);
		sqlite3_close(impl->db);
		delete impl;
	}
	int SQLiteTable::get_next(string &s)
	{
		if (impl->ret == SQLITE_ROW) {
			s = reinterpret_cast<const char *>(sqlite3_column_text(impl->qw_stmt, 0));
			impl->ret = sqlite3_step(impl->qw_stmt);
			return 1;
		}
		return 0;
	}
	int SQLiteTable::get_next(ArrayCode &ac)
	{
		if (impl->ret == SQLITE_ROW) {
			ac = static_cast<ArrayCode>(sqlite3_column_int(impl->qwr_stmt, 0));
			impl->ret = sqlite3_step(impl->qwr_stmt);
			return 1;
		}
		return 0;
	}


#if 0

	SQLiteTable::fetch(ArrayCode ac, int max_size) {
		db->execute("SELECT word FROM %s", );
		sqlite3_stmt *stmt;
		retcode = sqlite3_prepare_v2(db, "SELECT word FROM %s WHERE code=?", -1, &stmt, NULL);
		if (retcode == SQLITE_OK) {
			sqlite3_bind_text(stmt, 1, ac, -1, SQLITE_TRANSIENT);
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				gchar *ch = (gchar*)sqlite3_column_text(stmt, 0);
				gchar *chstr = g_strdup(ch);
				g_array_append_val(result, chstr);
			}
		}
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
	}
	SQLiteTable::SQLiteTable() {
		if (instances == 0) {
			if (sqlite3_open_v2(ARRAY_SQLITE_DB, &db, SQLITE_OPEN_READONLY, NULL) != SQLITE_OK) {
			}
			context->conn = NULL;
		}
		++instances;
	}
	SQLiteTable::~SQLiteTable()
	{
		--instances;
		if (instances == 0) {
			sqlite3_close(db);
		}
	}



	DataTable tc_table(TCHAR_CIN_FILE), sign_table(SIGN_CIN_FILE);

#endif
	SQLiteTable sqdtchar("../data/freearray.db", "TC_CHAR");
	DataTable &dtchar = sqdtchar;
}
