/* 2024.12.15 駒沢風助	ファイル作成 */
/* 2025.01.27 菊池雅道	エフェクト処理追加 */
/* 2025.01.30 菊池雅道	モーション処理追加 */
/* 2025.02.05 菊池雅道	ステータス関連修正 */
/* 2025.02.14 菊池雅道	回転関連の関数追加 */
/* 2025.02.14 菊池雅道	クナイ関連の処理追加 */
/* 2025.02.19 菊池雅道	エフェクト処理追加 */
/* 2025.02.22 菊池雅道	壁キック処理追加 */
/* 2025.02.26 菊池雅道	クールタイムの処理追加 */
/* 2025.03.02 駒沢風助	落下復帰処理作成 */
/* 2025.03.06 菊池雅道	当たり判定処理修正 */
/* 2025.03.08 駒沢風助	新モデル対応 */
/* 2025.03.11 菊池雅道	モーション関連の処理追加 */

#include "CharacterPlayer.h"

/* プレイヤークラスの定義 */
// コンストラクタ
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* 初期化 */
	{
		/* オブジェクトのハンドル */
		this->pBulletMeleeWeak	=	nullptr;	// 近接攻撃(弱)の弾
		this->pBulletKunaiEffect =	nullptr;	// クナイ(エフェクト)の弾	/* 2025.02.14 菊池雅道	クナイ関連の処理追加 */


		/* エフェクトのハンドル */
		this->pChargeEffect			=	nullptr;		//溜めエフェクト			/* 2025.01.27 菊池雅道	エフェクト処理追加 */
		this->pChargeHoldEffect		=	nullptr;		//溜め完了後エフェクト		/* 2025.01.27 菊池雅道	エフェクト処理追加 */
		this->pDodgeEffect			=	nullptr;		//回避エフェクト			/* 2025.01.27 菊池雅道	エフェクト処理追加 */
	

		/* 変数 */
		this->vecMove					= VGet(0.f, 0.f, 0.f);	// 移動量
		this->vecNormalSum				= VGet(0.f, 0.f, 0.f);	// プレイヤーに接触するオブジェクトの法線ベクトルの合計		/* 2025.02.22 菊池雅道	壁キック処理追加 */
		this->iObjectType				= OBJECT_TYPE_PLAYER;	// オブジェクトの種類
		this->iMeleeWeakCoolTime		= 0;					// 近接攻撃(弱)クールタイム									/* 2025.02.26 菊池雅道	クールタイムの処理追加 */
		this->iProjectileCoolTime		= 0;					// 遠距離攻撃クールタイム									/* 2025.02.26 菊池雅道	クールタイムの処理追加 */
		this->iDodgeCoolTime			= 0;					// 回避クールタイム											/* 2025.02.26 菊池雅道	クールタイムの処理追加 */

		/* 変数(デバッグ用) */
		this->stVerticalCollision								= {};				// 垂直方向のコリジョン
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP]	= {};				// 水平方向コリジョン(上側)
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN]	= {};				// 水平方向コリジョン(下側)
		this->stMeleeStrongMoveCollsion							= {};				// 近接攻撃(強)のコリジョン(移動後の座標)
		this->vecMoveSize										= VGet(0, 0, 0);	// 移動量
		this->iFallingFrame										= 0;				// 落下状態になってからのフレーム数		/* 2025.03.11 菊池雅道 モーション関連の処理追加 */
	}

	/* データリスト取得 */
	{
		/* "入力管理"を取得 */
		this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

		/* "オブジェクト管理"を取得 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "エフェクトリソース管理"を取得 */
		this->EffectList		= dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));

		/* "ステージ状態管理"を取得 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));;
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Player/Player");

		/* コリジョンフレーム番号取得 */
		/* 刀のフレーム */
		this->iKatanaFrameNo		= MV1SearchFrame(this->iModelHandle, "Katana_Waist_Hips");		/* 2025.02.19 菊池雅道	追加 */

		/* 2025.03.13 駒沢風助 新モデル追加 開始 */
		/* 刀のフレーム番号 */
		this->iKatanaFrameNo_Waist		= MV1SearchFrame(this->iModelHandle, "Katana_Waist");		// 刀のフレーム番号(背面)
		this->iKatanaFrameNo_RightHand	= MV1SearchFrame(this->iModelHandle, "Katana_RightHand");	// 刀のフレーム番号(右手)
		/* 2025.03.13 駒沢風助 新モデル追加 終了 */

		/* 上半身のフレーム番号取得 */
		this->iUpperBodyFrameNo		= MV1SearchFrame(this->iModelHandle, "Character1_Spine");		/* 2025.03.08 駒沢風助 新モデル対応 */
		
		/* クナイを持つ手のフレーム */
		this->iKunaiHandFrameNo		= MV1SearchFrame(this->iModelHandle, "Kunai");					/* 2025.03.10 菊池雅道	追加 */
	}
}

