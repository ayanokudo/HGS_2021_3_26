//====================================================================
//
// �v���C���[�̏��� (player.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define PLAYER_START_POS_X 200.0f                                           // ���@�̊J�nX���W
#define PLAYER_START_POS_Y (SCREEN_HEIGHT / 2)                              // ���@�̊J�nY���W
#define PLAYER_POS D3DXVECTOR3(PLAYER_START_POS_X, PLAYER_START_POS_Y, 0.0f)// ���@�̈ʒu
#define PLAYER_SIZE D3DXVECTOR3(100.0f, 100.0f, 0.0f)		                // ���@�̕`��T�C�Y
#define PLAYER_COLLISION_SIZE D3DXVECTOR3(60.0f, 60.0f, 0.0f)	            // ���@�̏Փ˃T�C�Y
#define PLAYER_COLLISION_ITEM_SIZE D3DXVECTOR3(75.0f, 75.0f, 0.0f)	        // ���@�̃A�C�e���ɑ΂���Փ˃T�C�Y
#define PLAYER_START_STOCK 3                                                // �J�n���̃X�g�b�N��
#define PLAYER_INVINCIBLE_FRAME 150                                         // �v���C���[�̖��G����
#define PLAYER_ENABLE_SHOT_FRAME 110                                        // �v���C���[���e�������Ƃ��ł���悤�ɂȂ�t���[��
#define PLAYER_MAX_STOCK 5                                                  // �v���C���[�̍ő�X�g�b�N
#define PLAYER_MAX_BARRIER 5                                                // �v���C���[�̍ő�o���A
#define PLAYER_ADD_WATAR_POS -45.0f                                         // �v���C���[�̐��e�̔��ˈʒu�𒆐S������Z
#define PLAYER_MOVE_LIMITED_BY_UI 120.0f                                    // UI�ɂ��A�v���C���[�̈ړ��͈͐���

// �X�s�[�h����
#define PLAYER_SPEED_1 3.5f                                     // ���@�̑���1
#define PLAYER_SPEED_2 6.0f                                     // ���@�̑���2
#define PLAYER_SPEED_3 10.0f                                    // ���@�̑���3
#define PLAYER_SPEED_4 15.0f                                    // ���@�̑���4
#define PLAYER_FIRST_SPEED_RANK 2                               // ���@�̍ŏ��̃X�s�[�h�����N
#define PLAYER_MAX_SPEED_RANK 4                                 // ���@�̍ő�X�s�[�h�����N
#define PLAYER_POS_Y_DOWN_IN_WATAR 0.5f                         // ���̒��ŁA���X�Ɉʒu��������

#define MAX_CHARGE_TIME 100                                     // �ő�`���[�W����
#define PLAYER_TILT_RATE 0.01f                                  // �v���C���[���X������

//================================================
// �N���X�錾
//================================================

// �v���C���[�N���X
class CPlayer : public CScene2D
{
public:
    CPlayer();
    ~CPlayer();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    void ChangeShotAngle(void);                         // ���̔��ˊp�x����
    void ChangeSpeed(void);                             // �X�s�[�h�ύX
    D3DXVECTOR3 ControlPlayer(D3DXVECTOR3 pos);         // �ړ�����
    void ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size); // �U������
    static HRESULT Load(void);
    static void Unload(void);
    static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, int nCntInvincibleFrame);
    float GetShotAngle(void) { return m_fShotAngle; }               // �����o�ϐ��̔��ˊp�x��Ԃ�
    int GetChargeTime(void) { return m_nChargeTime; }               // �����o�ϐ��̃`���[�W���Ԃ�Ԃ�
    int GetBarrier(void) { return m_nBarrier; }                     // �����o�ϐ��̃o���A��Ԃ�
    int GetSpeedRank(void) { return m_nSpeedRank; }                 // �����o�ϐ��̃X�s�[�h�����N��Ԃ�
    int GetInvincibleFrame(void) { return m_nCntInvincibleFrame; }  // �����o�ϐ��̖��G���Ԃ�Ԃ�
    void Hit(void);                                                 // �U�����󂯂���
    D3DXVECTOR3 HitFloor(D3DXVECTOR3 pos, D3DXVECTOR3 size);        // ���ɓ����������ǂ���
    void SetStartPos(void);                                         // �X�^�[�g�ʒu�ɐݒ�

    float GetPlayerAngle(void) { return m_fPlayerAngle; }           // �v���C���[�̊p�x���擾

private:
    int m_nAttackCoolTime;                  // �U���̃N�[���^�C��
    float m_fShotAngle;                     // ���̔��ˊp�x
    float m_fPlayerAngle;                   // ���@�̊p�x
    int m_nChargeTime;                      // ���̃`���[�W����
    int m_nBarrier;                         // �o���A�̖���
    int m_nCntInvincibleFrame;              // ���G����
    float m_fSpeed;                         // ����
    int m_nSpeedRank;                       // �X�s�[�h�����N
    bool m_bUse;                            // �g�p�t���O
    static LPDIRECT3DTEXTURE9 m_pTexture;   // �ǂݍ��񂾃e�N�X�`����ۑ�����
};

#endif