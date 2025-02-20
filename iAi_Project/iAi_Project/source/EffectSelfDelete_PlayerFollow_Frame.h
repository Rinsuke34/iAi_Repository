/* 2025.02.19 菊池雅道 ファイル作成 */

#pragma once
#include "EffectSelfDelete.h"

/* データリスト */
#include "DataList_Object.h"
#include "PlayerStatusDefine.h"

/* 時間経過で削除されるエフェクトクラスの宣言 */
// ※プレイヤーのフレームに自動追従

// エフェクトクラス(自動削除/プレイヤーフレーム追従)
class EffectSelfDelete_PlayerFollow_Frame : public EffectSelfDelete
{
public:
	EffectSelfDelete_PlayerFollow_Frame(int iFrameHandle);		// コンストラクタ
	virtual ~EffectSelfDelete_PlayerFollow_Frame() {};			// デストラクタ

	void	Update()	override;	// 更新

private:
	/* 追従対象のプレイヤークラス */
	CharacterBase* pCharacterPlayer;

	/* 変数 */
	int iFrameHandle;	// フレームハンドル
	int iModelHandle;	// モデルハンドル
};
#pragma once
