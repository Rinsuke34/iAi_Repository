/* 2025.01.30 駒沢風助 ファイル作成 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "SoundDefine.h"

/* サウンド管理データリストの宣言 */

// サウンド管理データリスト
class DataList_Sound : public DataListBase
{
	public:
		DataList_Sound();				// コンストラクタ
		virtual ~DataList_Sound();		// デストラクタ

		/* BGM系 */
		void BGM_SetHandle(int iBgmNo);			// BGMを設定
		void BGM_DeleteHandle();				// BGMを削除
		void BGM_PlaySound();					// BGMを再生
		void BGM_VolumeChange();				// BGMを音量変更
		void BGM_StopSound();					// BGMを停止

		/* SE系 */
		//void SE_AllSetHandle();					// 全てのサウンドハンドルを取得

	private:
		/* BGM関係 */
		// ※BGMは再生するタイミングで読み込みを行う
		int iBgmVolume;								// BGMの音量(0 ～ 255)
		int iBgmHandle;								// BGMのハンドル

		/* SE関係 */
		int iSeVolum;								// SEの音量(0 ～ 255)
		std::map<std::string, int>	pSeHandleList;	// サウンドハンドルリスト
};
