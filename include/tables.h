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
#include <sqlite3.h>
#include "code.h"

namespace freearray {
	class Table {
		public:
			virtual Result query(std::string str) = 0;
			virtual Result query(ArrayCode code) = 0;
			virtual Result query(ArrayCode begin, ArrayCode end) = 0;

			/*
			virtual int get_next(std::string &s) = 0;
			virtual int get_next(ArrayCode &ac) = 0;
			*/

			virtual ~Table() {}
	};

	class Result {
		public:
			virtual bool next() = 0;
			virtual std::string get_string() = 0;
			virtual ArrayCode get_code() = 0;

			virtual ~Result() {}
	};
	class BufferedResult {
		public:
			typedef std::vector<std::pair<std::string, ArrayCode> > buffer_type;

			BufferedResult(const buffer_type &vec)
				: buffer(vec), curr(buffer.begin()) {}
			bool next() { return curr != vec.end() && ++curr != vec.end(); }
			std::string get_string()
			{
				if (curr != vec.end()) return curr->first;
				else return std::string();
			};
			ArrayCode get_code()
			{
				if (curr != vec.end()) return curr->second;
				else return KEYCODE_END;
			};
			~Result() {}

		private:
			std::vector<std::pair<std::string, ArrayCode> > buffer;
			std::vector<std::pair<std::string, ArrayCode> >::iterator curr;
	};

	class SQLiteTable : public Table {
		public:
			virtual bool query(std::string s);
			bool open_db(const char *db_path);
			void close_db();

			bool open_table(const char *table_name);
			bool query(ArrayCode array_code);
			bool query(ArrayCode begin, ArrayCode end);
			//int get_next(std::string &s);
			//int get_next(ArrayCode &ac);
			//int total();
			//bool empty();


		public:
			SQLiteTable();
			SQLiteTable(const char *db_path, const char *table_name);
			SQLiteTable(sqlite3*);

			~SQLiteTable();
		private:
			sqlite3 *db;
			int ret;
	};

	//extern Table &dtshort;
	extern Table &dtchar;
	//extern Table &dtspecial;
	//extern Table &dtsign;
}
#endif
