//====================================================================
//
// �e�̏��� (bullet.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define BULLET_COUNTERATTACK_FIRE_SPEED 6.0f                            // �����e�̑���(��)
#define BULLET_COUNTERATTACK_WATAR_SPEED 4.5f                           // �����e�̑���(��)
#define BULLET_COUNTERATTACK_LIGHT_SPEED 7.0f                           // �����e�̑���(��)
#define BULLET_COUNTERATTACK_LIFE 1000                                  // �����e�̃��C�t
#define BULLET_COUNTERATTACK_FIRE_SCORE 390                             // �����e�̃X�R�A(��)
#define BULLET_COUNTERATTACK_WATAR_SCORE 1800                           // �����e�̃X�R�A(��)
#define BULLET_COUNTERATTACK_GRASS_SCORE 1200                           // �����e�̃X�R�A(��)
#define BULLET_COUNTERATTACK_FIRE_SIZE D3DXVECTOR3(25.0f, 25.0f, 0.0f)	// �����e�̃T�C�Y(��)
#define BULLET_COUNTERATTACK_WATAR_SIZE D3DXVECTOR3(32.5f, 32.5f, 0.0f)	// �����e�̃T�C�Y(��)
#define BULLET_COUNTERATTACK_LIGHT_SIZE D3DXVECTOR3(27.5f, 27.5f, 0.0f)	// �����e�̃T�C�Y(��)

#define BULLET_FIRE_SIZE D3DXVECTOR3(25.0f, 25.0f, 0.0f)	// ���̒e�̃T�C�Y
#define BULLET_FIRE_SPEED 16.0f                             // ���̒e�̑���
#define BULLET_FIRE_LIFE 1000                               // ���̒e�̃��C�t
#define BULLET_FIRE_DAMAGE 15                               // ���̒e�̃_���[�W
#define BULLET_FIRE_COOL_TIME 6                             // ���̒e�̃N�[���^�C��
#define BULLET_FIRE_CHANGE_ENEMY_COLOR_FRAME 15             // ���̒e���G�̐F��ς���t���[��
#define BULLET_FIRE_COLOR D3DXCOLOR(1.0f,0.0f,0.0f,0.7f)    // ���̒e�̐F

#define BULLET_WATER_SIZE D3DXVECTOR3(80.0f, 80.0f, 0.0f)	     // ���̒e�̃T�C�Y
#define BULLET_WATER_SPEED 12.5f                                 // ���̒e�̑���
#define BULLET_WATER_LIFE 1000                                   // ���̒e�̃��C�t
#define BULLET_WATER_DAMAGE 100                                  // ���̒e�̃_���[�W
#define BULLET_WATAR_HELPER_DAMAGE 20                            // �w���p�[�̐��̒e�̃_���[�W
#define BULLET_WATER_COOL_TIME 25                                // ���̒e�̃N�[���^�C��
#define BULLET_WATER_CHANGE_ENEMY_COLOR_FRAME 20                 // ���̒e���G�̐F��ς���t���[��
#define BULLET_WATER_AVOID_MULTIPLE_HITS_FRAME 24                // ���̒e�̑��i�q�b�g����t���[��(�N�[���^�C���l��)
#define BULLET_WATER_COLOR D3DXCOLOR(0.2f, 0.858f, 0.98f, 1.0f)  // ���̒e�̐F
#define BULLET_WATER_AIR_RESISTANCE 0.4f                         // ���̒e�̋�C��R

#define BULLET_LIGHT_SPEED 22.5f                            // ���̒e�̑���
#define BULLET_LIGHT_LIFE 1000                              // ���̒e�̃��C�t
#define BULLET_LIGHT_EXTEND_RATE 1.0f                       // ���̒e�̊g�劄��
#define BULLET_LIGHT_HELPER_DAMAGE 20                       // �w���p�[�̗��̒e�̃_���[�W
#define BULLET_LIGHT_MIN_SIZE 50.0f                         // ���̍ŏ��T�C�Y
#define BULLET_LIGHT_MAX_SIZE 150.0f                        // ���̍ő�T�C�Y
#define BULLET_LIGHT_MAX_DAMAGE 250                         // ���̍ő�_���[�W
#define BULLET_LIGHT_COOL_TIME 20                           // ���̒e�̃N�[���^�C��
#define BULLET_LIGHT_CHANGE_ENEMY_COLOR_FRAME 25            // ���̒e���G�̐F��ς���t���[��
#define BULLET_LIGHT_AVOID_MULTIPLE_HITS_FRAME 19           // ���̒e�̑��i�q�b�g����t���[��(�N�[���^�C���l��)
#define BULLET_LIGHT_COLOR D3DXCOLOR(1.0f,0.99f,0.0f,1.0f)  // ���̃G�t�F�N�g�̐F

#define BULLET_GRASS_LIFE 1000                              // ���̒e�̃��C�t
#define BULLET_GRASS_DAMAGE 10                              // ���̒e�̃_���[�W
#define BULLET_GRASS_COLOR D3DXCOLOR(0.0f,1.0f,0.0f,0.9f)   // ���̒e�̃G�t�F�N�g�̐F

