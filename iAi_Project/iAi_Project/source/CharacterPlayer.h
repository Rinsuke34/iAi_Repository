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
/* 2025.03.17 菊池雅道 クールタイム関連の関数・変数追加 */
/* 2025.03.22 駒沢風助 落下時のカメラプレイヤー追従作成 */
/* 2025.03.25 駒沢風助 サウンド追加 */
/* 2025.07.19 菊池雅道 コードリファクタリング */
/* 2025.08.19 菊池雅道 コードリファクタリング */
/* 2025.10.15 菊池雅道 近距離攻撃(強)処理修正 */
/* 2025.11.23 菊池雅道 コードリファクタリング */
/* 2025.12.13 菊池雅道 コードリファクタリング */

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
#include "BulletPlayerKunaiExplosion.h"
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
		virtual ~CharacterPlayer();		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Draw()				override;		// 描写
		virtual void	CollisionDraw()		override;		// 当たり判定描写
		virtual void	BloomDraw()			override;		// 発光描写
		virtual void	Reset()				override;		// リセット処理

	private:
		/* 使用するデータリスト */
		// 毎回データリストサーバーから取得するのは非効率なため、ここで保存しておく
		std::shared_ptr<DataList_Input>			InputList;			// 入力管理
		std::shared_ptr<DataList_PlayerStatus>	PlayerStatusList;	// プレイヤー状態
		std::shared_ptr<DataList_Object>		ObjectList;			// オブジェクト管理
		std::shared_ptr<DataList_Effect>		EffectList;			// エフェクトリソース管理
		std::shared_ptr<DataList_StageStatus>	StageStatusList;	// ステージ状態リスト

		/* 関数 */
		void	CollisionUpdate();																	// コリジョン更新
		void	PlayerHitCheck();																	// 当たり判定処理
		void	RadianLimitAdjustment(float& fRadian);												// 角度(ラジアン)の制限と補正		/* 2025.02.13 菊池雅道 回転関連の関数追加 */
		void	AngleIterpolation(float vecInputX,float vecInputZ,float &fAngleX);					// 向き変化時の補間					/* 2025.08.19 菊池雅道 コードリファクタリング */
		void	UpdateCooldownTime();																// クールタイムの更新				/* 2025.02.26 菊池雅道 クールタイム関連の関数追加 */
		void	PlayerFallRecovery();																// 落下からの復帰					/* 2025.03.02 駒沢風助 落下復帰処理作成 */
		void	FastMotion();																		// ゲーム開始時のモーション
		void	MotionReset();																		// モーション初期化
		void	StartMotionSet();																	// 開始時のモーション設定
		void	CreateScreenEffectLine();															// 画面集中線エフェクト生成処理		2025.12.13 菊池雅道 関数追加

		// 移動アクション
		void	Player_Jump();									// ジャンプ
		void	Player_Gravity();								// 重力処理
		void	Player_Move();									// 移動
		void	Player_Dodg();									// 回避 2025.01.09 菊池雅道 関数追加
		void	Movement_Vertical();							// 移動処理(垂直方向)
		void	Movement_Horizontal();							// 移動処理(水平方向)
		void	Player_WallKick_Movement_Vertical();			// 壁キック処理(垂直方向)
		void	Player_WallKick_Movement_Horizontal();			// 壁キック処理(水平方向)	

		// 攻撃アクション
		void	Player_Attack_Transition();								// 攻撃状態遷移管理
		void	Player_Attack_Free();									// 自由状態							2025.07.19 菊池雅道 関数追加 
		void	Player_Melee_Posture();									// 近接攻撃(構え)
		void	Player_Melee_Weak();									// 近接攻撃(弱)
		void	Player_Charge_Attack();									// プレイヤー溜め攻撃				2025.01.22 菊池雅道 関数追加  
		void	Player_Projectile_Posture();							// 遠距離攻撃(構え)
		void	Player_Projectile();									// 遠距離攻撃
		
		// 移動関連関数
		void				SetupMoveStateByStatus(int iPlayerMoveState, int iPlayerAttackState, float& fMoveSpeedRatio, bool& bPlayerAngleSetFlg, bool& bPlayerMoveFlg);														// 移動状態・攻撃状態に応じた移動制御設定	2025.12.13 菊池雅道 関数追加
		bool				bIsMoveInput(const VECTOR& vecInput) const;																																							// 移動入力があるかの判定					2025.12.13 菊池雅道 関数追加
		VECTOR				vecCalculateMove(const VECTOR& vecInput, float fMoveSpeedRatio, float fEditAddSpeed, bool bPlayerAngleSetFlg);																						// 移動量計算処理							2025.12.13 菊池雅道 関数追加
		void				HandleNoMoveInput();																																												// 移動入力が無い場合の処理					2025.12.13 菊池雅道 関数追加
		bool				bIsJumpableState();																																													// ジャンプ可能状態の判定					2025.12.13 菊池雅道 関数追加
		bool				bCanExecuteJump();																																													// ジャンプ実行条件判定処理					2025.12.13 菊池雅道 関数追加
		void				HandleAfterWallKickJumpInput();																																										// 壁キック後のジャンプ入力処理				2025.12.13 菊池雅道 関数追加
		void				ExecuteJump();																																														// ジャンプ処理								2025.12.13 菊池雅道 関数追加
		void				CreateAirJumpEffectIfNeeded();																																										// 空中ジャンプエフェクト生成処理			2025.12.13 菊池雅道 関数追加
		void				HandleKickWallStopOnHit();																																											// 壁キック中の停止処理処理					2025.12.13 菊池雅道 関数追加
		void				AddNormalSumForPushOut(MV1_COLL_RESULT_POLY_DIM& stHitPolyDimNormal, VECTOR& vecNormalSum);																											// 押し出し用法線ベクトル加算処理			2025.12.13 菊池雅道 関数追加
		void				AddNormalSumForWallKick(MV1_COLL_RESULT_POLY_DIM& stHitPolyDim);																																	// 壁キック用法線ベクトル加算処理			2025.12.13 菊池雅道 関数追加
		void				HandleWallKickInput();																																												// 壁キック入力処理							2025.12.13 菊池雅道 関数追加
		void				JudgeWallKickTime();																																												// 壁キック猶予時間判定処理					2025.12.13 菊池雅道 関数追加
		void				ResolveHorizontalPlatformCollision(const std::vector<std::shared_ptr<PlatformBase>>& PlatformList, const COLLISION_CAPSULE& stNormalCollision, VECTOR& vecNormalSum, VECTOR& vecNextPosition);		// 水平移動の衝突解決処理					2025.12.13 菊池雅道 関数追加	
		COLLISION_CAPSULE	stCreateNormalCollision() const;																																									// 法線取得用カプセルの生成処理				2025.12.13 菊池雅道 関数追加
		void				PushOutPlayerByNormal(const std::shared_ptr<PlatformBase>& platform, const VECTOR& vecNormalSum, VECTOR& vecNextPosition);																			// プレイヤー押し出し処理					2025.12.13 菊池雅道 関数追加
		void				SetupHorizontalMoveCollision(const VECTOR& vecNextPosition);																																		// 水平方向移動用コリジョン設定処理			2025.12.13 菊池雅道 関数追加
		VECTOR				vecGetNextHorizontalPosition() const;																																								// 移動後の座標取得(水平方向)				2025.12.13 菊池雅道 関数追加
		bool				bIsDodgeExecutable();																																												// 回避実行可能判定処理						2025.12.13 菊池雅道 関数追加
		bool				bCanStartDodge();																																													// 回避開始条件判定処理						2025.12.13 菊池雅道 関数追加
		void				UpdateDodging();																																													// 回避中の更新処理							2025.12.13 菊池雅道 関数追加
		void				EndDodge();																																															// 回避終了処理								2025.12.13 菊池雅道 関数追加
		void				StartDodge();																																														// 回避開始処理								2025.12.13 菊池雅道 関数追加
		void				SetDodgeDirection();																																												// 回避方向設定処理							2025.12.13 菊池雅道 関数追加
		void				CreateDodgeEffect();																																												// 回避エフェクト生成処理					2025.12.13 菊池雅道 関数追加
		bool				bIsGravityExecutable();																																												// 重力処理実行可能判定処理					2025.12.13 菊池雅道 関数追加
		void				ApplyGravity();																																														// 重力適用処理								2025.12.13 菊池雅道 関数追加
		VECTOR				vecGetNextVerticalPosition() const;																																									// 移動後の座標取得(垂直方向)				2025.12.13 菊池雅道 関数追加
		void				SetupVerticalCollisionLine();																																										// 垂直方向コリジョンライン設定				2025.12.13 菊池雅道 関数追加
		void				ResolveVerticalPlatformCollision(VECTOR& vecNextPosition, float& fStandPosY);																														// 垂直方向の足場判定と着地処理				2025.12.13 菊池雅道 関数追加
		void				HandleLandingEvent(bool bPrevJumpingFlg);																																							// 着地時のSE・エフェクト処理				2025.12.13 菊池雅道 関数追加
		void				UpdateAirMotion();																																													// 空中モーション更新処理					2025.12.13 菊池雅道 関数追加
		
		// 攻撃関連関数
		void	Player_Projectile_Posture_Cancel();																		// 遠距離攻撃(構え)キャンセル処理					2025.07.19 菊池雅道 関数追加
		void	Player_Charge_Attack_RockOn();																			// 近距離攻撃(強)ロックオン処理						2025.10.15 菊池雅道 関数追加
		bool	bHandleAfterStrongKill(int iAfterCount, int iAfterContinueMax, int iChargeMax);							// 連続溜め攻撃の処理判定							2025.11.23 菊池雅道 関数追加
		bool	bHandleAirStrongLimit(int iAirCount);																	// 空中連続溜め攻撃の制限判定						2025.11.23 菊池雅道 関数追加
		bool	bHandleAfterStrongKillAttackTransition(int iAfterCount, int iAfterContinueMax, int iChargeMax);			// 近接攻撃(強)で敵を倒した後の遷移処理				2025.11.23 菊池雅道 関数追加
		void	HandleChargeToStrongAttack(int iNowCharge, int iChangeFrame, int IChargeMax);							// 近接攻撃(強)への切り替わり処理（チャージ到達時）	2025.11.23 菊池雅道 関数追加
		void	ProcessCharge(int iNowCharge, int iChargeMax);															// 溜め処理											2025.11.23 菊池雅道 関数追加
		void	ApplyChargeMovement();																					// 溜め攻撃移動量適用処理							2025.11.23 菊池雅道 関数追加
		void	OnChargeComplete(); 																					// 溜め完了時の処理									2025.11.23 菊池雅道 関数追加
		void	CreateChargeEffect();																					// 溜めエフェクト生成処理							2025.11.23 菊池雅道 関数追加
		void	DeleteChargeEffect();																					// 溜め関連エフェクト削除処理						2025.11.23 菊池雅道 関数追加
		void	HandleRockOnDuringCharge(int iNowCharge, int iChangeFrame);												// 溜め中のロックオン処理							2025.11.23 菊池雅道 関数追加
		void	HandleAttackRelease(int iNowAttakChargeFlame, int iMeleeStrongChangeFrame, int iMeleeChargeMaxFlame);	// 攻撃入力リリース時の処理							2025.11.23 菊池雅道 関数追加
		void	CleanupEffectsIfPostureEnded();																			// 構え終了時のエフェクト削除処理					2025.11.23 菊池雅道 関数追加
		void	HandleChargeAttackStart();																				// 溜め攻撃開始時の処理								2025.12.13 菊池雅道 関数追加
		void	PlayChargeAttackSounds();																				// 溜め攻撃音声再生処理								2025.12.13 菊池雅道 関数追加
		void	HandleAirStrongAttackCount();																			// 空中連続溜め攻撃回数管理処理						2025.12.13 菊池雅道 関数追加
		void	SetupChargeAttackTargetPosition();																		// 溜め攻撃ターゲット設定処理						2025.12.13 菊池雅道 関数追加
		void	AdjustMoveForPlatformLanding(VECTOR& vecMoveDirection);													// 近距離攻撃(強)に伴うプレイヤー落下防止処理		2025.12.13 菊池雅道 関数追加
		void	HandleChargeAttackMove(int iChargeCount);																// 溜め攻撃中の移動処理								2025.12.13 菊池雅道 関数追加
		void	FinishChargeAttack(const VECTOR& vecMoveDirection, float fMove, float fMoveSpeed, int iMoveCount);		// 溜め攻撃終了処理									2025.12.13 菊池雅道 関数追加
		void	CreateChargeAttackBullet();																				// 近距離攻撃(強)攻撃判定生成						2025.12.13 菊池雅道 関数追加
		void	CreateChargeAttackEffect();																				// 近距離攻撃(強)エフェクト生成						2025.12.13 菊池雅道 関数追加
		void	HandleContinuousChargeSearch();																			// 連続溜め攻撃の敵検索処理							2025.12.13 菊池雅道 関数追加
		void	Player_Continuous_Charge_Attack_Enemy_Search();															// 溜め攻撃後の敵検索								2025.07.19 菊池雅道 関数追加
		void	Player_Continuous_Charge_Attack_Enabled_Process();														// 連続溜め攻撃可能状態の処理						2025.07.19 菊池雅道 関数追加
		void	Player_Projectile_Posture_SlowMotion();																	// 遠距離攻撃(構え)スローモーション処理				2025.12.13 菊池雅道 関数追加
		void	Player_Projectile_Posture_SetMotion();																	// 遠距離攻撃(構え)モーション設定処理				2025.12.13 菊池雅道 関数追加
		bool	bPlayer_Projectile_Posture_AttackInput();																// 遠距離攻撃(構え)攻撃入力判定						2025.12.13 菊池雅道 関数追加
		void	Player_Projectile_Posture_CancelInput();																// 遠距離攻撃(構え)キャンセル入力処理				2025.12.13 菊池雅道 関数追加
		void	Player_SlowMotion_Stop();																				// スローモーション終了処理							2025.07.19 菊池雅道 関数追加
		
		// モーション関連
		void	Player_Motion_Transition();			// モーション遷移管理　2025.01.30 菊池雅道 関数追加 

		// シェイプ関連
		void	Player_Shape();						// シェイプ処理

		//スローモーション関連
		void	Player_UpdateSlowMotionCount();		// スローモーションカウント処理

		/* オブジェクトのハンドル */
		// ※プレイヤー側から削除タイミングを指定するためにハンドルを所持
		std::shared_ptr<BulletPlayerMeleeWeak>		pBulletMeleeWeak;			// 近接攻撃(弱)の弾
		std::shared_ptr<BulletPlayerKunaiWarp> 		pBulletKunaiWarp;			// クナイ(ワープ)の弾			/* 2025.03.13 菊池雅道 クナイ関連の変数追加 */
		std::shared_ptr<BulletPlayerKunaiExplosion>	pBulletKunaiExplosion;		// クナイ(攻撃)の弾				/* 2025.03.13 菊池雅道 クナイ関連の変数追加 */

		/* エフェクトのハンドル */
		std::shared_ptr<EffectManualDelete_PlayerFollow_Frame>	pChargeEffect;			//溜めエフェクト		/* 2025.01.27 菊池雅道 エフェクト関連の変数追加 */	/* 2025.02.06 菊池雅道 エフェクト関連修正 */
		std::shared_ptr<EffectManualDelete_PlayerFollow_Frame>	pChargeHoldEffect;		//溜め完了後エフェクト	/* 2025.01.27 菊池雅道 エフェクト関連の変数追加 */	/* 2025.02.06 菊池雅道 エフェクト関連修正 */
		std::shared_ptr<EffectManualDelete_PlayerFollow>		pDodgeEffect;			//回避エフェクト		/* 2025.01.27 菊池雅道 エフェクト関連の変数追加 */	/* 2025.02.06 菊池雅道 エフェクト関連修正 */

		/* フレーム番号 */
		int		iKatanaFrameNo;				// 刀のフレーム番号								/* 2025.02.19 菊池雅道 フレーム関連の変数追加 */
		int		iKatanaFrameNo_Waist;		// 刀のフレーム番号(背面)						/* 2025.03.13 駒沢風助 新モデル対応 */
		int		iKatanaFrameNo_RightHand;	// 刀のフレーム番号(右手)						/* 2025.03.13 駒沢風助 新モデル対応 */
		int		iUpperBodyFrameNo;			// 上半身のフレーム番号							/* 2025.03.08 駒沢風助 新モデル対応 */
		int		iKunaiHandFrameNo;			// クナイを持つ手のフレーム番号					/* 2025.03.10 菊池雅道 フレーム関連の変数追加 */
		int		iKunaiEffectFrameNo;		// クナイのエフェクトを出すフレーム番号			/* 2025.03.10 菊池雅道 フレーム関連の変数追加 */

		/* シェイプ関連 */
		int		iShapeNo_Blink;				// シェイプ番号(瞬き)
		float	fShapeRate;					// シェイプ適用率

		/* 変数 */
		VECTOR				vecMove;						// 移動量
		VECTOR				vecWallKickNormalSum;			// プレイヤーに接触するオブジェクトの法線ベクトルの合計			/* 2025.02.22 菊池雅道 壁キック関連の変数追加 */

		/* 変数(デバッグ用) */
		COLLISION_LINE		stVerticalCollision;			// 垂直方向のコリジョン
		COLLISION_CAPSULE	stHorizontalCollision[2];		// 水平方向コリジョン(0:上側, 1:下側)
		COLLISION_CAPSULE	stMeleeStrongMoveCollsion;		// 近接攻撃(強)のコリジョン(移動後の座標)
		int					iFallingFrame;					// 落下状態になってからのフレーム数(意図しないモーション切り替えを防止するために使用)		/* 2025.03.11 菊池雅道 モーション関連の変数追加 */

		/* クールタイム関連 */
		int		iMeleeWeakNowCoolTime;		// 近接攻撃(弱)クールタイム		/* 2025.02.26 菊池雅道 クールタイム関連の変数追加 */
		int		iProjectileNowCoolTime;		// 遠距離攻撃クールタイム		/* 2025.02.26 菊池雅道 クールタイム関連の変数追加 */
		int		iDodgeNowCoolTime;			// 回避クールタイム				/* 2025.02.26 菊池雅道 クールタイム関連の変数追加 */
		int		iJumpNowCoolTime;			// ジャンプクールタイム			/* 2025.03.17 菊池雅道 クールタイム関連の変数追加 */
		int		iFallRecoveryDelayTime;		// 落下時の復帰までの待機時間	/* 2025.03.22 駒沢風助 落下時のカメラプレイヤー追従作成 */

		/* サウンド関連 */
		bool	bPlayRunSound;			// サウンド"走る"が再生中であるか
		bool	bPlayChargeSound;		// サウンド"溜め居合チャージ"が再生中であるか
};
