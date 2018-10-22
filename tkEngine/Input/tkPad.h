/*!
 *@brief	パッド
 */

#pragma once

namespace tkEngine{
	
	/*!
	 *@brief	仮想ボタン定義。
	 */
	enum EnButton{
		enButtonUp,		//!<上。
		enButtonDown,		//!<下。
		enButtonLeft,		//!<左。
		enButtonRight,		//!<右。
		enButtonA,			//!<Aボタン。
		enButtonB,			//!<Bボタン。
		enButtonX,			//!<Xボタン。
		enButtonY,			//!<Yボタン。
		enButtonSelect,	//!<セレクトボタン。
		enButtonStart,		//!<スタートボタン。
		enButtonRB1,		//!<RB1ボタン。
		enButtonRB2,		//!<RB2ボタン。
		enButtonRB3,		//!<RB3ボタン。
		enButtonLB1,		//!<LB1ボタン。
		enButtonLB2,		//!<LB2ボタン。
		enButtonLB3,		//!<LB3ボタン。
		enButtonNum,	//!<ボタンの数。
	};
	/*!
	 *@brief	パッド
	 */
	class CPad : Noncopyable{
	public:
		static const int CONNECT_PAD_MAX = 4;		//接続可能なパッドの最大数。
		/*!
		 *@brief	パッドステート。
		 */
		struct PAD_STATE
		{
			XINPUT_STATE state;
			bool bConnected;
		};
		/*!
		 *@brief	コンストラクタ。
		 */
		CPad();
		/*!
		 *@brief	デストラクタ。
		 */
		~CPad();
		/*!
		*@brief	初期化。
		*@param[in]	padNo	パッド番号。
		*/
		void Init(int padNo)
		{
			m_padNo = padNo;
		}
		/*!
		*@brief	更新。
		*/
		void Update();
		/*!
		 *@brief	ボタンのトリガー判定。
		 *@return	trueが返ってきたらトリガー入力。
		 */
		bool IsTrigger(EnButton button) const
		{
			TK_ASSERT( button < enButtonNum, "button is invalid" );
			return m_trigger[button] != 0;
		}
		/*!
		 *@brief	ボタンが押されているか判定。
		 *@return	trueが返ってきたら押されている。
		 */
		bool IsPress(EnButton button) const
		{
			TK_ASSERT(button < enButtonNum, "button is invalid");
			return m_press[button] != 0;
		}
		/*!
		*@brief	何かのボタンが押されているか判定
		*@return	trueが返ってきたら押されている。
		*/
		bool IsPressAnyKey() const
		{
			return IsPress(enButtonUp)
				|| IsPress(enButtonDown)
				|| IsPress(enButtonLeft)
				|| IsPress(enButtonRight)
				|| IsPress(enButtonA)
				|| IsPress(enButtonB)
				|| IsPress(enButtonX)
				|| IsPress(enButtonY)
				|| IsPress(enButtonSelect)
				|| IsPress(enButtonStart)
				|| IsPress(enButtonRB1)
				|| IsPress(enButtonRB2)
				|| IsPress(enButtonRB3)
				|| IsPress(enButtonLB1)
				|| IsPress(enButtonLB2)
				|| IsPress(enButtonLB3);
		}
		/*!
		*@brief	何かのボタンが押されているか判定
		*@return	trueが返ってきたら押されている。
		*/
		bool IsTriggerAnyKey() const
		{
			return IsTrigger(enButtonUp)
				|| IsTrigger(enButtonDown)
				|| IsTrigger(enButtonLeft)
				|| IsTrigger(enButtonRight)
				|| IsTrigger(enButtonA)
				|| IsTrigger(enButtonB)
				|| IsTrigger(enButtonX)
				|| IsTrigger(enButtonY)
				|| IsTrigger(enButtonSelect)
				|| IsTrigger(enButtonStart)
				|| IsTrigger(enButtonRB1)
				|| IsTrigger(enButtonRB2)
				|| IsTrigger(enButtonRB3)
				|| IsTrigger(enButtonLB1)
				|| IsTrigger(enButtonLB2)
				|| IsTrigger(enButtonLB3);
		}
		/*!
		*@brief	自作　
		*@return	押されたボタンを出力。
		*/
		EnButton GetPushKey() const
		{
			if (IsPress(enButtonA)) return EnButton::enButtonA;
			else if (IsPress(enButtonB)) return EnButton::enButtonB;
			else if (IsPress(enButtonX)) return EnButton::enButtonX;
			else if (IsPress(enButtonY)) return EnButton::enButtonY;
			else if (IsPress(enButtonUp)) return EnButton::enButtonUp;
			else if (IsPress(enButtonDown)) return EnButton::enButtonDown;
			else if (IsPress(enButtonLeft)) return EnButton::enButtonLeft;
			else if (IsPress(enButtonRight)) return EnButton::enButtonRight;
			else if (IsPress(enButtonSelect)) return EnButton::enButtonSelect;
			else if (IsPress(enButtonStart)) return EnButton::enButtonStart;
			else if (IsPress(enButtonLB1)) return EnButton::enButtonLB1;
			else if (IsPress(enButtonLB2)) return EnButton::enButtonLB2;
			else if (IsPress(enButtonLB3)) return EnButton::enButtonLB3;
			else if (IsPress(enButtonRB1)) return EnButton::enButtonRB1;
			else if (IsPress(enButtonRB2)) return EnButton::enButtonRB2;
			else if (IsPress(enButtonRB3)) return EnButton::enButtonRB3;
		}
		
		/*!
		*@brief	左スティックのX軸の入力量を取得。
		*@return	-1.0～1.0の正規化された値を返す。
		*/
		float GetLStickXF() const
		{
			return m_lStickX;
		}
		/*!
		*@brief	左スティックのY軸の入力量を取得。
		*@return	-1.0～1.0の正規化された値を返す。
		*/
		float GetLStickYF() const
		{
			return m_lStickY;
		}
		/*!
		*@brief	右スティックのX軸の入力量を取得。
		*@return	-1.0～1.0の正規化された値を返す。
		*/
		float GetRStickXF() const
		{
			return m_rStickX;
		}
		/*!
		*@brief	右スティックのY軸の入力量を取得。
		*@return	-1.0～1.0の正規化された値を返す。
		*/
		float GetRStickYF() const
		{
			return m_rStickY;
		}

		float GetMouseX() const
		{
			return m_mouseX;
		}
		float GetMouseY() const
		{
			return m_mouseY;
		}
		bool IsMouseLeftC() const
		{
			return clickL;
		}
		void SetMouseLeftC(bool c)
		{
			clickL = c;
		}
	private:
		PAD_STATE m_state;	//!<パッドステート。
		int m_padNo = 0;			//!<パッド番号。
		int m_trigger[enButtonNum];	//!<トリガー入力のフラグ。
		int m_press[enButtonNum];	//!<press入力のフラグ。
		float m_lStickX = 0.0f;		//!<左スティックのX軸の入力量。
		float m_lStickY = 0.0f;		//!<左スティックのY軸の入力量。
		float m_rStickX = 0.0f;		//!<右スティックのX軸の入力量。
		float m_rStickY = 0.0f;		//!<右スティックのY軸の入力量。

		float m_mouseX = 0.0f;
		float m_mouseY = 0.0f;
		POINT oldpt = {0,0};
		float oldx = 0.0f;
		float oldy = 0.0f;
		bool clickL = false;
		bool clickR = false;
	};
}