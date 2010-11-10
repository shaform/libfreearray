/** 
 * @file tables.h
 * @brief FreeArray data table handling classes
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

#ifndef FREEARRAY_TABLES_H
#define FREEARRAY_TABLES_H
#include <string>
#include <utility>
#include <sqlite3.h>
#include "code.h"

namespace freearray {
	class Result {
		public:
			virtual bool next() = 0;
			virtual std::string get_string() = 0;
			virtual ArrayCode get_code() = 0;

			virtual ~Result() {}
	};

	class BufferedResult : public Result {
		public:
			typedef std::vector<std::pair<ArrayCode, std::string> > buffer_type;

			BufferedResult(const buffer_type &vec)
				: buffer(vec), curr(buffer.begin()), first(true) {}
			bool next()
			{
				if (first) {
					first = false;
					return curr != buffer.end();
				} else
					return curr != buffer.end() && ++curr != buffer.end();
			}
			ArrayCode get_code()
			{
				if (curr != buffer.end()) return curr->first;
				else return KEYCODE_END;
			};
			std::string get_string()
			{
				if (curr != buffer.end()) return curr->second;
				else return std::string();
			};
			~BufferedResult() {}

		private:
			std::vector<std::pair<ArrayCode, std::string> > buffer;
			std::vector<std::pair<ArrayCode, std::string> >::iterator curr;
			bool first;
	};

	class Table {
		public:
			virtual Result *query(std::string str) = 0;
			virtual Result *query(ArrayCode code) = 0;
			virtual Result *query(ArrayCode begin, ArrayCode end) = 0;

			/*
			virtual int get_next(std::string &s) = 0;
			virtual int get_next(ArrayCode &ac) = 0;
			*/

			virtual ~Table() {}
	};


	class SQLiteTable : public Table {
		public:
			BufferedResult *query(std::string s);
			BufferedResult *query(ArrayCode array_code);
			BufferedResult *query(ArrayCode begin, ArrayCode end) { return 0; }


			bool open_db(const char *db_path);
			void close_db();
			bool open_table(const char *table_name);
			void close_table();
		public:
			SQLiteTable() : db(0), qc_stmt(0), qw_stmt(0) {}
			SQLiteTable(const char *db_path, const char *table_name);
			SQLiteTable(sqlite3 *db) : db(db), qc_stmt(0), qw_stmt(0) {}

			~SQLiteTable() { close_db(); }
		private:
			sqlite3 *db;
			sqlite3_stmt *qc_stmt;
			sqlite3_stmt *qw_stmt;
	};

	extern Table &dtchar;
	//extern Table &dtshort;
	extern Table &dtspecial;
	extern Table &dtsign;
	extern Table &dtphrase;
}
#endif
