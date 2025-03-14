/* 2025.03.13 菊池雅道 ファイル作成 */

#include "BulletPlayerKunaiWarp.h"

/* クナイ(ワープ)クラスの定義 */

// コンストラクタ
BulletPlayerKunaiWarp::BulletPlayerKunaiWarp()
{
	this->pTargetEnemy = nullptr;							// 敵管理
}

// デストラクタ
BulletPlayerKunaiWarp::~BulletPlayerKunaiWarp()
{

}

// 初期化
void BulletPlayerKunaiWarp::Initialization()
{
	/* クナイの生成地点からターゲットまでのベクトルをクナイの移動ベクトルに設定 */
	this->vecKunaiMoveDirection = VSub(this->vecKunaiTargetPosition, this->vecPosition);

	/* クナイの射線上を確認する線分コリジョンを設定 */
	COLLISION_LINE stCollisionLine;

	/* 射線の開始点を設定 */
	stCollisionLine.vecLineStart = this->StageStatusList->vecGetCameraPosition();

	/* 射線の終了点を設定 */
	stCollisionLine.vecLineEnd = this->vecKunaiTargetPosition;

	/* クナイ発射地点からターゲットの最小ベクトルを保持する */
	VECTOR vecMinDirection = VSub(this->vecKunaiTargetPosition, this->StageStatusList->vecGetCameraPosition());

	/* クナイ発射地点からターゲットの最小距離を保持する */
	float fMinDistance = VSize(vecMinDirection);

	/* プラットフォームを取得 */
	auto& PlatformList = ObjectList->GetCollisionList();

	// 射線上にプラットフォームが存在するか確認する
	for (auto* platform : PlatformList)
	{
		/* プラットフォームと接触しているか確認 */
		MV1_COLL_RESULT_POLY stHitPoly = platform->HitCheck_Line(stCollisionLine);

		/* 接触している場合 */
		if (stHitPoly.HitFlag == true)
		{
			/* クナイ発射地点から接触地点のベクトルを設定 */
			VECTOR vecDirection = VSub(stHitPoly.HitPosition, this->StageStatusList->vecGetCameraPosition());

			/* クナイ発射地点から接触地点の距離を設定 */
			float fDistance = VSize(vecDirection);

			/* クナイの射線上の最小距離を確認 */
			if (fMinDistance >= fDistance)
			{
				/* 接触した座標をターゲット座標に設定 */
				vecKunaiTargetPosition = stHitPoly.HitPosition;

				/* クナイの移動ベクトルを再設定 */
				this->vecKunaiMoveDirection = VSub(this->vecKunaiTargetPosition, this->vecPosition);

				/* クナイの射線上の最小距離を更新 */
				fMinDistance = fDistance;
			}
		}
	}

	/* クナイの移動距離を設定 */
	this->fKunaiTargetDistance = VSize(this->vecKunaiMoveDirection);

	/* クナイの移動ベクトルを正規化 */
	this->vecKunaiMoveDirection = VNorm(this->vecKunaiMoveDirection);

	/* モデルのX軸回転の計算 */
	/* 高さ(Y軸)の差 */
	float fHeightDiff = this->vecKunaiTargetPosition.y - this->vecPosition.y;
	/* X - Z 平面上の距離を計算 */
	float fHorizontalDist = VSize(VGet(this->vecKunaiTargetPosition.x - this->vecPosition.x, 0, this->vecKunaiTargetPosition.z - this->vecPosition.z));

	/* X軸の回転角度を求める（ラジアン単位） */
	fKunaiAngleX = atan2f(fHeightDiff, fHorizontalDist);

	/* モデルのY軸回転の計算(X-Z 平面上の方向) */
	fKunaiAngleY = atan2f(this->vecKunaiTargetPosition.x - this->vecPosition.x, this->vecKunaiTargetPosition.z - this->vecPosition.z);
}

// 描画
void BulletPlayerKunaiWarp::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転(元のモデルの向き + 標的の向きの分回転させる) */
	MV1SetRotationXYZ(this->iModelHandle, VGet(fKunaiAngleX, DEG2RAD(180.0f) + fKunaiAngleY, 0.0f));

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}

// 更新
void BulletPlayerKunaiWarp::Update()
{
	/* クナイの移動ベクトルをスケールして移動 */
	this->vecPosition = VAdd(this->vecPosition, VScale(vecKunaiMoveDirection, KUNAI_SPEED));;

	/* クナイの移動距離を加算 */
	this->fKunaiMoveDistance += KUNAI_SPEED;

	/* クナイの移動距離がターゲットまでの距離を超えたら */
	if (this->fKunaiMoveDistance >= this->fKunaiTargetDistance)
	{
		/* ワープ処理を行う */
		this->Warp();
	}
}