// 初期化
void CharacterPlayer::Initialization()
{
	CharacterBase::Initialization();

	/* コリジョンを更新 */
	CollisionUpdate();
}

// リセット処理
void CharacterPlayer::Reset()
{
	/* 座標、回転量、拡大率を初期値に設定 */
	this->vecPosition	= this->vecPosition_Initial;
	this->vecScale		= this->vecScale_Initial;
	this->vecRotation	= this->vecRotation_Initial;
}

// 更新
void CharacterPlayer::Update()
{
	/* 毎フレーム実施する初期化処理 */
	{
		/* 移動量をリセット */
		this->vecMove = VGet(0, 0, 0);

		/* カメラモードを"フリーモード"に変更 */
		this->StageStatusList->SetCameraMode(CAMERA_MODE_NORMAL);
	}

	/* 当たり判定処理 */
	PlayerHitCheck();

	/* 2025.03.02 駒沢風助 落下復帰処理作成 開始 */
	/* プレイヤーが落下したか確認 */
	if (PlayerStatusList->bGetFallFlg() == true)
	{
		// 落下している場合
		/* 落下復帰処理 */
		PlayerFallRecovery();
	}
	/* 2025.03.02 駒沢風助 落下復帰処理作成 終了 */

	/* プレイヤーの現在HPが0以下(死亡状態)であるか確認 */
	if (this->PlayerStatusList->iGetPlayerNowHp() <= 0)
	{
		// HPが0以下(死亡状態)である場合
		/* プレイヤーの状態を"死亡"にする */
		this->PlayerStatusList->SetPlayerMoveState(PLYAER_MOVESTATUS_DEAD);
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_DEAD);

		/* プレイヤーのモーションを"死亡"に設定 */
		this->PlayerStatusList->SetPlayerMotion_Move(MOTION_ID_MOVE_DIE);
		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
	}

	/* 攻撃系アクション処理 */
	{
		/* 攻撃状態遷移管理 */
		// ※プレイヤーの入力に応じて攻撃状態を遷移
		Player_Attack_Transition();
	}

	/* 平行方向(X軸)移動処理 */
	{
		/* 移動処理 */
		Player_Move();

		/* 回避処理 */
		Player_Dodg();

		/* 移動処理(水平方向) */
		Movement_Horizontal();
	}

	/* 上下方向(Y軸)移動処理 */
	{
		/* ジャンプ処理 */
		Player_Jump();

		/* 重力処理 */
		Player_Gravity();

		/* 移動処理(垂直方向) */
		Movement_Vertical();
	}

	/* コリジョンを更新 */
	CollisionUpdate();

	/* モーション遷移管理 */
	Player_Motion_Transition();

	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* クールタイムの更新 */
	UpdateCooldownTime();
}

// コリジョン更新
void CharacterPlayer::CollisionUpdate()
{
	/* プレイヤーのコリジョンを更新 */
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT - PLAYER_WIDE, 0));
	this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, PLAYER_WIDE, 0));
	this->stCollisionCapsule.fCapsuleRadius		= PLAYER_WIDE;
}

