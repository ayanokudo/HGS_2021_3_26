//=============================================================================
//
// タイトル処理 [title.h]
// Author : 後藤慎之助
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//************************************************
// ヘッダファイルのインクルード
//************************************************
#include "main.h"
#include "mode.h"

//================================================
// マクロ定義
//================================================

// タイトルの管理フレーム
#define TITLE_NEXT_SCENE 150  // STARTを押したとき、次のシーンに行くかタイトルロゴを下すかの境目の時間
#define TITLE_MAX_TIME 1000   // タイトルのカウンタの最大時間

//================================================
// クラス宣言
//================================================
class CTitle : public CMode
{
public:
    CTitle();
    ~CTitle();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);

private:
    int m_nCntTime;     // スタートを押すまでの時間
    bool m_bNextScene;  // 次のシーンに行けるかどうか
};

#endif