// �e�����ɓ����������̃G�t�F�N�g�̈ʒu����
#define BULLET_HIT_FLOOR_EFFECT_ADD_POS D3DXVECTOR3(0.0f,-5.0f,0.0f)

// ���C�t���J�E���^����Ɏg�p
#define BULLET_LIFE_COUNTER 1000

// �ђʂ��l�����Ȃ��A��ԃJ�E���^�̒l
#define DONT_GO_THROUGH 19

// ���C�j�[�o���b�g
#define BULLET_RAINY_FIRST_SPEED 2.0f                                           // ����
#define BULLET_RAINY_ACCEL_SPEED 10.0f                                          // ������X�s�[�h
#define BULLET_RAINY_LIFE_ACCEL 820                                             // ��������J�E���^
#define BULLET_SET_FIRE_EFFECT_COUNT 2                                          // �����Z�b�g����J�E���^
#define CHANGE_LIGHT (D3DXVECTOR3(-1.0f, -1.0f, 0.0f))                          // ���ɕς���
#define BULLET_BULE_FIRE_COLOR D3DXCOLOR(D3DXCOLOR(0.588f,0.937f,1.0f,0.6f))    // �����̐F

// ���z�[�~���O�V���b�g
#define BULLET_HOMING_WATAR_SPEED 7.5f        // �z�[�~���O����
#define BULLET_HOMING_LIFE_STOP_HOMING 907    // �z�[�~���O����߂�J�E���^

// ���o�[�X�g
#define BULLET_FIRE_BURST_SPEED 8.75f                                       // ����(�G�l�~�[�̔��ˎ��Ɠ����l�ɂ���)
#define BULLET_FIRE_BURST_LIFE_ACCEL 880                                    // �o�[�X�g����J�E���^
#define BULLET_FIRE_BURST_DECELERATE 0.075f                                 // �����̊���
#define BULLET_FIRE_BURST_CREATE_BULLET_SIZE D3DXVECTOR3(30.0f,30.0f,0.0f)  // �������鉊�o���b�g�̑傫��
#define BULLET_FIRE_BURST_CREATE_BULLET_SPEED 5.0f                          // �������鉊�o���b�g�̑���
#define BULLET_FIRE_BURST_SCORE 2100                                        // �ł��������ۂ̃X�R�A

// �o�[�j���O�o���b�g
#define BULLET_BURNING_FIRST_SPEED 2.0f                                     // ����
#define BULLET_BURNING_ACCEL_SPEED 11.0f                                    // ������X�s�[�h
#define BULLET_BURNING_LIFE_ACCEL 817                                       // ��������J�E���^
#define BULLET_BURNING_BURST_SCORE 400                                      // �ł��������ۂ̃X�R�A
#define CHANGE_MULTI (D3DXVECTOR3(-0.1f, -0.1f, 0.0f))                      // �}���`�ɕς���

// �E�B���h�o���b�g
#define BULLET_WIND_FIRST_SPEED 8.75f                                       // ����(�G�l�~�[�̔��ˎ��Ɠ����l�ɂ���)
#define BULLET_WIND_DECELERATE 0.075f                                       // �����̊���
#define BULLET_WIND_ACCEL_SPEED 17.5f                                       // ������X�s�[�h
#define BULLET_WIND_LIFE_ACCEL 880                                          // �}��������J�E���^

//================================================
// �N���X�錾
//================================================

// �e�N���X
class CBullet : public CScene2D
{
public:
    // �e�̎��
    typedef enum
    {
        TYPE_FIRE = 0,      // ��
        TYPE_WATER,         // ��
        TYPE_HELPER_WATER,  // �w���p�[�̐�
        TYPE_LIGHT,         // ��
        TYPE_GRASS,         // ��
        TYPE_RAINY,         // ���C�j�[�o���b�g
        TYPE_WATAR_HOMING,  // ���z�[�~���O
        TYPE_FIRE_BURST,    // ���o�[�X�g
        TYPE_BURNING,       // �o�[�j���O�o���b�g
        TYPE_WIND,          // �E�B���h�o���b�g
        TYPE_MAX            // ��ނ̍ő吔
    }TYPE;
    CBullet();
    ~CBullet();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, TYPE type, TRIBE tribe);
    TRIBE GetTribe(void) { return m_tribe; }                  // �푰���擾
    ELEMENT GetElement(void) { return m_element; }            // �������擾
    TYPE GetType(void) { return m_type; }                     // ��ނ��擾
    bool HitFloor(D3DXVECTOR3 pos, D3DXVECTOR3 size);         // ���ɓ����������ǂ���
    float GetAngleToPlayer(void);                             // ���@�ւ̊p�x���擾
    void FireBurst(D3DXVECTOR3 pos);                          // ���o�[�X�g
    void SmallExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size);   // ������

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXVECTOR3 m_posOld;                              // 1F�O�̈ʒu
    D3DXVECTOR3 m_move;                                // �ړ���
    float m_fSpeed;                                    // ���x
    int m_nLife;                                       // ���C�t
    int m_nDamage;                                     // �_���[�W
    TYPE m_type;                                       // �e�̎��
    ELEMENT m_element;                                 // �e�̑���
    TRIBE m_tribe;                                     // �e�̎푰
};

#endif