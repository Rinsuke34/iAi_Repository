/* 2025.03.13 菊池雅道 ファイル作成 */
/* 2025.03.17 菊池雅道 ワープ処理修正 */
/* 2025.03.27 菊池雅道 ワープ処理修正 */
/* 2025.12.13 菊池雅道	コードリファクタリング */

#include "BulletPlayerKunaiWarp.h"

/* クナイ(ワープ)クラスの定義 */

// コンストラクタ
BulletPlayerKunaiWarp::BulletPlayerKunaiWarp() : BulletPlayerKunai()
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
	auto& PlatformList = ObjectList->GetPlatformList();

	// 射線上にプラットフォームが存在するか確認する
	for (auto& platform : PlatformList)
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
	float fHeightDifference = this->vecKunaiTargetPosition.y - this->vecPosition.y;
	/* X - Z 平面上の距離を計算 */
	float fHorizontalDistance = VSize(VGet(this->vecKunaiTargetPosition.x - this->vecPosition.x, 0, this->vecKunaiTargetPosition.z - this->vecPosition.z));

	/* X軸の回転角度を求める（ラジアン単位） */
	fKunaiAngleX = atan2f(fHeightDifference, fHorizontalDistance);

	/* モデルのY軸回転の計算(X-Z 平面上の方向) */
	fKunaiAngleY = atan2f(this->vecKunaiTargetPosition.x - this->vecPosition.x, this->vecKunaiTargetPosition.z - this->vecPosition.z);
}

// 描画
void BulletPlayerKunaiWarp::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転(元のモデルの向き + 標的の向きの分回転させる) */
	MV1SetRotationXYZ(this->iModelHandle, VGet(fKunaiAngleX, DEG2RAD(KUNAI_MODEL_ROTATION) + fKunaiAngleY, 0.0f));

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}

// 更新
void BulletPlayerKunaiWarp::Update()
{
	/* クナイの移動ベクトルをスケールして移動 */
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecKunaiMoveDirection, WARP_KUNAI_SPEED));;

	/* クナイの移動距離を加算 */
	this->fKunaiMoveDistance += WARP_KUNAI_SPEED;

	/* クナイの移動距離がターゲットまでの距離を超えたら */
	if (this->fKunaiMoveDistance >= this->fKunaiTargetDistance)
	{
		/* ワープ処理を行う */
		this->Warp();
	}
}

/* 2025.03.17 菊池雅道 ワープ処理修正 開始 */
/* 2025.03.27 菊池雅道 ワープ処理修正 開始 */
// ワープ処理
void BulletPlayerKunaiWarp:: Warp()
{
	if (this->pTargetEnemy != nullptr)
	{
		// ターゲットエネミーが存在する場合
		Warp_ToTargetEnemy();
	}
	else
	{
		// ターゲットエネミーが存在しない場合
		WarpToKunaiHitPosition();
	}

	// クナイ攻撃後の削除処理
	HandleKunaiDeleteAfterAttack();
}
/* 2025.03.17 菊池雅道 ワープ処理修正 終了 */
/* 2025.03.27 菊池雅道 ワープ処理修正 終了 */


