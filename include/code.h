/** 
 * @file code.h
 * @brief Defines the KeyCode & ArrayCode
 */

/**
 * FreeArray Input Method Library
 * 
 * Copyright (c) 2007-2010
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

/**
 *	KeyCode:
 *
 *	0	:	END
 *	1~30	:	Standard Array keys
 *	31~60	:	Extended Array keys *reserved*
 *	61	:	?
 *	62	:	*
 *	63	:	Error
 *
 *
 *      ArrayCode:
 *
 *	 *reserved*       1st           2nd           3rd           4th           5th
 *	|-- 2bits --|--- 6bits ---|--- 6bits ---|--- 6bits ---|--- 6bits ---|--- 6bits ---|
 *           00         KeyCode       KeyCode     ...trailing bits are filled with END(0)
 *
 */

#ifndef FREEARRAY_CODE_H
#define FREEARRAY_CODE_H
#include <vector>
#include <string>

namespace freearray {
	typedef unsigned short KeyCode;
	typedef unsigned long ArrayCode;
	typedef std::vector<KeyCode> KeyCodeVec;
	
	const KeyCode KEYCODE_END = 0u;
	const KeyCode KEYCODE_QUESTION = 61u;
	const KeyCode KEYCODE_ASTERISK = 62u;
	const KeyCode KEYCODE_ERROR = 63u;
	const size_t ARRAYCODE_MAX_LEN = 5;

	

	inline bool is_key_end(KeyCode key) { return key == KEYCODE_END; }
	inline bool is_key_std(KeyCode key) { return (key <= 30u && key >= 1u); }
	inline bool is_key_ext(KeyCode key) { return (key <= 60u && key >= 31u); }

	inline bool is_key_valid(KeyCode key) { return is_key_std(key) || is_key_ext(key)
		|| key == KEYCODE_QUESTION || key == KEYCODE_ASTERISK; }

	bool is_code_valid(ArrayCode code);
	bool is_code_valid(const KeyCodeVec &code);


	/**
	 * @brief Convert a KeyCode vector into an ArrayCode.
	 *
	 * If the length of the vector is longer than KEYCODE_MAX_LEN, the behaviour is undefined.
	 * If the vector contains invalid KeyCodes, KEYCODE_ERROR is inserted into the ArrayCode
	 * and the converting stops.
	 *
	 * @return The converted ArrayCode.
	 */
	ArrayCode keytocode(const KeyCodeVec &keys);



	/**
	 * @brief Convert an ArrayCode into a KeyCode vector.
	 * 
	 * All codes other than KEYCODE_END are converted,
	 * and invalid KeyCodes will be converted into KEYCODE_ERRORs.
	 *
	 * @return The converted KeyCode vector.
	 */
	KeyCodeVec codetokey(ArrayCode code);


	/**
	 * @brief Convert a KeyCode into a string.
	 *
	 * If the KeyCode is invalid, it returns an empty string.
	 *
	 * @return The converted KeyCode vector.
	 */
	std::string keytostr(KeyCode key);


	/**
	 * @brief Convert a KeyCode vector into a string.
	 *
	 * It can convert more than ARRAYCODE_MAX_LEN KeyCodes.
	 * If an invalid KeyCode is found, the conversion stops.
	 *
	 * @return The converted KeyCode vector.
	 */
	std::string keytostr(const KeyCodeVec &keys);


	/**
	 * @brief Convert an ArrayCode vector into a string.
	 *
	 * If an invalid KeyCode is found, the conversion stops.
	 *
	 * @return The converted KeyCode vector.
	 */
	std::string codetostr(ArrayCode code);


	/**
	 * @brief Convert a string into an ArrayCode.
	 *
	 * If an invalid KeyCode is found, the conversion stops.
	 * If no valid KeyCode is found, return an KEYCODE_END filled ArrayCode.
	 *
	 * @return The converted ArrayCode.
	 */
	ArrayCode strtocode(std::string s);


	/**
	 * @brief Convert an string into a KeyCode vector.
	 *
	 * If an invalid KeyCode is found, the conversion stops.
	 * If no valid KeyCode is found, return an empty vector.
	 *
	 * @return The converted KeyCode vector.
	 */
	KeyCodeVec strtokey(std::string s);


	/**
	 * @brief Get the n-th KeyCode of an ArrayCode. (n starts from 0)
	 *
	 * If n is an invalid position, KEYCODE_END is returned;
	 * Otherwise, it retrives the data in the ArrayCode without checking.
	 *
	 * @return The n-th KeyCode.
	 */
	KeyCode get_key(ArrayCode code, int pos);


	/**
	 * @brief Set the n-th KeyCode of an ArrayCode. (n starts from 0)
	 *
	 * If n is an invalid position, nothing would be done.
	 * Otherwise, it sets the data in the ArrayCode without checking.
	 *
	 * @return The new ArrayCode.
	 */
	ArrayCode set_key(ArrayCode code, KeyCode key, int pos);
}
#endif
