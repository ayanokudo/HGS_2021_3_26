//====================================================================
//
// �G�t�F�N�g�̏��� (effect.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define EXPLOSION_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)          // �����̑傫��
#define WATAR_EXPLOSION_SIZE D3DXVECTOR3(100.0f, 100.0f, 0.0f)  // �������̑傫��

#define CHARGE_COLOR D3DXCOLOR(0.0f,1.0f,0.0f,0.9f)             // �`���[�W�̃J���[
#define CHARGE_PART_SIZE 30.0f                                  // �`���[�W�̃p�[�e�B�N���̑傫��
#define CHARGE_PART_SPEED 6.0f                                  // �`���[�W�̃p�[�e�B�N���̑���
#define CHARGE_SIZE 200.0f                                      // �`���[�W�̃T�C�Y
#define CHARGE_RATE_SIZE 2.0f                                   // �`���[�W�̊g�劄��

#define PERCENTAGE_SIZE D3DXVECTOR3(200.0f, 100.0f, 0.0f)   // ���\���̑傫��
#define PERCENTAGE_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,0.1f)     // ���\���̐F
#define PERCENTAGE_FADE_RATE 0.01f                          // ���\���̃t�F�[�h����

#define BONUS_POINT_SIZE D3DXVECTOR3(200.0f, 100.0f, 0.0f)   // �{�[�i�X�|�C���g�̑傫��
#define BONUS_POINT_MOVE_RATE 1.0f                           // �{�[�i�X�|�C���g�̏�֍s���ړ���
#define BONUS_POINT_FADE_RATE 0.025f                         // �{�[�i�X�|�C���g�̏����Ă�����
#define BONUS_POINT_ADD_POS_Y -50.0f                         // �{�[�i�X�|�C���g�̉��Z�ʒuY

#define EFFECT_DOUBLE_WAVE_SHOT_SIZE D3DXVECTOR3(200.0f, 200.0f, 0.0f)                // ��d�E�F�[�u�̑傫��(�V���b�g��)
#define EFFECT_DOUBLE_WAVE_SHOT_COLOR D3DXCOLOR(1.0f,0.99f,0.0f,1.0f)                 // ��d�E�F�[�u�̐F(�V���b�g��)
#define EFFECT_DOUBLE_WAVE_ITEM_SIZE D3DXVECTOR3(150.0f, 150.0f, 0.0f)                // ��d�E�F�[�u�̑傫��(�A�C�e���擾��)
#define EFFECT_DOUBLE_WAVE_ITEM_BARRIER_COLOR D3DXCOLOR(0.2f, 0.858f, 0.98f, 1.0f)    // ��d�E�F�[�u�̐F(�o���A�擾��)
#define EFFECT_DOUBLE_WAVE_ITEM_STOCK_COLOR D3DXCOLOR(1.0f, 0.262f, 0.447f, 1.0f)     // ��d�E�F�[�u�̐F(�X�g�b�N�擾��)
#define EFFECT_DOUBLE_WAVE_BLAZE_SIZE D3DXVECTOR3(250.0f, 250.0f, 0.0f)               // ��d�E�F�[�u�̑傫��(�{�X�u���C�Y)
#define EFFECT_DOUBLE_WAVE_BLAZE_COLOR D3DXCOLOR(0.627f,0.007f,0.827f, 1.0f)          // ��d�E�F�[�u�̐F(�{�X�u���C�Y)
#define EFFECT_DOUBLE_WAVE_EXTEND_RATE 20.0f                                          // ��d�E�F�[�u�̊g�劄��
#define EFFECT_DOUBLE_WAVE_FADE_OUT_RATE 0.05f                                        // ��d�E�F�[�u�̃t�F�[�h�A�E�g����

