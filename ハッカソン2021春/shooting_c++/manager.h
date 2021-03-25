//====================================================================
//
// �����̊Ǘ����� (manager.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �O���錾(�s���S�ȃN���X�́Acpp�̕��Ńw�b�_���Ăяo��)
//================================================
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CSound;
class CMode;
class CFade;

//================================================
// �N���X�錾
//================================================

// �}�l�[�W���[�N���X
class CManager
{
public:

    // ���[�h�̎��
    typedef enum
    {
        MODE_NONE =0,   // �Ȃ�
        MODE_TITLE,     // �^�C�g��
        MODE_MANUAL,    // �V�ѕ�
        MODE_GAME,      // �Q�[��
        MODE_RESULT,    // ���U���g
        MODE_MAX
    }MODE;

    // �X�e�[�W
    typedef enum
    {
        STAGE_NONE = 0,     // �Ȃ�
        STAGE_A,	        // ��
        STAGE_B,	        // ��
        STAGE_C,            // ��
        STAGE_MAX			// �X�e�[�W�̍ő吔
    }STAGE;

    CManager();
    ~CManager();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
    void Uninit(void);
    void Update(void);
    void Draw(void);  
    static CRenderer *GetRenderer(void) { return m_pRenderer; }
    static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
    static CInputJoypad *GetInputJoypad(void) { return m_pInputJoypad; }
    static CSound *GetSound(void) { return m_pSound; }
    static MODE GetMode(void);
    static void SetMode(MODE mode);

    static void SetScore(int nScore) { m_nScore = nScore; }
    static int GetScore(void) { return m_nScore; }
    static void SetUseHelper(bool bUse) { m_bUseHelper = bUse; }
    static bool GetUseHelper(void) { return m_bUseHelper; }
    static STAGE GetSetStage(void) { return m_stage; }
    static void SetSetStage(STAGE setStage) { m_stage = setStage; }

private:
    static CRenderer *m_pRenderer;              // �����_���[�̃|�C���^
    static CInputKeyboard *m_pInputKeyboard;    // �L�[�{�[�h�̃|�C���^
    static CInputJoypad *m_pInputJoypad;        // �R���g���[���[�̃|�C���^
    static CSound *m_pSound;                    // �T�E���h�̃|�C���^
    static CMode *m_pMode;                      // ���[�h�̃|�C���^
    static CFade *m_pFade;                      // �t�F�[�h�̃|�C���^

    static int m_nScore;                        // �X�R�A
    static bool m_bUseHelper;                   // �w���p�[���g�������ǂ���
    static STAGE m_stage;                // �Z�b�g����X�e�[�W
};

#endif