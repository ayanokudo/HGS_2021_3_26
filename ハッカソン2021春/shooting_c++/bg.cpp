//===============================================
//
// �w�i���� (bg.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "bg.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "enemy.h"

//================================================
// �}�N����`
//================================================

// �X�e�[�W1�̔w�i 
#define STAGE1_SKY_FLOW_SPEED 1000           // ��̗���鑬�x
#define STAGE1_SKY_FLOW_SPEED_BOSS 1000      // �{�X�펞�́A��̗���鑬�x
#define STAGE1_SKY_RED_RATE 0.001f           // ���񂾂���Ԃ�����
#define STAGE1_MOUNTAIN_FLOW_SPEED 500       // �R�̗���鑬�x
#define STAGE1_MOUNTAIN_FLOW_SPEED_BOSS 1000 // �R�̗���鑬�x(�{�X��ɓ���Ƃ�)
#define STAGE1_MOUNTAIN_FLOW_UP_RATE 0.175f  // �R�����񂾂�オ���Ă�������
#define STAGE1_WOODS_FLOW_SPEED 250          // �т̗���鑬�x
#define STAGE1_WOODS_FLOW_SPEED_BOSS 500     // �т̗���鑬�x(�{�X��ɓ���Ƃ�)
#define STAGE1_WOODS_STOP_POS 400.0f         // �т̗��ꂪ�~�܂�ʒu
#define STAGE1_WOODS_FLOW_UP_RATE 0.35f      // �т����񂾂�オ���Ă�������
#define STAGE1_FOREST_FIRST_POS D3DXVECTOR3(SCREEN_WIDTH + 825.0f, SCREEN_HEIGHT / 2 + 80.0f, 0.0f)    // �X�̍ŏ��̈ʒu
#define STAGE1_FOREST_SIZE  (D3DXVECTOR3(625.0f, 625.0f,0.0f))                                 // �X�̑傫��
#define STAGE1_FOREST_SPEED_X 2.75f                                                            // �X�̉��ړ��̑���
#define STAGE1_FOREST_STOP_COUNT 330                                                           // �X���~�܂�܂ł̃J�E���^
#define STAGE1_FOREST_SHAKE_POS_X 4.5f                                                         // �X���h���l

// �X�e�[�W2�̔w�i
#define STAGE2_SAND_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 80.0f,0.0f))   // ���̈ʒu
#define STAGE2_SAND_SIZE (D3DXVECTOR3(SCREEN_WIDTH, 180.0f,0.0f))                     // ���̑傫��
#define STAGE2_SAND_FLOW_SPEED 400                                                    // ���̗���鑬�x
#define STAGE2_ROCKS_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150.0f,0.0f)) // ��̈ʒu
#define STAGE2_ROCKS_SIZE (D3DXVECTOR3(SCREEN_WIDTH + 60.0f, 360.0f,0.0f))            // ��̑傫��
#define STAGE2_ROCKS_FLOW_SPEED 600                                                   // ��̗���鑬�x
#define STAGE2_FISHES_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 400.0f,0.0f))// ���Q�̈ʒu
#define STAGE2_FISHES_SIZE (D3DXVECTOR3(SCREEN_WIDTH + 720.0f, 360.0f,0.0f))          // ���Q�̑傫��
#define STAGE2_FISHES_FLOW_SPEED 2000                                                 // ���Q�̗���鑬�x
#define STAGE2_OCEAN_FLOW_SPEED 800                                                   // �C�̗���鑬�x
#define STAGE2_OCEAN_FLOW_SPEED_BOSS 800                                              // �C�̗���鑬�x(�{�X��)
#define STAGE2_RED_FADE_RATE 0.003f                                                   // �ԃt�F�[�h����
#define STAGE2_RED_FADE_MAX 0.78f                                                     // �ԃt�F�[�h�̍ő�l

