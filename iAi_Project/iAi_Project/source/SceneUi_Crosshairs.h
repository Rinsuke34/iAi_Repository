/* 2025.01.27 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_GameStatus.h"

/* UI(クロスヘア)クラスの宣言 */

// UI(クロスヘア)クラス
class SceneUi_Crosshairs : public SceneBase
{
	public:
		SceneUi_Crosshairs();					// コンストラクタ
		virtual ~SceneUi_Crosshairs()	{};		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
		DataList_GameStatus*	GameStatusList;		// ゲーム状態管理

		/* 構造体(ここでしか使用しないのでここで定義) */
		// 最も画面の中心点から近いエネミー
		struct NearEnemy
		{
			EnemyBasic* pEnemy;		// エネミーのポインタ
			float fDistance;		// 画面中心からの距離(軽量化のため座標の差の二乗)
		};
};

