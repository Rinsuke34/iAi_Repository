/* 2025.01.24 駒沢風助 ファイル作成 */

#include "BulletPlayerMeleeWeak.h"

/* 近接攻撃(弱)クラスの定義 */

// コンストラクタ
BulletPlayerMeleeWeak::BulletPlayerMeleeWeak() : BulletBase()
{
	/* 初期化 */
	this->iObjectType	= OBJECT_TYPE_BULLET_PLAYER;	// オブジェクトの種類を"弾(プレイヤー)"に設定
	this->pEffect		= nullptr;

	/* 仮追加 */
	iDeleteCount = 30;
}

// デストラクタ
BulletPlayerMeleeWeak::~BulletPlayerMeleeWeak()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
	this->pEffect->SetDeleteFlg(true);
}

// 初期化
void BulletPlayerMeleeWeak::Initialization()
{
	/* 当たり判定設定 */
	{
		this->stCollisionSqhere.vecSqhere		= this->vecPosition;
		this->stCollisionSqhere.fSqhereRadius	= 100.0f;
	}

	/* エフェクト追加 */
	{
		/* 近接攻撃(弱)のエフェクトを生成 */
		this->pEffect = new EffectManualDelete();

		/* エフェクトの読み込み */
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_slash/FX_slash")));
		//this->pEffect->Effect_Load("FX_slash/FX_slash");

		/* エフェクトの座標設定 */
		this->pEffect->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		this->pEffect->SetRotation(this->vecRotation);

		/* エフェクトの初期化 */
		this->pEffect->Initialization();

		/* エフェクトをリストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(this->pEffect);
		}
	}
}

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
}
