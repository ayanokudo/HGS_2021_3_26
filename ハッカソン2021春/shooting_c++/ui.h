//====================================================================
//
// UI�̏��� (ui.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _UI_H_
#define _UI_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "scene2d.h"

//================================================
// �}�N����`
//================================================
#define ARROW_SYMBOL_SIZE (D3DXVECTOR3(80.0f,80.0f,0.0f))   // ���̑傫��

#define PLAYER1_UI_POS (D3DXVECTOR3(100.0f,40.0f,0.0f))     // �v���C���[1�̈ʒu
#define PLAYER1_UI_SIZE (D3DXVECTOR3(150.0f,40.0f,0.0f))    // �v���C���[1�T�C�Y

#define STOCK_UI_POS (D3DXVECTOR3(80.0f,90.0f,0.0f))     // �X�g�b�N�̈ʒu
#define STOCK_UI_SIZE (D3DXVECTOR3(120.0f,40.0f,0.0f))    // �X�g�b�N�T�C�Y

#define BARRIER_UI_POS (D3DXVECTOR3(210.0f,90.0f,0.0f))     // �o���A�̈ʒu
#define BARRIER_UI_SIZE (D3DXVECTOR3(120.0f,40.0f,0.0f))    // �o���A�T�C�Y

#define SPEED_UI_POS (D3DXVECTOR3(340.0f,90.0f,0.0f))     // �X�s�[�h�̈ʒu
#define SPEED_UI_SIZE (D3DXVECTOR3(120.0f,40.0f,0.0f))    // �X�s�[�h�T�C�Y

#define STOCK_BAR_UI_POS (D3DXVECTOR3(100.0f,100.0f,0.0f))                    // �X�g�b�N�̃o�[�̈ʒu
#define STOCK_BAR_UI_SIZE_X (75.0f)                                           // �X�g�b�N�o�[�̉��T�C�Y
#define STOCK_BAR_UI_SIZE (D3DXVECTOR3(STOCK_BAR_UI_SIZE_X,15.0f,0.0f))       // �X�g�b�N�o�[�̃T�C�Y

#define BARRIER_BAR_UI_POS (D3DXVECTOR3(230.0f,100.0f,0.0f))                  // �o���A�̃o�[�̈ʒu
#define BARRIER_BAR_UI_SIZE_X (75.0f)                                         // �o���A�o�[�̉��T�C�Y
#define BARRIER_BAR_UI_SIZE (D3DXVECTOR3(BARRIER_BAR_UI_SIZE_X,15.0f,0.0f))   // �o���A�o�[�̃T�C�Y

#define SPEED_BAR_UI_POS (D3DXVECTOR3(360.0f,100.0f,0.0f))                  // �X�s�[�h�̃o�[�̈ʒu
#define SPEED_BAR_UI_SIZE_X (75.0f)                                         // �X�s�[�h�o�[�̉��T�C�Y
#define SPEED_BAR_UI_SIZE (D3DXVECTOR3(SPEED_BAR_UI_SIZE_X,15.0f,0.0f))     // �X�s�[�h�o�[�̃T�C�Y

#define TITLE_LOGO_FIRST_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, -150.0f, 0.0f))  // �^�C�g�����S�̍ŏ��̈ʒu
#define TITLE_LOGO_TARGET_POS_Y 150.0f                                       // �^�C�g�����S�̖ڕW�ʒu 
#define TITLE_LOGO_SIZE (D3DXVECTOR3(500.0f, 250.0f, 0.0f))                  // �^�C�g�����S�̃T�C�Y
#define TITLE_LOGO_FLOW_DOWN_SPEED 2.0f                                      // �^�C�g�����S�̗��ꗎ���鑬�x

#define MANUAL_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))  // �V�ѕ��̈ʒu
#define MANUAL_SIZE (D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))         // �V�ѕ��̃T�C�Y

#define RESULT_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)) // ���U���g�̈ʒu
#define RESULT_SIZE (D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))        // ���U���g�̃T�C�Y

#define STAGE_START_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25.0f, 0.0f))  // �X�e�[�W�J�n�̈ʒu
#define STAGE_START_MAX_SIZE_X (400.0f)                                                   // �X�e�[�W�J�n�̉��̍ő�T�C�Y
#define STAGE_START_MAX_SIZE_Y (200.0f)                                                   // �X�e�[�W�J�n�̏c�̍ő�T�C�Y
#define STAGE_START_EXTEND_RATE_X (10.0f)                                                 // �X�e�[�W�J�n�̉��̊g�劄��
#define STAGE_START_EXTEND_RATE_Y (5.0f)                                                  // �X�e�[�W�J�n�̏c�̊g�劄��
#define STAGE_START_FADE_OUT_COUNT (180)                                                  // �X�e�[�W�J�n�̃t�F�[�h���n�܂�J�E���^
#define STAGE_START_FADE_OUT_RATE (0.05f)                                                 // �X�e�[�W�J�n�̃t�F�[�h�A�E�g����

