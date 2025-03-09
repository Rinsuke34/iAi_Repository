/* 2025.01.27 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"
#include "EnemyDefine.h"

/* データリスト */
#include "DataList_Effect.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"
#include "DataList_GameResource.h"
#include "DataList_StageStatus.h"
#include "DataList_Option.h"

/* エフェクト */
#include "EffectSelfDelete.h"

/* オブジェクト */
#include "EffectItem_Blood.h"

/* 基本エネミークラスの宣言 */

// 基本エネミークラス
class Enemy_Basic : public EnemyBase
{
	public:
		Enemy_Basic();				// コンストラクタ
		virtual ~Enemy_Basic() {};	// デストラクタ

		virtual void	BloomDraw()			override;	// 発光描写
		virtual void	CollisionDraw()		override;	// 当たり判定描写
		virtual void	Draw()				override;	// 描写
		virtual void	Reset();						// リセット処理

		void	Defeat();			// 敵撃破時の処理
		void	LoadCoreFrameNo();	// コアフレーム番号取得

		/* データ取得 */
		int		iGetPlayerLockOnType()	{ return this->iPlayerLockOnType; }		// プレイヤー視点でのロックオン状態を取得
		int		iGetCoreFrameNo()		{ return this->iCoreFrameNo; }			// コアとなるフレーム番号を取得

		/* データ設定 */
		void	SetPlayerLockOnType(int iPlayerLockOnType)	{ this->iPlayerLockOnType	= iPlayerLockOnType; }	// プレイヤー視点でのロックオン状態を設定
		void	SetCoreFrameNo(int iCoreFrameNo)			{ this->iCoreFrameNo		= iCoreFrameNo; }		// コアとなるフレーム番号を設定

	private:
		/* 使用するデータリスト */
		DataList_StageStatus*	StageStatusList;	// ステージ状態
		DataList_Option*		OptionList;			// オプション

		/* 変数 */
		int		iPlayerLockOnType;	// プレイヤー視点でのロックオン状態
		int		iCoreFrameNo;		// コアとなるフレーム番号
};