// �X�e�[�W3�̔w�i
#define STAGE3_TAKE_OFF_TO_THE_SKY 2850                                                     // ��ɔ�ї��J�E���^(game.cpp�̃J�E���^�ƒ���)
#define STAGE3_END_SKY_MODE 4850                                                            // �󃂁[�h�̏I��
#define STAGE3_RED_SKY_FLOW_SPEED 2850                                                      // �Ԃ���̗���鑬�x
#define STAGE3_IN_THE_RED_SKY_FLOW_SPEED 400                                                // �Ԃ���̒��̎��́A����鑬�x
#define STAGE3_RED_SKY_SPEED_BOSS 600                                                       // �Ԃ���̃{�X�펞�̗���鑬�x
#define STAGE3_DEAD_END_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100.0f,0.0f))    // �s���~�܂�̈ʒu
#define STAGE3_DEAD_END_SIZE (D3DXVECTOR3(SCREEN_WIDTH + 70.0f, 400.0f,0.0f))               // �s���~�܂�̑傫��
#define STAGE3_RED_GROUND_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150.0f,0.0f))  // �Ԃ��n�ʂ̈ʒu
#define STAGE3_RED_GROUND_SIZE (D3DXVECTOR3(SCREEN_WIDTH + 60.0f, 360.0f,0.0f))             // �Ԃ��n�ʂ̑傫��
#define STAGE3_RED_GROUND_FLOW_SPEED 600                                                    // �Ԃ��n�ʂ̗���鑬�x
#define STAGE3_VOLCANO_POS (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 400.0f,0.0f))     // �ΎR�̈ʒu
#define STAGE3_VOLCANO_SIZE (D3DXVECTOR3(SCREEN_WIDTH + 720.0f, 275.0f,0.0f))               // �ΎR�̑傫��
#define STAGE3_VOLCANO_FLOW_SPEED 2000                                                      // �ΎR�̗���鑬�x
#define STAGE3_THE_TOP_POS (D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2) + 300.0f, SCREEN_HEIGHT - 135.0f,0.0f))// ����̈ʒu
#define STAGE3_THE_TOP_SIZE (D3DXVECTOR3(SCREEN_WIDTH + 100.0f, 300.0f,0.0f))                                    // ����̑傫��
#define STAGE3_THE_TOP_FLOAT_IN_SPEED 3.6f                                                  // ����̗���鑬�x
#define STAGE3_STOP_POS_X -2000.0f                                                          // �s���~�܂���~�߂�ʒu
#define STAGE3_STOP_POS_Y 1440.0f                                                           // ��ȊO���~�߂�ʒu
#define STAGE3_RED_RATE 0.001f                                                              // ���񂾂�Ԃ�����
#define STAGE3_RED_MAX 0.5f                                                                 // �Ԃ݂̍ő�
#define STAGE3_RED_MIN 0.9f                                                                 // �Ԃ݂̍ŏ�

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[CBg::TYPE_MAX] = {};
bool CBg::m_bShake = false;
int CBg::m_nCntState = 0;
bool CBg::m_bEraseForest = false;
bool CBg::m_bInTheSky = false;

//========================================
// �w�i�̃R���X�g���N�^
//========================================
CBg::CBg() :CScene(OBJTYPE::OBJTYPE_BG)
{
    for (int nCntBg = 0; nCntBg < CBg::TYPE_MAX; nCntBg++)
    {
        m_apScene2D[nCntBg] = NULL;
    }

    m_col = DEFAULT_COLOR;
    m_set = SET_NONE;
    m_nCntTime = 0;
    m_nCntState = 0;
    m_bShake = false;
    m_bEraseForest = false;
    m_bInTheSky = false;
}

//========================================
// �w�i�̃f�X�g���N�^
//========================================
CBg::~CBg()
{

}

//========================================
// �w�i�̉摜���[�h����
//========================================
HRESULT CBg::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg000.jpg", &m_apTexture[CBg::TYPE_SKY]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg003.png", &m_apTexture[CBg::TYPE_MOUNTAIN]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg001.png", &m_apTexture[CBg::TYPE_WOODS]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/forest000.png", &m_apTexture[CBg::TYPE_FOREST]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/sand000.png", &m_apTexture[CBg::TYPE_SAND]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg002.png", &m_apTexture[CBg::TYPE_OCEAN]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg004.png", &m_apTexture[CBg::TYPE_ROCKS]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg005.png", &m_apTexture[CBg::TYPE_FISHES]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg006.png", &m_apTexture[CBg::TYPE_DEAD_END]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg000.jpg", &m_apTexture[CBg::TYPE_RED_SKY]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg007.png", &m_apTexture[CBg::TYPE_RED_GROUND]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg008.png", &m_apTexture[CBg::TYPE_VOLCANO]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg009.png", &m_apTexture[CBg::TYPE_THE_TOP]);

    return S_OK;
}

