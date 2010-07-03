/**
 * @file kbtype.h
 * @brief Defines the keyboard types that FreeArray library supports.
 *
 */

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
#ifndef FREEARRAY_KBTYPE_H
#define FREEARRAY_KBTYPE_H
#ifndef EOF
#define EOF (-1)
#endif

#include <string>
#include "code.h"

namespace freearray {
	class KbType {
		public:

			/**
			 * @brief Empty Constructor.
			 */
			KbType();

			/**
			 * @brief Constructor, setting the name of the KbType & its convert strings.
			 */
			KbType(const std::string &kbtype, const std::vector<std::string> &conv_strs = std::vector<std::string>());
			KbType(const KbType &rhs);

			~KbType();

			/**
			 * @brief Get the name string of the KbType.
			 * @return A string containing the name of the KbType.
			 */
			const std::string get_kbtype_string() const;


			/**
			 * @brief Get the KeyCode of *c* in this KbType.
			 * @return A KeyCode
			 */
			KeyCode get_key(char c) const;


			/**
			 * @brief Get the character of *key in this KbType.
			 *
			 * Notice that the mapping from KeyCode to character may not be unique,
			 * but the KbType must always return the same character for the same KeyCode.
			 *
			 * @return A character, EOF if failed
			 */
			int get_char(KeyCode key) const;


			/**
			 * @brief Convert the string *source* to *dest* from KbType *from* to this KbType.
			 *
			 * Converting would stop once an invalid character is found.
			 *
			 * @return The number of characters converted.
			 */
			int convert(std::string &dest, const std::string &source, const KbType &from) const;


			/**
			 * @brief Convert the char c from KbType *from* to this KbType.
			 *
			 * @return The converted character, EOF if failed.
			 */
			int convert(char c, const KbType &from) const;

			KbType &operator=(const KbType &rhs);

			bool operator==(const KbType &rhs) const;

			bool operator!=(const KbType &rhs) const;

		private:
			/**
			 * @brief Add a convert_string.
			 *
			 * Multiple mappings can be set, but if the same character occurs in different convert_string
			 * and in different places, the behaviour is undefined
			 *
			 */
			void add_convert_string(const std::string &convert_string);


		private:
			class Data;
			Data *data;

			void decr_use();
			void incr_use();
	};





	inline KbType::KbType() : data(0) {}
	inline KbType::KbType(const KbType &rhs)
		: data(rhs.data)
	{
		incr_use();
	}
	inline KbType::~KbType()
	{
		decr_use();
	}
	inline KbType &KbType::operator=(const KbType &rhs)
	{
		if (&rhs != this) {
			decr_use();
			data = rhs.data;
			incr_use();
		}
		return *this;
	}

	inline bool KbType::operator==(const KbType &rhs) const
	{
		return rhs.data == data;
	}

	inline bool KbType::operator!=(const KbType &rhs) const
	{
		return rhs.data != data;
	}






	extern const KbType kbt_default;
	extern const KbType kbt_dvorak;
}
#endif

