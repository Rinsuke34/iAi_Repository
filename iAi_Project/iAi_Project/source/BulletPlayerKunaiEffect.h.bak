/* 2025.02.14 菊池雅道 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"

/* オブジェクト */
#include "PlayerBulletDefine.h"
#include "DataList_Object.h"

/* 定数 */
#include "PublicInclude.h"

/* クナイ(エフェクト)クラスの宣言 */

// クナイ(エフェクト)
class BulletPlayerKunaiEffect : public BulletBase
{
public:
	BulletPlayerKunaiEffect();				// コンストラクタ
	virtual ~BulletPlayerKunaiEffect();		// デストラクタ

	virtual void	Initialization()	override;	// 初期化
	virtual void	Update()			override;	// 更新
	virtual void	Draw()				override;	// 描画	

	void	Attack();								// 攻撃処理

	VECTOR	GetKunaiTargetPosition()							{ return this->vecKunaiTargetPosition; }					// クナイのターゲット座標を取得

	void	SetKunaiTargetPosition(VECTOR vecTargetPosition)	{ this->vecKunaiTargetPosition = vecTargetPosition; }		// クナイのターゲット座標を設定

private:
	VECTOR	vecKunaiTargetPosition;			// ターゲット座標
	VECTOR	vecKunaiMoveDirection;			// クナイの移動する方向
	float	fKunaiTargetDistance;			// クナイの発射地点からターゲットまでの距離
	float	fKunaiMoveDistance;				// クナイの移動距離
	float	fKunaiAngleX;					// クナイのX軸回転角度
	float	fKunaiAngleY;					// クナイのY軸回転角度
	int		iKunaiDeleteCount;				// クナイの削除カウント
	bool	bKunaiAttackFlg;				// クナイの攻撃フラグ

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理

protected:
};