//========================================
// �w�i�̉摜�j������
//========================================
void CBg::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CBg::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// �w�i�̍쐬
//================================
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, SET set)
{
    CBg *pBg = NULL;

    // ���������m��
    pBg = new CBg;

    // �����ƃ����o�ϐ������т���
    pBg->m_set = set;

    // ������
    pBg->Init(pos, size);

    return pBg;
}

//========================================
// �w�i�̏���������
//========================================
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    switch (m_set)
    {
    case SET_A:

        // �����Ə�����
        m_apScene2D[CBg::TYPE_SKY] = new CScene2D;
        m_apScene2D[CBg::TYPE_SKY]->CScene2D::Init(pos, size);
        m_apScene2D[CBg::TYPE_MOUNTAIN] = new CScene2D;
        m_apScene2D[CBg::TYPE_MOUNTAIN]->CScene2D::Init(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), size);
        m_apScene2D[CBg::TYPE_WOODS] = new CScene2D;
        m_apScene2D[CBg::TYPE_WOODS]->CScene2D::Init(pos + D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 4 - 25.0f, 0.0f), size);
        m_apScene2D[CBg::TYPE_FOREST] = new CScene2D;
        m_apScene2D[CBg::TYPE_FOREST]->CScene2D::Init(STAGE1_FOREST_FIRST_POS, STAGE1_FOREST_SIZE);

        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_SKY]->BindTexture(m_apTexture[CBg::TYPE_SKY]);
        m_apScene2D[CBg::TYPE_WOODS]->BindTexture(m_apTexture[CBg::TYPE_WOODS]);
        m_apScene2D[CBg::TYPE_MOUNTAIN]->BindTexture(m_apTexture[CBg::TYPE_MOUNTAIN]);
        m_apScene2D[CBg::TYPE_FOREST]->BindTexture(m_apTexture[CBg::TYPE_FOREST]);

        break;

    case SET_B:

        // �C
        // �����Ə�����
        m_apScene2D[CBg::TYPE_OCEAN] = new CScene2D;
        m_apScene2D[CBg::TYPE_OCEAN]->CScene2D::Init(pos, size);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_OCEAN]->BindTexture(m_apTexture[CBg::TYPE_OCEAN]);

        // ���Q
        // �����Ə�����
        m_apScene2D[CBg::TYPE_FISHES] = new CScene2D;
        m_apScene2D[CBg::TYPE_FISHES]->CScene2D::Init(STAGE2_FISHES_POS, STAGE2_FISHES_SIZE);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_FISHES]->BindTexture(m_apTexture[CBg::TYPE_FISHES]);

        // ��
        // �����Ə�����
        m_apScene2D[CBg::TYPE_ROCKS] = new CScene2D;
        m_apScene2D[CBg::TYPE_ROCKS]->CScene2D::Init(STAGE2_ROCKS_POS, STAGE2_ROCKS_SIZE);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_ROCKS]->BindTexture(m_apTexture[CBg::TYPE_ROCKS]);

        // ��
        // �����Ə�����
        m_apScene2D[CBg::TYPE_SAND] = new CScene2D;
        m_apScene2D[CBg::TYPE_SAND]->CScene2D::Init(STAGE2_SAND_POS, STAGE2_SAND_SIZE);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_SAND]->BindTexture(m_apTexture[CBg::TYPE_SAND]);

        break;

    case SET_C:

        // �Ԃ���
        // �����Ə�����
        m_apScene2D[CBg::TYPE_RED_SKY] = new CScene2D;
        m_apScene2D[CBg::TYPE_RED_SKY]->CScene2D::Init(pos, size);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_RED_SKY]->BindTexture(m_apTexture[CBg::TYPE_RED_SKY]);

        // �Ԃ��n��
        // �����Ə�����
        m_apScene2D[CBg::TYPE_RED_GROUND] = new CScene2D;
        m_apScene2D[CBg::TYPE_RED_GROUND]->CScene2D::Init(STAGE3_RED_GROUND_POS, STAGE3_RED_GROUND_SIZE);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_RED_GROUND]->BindTexture(m_apTexture[CBg::TYPE_RED_GROUND]);

        // �ΎR
        // �����Ə�����
        m_apScene2D[CBg::TYPE_VOLCANO] = new CScene2D;
        m_apScene2D[CBg::TYPE_VOLCANO]->CScene2D::Init(STAGE3_VOLCANO_POS, STAGE3_VOLCANO_SIZE);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_VOLCANO]->BindTexture(m_apTexture[CBg::TYPE_VOLCANO]);

        // �s���~�܂�
        // �����Ə�����
        m_apScene2D[CBg::TYPE_DEAD_END] = new CScene2D;
        m_apScene2D[CBg::TYPE_DEAD_END]->CScene2D::Init(STAGE3_DEAD_END_POS, STAGE3_DEAD_END_SIZE);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_DEAD_END]->BindTexture(m_apTexture[CBg::TYPE_DEAD_END]);

        // ����
        // �����Ə�����
        m_apScene2D[CBg::TYPE_THE_TOP] = new CScene2D;
        m_apScene2D[CBg::TYPE_THE_TOP]->CScene2D::Init(STAGE3_THE_TOP_POS, STAGE3_THE_TOP_SIZE);
        // �e�N�X�`�������蓖��
        m_apScene2D[CBg::TYPE_THE_TOP]->BindTexture(m_apTexture[CBg::TYPE_THE_TOP]);

        break;
    }

    return S_OK;
}

