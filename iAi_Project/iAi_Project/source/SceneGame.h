/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* オブジェクト */
#include "CharacterPlayer.h"

/* シーン */


/* シーン「ゲーム」の宣言 */

// シーン "ゲーム画面"
class SceneGame : public SceneBase
{
	public:
		SceneGame();							// コンストラクタ
		virtual ~SceneGame();					// デストラクタ

		void	Process()	override;			// 計算
		void	Draw()		override;			// 描画

	private:
		/* 使用するデータリスト */
		// 毎回データリストサーバーから取得するのは非効率なため、ここで保存しておく
		DataList_Object* ObjectList;				// オブジェクト管理
		DataList_PlayerStatus* PlayerStatusList;	// プレイヤー状態管理

		/* 関数 */
		void	LoadMapData();						// マップデータのロード
		void	SetCamera();						// カメラ設定

		/* カメラ関連 */
		void	SetCamera_Free();					// カメラ設定(フリーモード)

	protected:
};
