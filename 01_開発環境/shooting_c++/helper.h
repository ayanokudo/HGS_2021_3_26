//====================================================================
//
// �w���p�[�̏��� (helper.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _HELPER_H_
#define _HELPER_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define HELPER_START_POS_X 200.0f                                           // �w���p�[�̊J�nX���W
#define HELPER_START_POS_Y (SCREEN_HEIGHT / 2 - 120.0f)                     // �w���p�[�̊J�nY���W
#define HELPER_POS D3DXVECTOR3(HELPER_START_POS_X, HELPER_START_POS_Y, 0.0f)// �w���p�[�̈ʒu
#define HELPER_SIZE D3DXVECTOR3(100.0f, 100.0f, 0.0f)		                // �w���p�[�̕`��T�C�Y
#define HELPER_COLLISION_SIZE D3DXVECTOR3(40.0f, 40.0f, 0.0f)	            // �w���p�[�̏Փ˃T�C�Y
#define HELPER_INVINCIBLE_FRAME 120                                         // �w���p�[�̖��G����
#define HELPER_ENABLE_SHOT_FRAME 75                                         // �w���p�[���e�������Ƃ��ł���悤�ɂȂ�t���[��
#define HELPER_MOVE_LIMITED_BY_UI 120.0f                                    // UI�ɂ��A�w���p�[�̈ړ��͈͐���
#define HELPER_KNOCKBACK_CONTROL 0.9f                                       // �w���p�[�̃m�b�N�o�b�N�𐧌�
#define HELPER_KNOCKBACK_VALUE 27.5f                                        // �w���p�[�̃m�b�N�o�b�N��
#define HELPER_TILT_RATE 0.01f                                              // �w���p�[���X������

// �e����
#define HELPER_BULLET_SIZE D3DXVECTOR3(30.0f, 30.0f, 0.0f)		           // �w���p�[�̒e�T�C�Y
#define HELPER_BULLET_SPEED 17.5f                                          // �w���p�[�̒e�̑��x
#define HELPER_BULLET_FIRE_COOL_TIME 23                                    // �w���p�[�̉��e�̃N�[���^�C��
#define HELPER_BULLET_WATER_COOL_TIME 23                                   // �w���p�[�̐��e�̃N�[���^�C��
#define HELPER_BULLET_LIGHT_COOL_TIME 23                                   // �w���p�[�̗��e�̃N�[���^�C��

// �X�s�[�h����
#define HELPER_SPEED 7.5f                                       // �w���p�[�̑���
#define HELPER_POS_Y_DOWN_IN_WATAR 0.5f                         // ���̒��ŁA���X�Ɉʒu��������

//================================================
// �N���X�錾
//================================================

// �w���p�[�N���X
class CHelper : public CScene2D
{
public:
    CHelper();
    ~CHelper();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    D3DXVECTOR3 ControlHelper(D3DXVECTOR3 pos);         // �ړ�����
    void ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size); // �U������
    static HRESULT Load(void);
    static void Unload(void);
    static CHelper *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, int nCntInvincibleFrame);
    void Hit(D3DXVECTOR3 posOld);                                                       // �U�����󂯂���
    D3DXVECTOR3 HitFloor(D3DXVECTOR3 pos, D3DXVECTOR3 size);                            // ���ɓ����������ǂ���
    void SetStartPos(void);                                                             // �X�^�[�g�ʒu�ɐݒ�

private:
    D3DXVECTOR3 m_move;                     // �ړ���
    float m_fHelperAngle;                   // �w���p�[�̊p�x
    int m_nAttackCoolTime;                  // �U���̃N�[���^�C��
    int m_nCntInvincibleFrame;              // ���G����
    float m_fSpeed;                         // ����
    static LPDIRECT3DTEXTURE9 m_pTexture;   // �ǂݍ��񂾃e�N�X�`����ۑ�����
};

#endif