/* 2024.01.02 駒沢風助 ファイル追加 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* オブジェクト */
#include "CharacterPlayer.h"

/* シーン「ゲーム - カメラ」の宣言 */

// シーン "ゲーム画面 - カメラ"
class SceneGame_Camera : public SceneBase
{
	public:
		SceneGame_Camera();				// コンストラクタ
		virtual ~SceneGame_Camera();	// デストラクタ

		void	Process()	override;			// 計算
		void	Draw()		override;			// 描画

	private:
		/* 使用するデータリスト */
		// 毎回データリストサーバーから取得するのは非効率なため、ここで保存しておく
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理

	protected:
};