#define EFFECT_FIRE_FIRST_COLOR D3DXCOLOR(1.0f,0.99f,0.0f,0.1f)      // ���̐F
#define EFFECT_FIRE_TO_RED_RATE 0.015f                               // �Ԃɋ߂Â��Ă�������
#define EFFECT_FIRE_FADE_IN_RATE 0.02f                               // ���̃t�F�[�h�C������
#define EFFECT_FIRE_FADE_OUT_RATE 0.003f                             // ���̃t�F�[�h�A�E�g����
#define EFFECT_FIRE_START_POS_Y 30.0f                                // ���̊J�n�ʒuY
#define EFFECT_FIRE_START_POS_Y_BOSS -70.0f                          // �{�X�펞�́A���̊J�n�ʒuY
#define EFFECT_FIRE_ALPHA_START_MOVE 0.3f                            // ���̓����������l
#define EFFECT_FIRE_ALPHA_START_FADE_OUT 0.6f                        // ���̏����Ă������l
#define EFFECT_FIRE_MIN_SIZE 2000                                    // ���̍ŏ��T�C�Y
#define EFFECT_FIRE_MAX_SIZE 5000                                    // ���̍ő�T�C�Y

#define EFFECT_MAGMA_COLOR D3DXCOLOR(1.0f,0.99f,0.0f,0.8f)           // �}�O�}�̐F
#define EFFECT_MAGMA_MIN_SIZE 3000                                   // �}�O�}�̍ŏ��T�C�Y
#define EFFECT_MAGMA_MAX_SIZE 5000                                   // �}�O�}�̍ő�T�C�Y

#define EFFECT_LEAF_SIZE D3DXVECTOR3(50.0f, 50.0f ,0.0f)          // �t���ς̑傫��
#define EFFECT_BRANCH_SIZE D3DXVECTOR3(80.0f, 80.0f ,0.0f)        // �؂̎}�̑傫��
#define EFFECT_LEAF_FADE_RATE 0.02f                               // �t���ς̃t�F�[�h�A�E�g����
#define EFFECT_BRANCH_FADE_RATE 0.03f                             // �؂̎}�̃t�F�[�h�A�E�g����

#define EFFECT_RED_FIRE_FIRST_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)       // �Ԃ����̍ŏ��̑傫��
#define EFFECT_RED_FIRE_FIRST_COLOR D3DXCOLOR(1.0f,0.99f,0.0f,1.0f)      // �Ԃ����̐F
#define EFFECT_RED_FIRE_EXTEND_RATE 0.5f                                 // �Ԃ����̊g�劄��
#define EFFECT_YELLOW_FIRE_TO_RED_RATE 0.05f                             // �Ԃɋ߂Â��Ă�������
#define EFFECT_RED_FIRE_RED D3DXCOLOR(1.0f,0.0f,0.0f,1.0f)               // ��
#define EFFECT_RED_FIRE_OVER_SIZE 70.0f                                  // �傫��������̂́A�Ԃɂ���
#define EFFECT_RED_FIRE_FADE_OUT_RATE 0.01f                              // �Ԃ����̃t�F�[�h�A�E�g����
#define EFFECT_RED_FIRE_POS_X 1070.0f
#define EFFECT_RED_FIRE_POS_Y 460.0f

#define EFFECT_BLUE_FIRE_FIRST_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)       // �����̍ŏ��̑傫��
#define EFFECT_BLUE_FIRE_FIRST_COLOR D3DXCOLOR(0.588f,0.937f,1.0f,1.0f)   // �����̐F
#define EFFECT_BLUE_FIRE_EXTEND_RATE 0.5f                                 // �����̊g�劄��
#define EFFECT_WHITE_FIRE_TO_BLUE_RATE 0.05f                              // �ɋ߂Â��Ă�������
#define EFFECT_BLUE_FIRE_BLUE D3DXCOLOR(0.0f,0.0f,1.0f,1.0f)              // ��
#define EFFECT_BLUE_FIRE_OVER_SIZE 70.0f                                  // �傫��������̂́A�ɂ���
#define EFFECT_BLUE_FIRE_FADE_OUT_RATE 0.01f                              // �����̃t�F�[�h�A�E�g����
#define EFFECT_BLUE_FIRE_POS_X 200.0f
#define EFFECT_BLUE_FIRE_POS_Y 460.0f

