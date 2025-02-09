/* 2024.12.15 駒沢風助	ファイル作成 */
/* 2025.01.27 菊池雅道	エフェクト処理追加 */
/* 2025.01.30 菊池雅道	モーション処理追加 */
/* 2025.02.05 菊池雅道	ステータス関連修正 */

#include "CharacterPlayer.h"

/* プレイヤークラスの定義 */
// コンストラクタ
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* 初期化 */
	{
		/* オブジェクトのハンドル */
		this->pBulletMeleeWeak	=	nullptr;	// 近接攻撃(弱)の弾

		/* 2025.01.27 菊池雅道	エフェクト処理追加 開始 */
		/* エフェクトのハンドル */
		this->pChargeEffect			=	nullptr;		//溜めエフェクト
		this->pChargeHoldEffect		=	nullptr;		//溜め完了後エフェクト
		this->pDodgeEffect			=	nullptr;		//回避エフェクト
		/* 2025.01.27 菊池雅道	エフェクト処理追加 終了 */

		/* 変数 */
		this->vecMove		= VGet(0.f, 0.f, 0.f);	// 移動量
		this->iObjectType	= OBJECT_TYPE_PLAYER;	// オブジェクトの種類

		/* 変数(デバッグ用) */
		this->stVerticalCollision								= {};		// 垂直方向のコリジョン
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_UP]	= {};		// 水平方向コリジョン(上側)
		this->stHorizontalCollision[PLAYER_MOVE_COLLISION_DOWN]	= {};		// 水平方向コリジョン(下側)
		this->stMeleeStrongMoveCollsion							= {};		// 近接攻撃(強)のコリジョン(移動後の座標)
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
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Player/Player");
	}

	/* モーションリストの設定 */
	{
		for (int i = 0; i < MOTION_ID_MAX; i++)
		{
			/* モーションIDを設定 */
			this->PlayerMotionList[i].iMotionID			= MOTION_LIST[i].iMotionID;

			/* モーション名を設定 */
			this->PlayerMotionList[i].strMotionName		= MOTION_LIST[i].strMotionName;

			/* モーションの総再生時間を取得＆設定 */
			this->PlayerMotionList[i].fMotion_MaxTime	= MV1GetAnimTotalTime(this->iModelHandle, this->PlayerMotionList[i].iMotionID);

			/* 次のモーションIDを設定 */
			this->PlayerMotionList[i].iNextMotionID		= MOTION_LIST[i].iNextMotionID;
		}
	}
}

// 初期化
void CharacterPlayer::Initialization()
{
	CharacterBase::Initialization();

	/* コリジョンを更新 */
	CollisionUpdate();

	/* カメラモードを"フリーモード"に変更 */
	this->PlayerStatusList->SetCameraMode(CAMERA_MODE_FREE);
}

// 更新
void CharacterPlayer::Update()
{
	/* カメラモードを"フリーモード"に変更 */
	this->PlayerStatusList->SetCameraMode(CAMERA_MODE_FREE);

	/* 接触確認 */
	{
		// ※攻撃やオブジェクトに対する当たり判定処理を行う
		/* 当たり判定処理 */
		HitCheck();
	}

	/* 毎フレームの初期化処理 */
	{
		/* 移動量をリセット */
		this->vecMove = VGet(0, 0, 0);

		/* ロックオン範囲コリジョン使用フラグを無効化 */
		this->PlayerStatusList->SetMeleeSearchCollisionUseFlg(false);
	}

	///* プレイヤーのモーション状態を保存する */
	//this->PlayerStatusList->SetPlayerMotion_Move_Old(this->PlayerStatusList->iGetPlayerMotion_Move());
	//this->PlayerStatusList->SetPlayerMotion_Attack_Old(this->PlayerStatusList->iGetPlayerMotion_Attack());

	/* 攻撃系アクション処理 */
	{
		/* 攻撃状態遷移管理 */
		// ※プレイヤーの入力に応じて攻撃状態を遷移
		Player_Attack_Transition();
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

	/* 平行方向(X軸)移動処理 */
	{
		/* 移動処理 */
		Player_Move();

		/* 回避処理 */
		Player_Dodg();

		/* 移動処理(水平方向) */
		Movement_Horizontal();
	}

	/* コリジョンを更新 */
	CollisionUpdate();
	
	/* モーション遷移管理 */
	Player_Motion_Transition();
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
/* 当たり判定処理 */
void CharacterPlayer::HitCheck()
{
	/* プレイヤーの移動状態を取得 */
	int iPlayerMoveState = this->PlayerStatusList->iGetPlayerMoveState();
	/* プレイヤーの攻撃状態を取得 */
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
		case PLAYER_MOVESTATUS_DODGING:				// 回避状態中
				
			/* 被弾処理を行わない(無敵状態) */
			bHiteFlag = true;
					
			break;
		}
		
		/* 被弾処理を受けるプレイヤーの攻撃状態か確認 */
		switch (iPlayerAttackState)
		{
			/* 被弾処理を行う状態 */
		case PLAYER_ATTACKSTATUS_FREE:				// 自由状態
		case PLAYER_ATTACKSTATUS_MELEE_POSTURE:		// 近接攻撃構え中
		case PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE:	// 遠距離攻撃構え中
		case PLAYER_ATTACKSTATUS_MELEE_STRONG:		// 近接攻撃中(強)
		case PLAYER_ATTACKSTATUS_PROJECTILE:			// 遠距離攻撃中
				
			/* 被弾処理を行う */
			bHiteFlag = true;

			break;

			/* 被弾処理を行わない状態(無敵状態) */
		case PLAYER_ATTACKSTATUS_MELEE_WEEK:			// 近接攻撃中(弱)
				
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

								/* プレイヤーの無敵時間を設定 */
								this->PlayerStatusList->SetPlayerNowInvincibleTime(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());

								/* 弾の削除フラグを有効にする */
								bullet->SetDeleteFlg(true);

								/* 被ダメージのSEを再生 */
								gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE);
							}
						}
					}
				}
	}
}
/* 2025.02.05 菊池雅道	ステータス関連修正 終了 */