#define WARNING_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25.0f, 0.0f))  // ���[�j���O�̈ʒu
#define WARNING_SIZE (D3DXVECTOR3(600.0f, 200.0f, 0.0f))                              // ���[�j���O�̃T�C�Y
#define WARNING_FADE_RATE (0.025f)                                                    // ���[�j���O�̃t�F�[�h�A�E�g����
#define WARNING_FADE_OUT_COUNT (360)                                                  // ���[�j���O�̃t�F�[�h�A�E�g���n�܂�J�E���^

#define BARRIER_SIZE (D3DXVECTOR3(144.0f, 120.0f, 0.0f))    // �o���A�̃T�C�Y
#define BARRIER_FADE_RATE (0.025f)                          // �o���A�̃t�F�[�h�A�E�g����
#define BARRIER_START_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,0.0f)  // �o���A�̊J�n���̐F
#define BARRIER_MAX_ALPHA_1 0.3f                            // �o���A�̍ő僿�l1
#define BARRIER_MAX_ALPHA_2 0.4f                            // �o���A�̍ő僿�l2
#define BARRIER_MAX_ALPHA_3 0.5f                            // �o���A�̍ő僿�l3
#define BARRIER_MAX_ALPHA_4 0.6f                            // �o���A�̍ő僿�l4
#define BARRIER_MAX_ALPHA_5 0.7f                            // �o���A�̍ő僿�l5

#define ZONE_POS D3DXVECTOR3(SCREEN_WIDTH / 2, 65.0f, 0.0f) // �]�[��UI�̈ʒu
#define ZONE_SIZE D3DXVECTOR3(110.0f,110.0f,0.0f)           // �]�[��UI�̃T�C�Y

#define TO_START_POS (D3DXVECTOR3(1000.0f, 65.0f, 0.0f))    // 2P TO START�̈ʒu
#define TO_START_SIZE (D3DXVECTOR3(280.0f, 70.0f, 0.0f))    // 2P TO START�̃T�C�Y

#define CLEAR_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25.0f, 0.0f))  // CLEAR�̈ʒu
#define CLEAR_SIZE (D3DXVECTOR3(600.0f, 100.0f, 0.0f))                              // CLEAR�̃T�C�Y
#define CLEAR_FADE_RATE (0.005f)                                                    // CLEAR�̃t�F�[�h����
#define CLEAR_FADE_OUT_COUNT (480)                                                  // CLEAR�̃t�F�[�h�A�E�g���n�܂�J�E���^

#define GAMEOVER_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25.0f, 0.0f))  // GAMEOVER�̈ʒu
#define GAMEOVER_SIZE (D3DXVECTOR3(700.0f, 150.0f, 0.0f))                              // GAMEOVER�̃T�C�Y
#define GAMEOVER_FADE_RATE (0.0075f)                                                   // GAMEOVER�̃t�F�[�h����

#define PRESS_START_POS D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f)                 // �X�^�[�g�{�^���������Ă˂̈ʒu
#define PRESS_START_SIZE D3DXVECTOR3(500.0f,150.0f,0.0f)                            // �X�^�[�g�{�^���������Ă˂̃T�C�Y
#define PRESS_START_INACTIVE_COLOR D3DXCOLOR(0.431f, 0.431f, 0.388f, 1.0f)          // �X�^�[�g�{�^���������Ă˂̔�A�N�e�B�u�F
#define PRESS_START_FADE_RATE 0.01f                                                 // �X�^�[�g�{�^���������Ă˂̓_�Ŋ���
#define PRESS_START_FADE_OUT_MIN 0.6f                                               // �X�^�[�g�{�^���������Ă˂̃t�F�[�h�A�E�g�̍ŏ��l