#define EFFECT_YELLOW_FIRE_FIRST_SIZE D3DXVECTOR3(50.0f, 50.0f, 0.0f)       // ���̉��̍ŏ��̑傫��
#define EFFECT_YELLOW_FIRE_FIRST_COLOR D3DXCOLOR(1.0f,0.99f,0.0f,1.0f)      // ���̉��̐F
#define EFFECT_YELLOW_FIRE_EXTEND_RATE 0.5f                                 // ���̉��̊g�劄��
#define EFFECT_YELLOW_FIRE_TO_GREEN_RATE 0.05f                              // �΂ɋ߂Â��Ă�������
#define EFFECT_YELLOW_FIRE_GREEN D3DXCOLOR(0.0f,1.0f,0.0f,1.0f)             // ��
#define EFFECT_YELLOW_FIRE_OVER_SIZE 70.0f                                  // �傫��������̂́A�΂ɂ���
#define EFFECT_YELLOW_FIRE_FADE_OUT_RATE 0.01f                              // ���̉��̃t�F�[�h�A�E�g����
#define EFFECT_YELLOW_FIRE_POS_X 640.0f
#define EFFECT_YELLOW_FIRE_POS_Y 460.0f

#define EFFECT_PURPLE_FIRE_FIRST_COLOR D3DXCOLOR(0.835f,0.901f,1.0f,0.5f)         // ���̉��̐F
#define EFFECT_PURPLE_FIRE_FIRST_COLOR_BLAZE D3DXCOLOR(0.835f,0.901f,1.0f,0.35f)  // �u���C�Y�̎��̉��̐F
#define EFFECT_WHITE_FIRE_TO_PURPLE_RATE_R 0.025f                                 // ���ɋ߂Â��Ă�������R
#define EFFECT_WHITE_FIRE_TO_PURPLE_RATE_G 0.05f                                  // ���ɋ߂Â��Ă�������G
#define EFFECT_PURPLE_FIRE_FADE_OUT_RATE 0.005f                                   // ���̉��̃t�F�[�h�A�E�g����

#define EFFECT_CLOUD_COUNT_LOOP 40                                          // �_�������ɁA��x�ɉ�for��
#define EFFECT_CLOUD_SIZE_X 10000                                           // ���̑傫��(�_���S����̑傫���Ȃ̂ŁA���ۂ�2�{�ɂȂ�)
#define EFFECT_CLOUD_SIZE_Y 2500                                            // �c�̑傫��(�_���S����̑傫���Ȃ̂ŁA���ۂ�2�{�ɂȂ�)
#define EFFECT_CLOUD_EDGE 60.0f                                             // �_�̒[
#define EFFECT_CLOUD_PARTICLES_MAX_SIZE 4000                                // �_�̗��̍ő�T�C�Y
#define EFFECT_CLOUD_PARTICLES_MID1_SIZE 3000                               // �_�̗��̒��ԃT�C�Y1
#define EFFECT_CLOUD_PARTICLES_MID2_SIZE 1500                               // �_�̗��̒��ԃT�C�Y2
#define EFFECT_CLOUD_PARTICLES_MIN_SIZE 1000                                // �_�̗��̍ŏ��T�C�Y
#define EFFECT_CLOUD_PARTICLES_MAX_ALPHA 15                                 // �_�̗��̍ő僿�l
#define EFFECT_CLOUD_PARTICLES_MID_ALPHA 12                                 // �_�̗��̒��ԃ��l
#define EFFECT_CLOUD_PARTICLES_MIN_ALPHA 7                                  // �_�̗��̍ŏ����l
#define EFFECT_CLOUD_FLOWING_SPEED 7.5f                                     // �_������鑬�x
#define EFFECT_CLOUD_FLOWING_SPEED_BOSS 3.525f                              // �{�X�펞�A�_������鑬�x
#define EFFECT_CLOUD_FADE_OUT_RATE 0.1f                                     // �_�̃t�F�[�h�A�E�g����

#define EFFECT_EXPLOSION_COUNT_LOOP 50                                      // �����������ɁA��x�ɉ�for��
#define EFFECT_EXPLOSION_FADE_OUT_RATE 0.0075f                              // �����̃t�F�[�h�A�E�g����
#define EFFECT_EXPLOSION_FIRST_COLOR D3DXCOLOR(0.898f,0.968f,0.529f,1.0f)   // �����̉��̐F
#define EFFECT_EXPLOSION_TO_RED_RATE 0.025f                                 // �Ԃɋ߂Â��Ă�������
#define EFFECT_EXPLOSION_MAX_SIZE 10000                                     // �����̗��̍ő�T�C�Y
#define EFFECT_EXPLOSION_MIN_SIZE 7500                                      // �����̗��̍ŏ��T�C�Y

#define EFFECT_SMALL_EXPLOSION_COUNT_LOOP 10                                // �������������ɁA��x�ɉ�for��
#define EFFECT_SMALL_EXPLOSION_FADE_OUT_RATE 0.005f                         // �������̃t�F�[�h�A�E�g����
#define EFFECT_SMALL_EXPLOSION_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,0.3f)         // �������̉��̐F
#define EFFECT_SMALL_EXPLOSION_BORDER_SIZE_THAT_CHANGE_SPEED 50.0f          // �������̃X�s�[�h��ς��鋫�ڂ̑傫��

//================================================
// �N���X�錾
//================================================

// �G�t�F�N�g�N���X
class CEffect : public CScene2D
{
public:
    // �G�t�F�N�g�̎��
    typedef enum
    {
        TYPE_PARTICLE = 0,	    // ���p�[�e�B�N��
        TYPE_WAVE,              // ���Ռ��g
        TYPE_EXPLOSION,         // ����
        TYPE_CHARGE,            // �`���[�W
        TYPE_CHARGE_PART,       // �`���[�W�̃p�[�e�B�N��
        TYPE_LIGHT_BULLET,      // ���o���b�g
        TYPE_SHOCK,             // �d��
        TYPE_BIG_EXPLOSION,     // �唚��
        TYPE_RED_SPARK,         // �ԉΉ�
        TYPE_GREEN_SPARK,       // �ΉΉ�
        TYPE_BLUE_SPARK,        // �Ή�
        TYPE_BLACK_SPARK,       // ���Ή�
        TYPE_WATER_EXPLOSION,   // ������
        TYPE_REVERSE_CHARGE,    // ���]�`���[�W
        TYPE_25,                // 25%
        TYPE_50,                // 50%
        TYPE_75,                // 75%
        TYPE_100,               // 100%
        TYPE_DRAGON_AURA,       // �h���S���I�[��
        TYPE_DOUBLE_WAVE,       // ��d�E�F�[�u
        TYPE_PARTICLE_JPG,	    // ���p�[�e�B�N��(jpg)
        TYPE_FIRE,              // ��
        TYPE_MAGMA,             // �}�O�}
        TYPE_LEAF,              // �t����
        TYPE_BRANCH,            // �}
        TYPE_RED_FIRE,          // �Ԃ���
        TYPE_BLUE_FIRE,         // ����
        TYPE_YELLOW_FIRE,       // ���F����
        TYPE_PURPLE_FIRE,       // ���̉�
        TYPE_CLOUD,             // �_
        TYPE_PART_EXPLOSION,    // �p�[�e�B�N���ɂ�锚��
        TYPE_BONUS_POINT,       // �{�[�i�X�|�C���g
        TYPE_SMALL_EXPLOSION,   // �e�����������ꂽ���́A�����Ȕ���
        TYPE_MAX			    // ��ނ̍ő吔
    }TYPE;
    CEffect();
    ~CEffect();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type);
    float GetAngleToDragon(void);   // �h���S���ւ̊p�x���擾

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    D3DXVECTOR3 m_move; // �ړ���
    D3DXCOLOR m_col;    // �F
    int m_nLife;        // ���C�t
    TYPE m_type;        // �G�t�F�N�g�̎��

    bool m_bAlphaDown;  // �����x��������t���O

    float m_fRotSpeed;  // ��]���x
    float m_fAngle;     // �p�x
};

#endif