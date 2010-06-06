/** 
 * @file frontend.cpp
 * @brief 
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
namespace freearray {
#if 0
	/* PreEditBuffer Implementation */
	/* moved to generic im */
	class PreEditBuff {
		public:
			// Get methods
			ArrayCode get_ac() const;
			KeyCode get_kc(size_t pos) const;
			string get_str() const;

			// Modify methods
			bool insert_kc(KeyCode kc, size_t pos = -1);
			bool delete_kc(size_t pos = -1);

			// Helper methods
			bool clear();
			bool full() const;
			bool empty() const;
		private:
			typedef vector<KeyCode> BuffVector;
			BuffVector buff;
	};

	inline bool PreEditBuff::empty()
	{
		return buff.empty();
	}
	inline bool PreEditBuff::full()
	{
		return buff.size() >= ARRAYCODE_MAX_LEN;
	}
	inline bool PreEditBuff::clear()
	{
		buff.clear();
	}
	bool PreEditBuff::insert_kc(KeyCode kc, size_t pos) {
		if (full()) return false;
		if (!valid_kc(kc)) return false;

		if (pos == -1)
			buff.push_back(kc);
		else {
			int i=0;
			for (BuffVector::iterator it=buff.begin(); i!=pos && it!=buff.end(); ++i, ++it);
			insert(it, kc);
		}
		return true;
	}
	bool PreEditBuff::delete_kc(size_t pos) {
		if (empty())
			return false;
		if (pos = -1) {
			buff.pop_back();
		} else {
			int i=0;
			for (BuffVector::iterator it=buff.begin(); i!=pos && it!=buff.end(); ++i, ++it);
			if (it==buff.end())
				return false;
			erase(it);
		}
		return true;
	}

	inline string PreEditBuff::get_str()
	{
		return keytostr(buff);
	}
	inline KeyCode PreEditBuff::get_kc(size_t pos)
	{
		if (pos >= buf.size()) {
			throw out_of_range;
		} else {
			return buff[pos];
		}
	}

	inline ArrayCode PreEditBuff::get_ac()
	{
		return keytocode(buff);
	}
