//====================================================================
//
// �u���b�N�̏��� (block.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define BLOCK_APPLE_SIZE D3DXVECTOR3(95.0f, 95.0f, 0.0f)	        // �����S�̃T�C�Y
#define BLOCK_APPLE_COLLISION_SIZE D3DXVECTOR3(65.0f, 65.0f, 0.0f)  // �����S�̏Փ˃T�C�Y
#define BLOCK_APPLE_ROT_SPEED 0.2f                                  // ��]�X�s�[�h
#define BLOCK_APPLE_FALL_COUNT 90                                   // ��������܂ł̃J�E���^
#define BLOCK_APPLE_RIGHT_BOUND D3DXVECTOR3(3.0f, -10.0f, 0.0f)     // �E�Ƀo�E���h
#define BLOCK_APPLE_LEFT_BOUND D3DXVECTOR3(-3.0f, -10.0f, 0.0f)     // ���Ƀo�E���h

#define BLOCK_ROCK_SIZE D3DXVECTOR3(300.0f, 300.0f, 0.0f)	        // ��̃T�C�Y
#define BLOCK_ROCK_COLLISION_SIZE D3DXVECTOR3(130.0f, 130.0f, 0.0f) // ��̏Փ˃T�C�Y
#define BLOCK_ROCK_ROT_SPEED 0.05f                                  // ��̉�]�X�s�[�h
#define BLOCK_ROCK_MAX_FALL_SPEED 9.0f                              // ��̍ő嗎���X�s�[�h
#define BLOCK_ROCK_RIGHT_BOUND D3DXVECTOR3(3.0f, -7.0f, 0.0f)       // �E�Ƀo�E���h
#define BLOCK_ROCK_LEFT_BOUND D3DXVECTOR3(-3.0f, -7.0f, 0.0f)       // ���Ƀo�E���h

#define BLOCK_METEO_SIZE D3DXVECTOR3(300.0f, 300.0f, 0.0f)	        // ���e�I�̃T�C�Y
#define BLOCK_METEO_COLLISION_SIZE D3DXVECTOR3(150.0f, 150.0f, 0.0f)// ���e�I�̏Փ˃T�C�Y
#define BLOCK_METEO_ROT_SPEED 0.05f                                 // ���e�I�̉�]�X�s�[�h
#define BLOCK_METEO_FALL_SPEED 20.0f                                // ���e�I�̗����X�s�[�h

//================================================
// �N���X�錾
//================================================

// �u���b�N�N���X
class CBlock : public CScene2D
{
public:
    // �u���b�N�̎��
    typedef enum
    {
        TYPE_APPLE,     // �����S
        TYPE_ROCK,      // ��
        TYPE_METEO,     // ���e�I
        TYPE_MAX        // ��ނ̍ő吔
    }TYPE;
    CBlock();
    ~CBlock();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bRotRight, TYPE type);
    D3DXVECTOR3 Bound(D3DXVECTOR3 pos, D3DXVECTOR3 size);                   // ���ɓ����������̃o�E���h
    D3DXVECTOR3 GetCollisionSize(void) { return m_collisionSize; }          // �Փ˂̑傫����Ԃ�
    D3DXVECTOR3 GetPosOld(void) { return m_posOld; }                        // 1F�O�̈ʒu��Ԃ�
    float GetAngleToPlayer(D3DXVECTOR3 pos);
    bool MeteoInpact(D3DXVECTOR3 pos, D3DXVECTOR3 size);                    // 覐΂̏Փ�

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXVECTOR3 m_posOld;                              // 1F�O�̈ʒu
    D3DXVECTOR3 m_collisionSize;                       // �����蔻��̑傫��
    D3DXVECTOR3 m_move;                                // �ړ���
    int m_nCntChangeMove;                              // �ړ��ʂ��ς�肾���܂ł̃J�E���g
    float m_fRotAngle;                                 // ��]�p�x
    bool m_bRotRight;                                  // �E��]���ǂ���
    TYPE m_type;                                       // �u���b�N�̎��
};

#endif