// ワープ処理
void BulletPlayerKunaiWarp:: Warp()
{
	/* ターゲットエネミーが存在するか確認 */
	if (this->pTargetEnemy != nullptr)
	{
		// ターゲットエネミーが存在する場合
		//敵の後ろにワープし、撃破する
		/* クナイの座標をターゲット座標に固定 */
		this->vecPosition = pTargetEnemy->vecGetPosition();

		/* モデルを非表示に設定 */
		MV1SetVisible(this->iModelHandle, false);

		/* クナイの攻撃フラグが立っていないか確認 */
		if (this->bKunaiAttackFlg == false)
		{
			/* エネミーの角度からY軸の回転行列を求める */
			MATRIX matEnemyrRotation = MGetRotY((pTargetEnemy->vecGetRotation().y));

			/* エネミーの向きのベクトル */
			VECTOR vecEnemyDirection = VGet(0, 0, 1);

			/* 行列をベクトルに変換 */
			vecEnemyDirection = VTransform(vecEnemyDirection, matEnemyrRotation);

			/* エネミーの向きを正規化 */
			vecEnemyDirection = VNorm(vecEnemyDirection);

			/* エネミーの向きの角度(ラジアン)を取得 */
			float fEnemyRotate = -atan2f(vecEnemyDirection.x, vecEnemyDirection.z);

			/* プレイヤーの向きを敵と逆に設定 */
			this->PlayerStatusList->SetPlayerAngleX(fEnemyRotate - PI);

			/* プレイヤーのワープ位置を敵の後ろに設定 */
			VECTOR vecPlayerWarpPotition = VScale(vecEnemyDirection, 250);
			vecPlayerWarpPotition = VAdd(pTargetEnemy->vecGetPosition(), vecPlayerWarpPotition);

			/* プレイヤーの座標をワープ位置に設定 */
			this->ObjectList->GetCharacterPlayer()->SetPosition(vecPlayerWarpPotition);

			/* プレイヤーの攻撃状態を取得 */
			int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

			/* プレイヤーの攻撃状態が遠距離攻撃構え状態であるか確認 */
			if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
			{
				// 遠距離攻撃構え状態である場合
				/* 遠距離攻撃構え状態をキャンセルする */
				this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			}

			/* プレイヤーの状態を"自由状態"に遷移 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

			/* プレイヤーのモーションを"近距離攻撃(強)(終了)"に変更 */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG_END);

			/* スローモーションフラグが有効であるか確認 */
			if (this->StageStatusList->bGetGameSlowFlg() == true)
			{
				// 有効である場合
				/* スローモーションフラグを無効化 */
				this->StageStatusList->SetGameSlowFlg(false);
			}

			/* 当たり判定設定 */
			{
				/* 敵の位置に当たり判定を設定 */
				this->stCollisionSqhere.vecSqhere = pTargetEnemy->vecGetPosition();

				/* 当たり判定の半径を設定 */
				this->stCollisionSqhere.fSqhereRadius = 50;
			}

			/* クナイの攻撃フラグを設定 */
			this->bKunaiAttackFlg = true;

			/* ワープのSEを再生 */
			gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

			/* ワープエフェクトを生成 */
			EffectSelfDelete_PlayerFollow* pWarpeEffect = new EffectSelfDelete_PlayerFollow(true);

			/* ワープエフェクトの読み込み */
			pWarpeEffect->SetEffectHandle((this->EffectList->iGetEffect("charge_finish/FX_charge_finish")));

			/* ワープエフェクトの初期化 */
			pWarpeEffect->Initialization();

			/* ワープエフェクトの時間を設定 */
			pWarpeEffect->SetDeleteCount(90);

			/* ワープエフェクトをリストに登録 */
			{
				/* ワープエフェクトをリストに登録 */
				this->ObjectList->SetEffect(pWarpeEffect);
			}
		}
	}
	else
	{
		// ターゲットエネミーが存在する場合
		// ターゲット座標にワープする
		/* クナイの座標をターゲット座標に固定 */
		this->vecPosition = this->vecKunaiTargetPosition;

		/* プレイヤーをクナイの座標に移動 */
		this->ObjectList->GetCharacterPlayer()->SetPosition(this->vecPosition);

		/* プレイヤーの攻撃状態を取得 */
		int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

		/* プレイヤーの攻撃状態が遠距離攻撃構え状態であるか確認 */
		if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
		{
			// 遠距離攻撃構え状態である場合
			/* プレイヤーの状態を"自由状態"に遷移 */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

			/* プレイヤーのモーションを無しに設定 */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

			/* 遠距離攻撃構え状態をキャンセルする */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
		}

		/* スローモーションフラグが有効であるか確認 */
		if (this->StageStatusList->bGetGameSlowFlg() == true)
		{
			// 有効である場合
			/* スローモーションフラグを無効化 */
			this->StageStatusList->SetGameSlowFlg(false);
		}

		/* ワープのSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

		/* ワープエフェクトを生成 */
		EffectSelfDelete* pWarpeEffect = new EffectSelfDelete();

		/* ワープエフェクトの読み込み */
		pWarpeEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_finish/FX_charge_finish")));

		/* ワープエフェクトの初期化 */
		pWarpeEffect->Initialization();

		/* ワープエフェクトの時間を設定 */
		pWarpeEffect->SetDeleteCount(60);

		/* ワープエフェクトの座標を設定 */
		pWarpeEffect->SetPosition(vecPosition);

		/* ワープエフェクトをリストに登録 */
		{
			/* ワープエフェクトをリストに登録 */
			this->ObjectList->SetEffect(pWarpeEffect);
		}

		/* クナイの削除フラグを設定 */
		this->bDeleteFlg = true;
	}

	/* クナイの攻撃フラグが立っているか確認 */
	if (this->bKunaiAttackFlg == true)
	{
		// クナイの攻撃フラグが立っている場合
		// クナイの削除処理
		/* クナイの削除カウント(攻撃時間)が残っていた場合 */
		if (iKunaiDeleteCount > 0)
		{
			/* クナイの削除カウント(攻撃時間)を減算 */
			iKunaiDeleteCount--;
		}
		/* クナイの削除カウント(攻撃時間)が0になった場合 */
		else
		{
			/* クナイの削除フラグを設定 */
			this->bDeleteFlg = true;
		}
	}
}
