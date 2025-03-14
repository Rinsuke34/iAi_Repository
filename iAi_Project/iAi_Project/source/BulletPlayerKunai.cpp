/* 2025.02.14 菊池雅道 ファイル作成 */

#include "BulletPlayerKunai.h"

/* クナイクラスの定義 */

// コンストラクタ
BulletPlayerKunai::BulletPlayerKunai() : BulletBase()
{
	/* 初期化 */
	this->iObjectType					= OBJECT_TYPE_BULLET_PLAYER;		// オブジェクトの種類を"弾(プレイヤー)"に設定
	this->vecKunaiTargetPosition		= VGet(0,0,0);						// ターゲット座標
	this->vecKunaiMoveDirection			= VGet(0, 0, 0);					// クナイの移動する方向
	this->fKunaiTargetDistance			= 0.0f;								// クナイの発射地点からターゲットまでの距離
	this->fKunaiMoveDistance			= 0.0f;								// クナイの移動距離
	this->fKunaiAngleX					= 0.0f;								// クナイのX軸回転角度
	this->fKunaiAngleY					= 0.0f;								// クナイのY軸回転角度
	this->iKunaiDeleteCount				= KUNAI_ATTACK_COUNT;				// クナイの削除カウント(攻撃時間)
	this->bKunaiAttackFlg				= false;							// クナイの攻撃フラグ

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Bullet/Kunai/Kunai");
	}

	/* データリスト取得 */
	{
		/* "入力管理"を取得 */
		this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		
		/* "プレイヤー状態管理"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ステージ状態管理"を管理 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "エフェクトリソース管理"を取得 */
		this->EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));
	}
}

// デストラクタ
BulletPlayerKunai::~BulletPlayerKunai()
{
	
}

// 初期化
void BulletPlayerKunai::Initialization()
{

}

// 描画
void BulletPlayerKunai::Draw()
{
	
}

// 更新
void BulletPlayerKunai::Update()
{
	
}
