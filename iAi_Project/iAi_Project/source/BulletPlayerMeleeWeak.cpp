/* 2025.01.24 駒沢風助 ファイル作成 */
/* 2025.02.20 菊池雅道 近接攻撃(弱)処理追加・修正 */

#include "BulletPlayerMeleeWeak.h"

/* 近接攻撃(弱)クラスの定義 */

// コンストラクタ
BulletPlayerMeleeWeak::BulletPlayerMeleeWeak() : BulletBase()
{
	/* "プレイヤー状態"を取得 */
	this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* プレイヤー取得 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();

	/* 初期化 */
	this->iObjectType	= OBJECT_TYPE_BULLET_PLAYER;	// オブジェクトの種類を"弾(プレイヤー)"に設定
	this->pMeleeWeakEffect = nullptr;						// 近接攻撃(弱)エフェクトのハンドル
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
// 更新
void BulletPlayerMeleeWeak::Update()
{
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
