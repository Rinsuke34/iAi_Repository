/* 2025.02.19 菊池雅道 ファイル作成 */

#pragma once
#include "EffectManualDelete.h"

/* データリスト */
#include "DataList_Object.h"

/* 手動で削除タイミングを設定するエフェクトクラスの宣言 */
// ※プレイヤーモデルのフレームに自動追従

// エフェクトクラス(手動削除/プレイヤー追従)
class EffectManualDelete_PlayerFollow_Frame : public EffectManualDelete
{
public:
	EffectManualDelete_PlayerFollow_Frame(int iFrameHandle);		// コンストラクタ
	virtual ~EffectManualDelete_PlayerFollow_Frame() {};			// デストラクタ

	void	Update() override;	// 更新

private:
	/* 追従対象のプレイヤークラス */
	CharacterBase* pCharacterPlayer;

	/* 変数 */
	int iFrameHandle;	// フレームハンドル
	int iModelHandle;	// モデルハンドル
}; 