#define CAREFUL_UPPER_POS D3DXVECTOR3(SCREEN_WIDTH / 2 - 80.0f, 300.0f, 0.0f)       // �댯�I(��)�̈ʒu
#define CAREFUL_UPPER_SIZE D3DXVECTOR3(650.0f,200.0f,0.0f)                          // �댯�I(��)�̃T�C�Y
#define CAREFUL_DOWN_POS D3DXVECTOR3(SCREEN_WIDTH / 2 , 580.0f, 0.0f)               // �댯�I(��)�̈ʒu
#define CAREFUL_DOWN_SIZE D3DXVECTOR3(600.0f,150.0f,0.0f)                           // �댯�I(��)�̃T�C�Y
#define CAREFUL_LEFT_POS D3DXVECTOR3(150.0f, 360.0f, 0.0f)                          // �댯�I(��)�̈ʒu
#define CAREFUL_LEFT_SIZE D3DXVECTOR3(125.0f,500.0f,0.0f)                           // �댯�I(��)�̃T�C�Y
#define CAREFUL_RIGHT_POS D3DXVECTOR3(SCREEN_WIDTH - 150.0f, 360.0f, 0.0f)          // �댯�I(�E)�̈ʒu
#define CAREFUL_RIGHT_SIZE D3DXVECTOR3(125.0f,500.0f,0.0f)                          // �댯�I(�E)�̃T�C�Y
#define CAREFUL_INACTIVE_COLOR D3DXCOLOR(0.431f, 0.431f, 0.388f, 1.0f)              // �댯�I�̔�A�N�e�B�u�F
#define CAREFUL_FADE_OUT_COUNT (195)                                                // �댯�I�̃t�F�[�h�A�E�g���n�܂�J�E���^

#define DANGER_SIZE D3DXVECTOR3(250.0f,125.0f,0.0f)                                 // �f���W���[�̃T�C�Y
#define DANGER_FADE_OUT_COUNT (90)                                                  // �f���W���[�̃t�F�[�h�A�E�g���n�܂�J�E���^

//================================================
// �N���X�錾
//================================================

// UI�N���X
class CUI : public CScene2D
{
public:
    // UI�̎��
    typedef enum
    {
        TYPE_ARROW_SYMBOL = 0,	// ���
        TYPE_PLAYER1,           // �v���C���[1
        TYPE_STOCK,             // �X�g�b�N
        TYPE_BARRIER,           // �o���A
        TYPE_SPEED,             // �X�s�[�h
        TYPE_STOCK_BAR,         // �X�g�b�N�̃o�[
        TYPE_BARRIER_BAR,       // �o���A�̃o�[
        TYPE_ZONE_A,            // �]�[����
        TYPE_ZONE_B,            // �]�[����
        TYPE_ZONE_C,            // �]�[����
        TYPE_SPEED_BAR,         // �X�s�[�h�̃o�[
        TYPE_TITLE_LOGO,        // �^�C�g���̃��S
        TYPE_PRESS_START,       // �X�^�[�g�{�^���������Ă�
        TYPE_RESULT_SOLO,       // ���U���g(�\��)
        TYPE_RESULT_DUO,        // ���U���g(�f���I)
        TYPE_START_STAGE1,      // �X�e�[�W1�̊J�n
        TYPE_WARNING,           // ���[�j���O
        TYPE_GET_BARRIER,       // �o���A���܂Ƃ�
        TYPE_2P_TO_START,       // 2P�Q���҂�
        TYPE_MANUAL,            // �V�ѕ��̔w�i
        TYPE_CLEAR_A,           // ���N���A
        TYPE_START_STAGE2,      // �X�e�[�W2�̊J�n
        TYPE_START_STAGE3,      // �X�e�[�W3�̊J�n
        TYPE_CLEAR_B,           // ���N���A
        TYPE_CLEAR_C,           // ���N���A
        TYPE_GAMEOVER,          // �Q�[���I�[�o�[
        TYPE_CAREFUL_UPPER,     // �댯�I(��)
        TYPE_CAREFUL_LEFT,      // �댯�I(��)
        TYPE_CAREFUL_RIGHT,     // �댯�I(�E)
        TYPE_DANGER,            // �f���W���[
        TYPE_CAREFUL_DOWN,      // �댯�I(��)
        TYPE_MAX			    // ��ނ̍ő吔
    }TYPE;

    CUI();
    ~CUI();
    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static HRESULT Load(void);
    static void Unload(void);
    static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type);
    static void ChangeZoneTo��(void) { m_bChangeZoneTo�� = true; }
    static void ChangeZoneTo��(void) { m_bChangeZoneTo�� = true; }
    bool Careful(void);
    bool Danger(void);

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];   // �ǂݍ��񂾃e�N�X�`����ۑ�����
    static bool m_bChangeZoneTo��;  // �]�[����UI��ς��邩�ǂ���
    static bool m_bChangeZoneTo��;  // �]�[����UI��ς��邩�ǂ���
    D3DXVECTOR3 m_move; // �ړ���
    D3DXCOLOR m_col;    // �F
    TYPE m_type;        // UI�̎��
    bool m_bFadeOut;    // �t�F�[�h�A�E�g���ǂ���
    bool m_bBlinking;   // �_�Œ����ǂ���
    int m_nCntTime;     // ���Ԃ��J�E���g
};

#endif