/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
void BulletPlayerKunaiWarp::Warp_ToTargetEnemy()
{
	/* クナイの座標をターゲット座標に固定 */
	this->vecPosition = pTargetEnemy->vecGetPosition();

	/* モデルを非表示に設定 */
	MV1SetVisible(this->iModelHandle, false);

	/* クナイの攻撃フラグが立っていないか確認 */
	if (this->bKunaiAttackFlg == true)
	{
		return;
	}

	/* エネミー後方へワープする処理 */
	WarpPlayerBehindEnemy();

	/* プレイヤー状態の後処理（敵あり）*/
	FinalizePlayerStateAfterWarp();

	/* クナイ攻撃用当たり判定設定 */
	SetupKunaiAttackCollision();

	/* クナイの攻撃フラグを設定 */
	this->bKunaiAttackFlg = true;

	/* ワープ演出 */
	PlayWarpEffect();
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// エネミー後方へワープする処理
void BulletPlayerKunaiWarp::WarpPlayerBehindEnemy()
{
	/* エネミーの角度からY軸の回転行列を求める */
	MATRIX matEnemyRotation = MGetRotY(pTargetEnemy->vecGetRotation().y);

	/* エネミーの向きベクトル */
	VECTOR vecEnemyDirection = VTransform(VGet(0, 0, 1), matEnemyRotation);
	vecEnemyDirection = VNorm(vecEnemyDirection);

	/* エネミーの向きの角度(ラジアン)を取得 */
	float fEnemyRotate = -atan2f(vecEnemyDirection.x, vecEnemyDirection.z);

	/* プレイヤーの向きを敵と逆に設定 */
	this->PlayerStatusList->SetPlayerAngleX(fEnemyRotate - PI);

	/* プレイヤーのワープ位置を敵の後ろに設定 */
	VECTOR vecPlayerWarpPosition = VScale(vecEnemyDirection, KUNAI_WARP_POSITION_Z_OFFSET);

	/* プラットフォームに応じたワープ位置調整処理 */
	AdjustWarpPositionForPlatform(pTargetEnemy->vecGetPosition(), vecPlayerWarpPosition);

	/* プレイヤーの座標をワープ位置に設定 */
	this->ObjectList->GetCharacterPlayer()->SetPosition(vecPlayerWarpPosition);
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */


/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// プラットフォームに応じたワープ位置調整処理
void BulletPlayerKunaiWarp::AdjustWarpPositionForPlatform(const VECTOR& vecEnemyPos,VECTOR& vecWarpOffset)
{

	/* プレイヤーの足場を判定する線分 */
	COLLISION_LINE stCollisionLine;

	/* 足場を取得 */
	auto& PlatformList = ObjectList->GetPlatformList();

	/* ワープ後のプレイヤーの頂点から下方向へ向けた線分を作成 */
	stCollisionLine.vecLineStart = vecWarpOffset;
	stCollisionLine.vecLineStart.y += PLAYER_HEIGHT;
	stCollisionLine.vecLineEnd = stCollisionLine.vecLineStart;
	stCollisionLine.vecLineEnd.y -= PLAYER_HEIGHT + PLAYER_CLIMBED_HEIGHT;

	/* 足場と接触するか確認 */
	for (auto& platform : PlatformList)
	{
		/* 足場と線分の接触判定を行う */
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stCollisionLine);

		/* 接触しているか確認 */
		if (stHitPolyDim.HitFlag == 1)
		{
			// 接触している場合
			/* 敵の後ろにワープする */
			vecWarpOffset = VAdd(vecEnemyPos, vecWarpOffset);
		}
		else
		{
			// 接触していない場合
			/* 敵の位置にワープする */
			vecWarpOffset = vecEnemyPos;
		}
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// プレイヤー状態の後処理（敵あり）
void BulletPlayerKunaiWarp::FinalizePlayerStateAfterWarp()
{
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
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// ワープクナイ用当たり判定設定
// 壁などに当たった場合に、設定範囲の中で足場を探してワープするための当たり判定
void BulletPlayerKunaiWarp::SetupKunaiAttackCollision()
{
	this->stCollisionSqhere.vecSqhere = pTargetEnemy->vecGetPosition();
	this->stCollisionSqhere.fSqhereRadius = KUNAI_WARP_RADIUS;
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// 敵なしワープ処理
void BulletPlayerKunaiWarp::WarpToKunaiHitPosition()
{
	/* クナイの進行方向を正規化 */
	VECTOR vecWarpOffset = VNorm(vecKunaiMoveDirection);
	/* 高さ成分は除く */
	vecWarpOffset.y = 0;

	/* プレイヤーのワープ位置(着弾地点からプレイヤーの幅分ずらす) */
	VECTOR vecPlayerWarpPosition = VAdd(this->vecKunaiTargetPosition, VScale(vecWarpOffset, -PLAYER_WIDE));
	
	/* エネミー無し時のワープ位置調整処理 */
	AdjustWarpPositionWithoutEnemy(vecPlayerWarpPosition);

	/* エネミー無し時のプレイヤー状態の後処理 */
	FinalizePlayerStateWithoutEnemy();

	/* エフェクト再生 */
	PlayWarpEffect();

	/* クナイの削除フラグを設定 */
	this->bDeleteFlg = true;
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// エネミー無し時のワープ位置調整処理
void BulletPlayerKunaiWarp::AdjustWarpPositionWithoutEnemy(VECTOR& vecWarpPosition)
{
	/* プレイヤーの足場を判定する線分 */
	COLLISION_LINE stCollisionLine;

	/* 足場を取得 */
	auto& PlatformList = ObjectList->GetPlatformList();

	/* ワープ後のプレイヤーの頂点から下方向へ向けた線分を作成 */
	stCollisionLine.vecLineStart = vecWarpPosition;
	stCollisionLine.vecLineStart.y += PLAYER_HEIGHT;
	stCollisionLine.vecLineEnd = stCollisionLine.vecLineStart;
	stCollisionLine.vecLineEnd.y -= PLAYER_HEIGHT + PLAYER_CLIMBED_HEIGHT;

	/* 足場と接触するか確認 */
	for (auto& platform : PlatformList)
	{
		/* 足場と線分の接触判定を行う */
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stCollisionLine);

		/* 接触しているか確認 */
		if (stHitPolyDim.HitFlag == 1)
		{
			// 接触している場合
			/* クナイの座標をターゲット座標に固定 */
			this->vecPosition = this->vecKunaiTargetPosition;
			this->ObjectList->GetCharacterPlayer()->SetPosition(this->vecPosition);
		}
		else
		{
			// 接触していない場合
			// 近くに足場があったら移動する
			SearchNearbyPlatform(vecWarpPosition);
			this->ObjectList->GetCharacterPlayer()->SetPosition(vecWarpPosition);
		}
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// 足場探索（敵なし）
void BulletPlayerKunaiWarp::SearchNearbyPlatform(VECTOR& vecWarpPosition)
{
	/* 足場を探すカプセルコリジョン */
	COLLISION_CAPSULE stSearchPlatform;

	/* コリジョンの大きさを設定 */
	stSearchPlatform.vecCapsuleTop =VAdd(this->vecKunaiTargetPosition, VGet(0.f, PLAYER_HEIGHT * KUNAI_WARP_ADJUST_HEIGHT, 0.f));
	stSearchPlatform.vecCapsuleBottom = vecKunaiTargetPosition;
	stSearchPlatform.fCapsuleRadius = PLAYER_WIDE;

	/* 足場を探す */
	auto& PlatformList = ObjectList->GetPlatformList();
	for (auto& platform : PlatformList)
	{
		/* 足場とコリジョンの接触判定を行う */
		MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(stSearchPlatform);

		// 接触している場合
						/* 接触したポリゴンから法線ベクトルを取得する */
		for (int j = 0; j < stHitPolyDim.HitNum; j++)
		{
			/* 法線ベクトルを取得 */
			/* 法線ベクトルが上向きであるか確認 */
			if (VSize(stHitPolyDim.Dim[j].Normal) > 0.f && stHitPolyDim.Dim[j].Normal.y > 0.1f)
			{ 
				// 上向きである場合
				/* 足場に乗るようにプレイヤーのワープ位置を設定 */
				vecWarpPosition =VAdd(this->vecKunaiTargetPosition,VScale(VNorm(vecKunaiMoveDirection), PLAYER_WIDE));

				/* 足場の高さにする */
				vecWarpPosition.y = stHitPolyDim.Dim[j].Position[0].y;
			}
		}
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// プレイヤー状態の後処理(敵なし)
void BulletPlayerKunaiWarp::FinalizePlayerStateWithoutEnemy()
{
	/* プレイヤーの攻撃状態を取得 */
	int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

	/* プレイヤーの攻撃状態が遠距離攻撃構え状態であるか確認 */
	if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
	{
		// 遠距離攻撃構え状態である場合	
		/* プレイヤーの攻撃状態を"自由状態"に遷移 */
		this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
		/* プレイヤーのモーションを"なし"に変更 */
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
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// ワープ演出再生
void BulletPlayerKunaiWarp::PlayWarpEffect()
{
	/* SE再生 */
	gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

	/* ワープエフェクト再生 */
	auto pWarpEffect = std::make_shared<EffectSelfDelete_PlayerFollow>(true);
	pWarpEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_charge_finish/FX_charge_finish"));
	pWarpEffect->Initialization();
	pWarpEffect->SetDeleteCount(PLAYER_WARP_EFFECT_FRAME);
	pWarpEffect->SetPosition(vecPosition);
	this->ObjectList->SetEffect(pWarpEffect);
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */

/* 2025.12.13 菊池雅道	コードリファクタリング 開始 */
// クナイ攻撃後の削除処理
void BulletPlayerKunaiWarp::HandleKunaiDeleteAfterAttack()
{
	/* クナイの攻撃フラグが無効な場合は処理を抜ける */
	if (this->bKunaiAttackFlg == false)
	{
		return;
	}

	/* クナイの削除カウントを確認 */
	if (iKunaiDeleteCount > 0)
	{
		/* クナイの削除カウント(攻撃時間)が残っていた場合 */
		// 削除カウントを減らす
		iKunaiDeleteCount--;
	}
	else
	{
		// 削除カウントが0になった場合
		/* クナイの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}
}
/* 2025.12.13 菊池雅道	コードリファクタリング 終了 */