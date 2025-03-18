/* 2024.12.15 駒沢風助 ファイル作成 */
/* 2025.01.09 菊池雅道 回避関連の関数追加 */
/* 2025.01.22 菊池雅道 攻撃関連の関数追加 */
/* 2025.01.27 菊池雅道 エフェクト関連の変数追加 */
/* 2025.02.06 菊池雅道 エフェクト関連修正 */
/* 2025.02.14 菊池雅道 回転関連の関数追加 */
/* 2025.02.14 菊池雅道 クナイ関連の変数追加 */
/* 2025.02.19 菊池雅道 フレーム関連の変数追加 */
/* 2025.02.22 菊池雅道 壁キック関連の変数追加 */
/* 2025.02.26 菊池雅道 クールタイム関連の関数・変数追加 */
/* 2025.03.08 駒沢風助 新モデル対応 */
/* 2025.03.11 菊池雅道 モーション関連の変数追加 */
/* 2025.03.13 菊池雅道 クナイ関連の変数追加 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"
#include "DataList_Model.h"
#include "DataList_Effect.h"
#include "DataList_StageStatus.h"

/* オブジェクト */
#include "BulletPlayerMeleeWeak.h"
#include "BulletPlayerMeleeStrong.h"
#include "BulletPlayerKunaiAttack.h"
#include "BulletPlayerKunaiWarp.h"
#include "EffectSelfDelete.h"
#include "EffectSelfDelete_PlayerFollow.h"
#include "EffectManualDelete_PlayerFollow.h"
#include "EffectManualDelete_PlayerFollow_Frame.h"
#include "EffectSelfDelete_PlayerFollow_Frame.h"
#include "PlayerBulletDefine.h"
#include "Gimmick_CheckPoint.h"

/* 画像エフェクト */
#include "ScreenEffect_Damage.h"
#include "ScreenEffect_SlowMotion.h"
#include "ScreenEffect_ConcentrationLine.h"

/* 循環参照対策の先行定義 */
class ScreenEffect_Damage;
class ScreenEffect_SlowMotion;
class ScreenEffect_ConcentrationLine;
class Gimmick_CheckPoint;

/* プレイヤークラスの宣言 */

// プレイヤークラス
class CharacterPlayer : public CharacterBase
{
	public:
		CharacterPlayer();				// コンストラクタ
		virtual ~CharacterPlayer() {};	// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Draw()				override;		// 描写
		virtual void	CollisionDraw()		override;		// 当たり判定描写
		virtual void	Reset()				override;		// リセット処理

	private:
		/* 使用するデータリスト */
		// 毎回データリストサーバーから取得するのは非効率なため、ここで保存しておく
		DataList_Input*			InputList;			// 入力管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_Effect*		EffectList;			// エフェクトリソース管理
		DataList_StageStatus*	StageStatusList;	// ステージ状態リスト

		/* 関数 */
		void	CollisionUpdate();						// コリジョン更新
		void	PlayerHitCheck();						// 当たり判定処理
		void	RadianLimitAdjustment(float& fRadian);	// 角度(ラジアン)の制限と補正	/* 2025.02.13 菊池雅道 回転関連の関数追加 */
		void	UpdateCooldownTime();					// クールタイムの更新			/* 2025.02.26 菊池雅道 クールタイム関連の関数追加 */
		void	PlayerFallRecovery();					// 落下からの復帰				/* 2025.03.02 駒沢風助 落下復帰処理作成 */
		void	FastMotion();							// ゲーム開始時のモーション
		void	MotionReset();							// モーション初期化

		// 移動アクション
		void	Player_Jump();				// ジャンプ
		void	Player_Gravity();			// 重力処理
		void	Player_Move();				// 移動
		void	Player_Dodg();				// 回避 2025.01.09 菊池雅道 関数追加
		void	Movement_Vertical();		// 移動処理(垂直方向)
		void	Movement_Horizontal();		// 移動処理(水平方向)

		// 攻撃アクション
		void	Player_Attack_Transition();			// 攻撃状態遷移管理
		void	Player_Melee_Posture();				// 近接攻撃(構え)
		void	Player_Melee_Weak();				// 近接攻撃(弱)
		void	Player_Charge_Attack();				// プレイヤー溜め攻撃　2025.01.22 菊池雅道 関数追加  
		void	Player_Projectile_Posture();		// 遠距離攻撃(構え)
		void	Player_Projectile();				// 遠距離攻撃

