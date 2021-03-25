//=============================================================================
//
// �Q�[������ [game.h]
// Author : �㓡�T�V��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "mode.h"
#include "manager.h"

//================================================
// �O���錾(�s���S�ȃN���X�́Acpp�̕��Ńw�b�_���Ăяo��)
//================================================
class CPlayer;
class CScore;
class CPause;
class CHelper;

//================================================
// �}�N����`
//================================================

//�Q�[����Ԃ̊Ǘ��t���[��
#define COUNT_WAIT_GAME_OVER 180	    // �Q�[���I�[�o�[���ɁA���U���g��ʂ֍s���܂ł̎���
#define COUNT_WAIT_GAME_CLEAR 90        // �Q�[���N���A���ɁA���U���g��ʂ֍s���܂ł̎���
#define CREATE_PLAYER_COUNT 90          // �v���C���[�𐶐�����܂ł̃J�E���^

#define FLOOR_COLLISION (SCREEN_HEIGHT - 35.0f) // ���̔���
#define FLOWING_STAGE (3.195f)                  // �X�e�[�W������鑬�x

//================================================
// �N���X�錾
//================================================
class CGame : public CMode
{
public:

    // �Q�[���̏��
    typedef enum
    {
        STATE_NORMAL = 0,   // �ʏ�
        STATE_PAUSE,	    // �|�[�Y
        STATE_MAX			// ��Ԃ̍ő吔
    }STATE;

    CGame();
    ~CGame();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    static CScore *GetScore(void) { return m_pScore; }                      // �X�R�A���擾
    static CPlayer *GetPlayer(void) { return m_pPlayer; }                   // �v���C���[���擾 
    static int GetStock(void) { return m_nStock; }                          // �X�g�b�N�����擾
    static bool GetDispPlayer(void) { return m_bDispPlayer; }               // �v���C���[�����邩�ǂ����̎擾
    static void DefeatPlayer(void);                                         // �v���C���[�����ꂽ
    static void AddStock(void);                                             // �X�g�b�N�����Z
    static bool GetBossBattle(void){return m_bBossBattle; }                 // �{�X�o�g�������ǂ����擾
    static bool GetFloor(void) { return m_bFloor; }                         // ���̔��肪���邩�ǂ������擾
    static void StopGameCount(void);                                        // �Q�[���̃J�E���^���~�߂�
    static void SetState(STATE state) { m_state = state; }                  // �Q�[���̏�Ԃ�ݒ�
    static STATE GetState(void) { return m_state; }                         // �Q�[���̏�Ԃ��擾
    static void SetStage(CManager::STAGE stage);                            // �X�e�[�W��ݒ�
    static CManager::STAGE GetStage(void) { return m_stage; }               // �X�e�[�W���擾
    static void RespawnPlayer(void);                                        // �v���C���[�����X�|�[��
    static void Continue(void);                                             // �R���e�B�j���[
    static bool GetInvinciblePlayer(void) { return m_bInvinciblePlayer; }   // �v���C���[�����G���ǂ������擾
    static void SetInvinciblePlayer(void) { m_bInvinciblePlayer = true; }   // �v���C���[�𖳓G�ɂ���
    static bool GetMovePlayer(void) { return m_bMovePlayer; }               // �v���C���[�������邩�ǂ������擾
    static void SetMovePlayer(bool bMove);                                  // �v���C���[�������邩�ǂ�����ݒ�
    static void SetShockPlayer(bool bShock) { m_bShockPlayer = bShock; }    // �v���C���[�̃V���b�N��Ԃ𒲐�
    static bool GetShockPlayer(void) { return m_bShockPlayer; }             // �v���C���[���V���b�N��Ԃ��ǂ������擾
    static bool GetDarkening(void) { return m_bDarkening; }                 // �Ó]��Ԃ��ǂ����擾
    static bool GetDispHelper(void) { return m_bCreateHelper; }             // �w���p�[�����邩�ǂ����擾
    static void SetGameClear(void) { m_bGameClear = true; }                 // �Q�[���N���A
    static void SetGameOver(void){ m_bFinishGame = true; m_nCntFinishGame = COUNT_WAIT_GAME_OVER;}  // �Q�[���I�[�o�[
    void Stage��(void);      // �X�e�[�W���̏���
    void Stage��(void);      // �X�e�[�W���̏���
    void Stage��(void);      // �X�e�[�W���̏���
    void SetRandBubble(void);// �����_���ɖA�𐶐�
    void SetRandFire(void);  // �����_���ɉ��𐶐�
    void SetRandMagma(void); // �����_���Ƀ}�O�}�𐶐�
    void SetRandCloud(void); // �����_���ɉ_�𐶐�

private:
    int m_nCntCreatePlayer;              // �v���C���[�𐶐�����܂ł̃J�E���^

    static CScore *m_pScore;             // �X�R�A�̃|�C���^
    static CPlayer *m_pPlayer;           // �v���C���[�̃|�C���^
    static CHelper *m_pHelper;           // �w���p�[�̃|�C���^
    static CPause *m_pPause;             // �|�[�Y�̃|�C���^
    static STATE m_state;                // ���
    static CManager::STAGE m_stage;      // �X�e�[�W
    static int m_nCntGameTime;           // �Q�[�����Ԃ̃J�E���^
    static int m_nStock;                 // �X�g�b�N��
    static bool m_bCreatePlayer;         // �v���C���[�𐶐����邩�ǂ���
    static bool m_bDispPlayer;           // �v���C���[�����邩�ǂ���
    static bool m_bBossBattle;           // �{�X�o�g�������ǂ���
    static bool m_bFloor;                // ���̔�����g�����ǂ���
    static bool m_bInvinciblePlayer;     // �v���C���[�����G���ǂ���
    static bool m_bMovePlayer;           // �v���C���[�������邩�ǂ���
    static bool m_bShockPlayer;          // �v���C���[���V���b�N��Ԃ��ǂ���
    static bool m_bDarkening;            // �Ó]��Ԃ��ǂ���
    static bool m_bCreateHelper;         // �w���p�[����������Ă��邩�ǂ���
    static bool m_bGameClear;            // �Q�[���N���A�������ǂ���
    static int m_nCntFinishGame;         // �Q�[�����I���܂ł̃J�E���^
    static bool m_bFinishGame;           // �Q�[�����I��������ǂ���
};

#endif