/* 2025.02.05 菊池雅道	ステータス関連修正 開始 */
/* 2025.02.19 菊池雅道	エフェクト処理追加 開始 */
/* 2025.03.06 菊池雅道	当たり判定処理修正 開始 */
/* 当たり判定処理 */
void CharacterPlayer::PlayerHitCheck()
{
	/* プレイヤーの状態を取得 */
	/* 移動状態 */
	int iPlayerMoveState	= this->PlayerStatusList->iGetPlayerMoveState();
	/* 攻撃状態 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* プレイヤーが被弾処理を行うか(無敵か)判定するフラグ */
	bool bHiteFlag = true;

	/* 無敵時間中であるか確認 */
	if (this->PlayerStatusList->iGetPlayerNowInvincibleTime() > 0)
	{
		// 無敵時間中である場合
		/* 無敵時間を減少 */
		this->PlayerStatusList->SetPlayerNowInvincibleTime(this->PlayerStatusList->iGetPlayerNowInvincibleTime() - 1);
	}
	else
	{
		// 無敵時間中でない場合
		/* プレイヤーの移動状態が被弾処理を受ける状態か確認 */
		switch (iPlayerMoveState)
		{
			/* 被弾処理を行う状態 */
			case PLAYER_MOVESTATUS_FREE:			// 自由状態	
				/* 被弾処理を行う状態 */
				bHiteFlag = true;	
				break;

			/* 被弾処理を行わない状態(無敵状態) */
			case PLAYER_MOVESTATUS_EVENT:				// イベント状態(操作不可)
			case PLAYER_MOVESTATUS_DODGING:				// 回避状態中
			case PLYAER_MOVESTATUS_DEAD:				// 死亡状態(操作不可)

				/* 被弾処理を行わない(無敵状態) */
				bHiteFlag = false;
					
				break;
		}
		/* プレイヤーの攻撃状態が被弾処理を受ける状態か確認 */
		switch (iPlayerAttackState)
		{
			/* 被弾処理を行う状態 */			
			case PLAYER_ATTACKSTATUS_FREE:					// 自由状態	
			case PLAYER_ATTACKSTATUS_MELEE_POSTURE:			// 近接攻撃構え中
			case PLAYER_ATTACKSTATUS_MELEE_WEEK:			// 近接攻撃中(弱)	
			case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
			case PLAYER_ATTACKSTATUS_PROJECTILE:			// 遠距離攻撃中

				/* 被弾処理を行う */
				bHiteFlag = true;
				
				break;
	
			/* 被弾処理を行わない状態(無敵状態) */
			case PLAYER_ATTACKSTATUS_EVENT:					// イベント状態(操作不可)
			case PLAYER_ATTACKSTATUS_MELEE_STRONG:			// 近接攻撃中(強)
			case PLAYER_ATTACKSTATUS_DEAD:					// 死亡状態(操作不可)

				/* 被弾処理を行わない(無敵状態) */
				bHiteFlag = false;

				break;
			
		}
	
		/* 被弾処理 */
		/* 被弾処理を行う状態か確認する */
		if(bHiteFlag == true)
		{
			/* バレットリストを取得 */
			auto& BulletList = ObjectList->GetBulletList();

			/* 弾との当たり判定 */
			for (auto* bullet : BulletList)
			{
				/* オブジェクトタイプが弾丸(敵)であるなら判定を行う */
				if (bullet->iGetObjectType() == OBJECT_TYPE_BULLET_ENEMY)
				{
					// 弾丸(敵)である場合
					/* 弾丸との当たり判定 */
					if (bullet->HitCheck(this->stCollisionCapsule))
					{
						// 当たっている場合
						/* プレイヤーのHPを減少 */
						this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerNowHp() - 1);

						/* 被ダメージカウントを加算する */
						this->PlayerStatusList->SetPlayerDamageCount(this->PlayerStatusList->iGetPlayerDamageCount() + 1);

						/* プレイヤーの無敵時間を設定 */
						this->PlayerStatusList->SetPlayerNowInvincibleTime(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());

						/* 弾の削除フラグを有効にする */
						bullet->SetDeleteFlg(true);

						/* 被ダメージのSEを再生 */
						gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE);

						/* 被ダメージボイスを再生 */
						gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_DAMAGE);

						/* 被ダメージのエフェクトを生成 */
						{
							/* ダメージ発生時エフェクト */
							{
								/* 被ダメージの瞬間に発生するエフェクトを追加 */
								EffectSelfDelete* pDamageEffect = new EffectSelfDelete();

								/* 座標を設定 */
								pDamageEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2, 0)));

								/* エフェクトを取得 */
								pDamageEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_damaged/FX_damaged"));

								/* 拡大率を設定 */
								pDamageEffect->SetScale(VGet(1.f, 1.f, 1.f));

								/* 削除カウントを設定 */
								// ※仮で1秒間
								pDamageEffect->SetDeleteCount(60);

								/* エフェクト初期化処理 */
								pDamageEffect->Initialization();

								/* オブジェクトリストに登録 */
								this->ObjectList->SetEffect(pDamageEffect);
							}
							
							/* 感電エフェクト */
							{
								/* 感電エフェクトを生成 */
								EffectSelfDelete_PlayerFollow* pShockEffect = new EffectSelfDelete_PlayerFollow(false);

								/* 感電エフェクトの読み込み */
								pShockEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_eshock/FX_eshock")));

								/* 感電エフェクトの初期化 */
								pShockEffect->Initialization();

								/* 感電エフェクトの時間を設定 */
								pShockEffect->SetDeleteCount(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());

								/* 感電エフェクトをリストに登録 */
								this->ObjectList->SetEffect(pShockEffect);
							}
							
							/* 画面エフェクト(被ダメージ)作成 */
							this->StageStatusList->SetScreenEffect(new ScreenEffect_Damage());
						}
					}
				}
			}
		}
	}
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
/* 2025.02.19 菊池雅道	エフェクト処理追加 終了 */
/* 2025.03.06 菊池雅道	当たり判定処理修正 終了 */

