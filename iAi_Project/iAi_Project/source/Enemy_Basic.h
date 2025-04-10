/* 2025.01.27 駒沢風助 ファイル作成 */
/* 2025.03.23 石川智也 エネミー被弾時・重力の処理追加 */

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
#include "DataList_PlayerStatus.h"

/* エフェクト */
#include "EffectSelfDelete.h"

/* オブジェクト */
#include "EffectItem_Blood.h"

/* 循環参照対策の先行定義 */
class DataList_Object;

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

		void	Defeat();								// 敵撃破時の処理
		void	DefeatAttack();																	// 敵攻撃被弾時の処理	/* 2025.03.23 石川智也 敵攻撃被弾時のメソッドを追加 */
		void	LoadCoreFrameNo();						// コアフレーム番号取得

		/* データ取得 */
		int		iGetPlayerLockOnType()	{ return this->iPlayerLockOnType; }		// プレイヤー視点でのロックオン状態を取得
		int		iGetCoreFrameNo()		{ return this->iCoreFrameNo; }			// コアとなるフレーム番号を取得
		bool	bGetDeadFlg()			{ return this->bDeadFlg; };				// 死亡フラグを取得

		/* データ設定 */
		void	SetPlayerLockOnType(int iPlayerLockOnType)	{ this->iPlayerLockOnType	= iPlayerLockOnType; }	// プレイヤー視点でのロックオン状態を設定
		void	SetCoreFrameNo(int iCoreFrameNo)			{ this->iCoreFrameNo		= iCoreFrameNo; }		// コアとなるフレーム番号を設定
		void	SetDeadFlg(bool bDeadFlg)					{ this->bDeadFlg			= bDeadFlg; };			// 死亡フラグを設定

	protected:
		/* 変数 */
		bool	bDeadFlg;			// 死亡フラグ
		int		iBloodAmount;		// ブラッド量

		//関数
		void	Enemy_Gravity();																	// 重力処理　	/* 2025.03.23 石川智也 重力処理メソッドを追加 */


		COLLISION_LINE stVerticalCollision;						// 垂直方向のコリジョン
		VECTOR vecMove;											// 移動量
	private:
		/* 使用するデータリスト */
		DataList_StageStatus*	StageStatusList;	// ステージ状態
		DataList_Option*		OptionList;			// オプション
		DataList_Object*		ObjectList;			// オブジェクト管理
		/* 変数 */
		int		iPlayerLockOnType;	// プレイヤー視点でのロックオン状態
		int		iCoreFrameNo;		// コアとなるフレーム番号
};