//========================================
// �w�i�̏I������
//========================================
void CBg::Uninit(void)
{
    // �I������
    for (int nCntBg = 0; nCntBg < CBg::TYPE_MAX; nCntBg++)
    {
        if (m_apScene2D[nCntBg] != NULL)
        {
            m_apScene2D[nCntBg]->Uninit();
            m_apScene2D[nCntBg] = NULL;
        }
    }

    Release();
}
//========================================
// �w�i�̍X�V����
//========================================
void CBg::Update(void)
{
    // �ϐ��錾
    bool bBossBattle = false;           // �{�X�o�g�������ǂ���
    D3DXVECTOR3 pos = DEFAULT_VECTOR;   // �ʒu

    // �{�X�o�g�������ǂ������擾
    bBossBattle = CGame::GetBossBattle();

    switch (m_set)
    {
    case SET_A:

        if (bBossBattle == false)
        {// �ʏ펞

            m_apScene2D[CBg::TYPE_SKY]->SetFlowingAnimation(1, STAGE1_SKY_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);
            m_apScene2D[CBg::TYPE_MOUNTAIN]->SetFlowingAnimation(1, STAGE1_MOUNTAIN_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);
            m_apScene2D[CBg::TYPE_WOODS]->SetFlowingAnimation(1, STAGE1_WOODS_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);
        }
        else
        {// �{�X�o�g����

            // �^�C�����Z
            m_nCntTime++;

            // ����ŁA�^�C�����~�߂�
            if (m_nCntTime > STAGE1_FOREST_STOP_COUNT)
            {
                m_nCntTime = STAGE1_FOREST_STOP_COUNT;
            }

            // ����������ɂ���
            m_apScene2D[CBg::TYPE_SKY]->SetFlowingAnimation(1, STAGE1_SKY_FLOW_SPEED_BOSS, true, CScene2D::DIRECT_HORIZON);

            //====================================================================================================
            // �т̈ʒu���擾
            pos = m_apScene2D[CBg::TYPE_WOODS]->GetPosition();

            // �т̈ʒu�����񂾂���(���̈ʒu�ɒB����܂�)
            if (pos.y >= STAGE1_WOODS_STOP_POS)
            {
                // �т����񂾂���
                pos.y -= STAGE1_WOODS_FLOW_UP_RATE;

                // �т̈ʒu�𔽉f
                m_apScene2D[CBg::TYPE_WOODS]->SetPosition(pos);

                // �т��������ɂ���i���̈ʒu�Ŏ~�߂�j
                m_apScene2D[CBg::TYPE_WOODS]->SetFlowingAnimation(1, STAGE1_WOODS_FLOW_SPEED_BOSS, true, CScene2D::DIRECT_HORIZON);

                // �w�i��Ԃ����Ă���
                m_col.g -= STAGE1_SKY_RED_RATE;
                m_col.b -= STAGE1_SKY_RED_RATE;
                m_apScene2D[CBg::TYPE_SKY]->SetColor(m_col);
                m_apScene2D[CBg::TYPE_MOUNTAIN]->SetColor(m_col);
                m_apScene2D[CBg::TYPE_WOODS]->SetColor(m_col);

                // �R�̈ʒu���擾
                pos = m_apScene2D[CBg::TYPE_MOUNTAIN]->GetPosition();

                // �R�����񂾂���
                pos.y -= STAGE1_MOUNTAIN_FLOW_UP_RATE;

                // �R�̈ʒu�𔽉f
                m_apScene2D[CBg::TYPE_MOUNTAIN]->SetPosition(pos);

                // �R���������ɂ���i���̈ʒu�Ŏ~�߂�j
                m_apScene2D[CBg::TYPE_MOUNTAIN]->SetFlowingAnimation(1, STAGE1_MOUNTAIN_FLOW_SPEED_BOSS, true, CScene2D::DIRECT_HORIZON);
            }
            //======================================================================================================


            //=========================================================
            // �X�̈ʒu���擾
            pos = m_apScene2D[CBg::TYPE_FOREST]->GetPosition();

            // �^�C�������ȉ��Ȃ�ړ�
            if (m_nCntTime < STAGE1_FOREST_STOP_COUNT)
            {
                // ���ֈړ�
                pos.x -= STAGE1_FOREST_SPEED_X;
            }

            // �X�̈ʒu�𔽉f
            m_apScene2D[CBg::TYPE_FOREST]->SetPosition(pos);
            //=========================================================
        }

        // ���_���W�̍X�V
        m_apScene2D[CBg::TYPE_SKY]->SetVertex();
        m_apScene2D[CBg::TYPE_MOUNTAIN]->SetVertex();
        m_apScene2D[CBg::TYPE_WOODS]->SetVertex();

        // �X�͗h�炷���ǂ����ŏꍇ����
        if (m_bShake == true)
        {
            // �����Ŋ����Ȃ�A�E�ɗh���
            if (m_nCntState % 2 == 0)
            {
                // ��������̈ʒu��ݒ�
                m_apScene2D[CBg::TYPE_FOREST]->SetVisualVertex(D3DXVECTOR3(pos.x + STAGE1_FOREST_SHAKE_POS_X, pos.y, 0.0f),
                    STAGE1_FOREST_SIZE);
            }
            // ��Ȃ獶
            else
            {
                // ��������̈ʒu��ݒ�
                m_apScene2D[CBg::TYPE_FOREST]->SetVisualVertex(D3DXVECTOR3(pos.x - STAGE1_FOREST_SHAKE_POS_X, pos.y, 0.0f),
                    STAGE1_FOREST_SIZE);
            }

            // �F��ς���(��)
            m_apScene2D[CBg::TYPE_FOREST]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
        }
        else
        {
            // �ʏ�
            m_apScene2D[CBg::TYPE_FOREST]->SetVertex();
        }

        break;

    case SET_B:

        if (bBossBattle == false)
        {// �ʏ펞
            m_apScene2D[CBg::TYPE_OCEAN]->SetFlowingAnimation(1, STAGE2_OCEAN_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);
            m_apScene2D[CBg::TYPE_FISHES]->SetFlowingAnimation(1, STAGE2_FISHES_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);
            m_apScene2D[CBg::TYPE_ROCKS]->SetFlowingAnimation(1, STAGE2_ROCKS_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);
            m_apScene2D[CBg::TYPE_SAND]->SetFlowingAnimation(1, STAGE2_SAND_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);
        }
        else
        {// �{�X�o�g����

            // �w�i��Ԃ����Ă���
            m_col.g -= STAGE2_RED_FADE_RATE;
            m_col.b -= STAGE2_RED_FADE_RATE;

            // �ő�܂ŐԂ�����
            if (m_col.g <= STAGE2_RED_FADE_MAX)
            {
                m_col.g = STAGE2_RED_FADE_MAX;
                m_col.b = STAGE2_RED_FADE_MAX;
            }

            // �F�𔽉f
            m_apScene2D[CBg::TYPE_OCEAN]->SetColor(m_col);
            m_apScene2D[CBg::TYPE_SAND]->SetColor(m_col);

            // ���Q�͏�ɗ����
            m_apScene2D[CBg::TYPE_FISHES]->SetFlowingAnimation(1, STAGE2_FISHES_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);

            // �C�͂�����藬���
            m_apScene2D[CBg::TYPE_OCEAN]->SetFlowingAnimation(1, STAGE2_OCEAN_FLOW_SPEED_BOSS, true, CScene2D::DIRECT_HORIZON);
        }

        // ���_���W�̍X�V
        m_apScene2D[CBg::TYPE_OCEAN]->SetVertex();
        m_apScene2D[CBg::TYPE_FISHES]->SetVertex();
        m_apScene2D[CBg::TYPE_ROCKS]->SetVertex();
        m_apScene2D[CBg::TYPE_SAND]->SetVertex();

        break;

    case SET_C:

        // ���Ԃ𐔂���
        m_nCntTime++;

        // ��ї��܂�
        if (m_nCntTime < STAGE3_TAKE_OFF_TO_THE_SKY)
        {
            m_apScene2D[CBg::TYPE_RED_SKY]->SetFlowingAnimation(1, STAGE3_RED_SKY_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);

            m_apScene2D[CBg::TYPE_RED_GROUND]->SetFlowingAnimation(1, STAGE3_RED_GROUND_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);

            m_apScene2D[CBg::TYPE_VOLCANO]->SetFlowingAnimation(1, STAGE3_VOLCANO_FLOW_SPEED, true, CScene2D::DIRECT_HORIZON);

            // ���񂾂�Ԃ�
            if (m_col.g > STAGE3_RED_MAX)
            {
                m_col.g -= STAGE3_RED_RATE;
                m_col.b -= STAGE3_RED_RATE;
            }
        }
        // ��ї�������
        else if(m_nCntTime >= STAGE3_TAKE_OFF_TO_THE_SKY && m_nCntTime < STAGE3_END_SKY_MODE)
        {
            // ��̃J�E���^�����Z�b�g
            if (m_nCntTime == STAGE3_TAKE_OFF_TO_THE_SKY)
            {
                m_apScene2D[CBg::TYPE_RED_SKY]->ResetCountAnim();
            }

            // ��̒�
            m_bInTheSky = true;

            // ��̗���鑬�x���グ��
            m_apScene2D[CBg::TYPE_RED_SKY]->SetFlowingAnimation(1, STAGE3_IN_THE_RED_SKY_FLOW_SPEED, true, CScene2D::DIRECT_RIGHT_UP);

            // ��ȊO�������鏈��
            //===========================================================================
            // �ʒu���擾
            pos = m_apScene2D[CBg::TYPE_RED_GROUND]->GetPosition();

            // ���ֈړ�
            pos.y += FLOWING_STAGE;

            // ���S�Ɍ����Ȃ��ʒu�Ŏ~�߂Ă���
            if (pos.y > STAGE3_STOP_POS_Y)
            {
                pos.y = STAGE3_STOP_POS_Y;
            }

            // �ʒu�𔽉f
            m_apScene2D[CBg::TYPE_RED_GROUND]->SetPosition(pos);
            //============================================================================
            // �ʒu���擾
            pos = m_apScene2D[CBg::TYPE_VOLCANO]->GetPosition();

            // ���ֈړ�
            pos.y += FLOWING_STAGE;

            // ���S�Ɍ����Ȃ��ʒu�Ŏ~�߂Ă���
            if (pos.y > STAGE3_STOP_POS_Y)
            {
                pos.y = STAGE3_STOP_POS_Y;
            }

            // �ʒu�𔽉f
            m_apScene2D[CBg::TYPE_VOLCANO]->SetPosition(pos);
            //===========================================================================

            // ���񂾂�Ԃ݂�����
            if (m_col.g < STAGE3_RED_MIN)
            {
                m_col.g += STAGE3_RED_RATE;
                m_col.b += STAGE3_RED_RATE;
            }
        }
        else if(m_nCntTime >= STAGE3_END_SKY_MODE)
        {
            // �J�E���^�Œ�
            m_nCntTime = STAGE3_END_SKY_MODE;

            // �󃂁[�h�I��
            m_bInTheSky = false;

            // ��̗���鑬�x��x��
            m_apScene2D[CBg::TYPE_RED_SKY]->SetFlowingAnimation(1, STAGE3_RED_SKY_SPEED_BOSS, true, CScene2D::DIRECT_HORIZON);

            // �{�X�펞
            if (bBossBattle == true)
            {
                // ���񂾂�Ԃ�
                if (m_col.g > STAGE3_RED_MAX)
                {
                    m_col.g -= STAGE3_RED_RATE;
                    m_col.b -= STAGE3_RED_RATE;
                }

                // ����̏���
                //===========================================================================
                // �ʒu���擾
                pos = m_apScene2D[CBg::TYPE_THE_TOP]->GetPosition();

                // �^�񒆂��E���Ȃ�
                if (pos.x > SCREEN_WIDTH / 2)
                {
                    // ���ֈړ�
                    pos.x -= STAGE3_THE_TOP_FLOAT_IN_SPEED;
                }

                // �ʒu�𔽉f
                m_apScene2D[CBg::TYPE_THE_TOP]->SetPosition(pos);
                //===========================================================================
            }
        }

        // �s���~�܂�̏���
        //===========================================================================
        // �ʒu���擾
        pos = m_apScene2D[CBg::TYPE_DEAD_END]->GetPosition();

        // ���ֈړ�
        pos.x -= FLOWING_STAGE;

        // ���S�Ɍ����Ȃ��ʒu�Ŏ~�߂Ă���
        if (pos.x < STAGE3_STOP_POS_X)
        {
            pos.x = STAGE3_STOP_POS_X;
        }

        // �ʒu�𔽉f
        m_apScene2D[CBg::TYPE_DEAD_END]->SetPosition(pos);
        //===========================================================================

        // �F�̍X�V
        m_apScene2D[CBg::TYPE_RED_SKY]->SetColor(m_col);
        m_apScene2D[CBg::TYPE_RED_GROUND]->SetColor(m_col);
        m_apScene2D[CBg::TYPE_VOLCANO]->SetColor(m_col);
        m_apScene2D[CBg::TYPE_DEAD_END]->SetColor(m_col);
        m_apScene2D[CBg::TYPE_THE_TOP]->SetColor(m_col);

        // ���_���W�̍X�V
        m_apScene2D[CBg::TYPE_DEAD_END]->SetVertex();
        m_apScene2D[CBg::TYPE_RED_SKY]->SetVertex();
        m_apScene2D[CBg::TYPE_RED_GROUND]->SetVertex();
        m_apScene2D[CBg::TYPE_VOLCANO]->SetVertex();
        m_apScene2D[CBg::TYPE_THE_TOP]->SetVertex();

        break;
    }  

    // ��ԃJ�E���^�����Z
    if (m_nCntState > 0)
    {
        m_nCntState--;
    }
    // ��ԃJ�E���^���Ȃ��Ȃ�
    else
    {
        // �h����~�߂�
        m_bShake = false;

        // �X�e�[�W���Ȃ�
        if (m_set == SET_A)
        {
            // �X�������t���O��false�Ȃ�
            if (m_bEraseForest == false)
            {
                // �F��߂�
                m_apScene2D[CBg::TYPE_FOREST]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
            }
        }
    }

    // �X�������t���O��true�Ȃ�
    if (m_bEraseForest == true)
    {
        // �X�e�[�W���Ȃ�
        if (m_set == SET_A)
        {
            // �X������(������)
            m_apScene2D[CBg::TYPE_FOREST]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
        }
    }
}

//========================================
// �w�i�̕`�揈��
//========================================
void CBg::Draw(void)
{
    // DrawAll�ŌĂяo����Ă���
}