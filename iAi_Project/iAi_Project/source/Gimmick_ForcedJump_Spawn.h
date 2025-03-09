/* 2025.02.12 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "GimmickDefine.h"

/* データリスト */
#include "DataList_Object.h"

/* オブジェクト */
#include "PickUpItem_ForcedJump.h"

/* 循環参照対策(後ほど対策は実施) */
class PickUpItem_ForcedJump;

/* 強制ジャンプギミックスポナークラスの宣言 */

// 強制ジャンプギミックスポナークラス
class Gimmick_ForcedJump_Spawn : public PlatformBase
{
	public:
		Gimmick_ForcedJump_Spawn();				// コンストラクタ
		virtual ~Gimmick_ForcedJump_Spawn();	// デストラクタ

		virtual void	Initialization()	override {};	// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Draw()				override {};	// 描写
		virtual void	BloomDraw()			override {};	// 発光描写
		virtual void	CollisionDraw()		override {};	// 当たり判定描写

		/* データ設定 */
		void SetSpawnObjectFlg(bool bSpawnObjectFlg) { this->bSpawnObjectFlg = bSpawnObjectFlg; };	// オブジェクトのスポーンフラグを設定

	private:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;	// オブジェクト管理

		/* 変数 */
		bool	bSpawnObjectFlg;		// オブジェクトのスポーンフラグ(有効なら生成)
		int		iSpawnCoolTime;			// スポーンのクールタイム	
};