/* 2025.02.14 菊池雅道	回転関連の関数追加 開始 */
// 角度(ラジアン)の制限と補正
void CharacterPlayer::RadianLimitAdjustment(float& fRadian)
{
	// 角度(ラジアン)が一周の範囲(0~2π)を超えた場合、補正を行う
	/* 2πを超えた場合 */
	if (fRadian > PLAYER_TURN_LIMIT)
	{
		/* 角度を一周(2π)分補正する */
		fRadian -= PLAYER_TURN_LIMIT;
	}
	/* 0を下回った場合 */
	else if (fRadian < 0)
	{
		/* 角度を一周(2π)分補正する */
		fRadian += PLAYER_TURN_LIMIT;
	}
}
/* 2025.02.14 菊池雅道	回転関連の関数追加 終了 */

/* 2025.02.26 菊池雅道	クールタイムの処理追加 */
//クールタイムの更新
void CharacterPlayer::UpdateCooldownTime()
{
	/* クールタイムを更新する共通関数 */ 
	auto UpdateCooldownTime = [](int& iCooldownTime) 
	{
		/* クールタイムが残っているか確認 */ 
		if (iCooldownTime > 0)
		{
			// クールタイムが残っている場合
			/* クールタイムを減少 */
			iCooldownTime--;
		}
	};

	/* 近接攻撃(弱)のクールタイム更新 */
	UpdateCooldownTime(this->iMeleeWeakCoolTime);
	/* 遠距離攻撃のクールタイム更新 */
	UpdateCooldownTime(this->iProjectileCoolTime);
	/* 回避のクールタイム更新 */
	UpdateCooldownTime(this->iDodgeCoolTime);
}
/* 2025.02.26 菊池雅道	クールタイムの処理追加 */

/* 2025.03.02 駒沢風助 落下復帰処理作成 開始 */
// 落下からの復帰
void CharacterPlayer::PlayerFallRecovery()
{
	/* 最も近い復帰地点の座標 */
	VECTOR	vecCloseRecoveryPoint	= VGet(0.f, 0.f, 0.f);	// 座標
	float	fCloseDistance			= 0.f;					// 距離
	bool	bFastFlg				= true;					// 最初の確認フラグ

	/* 現在の座標から最も近い復帰地点を取得 */
	for (auto& vecRecoveryPoint : this->StageStatusList->vecGetFallRecoveryPointList())
	{
		/* 復帰地点と現在の座標の距離を取得 */
		// ※距離の2乗を取得
		float fDistance = VSize(VSub(vecRecoveryPoint, this->vecPosition));

		/* 現在設定されている復帰地点よりも距離が短いか、あるいは最初の確認であるか確認 */
		if ((fDistance < fCloseDistance) || (bFastFlg == true))
		{
			// 距離が短い、あるいは最初の確認である場合
			/* 最も近い復帰地点を更新 */
			vecCloseRecoveryPoint = vecRecoveryPoint;

			/* 最も近い復帰地点の距離を更新 */
			fCloseDistance = fDistance;
		}

		/* 最初の確認フラグを無効にする */
		bFastFlg = false;
	}

	/* プレイヤーの座標を最も近い復帰地点に設定 */
	this->vecPosition = vecCloseRecoveryPoint;

	/* プレイヤーのHPを-1する */
	this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerNowHp() - 1);

	/* 落下フラグを無効にする */
	this->PlayerStatusList->SetFallFlg(false);
}
/* 2025.03.02 駒沢風助 落下復帰処理作成 終了 */