#endif
	class FreeArrayFrontEnd::FreeArrayFrontEndImpl {
		//FreeArrayFactory *c, *sp, *sc, *as, *es;
		//PreEditBuff preedit;
		
		int insert_preedit(char ch);
		int commit_easysign();
		int commit_arraysign();
		int commit_traditional_chinese();
		// int commit_simplied_chinese();
		int commit_special();
		int commit_short(int n);
	};
	int FreeArrayFrontEnd::FreeArrayFrontEndImpl::insert_preedit(KeyCode kc)
	{
		if (preedit.full())
			return 1;
		if (!valid_kc(kc))
			return 1;

		return preedit.insert_kc(kc);
	}
	int FreeArrayFrontEnd::FreeArrayFrontEndImpl::commit_easysign()
	{
		frontend.something();
		//...
	}





	/**
	 * ::FrontEnd States::
	 * FreeArrayState
	 * The states of FreeArrayFrontEnd
	 */

	/* Ignore all actions by default */
	int FreeArrayState::handle_shift(char) { return 0; };
	int FreeArrayState::handle_ctrl(char) { return 0; };
	int FreeArrayState::handle_numlock() { return 0; };
	int FreeArrayState::handle_capslock() { return 0; };
	int FreeArrayState::handle_end() { return 0; };
	int FreeArrayState::handle_home() { return 0; };
	int FreeArrayState::handle_pagedown() { return 0; };
	int FreeArrayState::handle_pageup() { return 0; };
	int FreeArrayState::handle_default(char) { return 0; };
	int FreeArrayState::handle_space() { return 0; };
	int FreeArrayState::handle_tab() { return 0; };
	int FreeArrayState::handle_esc() { return 0; };
	int FreeArrayState::handle_enter() { return 0; };
	int FreeArrayState::handle_delete() { return 0; };
	int FreeArrayState::handle_backspace() { return 0; };
	int FreeArrayState::handle_tab() { return 0; };
	int FreeArrayState::handle_shiftleft() { return 0; };
	int FreeArrayState::handle_shiftright() { return 0; };
	int FreeArrayState::handle_left() { return 0; };
	int FreeArrayState::handle_right() { return 0; };
	int FreeArrayState::handle_up() { return 0; };
	int FreeArrayState::handle_down() { return 0; };
	/*
States:
Idle state
Keycode state
Buffer state
Menu state
Symbol menu state
Phrase menu state

*/

	/**
	 * FreeArrayStateIdle
	 */

	int Idle::handle_shift(char c)
	{
		symbol input();
	}
	int Idle::handle_default(char c)
	{
		if (c == '`') {
			instance.im.open_symbol_menu();
			instance.set_state(instance.get_symbol_menu_state());
		} else {
			instance.im.input_keycode(c);
			instance.set_state(instance.get_keycode_entering_state());
		}
		return 0;
	}
	int FreeArrayState::handle_shiftleft()
	{
		
	}
	int Idle::handle_shiftright()
	{
	}
	int Idle::handle_space()
	{
		instance->input_symbol(' ');
	}
	
	virtual int handle_shift(char)
	{
	}
	virtual int handle_ctrl(char);
	virtual int handle_shiftleft()
	{
		instance.change_shape();
	}
	virtual int handle_shiftright();
	int FreeArrayStateIdle::handle_default(char ch)
	{
		instance.insert_
	}

	/* FreeArrayStateEntering */
	int FreeArrayStateEntering::handle_space()
	{
		return instance.commit_preedit();
	}
	int FreeArrayStateEntering::handle_default(char ch)
	{
		return instance.input(char ch);
	}

	/* Let the state takes all actions by default */
	int FreeArrayFrontEnd::handle_shift(char ch) { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_ctrl(char ch) { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_numlock() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_capslock() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_end() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_home() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_pagedown() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_pageup() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_default(char ch) { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_space() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_tab() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_esc() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_enter() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_delete() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_backspace() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_tab() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_shiftleft() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_shiftright() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_left() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_right() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_up() { return state->hnadle_shift(ch); }
	int FreeArrayFrontEnd::handle_down() { return state->hnadle_shift(ch); }

	FreeArrayFrontEnd::FreeArrayFrontEnd()
	{
		FreeArrayFactory *c, *sp, *sc, *as, *es;
		FreeArrayFactory *tc;
		freearray = new FreeArrayInstance;
		freearray->attach_factory(c);
		freearray->attach_factory(sp);
		freearray->attach_factory(sc);
		freearray->attach_factory(as);
		freearray->attach_factory(es);
	}
	FreeArrayFrontEnd::~FreeArrayFrontEnd()
	{
		FreeArrayFactory *c, *sp, *sc, *as, *es;
		FreeArrayFactory *tc;
		freearray = new FreeArrayInstance;
		for (int i=0; freearray->factory_total(); ++i) {
			delete freearray->dettach_factory(i);
		}
	}

	/* FreeArrayFrontEnd Gerneric Im*/


	int FreeArrayFrontEnd::commit_preedit()
	{
		if (fe->input(preedit) == 0) {
			preedit.clear();
		} else
			return 1;
	}
	int FreeArrayFrontEnd::input(char ch)
	{
		int req;
		if (fe->full()) {
			req = commit_preedit();
			if (req != 0) {
				return 1;
			}
		}

		KeyCode kc = kbtype.get_kc(char ch);
		if (valid_kc(kc)) {
			fe->input(kc, cusor);
		} else {
			return easysign(ch);
		}
	}
	int FreeArrayFrontEnd::easysign(char ch)
	{
		impl->easysign
	}






	/* handles */
	int handle_commit()
	{
		if (preedit.empty()) {
			buff.clear();
		}

	}
	int handle_arraysign()
	{
		arraysign->query(preedit.getac());
	}
	~()
	{

	}

	FreeArrayFrontEnd::FreeArrayFrontEnd() {
		frontend = ();
		// ...
		int factor_id[i] = frontend->attachFactory();
		// ...

		internal_state = new InitState;
	}
	FreeArrayFrontEnd::handle_space() {
		internal_state->handle_space();
	}
	class Word {
		string word;
	};
	class ArrayCodeWord : public Word {
		ArrayCode ac;
	};
	class SignWord : public Word {
		char osign;
	};
}
