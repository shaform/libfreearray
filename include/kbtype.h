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

namespace freearray {
	typedef unsigned short KeyCode;
	class KbType {
		public:
			/**
			 * @brief Get the name string of the KbType.
			 * @return A string containing the name of the KbType.
			 */
			std::string get_kbtype_string() const;


			/**
			 * @brief Get the KeyCode of *c* in this KbType.
			 * @return A KeyCode
			 */
			KeyCode get_kc(char c) const;


			/**
			 * @brief Get the character of *kc* in this KbType.
			 *
			 * Notice that the mapping from KeyCode to character may not be unique,
			 * but the KbType must always return the same character for the same KeyCode.
			 *
			 * @return A character, EOF if failed
			 */
			int get_char(KeyCode kc) const;


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

			virtual ~KbType();
		protected:

			/**
			 * @brief Add a convert_string.
			 *
			 * Each KbType derived from this class should call this function to set its convert_string.
			 * Multiple mappings can be set, but if the same character occurs in different convert_string
			 * and in different places, the behaviour is undefined
			 *
			 * **Note**
			 * The length of a convert_string should be 30 now
			 * But in the future, up to 60 may be used
			 * 
			 */
			void add_convert_string(const std::string &convert_string);


			/**
			 * @brief Constructor, setting the name of the KbType.
			 */
			KbType(const std::string &kbtype);





		private:
			class Impl;
			Impl *impl;
	};

	class KbTypeDefault : public KbType {
		public:
			static KbTypeDefault *get_type();
		private:
			KbTypeDefault();
	};
	class KbTypeDvorak : public KbType {
		public:
			static KbTypeDvorak *get_type();
		private:
			KbTypeDvorak();
	};
}
#endif

