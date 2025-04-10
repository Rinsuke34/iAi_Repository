/* 2025.03.19 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "SpawnPoint_Base.h"
#include "GimmickDisappear.h"

/* 消失ギミックスポナークラスの宣言 */

// 消失ギミックスポナークラス
class GimmickDisappearSpawnPoint : public SpawnPoint_Base
{
public:
	GimmickDisappearSpawnPoint();						// コンストラクタ
	virtual ~GimmickDisappearSpawnPoint() {};			// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

	/* 関数 */
	void	SetAddobjectFlg(bool bAddObjectFlg) { this->bAddObjectFlg = bAddObjectFlg; }	// オブジェクト生成フラグの設定

private:

	/* 変数 */
	bool	bAddObjectFlg;								// オブジェクト生成中フラグ
	int		iRespawnDelay;								//リスポーンカウント
};
