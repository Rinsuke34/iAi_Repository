/* 2025.01.24 駒沢風助 ファイル作成 */
/* 2025.02.20 菊池雅道 近接攻撃(弱)処理追加・修正 */
/* 2025.03.13 駒沢風助 弾パリィ作成 */

#include "BulletPlayerMeleeWeak.h"

/* 近接攻撃(弱)クラスの定義 */

// コンストラクタ
BulletPlayerMeleeWeak::BulletPlayerMeleeWeak() : BulletBase()
{
	/* "プレイヤー状態"を取得 */
	this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* "オブジェクト管理"を取得 */
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* "エフェクト管理"を取得 */
	this->EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));

	/* プレイヤー取得 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();

	/* 初期化 */
	this->iObjectType		= OBJECT_TYPE_MELEE_PLAYER;	// オブジェクトの種類を"近接攻撃(プレイヤー)"に設定
	this->pMeleeWeakEffect	= nullptr;						// 近接攻撃(弱)エフェクトのハンドル
	ArrengementPositionPlayerFront();						// 座標設定(プレイヤーの前方に設定)

	/* 仮追加 */
	iDeleteCount = 30;
}

// デストラクタ
BulletPlayerMeleeWeak::~BulletPlayerMeleeWeak()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
	this->pMeleeWeakEffect->SetDeleteFlg(true);
}

/* 2025.02.20 菊池雅道 近接攻撃(弱)処理修正 開始 */
// 初期化
void BulletPlayerMeleeWeak::Initialization()
{
	/* 当たり判定設定 */
	{
		/* 当たり判定の位置を設定 */
		this->stCollisionSqhere.vecSqhere		= this->vecPosition;
		/* 当たり判定の範囲を設定 */
		this->stCollisionSqhere.fSqhereRadius	= PLAYER_MELEE_WEAK_RADIUS;
	}

	/* エフェクト追加 */
	{
		/* 近接攻撃(弱)のエフェクトを生成 */
		this->pMeleeWeakEffect = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pMeleeWeakEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_slash/FX_slash")));

		/* エフェクトの座標設定(プレイヤーの座標に設定) */
		this->pMeleeWeakEffect->SetPosition(VGet(this->pCharacterPlayer->vecGetPosition().x, this->pCharacterPlayer->vecGetPosition().y + PLAYER_HEIGHT / 2,this->pCharacterPlayer->vecGetPosition().z));

		/* エフェクトの回転量設定 */
		this->pMeleeWeakEffect->SetRotation(this->vecRotation);

		/* エフェクトの初期化 */
		this->pMeleeWeakEffect->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->pMeleeWeakEffect);
		}
	}
}
/* 2025.02.20 菊池雅道 近接攻撃(弱)処理修正 終了 */

/* 2025.02.20 菊池雅道 近接攻撃(弱)処理修正 開始 */
/* 2025.03.13 駒沢風助 弾パリィ作成			開始 */
// 更新
void BulletPlayerMeleeWeak::Update()
{
	/* 弾パリィ処理 */
	for (auto& bullet : this->ObjectList->GetBulletList())
	{
		/* パリィフラグが有効であるか確認 */
		if (bullet->bGetParryFlg() == true)
		{
			// パリィフラグが有効である場合
			/* 接触しているか確認 */
			if (bullet->HitCheck(this->stCollisionSqhere) == true)
			{
				// 接触している場合
				/* カウンターフラグが有効であるか確認 */
				if (this->PlayerStatusList->bGetAddCounter() == true)
				{
					// 有効である場合
					/* パリィフラグを無効に設定 */
					bullet->SetParryFlg(false);

					/* オブジェクトタイプを弾(プレイヤー)に変更 */
					bullet->SetObjectType(OBJECT_TYPE_BULLET_PLAYER);

					/* 対象オブジェクトの移動方向を取得 */
					VECTOR vecMoveDirection = bullet->vecGetMoveDirection();

					/* 移動方向を反転 */
					vecMoveDirection = VScale(vecMoveDirection, -1);

					/* 移動方向を設定 */
					bullet->SetDirection(vecMoveDirection);

					/* ダメージ発生時エフェクトを描写 */
					{
						/* 被ダメージの瞬間に発生するエフェクトを追加 */
						EffectSelfDelete* pDamageEffect = new EffectSelfDelete();

						/* 座標を設定 */
						pDamageEffect->SetPosition(this->vecPosition);

						/* エフェクトを取得 */
						pDamageEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_damaged/FX_damaged"));

						/* 拡大率を設定 */
						pDamageEffect->SetScale(VGet(1.f, 1.f, 1.f));

						/* 削除カウントを設定 */
						pDamageEffect->SetDeleteCount(60);

						/* エフェクト初期化処理 */
						pDamageEffect->Initialization();

						/* オブジェクトリストに登録 */
						this->ObjectList->SetEffect(pDamageEffect);
					}

					/* 攻撃ヒットのSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_SLASH_HIT);
				}
				else
				{
					// 無効である場合
					/* 削除フラグを有効にする */
					bullet->SetDeleteFlg(true);

					/* 攻撃吸収のSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_ABSORB);
				}
			}
		}
	}

	/* 仮処理 */
	// 本来はプレイヤー側で削除フラグを設定する予定
	if (iDeleteCount > 0)
	{
		iDeleteCount--;
	}
	else
	{
		this->bDeleteFlg = true;
	}

	/* 座標更新(プレイヤーの前方に設定) */ 
	ArrengementPositionPlayerFront();
	
	/* エフェクトの座標を更新(プレイヤーの座標に設定) */
	this->pMeleeWeakEffect->SetPosition((VGet(this->pCharacterPlayer->vecGetPosition().x, this->pCharacterPlayer->vecGetPosition().y + PLAYER_HEIGHT / 2, this->pCharacterPlayer->vecGetPosition().z)));

	/* エフェクトの回転量設定(プレイヤーの向きに設定) */
	this->pMeleeWeakEffect->SetRotation(VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* 当たり判定の位置を更新 */
	this->stCollisionSqhere.vecSqhere = this->vecPosition;
}
/* 2025.02.20 菊池雅道 近接攻撃(弱)処理修正 終了 */
/* 2025.03.13 駒沢風助 弾パリィ作成			終了*/

/* 2025.02.20 菊池雅道 近接攻撃(弱)処理追加 開始 */
// バレットの位置をプレイヤーの前方に設定する
void BulletPlayerMeleeWeak::ArrengementPositionPlayerFront()
{
	/* プレイヤーモデルの初期の向きがZ軸に対してマイナス方向を向いているとする */
	VECTOR vecMeleeWeakVector = { 0,0,-1 };
	
	/* プレイヤーの角度からY軸の回転行列を求める */
	MATRIX matPlayerRotation = MGetRotY(-(this->PlayerStatusList->fGetPlayerAngleX()));
	
	/* プレイヤーの前の位置ベクトルを求める */
	vecMeleeWeakVector = VTransform(vecMeleeWeakVector, matPlayerRotation);
	vecMeleeWeakVector = VNorm(vecMeleeWeakVector);
	vecMeleeWeakVector = VScale(vecMeleeWeakVector, PLAYER_MELEE_WEAK_DISTANCE);
	vecMeleeWeakVector.y = PLAYER_HEIGHT / 2;
	
	/* バレット座標を設定 */
	this->vecPosition = VAdd(this->pCharacterPlayer->vecGetPosition(), vecMeleeWeakVector);
}
/* 2025.02.20 菊池雅道 近接攻撃(弱)処理追加 開始 */