		// モーション関連
		void	Player_Motion_Transition();			// モーション遷移管理　2025.01.30 菊池雅道 関数追加 

		// シェイプ関連
		void	Player_Shape();						// シェイプ処理

		/* オブジェクトのハンドル */
		// ※プレイヤー側から削除タイミングを指定するためにハンドルを所持
		BulletPlayerMeleeWeak*		pBulletMeleeWeak;	// 近接攻撃(弱)の弾
		BulletPlayerKunaiWarp* 		pBulletKunaiWarp;			// クナイ(ワープ)の弾			/* 2025.03.13 菊池雅道 クナイ関連の変数追加 */
		BulletPlayerKunaiAttack*	pBulletKunaiAttack;			// クナイ(攻撃)の弾				/* 2025.03.13 菊池雅道 クナイ関連の変数追加 */

		/* エフェクトのハンドル */
		EffectManualDelete_PlayerFollow_Frame*	pChargeEffect;			//溜めエフェクト		/* 2025.01.27 菊池雅道 エフェクト関連の変数追加 */	/* 2025.02.06 菊池雅道 エフェクト関連修正 */
		EffectManualDelete_PlayerFollow_Frame*	pChargeHoldEffect;		//溜め完了後エフェクト	/* 2025.01.27 菊池雅道 エフェクト関連の変数追加 */	/* 2025.02.06 菊池雅道 エフェクト関連修正 */
		EffectManualDelete_PlayerFollow*		pDodgeEffect;			//回避エフェクト		/* 2025.01.27 菊池雅道 エフェクト関連の変数追加 */	/* 2025.02.06 菊池雅道 エフェクト関連修正 */

		/* フレーム番号 */
		int		iKatanaFrameNo;				// 刀のフレーム番号								/* 2025.02.19 菊池雅道 フレーム関連の変数追加 */
		int		iKatanaFrameNo_Waist;		// 刀のフレーム番号(背面)						/* 2025.03.13 駒沢風助 新モデル対応 */
		int		iKatanaFrameNo_RightHand;	// 刀のフレーム番号(右手)						/* 2025.03.13 駒沢風助 新モデル対応 */
		int		iUpperBodyFrameNo;			// 上半身のフレーム番号							/* 2025.03.08 駒沢風助 新モデル対応 */
		int		iKunaiHandFrameNo;			// クナイを持つ手のフレーム番号					/* 2025.03.10 菊池雅道 フレーム関連の変数追加 */

		/* シェイプ関連 */
		int		iShapeNo_Blink;				// シェイプ番号(瞬き)
		float	fShapeRate;					// シェイプ適用率

		/* 変数 */
		VECTOR				vecMove;				// 移動量
		VECTOR				vecNormalSum;			// プレイヤーに接触するオブジェクトの法線ベクトルの合計			/* 2025.02.22 菊池雅道 壁キック関連の変数追加 */

		/* 変数(デバッグ用) */
		COLLISION_LINE		stVerticalCollision;			// 垂直方向のコリジョン
		COLLISION_CAPSULE	stHorizontalCollision[2];		// 水平方向コリジョン(0:上側, 1:下側)
		COLLISION_CAPSULE	stMeleeStrongMoveCollsion;		// 近接攻撃(強)のコリジョン(移動後の座標)
		VECTOR				vecMoveSize;					// 移動量(デバッグ用)		<- ※この変数がないとパッケージ化する際にキーボードでの移動の不具合が発生する(駒沢)
		int					iFallingFrame;					// 落下状態になってからのフレーム数(意図しないモーション切り替えを防止するために使用)		/* 2025.03.11 菊池雅道 モーション関連の変数追加 */

		/* クールタイム関連 */
		int		iMeleeWeakCoolTime;		// 近接攻撃(弱)クールタイム		/* 2025.02.26 菊池雅道 クールタイム関連の変数追加 */
		int		iProjectileCoolTime;	// 遠距離攻撃クールタイム		/* 2025.02.26 菊池雅道 クールタイム関連の変数追加 */
		int		iDodgeCoolTime;			// 回避クールタイム				/* 2025.02.26 菊池雅道 クールタイム関連の変数追加 */
};
