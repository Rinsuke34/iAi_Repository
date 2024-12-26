/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "CharacterBase.h"

/* データリスト */
#include "DataList_Input.h"

/* プレイヤークラスの宣言 */

// プレイヤークラス
class CharacterPlayer : public CharacterBase
{
	public:
		CharacterPlayer();				// コンストラクタ
		virtual ~CharacterPlayer() {};	// デストラクタ

		virtual void	Update();	// 更新
		virtual void	Draw();		// 描写

	private:
	protected:
		/* 使用するデータリスト */
		// 毎回データリストサーバーから取得するのは非効率なため、ここで保存しておく
		DataList_Input*	InputList;	// 入力管理
};
