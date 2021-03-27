//===================================================================
//
// �G�l�~�[���� (enemy.cpp)
// Author : �㓡�T�V��
//
//===================================================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "effect.h"
#include "score.h"
#include "bullet.h"
#include "item.h"
#include "game.h"
#include "player.h"
#include "block.h"
#include "sound.h"
#include "ui.h"
#include "afterimage.h"
#include "reverse.h"
#include "bg.h"
#include "foreground.h"

//===========================================================
// �}�N����`
//===========================================================
#define COLOR_YELLOW D3DXCOLOR(0.929f, 0.427f, 0.0f, 1.0f)  // ���F���ƌ��Â炢���߁A�I�����W�ɋ߂�

//===========================================================
// �ÓI�����o�ϐ��錾
//===========================================================
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[CEnemy::TYPE_MAX] = {};

//============================================================
// �G�l�~�[�̃R���X�g���N�^
//============================================================
CEnemy::CEnemy() :CScene2D(OBJTYPE::OBJTYPE_ENEMY)
{
    m_posOld = DEFAULT_VECTOR;
    m_move = DEFAULT_VECTOR;
    for (int nCnt = 0; nCnt < MAX_ENEMY_COLLISION; nCnt++)
    {
        m_aCollision[nCnt].posToShift = DEFAULT_VECTOR;
        m_aCollision[nCnt].size = DEFAULT_VECTOR;
    }
    m_nCntCollision = 0;
    m_nWhereHit = -1;
    m_nLife = 0;
    m_nMaxLife = 0;
    m_nCounterState = 0;
    m_nCounterHitWater = 0;
    m_nCounterHitLight = 0;
    m_nCounterAttackCoolTime = 0;
    m_nCntChangeMove = 0;
    m_nBound = 1;   // �X�R�A�v�Z���ɂ����������̂ŁA�o�E���h�񐔂�1
    m_fMoveAngle = 0.0f;
    m_fDestAngle = 0.0f;
    m_fMinAngle = 0.0f;
    m_bMoveUp = false;
    m_bDefeatWithWeak = false;
    m_bDefeatOneHit = false;
    m_type = CEnemy::TYPE_MAX;
    m_element = ELEMENT_MAX;

    m_moveAngle = MOVE_STRAIGHT;
    m_fSpeed = 0.0f;

    m_bUse = true;
}

//============================================================
// �G�l�~�[�̃f�X�g���N�^
//============================================================
CEnemy::~CEnemy()
{

}

//============================================================
// �G�l�~�[�̏���������
//============================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//============================================================
// �G�l�~�[�̏I������
//============================================================
void CEnemy::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//============================================================
// �G�l�~�[�̍X�V����
//============================================================
void CEnemy::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();    // �ʒu���擾
    D3DXVECTOR3 size = GetSize();       // �T�C�Y���擾
    bool bUse = true;                   // �g�p���邩�ǂ���
    float fAngle = 0.0f;                // �p�x
    int nRandNum = 0;                   // �����_���Ȑ�

    // �v���C���[���̕ϐ��錾
    CPlayer *pPlayer = NULL;                   // �v���C���[���擾
    D3DXVECTOR3 playerPos = PLAYER_POS;        // �v���C���[�̈ʒu

    // �v���C���[�����݂��Ă���Ȃ�
    if (CGame::GetDispPlayer() == true)
    {
        // �v���C���[�����擾
        pPlayer = CGame::GetPlayer();
        playerPos = pPlayer->GetPosition();
    }

    // 1F�O�̈ʒu���L��
    m_posOld = pos;

    // �ړ�
    pos = move(pos, size);

    //==================================================================================================================
    // ��ނɉ������ꍇ����
    switch (m_type)
    {
    case CEnemy::TYPE_FLY:

        //// �e�N�X�`�����W���X�V
        //SetAnimation(1, 2);



        break;
    }
    //==================================================================================================================

    if (m_moveAngle == MOVE_ANGLE_LEFT)
    {
        m_fMoveAngle -= ROT_SPEED;
    }
    else if (m_moveAngle == MOVE_ANGLE_RIGHT)
    {
        m_fMoveAngle += ROT_SPEED;
    }
    else if (m_moveAngle == MOVE_STRAIGHT)
    {

    }

    // �ړ��ʂ��ʒu�ɉ��Z
    pos += m_moveAngle * m_fSpeed;

    // �C�����V�́A���ɓ���������o�E���h
    if (m_type == CEnemy::TYPE_CATERPILLAR)
    {
        pos = Bound(pos, size);
    }

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX(�C�����V�A�C��͉�])
    SetRotVertex(m_fMoveAngle);

    // ��ԃJ�E���^���m�F
    if (m_nCounterState > 0)
    {
        // 0���傫���Ȃ�1����
        m_nCounterState--;
    }
    else
    {
        // �������̃C�����V�ȊO�͒ʏ�F��
        if (m_type == CEnemy::TYPE_CATERPILLAR && m_nCntChangeMove < ENEMY_CATERPILLAR_FALL_COUNT)
        {

        }
        else
        {
            // �ʏ�F��
            SetColor(DEFAULT_COLOR);

            // ���������ꏊ�̃��Z�b�g
            m_nWhereHit = -1;
        }
    }

    // ���̑��i�q�b�g����̃J�E���^���m�F
    if (m_nCounterHitWater > 0)
    {
        m_nCounterHitWater--;
    }

    // ���̑��i�q�b�g����̃J�E���^���m�F
    if (m_nCounterHitLight > 0)
    {
        m_nCounterHitLight--;
    }

    // �����̃N�[���^�C�����m�F
    if (m_nCounterAttackCoolTime > 0)
    {
        m_nCounterAttackCoolTime--;
    }

    // �G�l�~�[�̎������Ȃ��Ȃ������ǂ���
    bUse = DefeatEnemy(pos, size);
   
    // �g�[�s�[�h�͏��ɓ��������甚��
    if (m_type == CEnemy::TYPE_TORPEDO)
    {
        // �̗͂�����Ȃ�
        if (m_nLife > 0)
        {
            bUse = TorpedoExplosion(pos, size);
        }
    }

    if (!m_bUse)
    {
        // �X�R�A���擾
        CScore *pScore = CGame::GetScore();

        // �X�R�A���Z
        pScore->AddScore(GET_SCORE);
    }

    // ��ʂ̒[����2�{�̏ꏊ����o����
    if (OutGame2D(&pos, &size) == true)
    {
        // ���g�p��
        bUse = false;
    }

    // ���g�p����Ȃ�
    if (!bUse || !m_bUse)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//============================================================
// �G�l�~�[�̈ړ�����
//============================================================
D3DXVECTOR3 CEnemy::move(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    D3DXVECTOR3 returnPos = pos;

    // �����̊p�x����
    if (pos.y < ZONE_1)
    {
        if (CForeground::GetDirect1() == CForeground::DIRECT_LEFT)
        {
            m_moveAngle = MOVE_ANGLE_LEFT;
        }
        else
        {
            m_moveAngle = MOVE_ANGLE_RIGHT;
        }
    }
    else if (pos.y >= ZONE_1, pos.y < ZONE_2)
    {
        if (CForeground::GetDirect2() == CForeground::DIRECT_LEFT)
        {
            m_moveAngle = MOVE_ANGLE_LEFT;
        }
        else
        {
            m_moveAngle = MOVE_ANGLE_RIGHT;
        }
    }
    else
    {
        if (CForeground::GetDirect3() == CForeground::DIRECT_LEFT)
        {
            m_moveAngle = MOVE_ANGLE_LEFT;
        }
        else
        {
            m_moveAngle = MOVE_ANGLE_RIGHT;
        }
    }

    // ���E�̋�Ԃ��䂪�܂���
    if (pos.x + (size.x / 2) < 0.0f)
    {
        returnPos.x = SCREEN_WIDTH + (size.x / 2);
    }
    else if (pos.x - (size.x / 2) > SCREEN_WIDTH)
    {
        returnPos.x = -(size.x / 2);
    }

    return returnPos;
}

//============================================================
// �G�l�~�[�̕`�揈��
//============================================================
void CEnemy::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//============================================================
// �G�l�~�[�̉摜���[�h����
//============================================================
HRESULT CEnemy::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //=======================================================================================================
    // ��ނ��Ƃ̃e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy000.png", &m_apTexture[CEnemy::TYPE_FLY]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy001.png", &m_apTexture[CEnemy::TYPE_SKELETON]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &m_apTexture[CEnemy::TYPE_GREEN_BIRD]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy003.png", &m_apTexture[CEnemy::TYPE_CROW]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy004.png", &m_apTexture[CEnemy::TYPE_BLUE_BIRD]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy005.png", &m_apTexture[CEnemy::TYPE_BOSS_FOREST]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy006.png", &m_apTexture[CEnemy::TYPE_CATERPILLAR]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy007.png", &m_apTexture[CEnemy::TYPE_GUSOKU]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy008.png", &m_apTexture[CEnemy::TYPE_SARDINE]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy009.png", &m_apTexture[CEnemy::TYPE_CANNON]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy010.png", &m_apTexture[CEnemy::TYPE_TORPEDO]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy011.png", &m_apTexture[CEnemy::TYPE_BOSS_DRAGON]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy012.png", &m_apTexture[CEnemy::TYPE_RED_BIRD]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy013.png", &m_apTexture[CEnemy::TYPE_BAT]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy014.png", &m_apTexture[CEnemy::TYPE_MULTI_BIRD]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy015.png", &m_apTexture[CEnemy::TYPE_BOSS_BLAZE]);
    //=======================================================================================================

    return S_OK;
}

//============================================================
// �G�l�~�[�̉摜�j������
//============================================================
void CEnemy::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CEnemy::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//====================================================
// �G�l�~�[�̍쐬
//====================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fSpeed, bool bMoveUp, CEnemy::TYPE type)
{
    CEnemy *pEnemy = NULL;

    // ���������m��
    pEnemy = new CEnemy;

    // �^�C�v�̂݁A�e�N�X�`�����蓖�Ă̂��߂Ɍ��т��Ă���
    pEnemy->m_type = type;

    // ������
    pEnemy->Init(pos, size);

    // �����o�ϐ������т���
    pEnemy->m_posOld = pos;
    pEnemy->m_fSpeed = fSpeed;
    pEnemy->m_bMoveUp = bMoveUp;

    //========================================================
    // �G�l�~�[�̎�ނɂ���āA���т���l��ς���
    switch (pEnemy->m_type)
    {
    case CEnemy::TYPE_FLY:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_FLY_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_GRASS;
        pEnemy->m_nLife = ENEMY_FLY_LIFE;
        pEnemy->m_nMaxLife = ENEMY_FLY_LIFE;

        break;

    case CEnemy::TYPE_SKELETON:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = ENEMY_SKELETON_COLLISION_POS;
        pEnemy->m_aCollision[0].size = ENEMY_SKELETON_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_FIRE;
        pEnemy->m_nLife = ENEMY_SKELETON_LIFE;
        pEnemy->m_nMaxLife = ENEMY_SKELETON_LIFE;

        if (bMoveUp == true)
        {// ���ɐi��
            pEnemy->m_move.x = -ENEMY_SKELETON_SPEED;
        }
        else
        {// �E�ɐi��
            pEnemy->m_move.x = ENEMY_SKELETON_SPEED;
        }

        break;

    case CEnemy::TYPE_GREEN_BIRD:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_GREEN_BIRD_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_GRASS;
        pEnemy->m_nLife = ENEMY_GREEN_BIRD_LIFE;
        pEnemy->m_nMaxLife = ENEMY_GREEN_BIRD_LIFE;

        // ���ɐi��
        pEnemy->m_move.x = -ENEMY_GREEN_BIRD_SPEED;

        break;

    case CEnemy::TYPE_CROW:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_CROW_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_MULTI;
        pEnemy->m_nLife = ENEMY_CROW_LIFE;
        pEnemy->m_nMaxLife = ENEMY_CROW_LIFE;

        if (bMoveUp == true)
        {// ���ɐi��
            pEnemy->m_move.x = -ENEMY_CROW_SPEED;
        }
        else
        {// �E�ɐi��
            pEnemy->m_move.x = ENEMY_CROW_SPEED;
        }

        break;

    case CEnemy::TYPE_BLUE_BIRD:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_BLUE_BIRD_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_WATER;
        pEnemy->m_nLife = ENEMY_BLUE_BIRD_LIFE;
        pEnemy->m_nMaxLife = ENEMY_BLUE_BIRD_LIFE;

        // �{�X�펞�͍����֐i��
        if (pEnemy->m_bMoveUp == true)
        {
            pEnemy->m_move.x = -ENEMY_BLUE_BIRD_SPEED;
            pEnemy->m_move.y = ENEMY_BLUE_BIRD_SPEED;
        }
        // �����́AHP����
        else
        {
            pEnemy->m_move.x = -ENEMY_BLUE_BIRD_SPEED;
            pEnemy->m_move.y = ENEMY_BLUE_BIRD_SPEED;

            pEnemy->m_nLife = ENEMY_BLUE_BIRD_WAY_LIFE;
            pEnemy->m_nMaxLife = ENEMY_BLUE_BIRD_WAY_LIFE;
        }

        break;

    case CEnemy::TYPE_BOSS_FOREST:

        pEnemy->m_nCntCollision = 2;
        pEnemy->m_aCollision[0].posToShift = ENEMY_BOSS_FOREST_COLLISION_POS_1;
        pEnemy->m_aCollision[0].size = ENEMY_BOSS_FOREST_COLLISION_SIZE_1;
        pEnemy->m_aCollision[1].posToShift = ENEMY_BOSS_FOREST_COLLISION_POS_2;
        pEnemy->m_aCollision[1].size = ENEMY_BOSS_FOREST_COLLISION_SIZE_2;
        pEnemy->m_element = ELEMENT_GRASS;
        pEnemy->m_nLife = ENEMY_BOSS_FOREST_LIFE;
        pEnemy->m_nMaxLife = ENEMY_BOSS_FOREST_LIFE;

        // ���ɐi��
        pEnemy->m_move.x = -ENEMY_BOSS_FOREST_SPEED_X;

        // ��ɐi��
        pEnemy->m_move.y = -ENEMY_BOSS_FOREST_SPEED_Y;

        break;

    case CEnemy::TYPE_CATERPILLAR:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_CATERPILLAR_SIZE;
        pEnemy->m_element = ELEMENT_GRASS;
        pEnemy->m_nLife = ENEMY_CATERPILLAR_LIFE;
        pEnemy->m_nMaxLife = ENEMY_CATERPILLAR_LIFE;

        break;

    case CEnemy::TYPE_GUSOKU:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_GUSOKU_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_MULTI;
        pEnemy->m_nLife = ENEMY_GUSOKU_LIFE;
        pEnemy->m_nMaxLife = ENEMY_GUSOKU_LIFE;

        if (bMoveUp == true)
        {// ���ɐi��
            pEnemy->m_move.x = -ENEMY_GUSOKU_SPEED;
        }
        else
        {// �E�ɐi��
            pEnemy->m_move.x = ENEMY_GUSOKU_SPEED;
        }

        break;

    case CEnemy::TYPE_SARDINE:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_SARDINE_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_WATER;
        pEnemy->m_nLife = ENEMY_SARDINE_LIFE;
        pEnemy->m_nMaxLife = ENEMY_SARDINE_LIFE;

        if (bMoveUp == true)
        {// ����ɐi��
            pEnemy->m_move = ENEMY_SARDINE_MOVE;
            pEnemy->m_move.x *= -1;
        }
        else
        {// �E��ɐi��
            pEnemy->m_move = ENEMY_SARDINE_MOVE;
        }

        break;

    case CEnemy::TYPE_CANNON:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_CANNON_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_LIGHT;
        pEnemy->m_nLife = ENEMY_CANNON_LIFE;
        pEnemy->m_nMaxLife = ENEMY_CANNON_LIFE;

        pEnemy->m_move.x = -FLOWING_STAGE;

        break;

    case CEnemy::TYPE_TORPEDO:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_TORPEDO_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_LIGHT;
        pEnemy->m_nLife = ENEMY_TORPEDO_LIFE;
        pEnemy->m_nMaxLife = ENEMY_TORPEDO_LIFE;

        // �{�X�o�g�����ȊO�͗����
        if (CGame::GetBossBattle() == false)
        {
            pEnemy->m_move.y = ENEMY_TORPEDO_FALLING_SPEED;
            pEnemy->m_move.x = -FLOWING_STAGE;
        }
        else
        {
            pEnemy->m_move.y = ENEMY_TORPEDO_FALLING_SPEED_IN_BOSS;
        }

        // �ΎR�X�e�[�W�ł́A���ɗ��ꂸ�A�����X�s�[�h�̓{�X�펞�̂���
        if (CGame::GetStage() == CManager::STAGE_C)
        {
            pEnemy->m_move.x = 0.0f;
            pEnemy->m_move.y = ENEMY_TORPEDO_FALLING_SPEED_IN_BOSS;
        }

        break;

    case CEnemy::TYPE_BOSS_DRAGON:

        pEnemy->m_nCntCollision = 3;
        pEnemy->m_aCollision[0].posToShift = ENEMY_BOSS_DRAGON_COLLISION_POS_1;
        pEnemy->m_aCollision[0].size = ENEMY_BOSS_DRAGON_COLLISION_SIZE_1;
        pEnemy->m_aCollision[1].posToShift = ENEMY_BOSS_DRAGON_COLLISION_POS_2;
        pEnemy->m_aCollision[1].size = ENEMY_BOSS_DRAGON_COLLISION_SIZE_2;
        pEnemy->m_aCollision[2].posToShift = ENEMY_BOSS_DRAGON_COLLISION_POS_3;
        pEnemy->m_aCollision[2].size = ENEMY_BOSS_DRAGON_COLLISION_SIZE_3;
        pEnemy->m_element = ELEMENT_WATER;
        pEnemy->m_nLife = ENEMY_BOSS_DRAGON_LIFE;
        pEnemy->m_nMaxLife = ENEMY_BOSS_DRAGON_LIFE;

        // ���ɐi��
        pEnemy->m_move.x = -FLOWING_STAGE;

        // �s���Ǘ��̂��߁A�o�E���h�񐔃��Z�b�g
        pEnemy->m_nBound = DRAGON_ATTACK_NONE;

        break;

    case CEnemy::TYPE_RED_BIRD:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_RED_BIRD_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_FIRE;
        pEnemy->m_nLife = ENEMY_RED_BIRD_LIFE;
        pEnemy->m_nMaxLife = ENEMY_RED_BIRD_LIFE;

        // �E�ɐi��
        pEnemy->m_move.x = ENEMY_RED_BIRD_SPEED;

        break;

    case CEnemy::TYPE_BAT:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_BAT_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_FIRE;
        pEnemy->m_nLife = ENEMY_BAT_LIFE;
        pEnemy->m_nMaxLife = ENEMY_BAT_LIFE;

        break;

    case CEnemy::TYPE_MULTI_BIRD:

        pEnemy->m_nCntCollision = 1;
        pEnemy->m_aCollision[0].posToShift = DEFAULT_VECTOR;
        pEnemy->m_aCollision[0].size = ENEMY_MULTI_BIRD_COLLISION_SIZE;
        pEnemy->m_element = ELEMENT_MULTI;
        pEnemy->m_nLife = ENEMY_MULTI_BIRD_LIFE;
        pEnemy->m_nMaxLife = ENEMY_MULTI_BIRD_LIFE;

        pEnemy->m_move.x = -ENEMY_BLUE_BIRD_SPEED;
        pEnemy->m_move.y = ENEMY_BLUE_BIRD_SPEED;

        break;

    case CEnemy::TYPE_BOSS_BLAZE:

        pEnemy->m_nCntCollision = 2;
        pEnemy->m_aCollision[0].posToShift = ENEMY_BOSS_BLAZE_COLLISION_POS_1;
        pEnemy->m_aCollision[0].size = ENEMY_BOSS_BLAZE_COLLISION_SIZE_1;
        pEnemy->m_aCollision[1].posToShift = ENEMY_BOSS_BLAZE_COLLISION_POS_2;
        pEnemy->m_aCollision[1].size = ENEMY_BOSS_BLAZE_COLLISION_SIZE_2;
        pEnemy->m_element = ELEMENT_FIRE;
        pEnemy->m_nLife = ENEMY_BOSS_BLAZE_LIFE;
        pEnemy->m_nMaxLife = ENEMY_BOSS_BLAZE_LIFE;

        // ���ɐi��
        pEnemy->m_move.x = -ENEMY_BOSS_BLAZE_SPEED;

        // �s���Ǘ��̂��߁A�o�E���h�񐔃��Z�b�g
        pEnemy->m_nBound = BLAZE_ATTACK_NONE;

        break;
    }
    //========================================================

    return pEnemy;
}

//====================================================
// �G�l�~�[�ɒe�������������̏���
//====================================================
void CEnemy::Hit(D3DXVECTOR3 posBullet, const int nCounterState, int nDamage, const int nWhereHit, const ELEMENT element)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();    // �ʒu���擾

    // �q�b�g���Đ�
    CSound *pSound = CManager::GetSound();
    pSound->Play(CSound::LABEL_SE_HIT);

    // ��ԃJ�E���^�����т���
    m_nCounterState = nCounterState;

    // �ǂ��ɓ���������
    m_nWhereHit = nWhereHit;

    // �ђʂ���Ȃ�A���Ɨ��̃q�b�g�J�E���^�����т���
    if (nCounterState != DONT_GO_THROUGH)
    {
        switch (element)
        {
        case ELEMENT_WATER:
            m_nCounterHitWater = BULLET_WATER_AVOID_MULTIPLE_HITS_FRAME;
            break;

        case ELEMENT_LIGHT:
            m_nCounterHitLight = BULLET_LIGHT_AVOID_MULTIPLE_HITS_FRAME;
            break;
        }
    }

    // ��_���������ǂ����̃t���O���A��Ufalse��
    m_bDefeatWithWeak = false;

    // �����p������p�̕ϐ��錾
    bool bMaxLife = false;  // �ő�HP���ǂ���

    // �ő�HP�Ȃ�A�ꔭ�œ|�������ǂ����̌v�Z������t���O��true��
    if (m_nLife == m_nMaxLife)
    {
        bMaxLife = true;
    }

    // �_���[�W�v�Z
    DamageCalculation(posBullet, element, nDamage);

    // �ꔭ�œ|�������ǂ���
    if (bMaxLife == true)
    {
        if (m_nLife <= 0)
        {
            // �ꔭ�œ|�����t���O��true��
            m_bDefeatOneHit = true;
        }
    }
}

//====================================================
// �G�l�~�[�̃_���[�W�v�Z
//====================================================
void CEnemy::DamageCalculation(D3DXVECTOR3 pos, const ELEMENT element, int nDamage)
{
    // �ŏI�I�ȃ_���[�W
    int nFinalDamage = 0;

    // ��_�̃t���O
    bool bWeak = false;

    // �����̃t���O
    bool bHalf = false;

    // �G�l�~�[�̑������ƂɃ_���[�W�v�Z
    switch (m_element)
    {
    case ELEMENT_FIRE:

        // �e�̑������ƂɃ_���[�W�v�Z
        // �e�̑����́A1�̎�_�A2�̔����A1�̒ʏ������
        switch (element)
        {
        case ELEMENT_FIRE:

            // �G�̐F��Ԃ�
            SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

            // ����
            CounterAttack();

            // �u���C�Y�Ȃ�A�����l���グ��
            if (m_type == TYPE_BOSS_BLAZE)
            {
                m_fDestAngle += GOD_FIRE_PLAYER_FIRE_ATTACK_VALUE;

                // �_�����[�h�Ȃ�A���{�Ń_���[�W��ʂ�
                if (m_bMoveUp == true)
                {
                    // �ʏ�
                    nFinalDamage = nDamage;
                }
            }

            break;

        case ELEMENT_WATER:

            // �G�̐F���
            SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

            // ��_
            nFinalDamage = nDamage * 2;
            bWeak = true;

            // ��_�̃t���O��true��
            m_bDefeatWithWeak = true;

            break;

        case ELEMENT_LIGHT:

            // �G�̐F�����F��
            SetColor(COLOR_YELLOW);

            // �ʏ�
            nFinalDamage = nDamage;

            break;
        }

        break;

    case ELEMENT_WATER:

        // �e�̑������ƂɃ_���[�W�v�Z
        switch (element)
        {
        case ELEMENT_FIRE:

            // �G�̐F��Ԃ�
            SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

            // ����
            nFinalDamage = nDamage / 2;
            bHalf = true;

            break;

        case ELEMENT_WATER:

            // �G�̐F���
            SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

            // ����
            CounterAttack();

            break;

        case ELEMENT_LIGHT:

            // �G�̐F�����F��
            SetColor(COLOR_YELLOW);

            // ��_
            nFinalDamage = nDamage * 2;
            bWeak = true;

            // ��_�̃t���O��true��
            m_bDefeatWithWeak = true;

            break;
        }

        break;

    case ELEMENT_LIGHT:

        // �e�̑������ƂɃ_���[�W�v�Z
        switch (element)
        {
        case ELEMENT_FIRE:

            // �G�̐F��Ԃ�
            SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

            // �ʏ�
            nFinalDamage = nDamage;

            break;

        case ELEMENT_WATER:

            // �G�̐F���
            SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

            // �ʏ�
            nFinalDamage = nDamage;

            break;

        case ELEMENT_LIGHT:

            // �G�̐F�����F��
            SetColor(COLOR_YELLOW);

            // ����
            CounterAttack();

            // ����
            nFinalDamage = nDamage / 2;
            bHalf = true;

            break;
        }

        break;

    case ELEMENT_GRASS:

        // �{�X�X�Ȃ�
        if (m_type == TYPE_BOSS_FOREST)
        {
            // �e�̑������ƂɃ_���[�W�v�Z
            switch (element)
            {
            case ELEMENT_FIRE:

                // ���Ȃ�
                if (m_nWhereHit == 0)
                {
                    // �G�̐F��Ԃ�
                    SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
                }

                // ��_
                nFinalDamage = nDamage * 2;
                bWeak = true;

                // ��_�̃t���O��true��
                m_bDefeatWithWeak = true;

                break;

            case ELEMENT_WATER:

                // ���Ȃ�
                if (m_nWhereHit == 0)
                {
                    // �G�̐F���
                    SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
                }

                // ����
                nFinalDamage = nDamage / 2;
                bHalf = true;

                break;

            case ELEMENT_LIGHT:

                // ���Ȃ�
                if (m_nWhereHit == 0)
                {
                    // �G�̐F�����F��
                    SetColor(COLOR_YELLOW);
                }

                // �ʏ�
                nFinalDamage = nDamage;

                break;
            }
        }
        else
        {
            // ���ʂ̓G�Ȃ�
            // �e�̑������ƂɃ_���[�W�v�Z
            switch (element)
            {
            case ELEMENT_FIRE:

                // �G�̐F��Ԃ�
                SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

                // ��_
                nFinalDamage = nDamage * 2;
                bWeak = true;

                // ��_�̃t���O��true��
                m_bDefeatWithWeak = true;

                break;

            case ELEMENT_WATER:

                // �G�̐F���
                SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

                // ����
                nFinalDamage = nDamage / 2;
                bHalf = true;

                break;

            case ELEMENT_LIGHT:

                // �G�̐F�����F��
                SetColor(COLOR_YELLOW);

                // �ʏ�
                nFinalDamage = nDamage;

                break;
            }
        }

        break;

        // �}���`�^�C�v�́A���ׂē��{
    case ELEMENT_MULTI:

        switch (element)
        {
        case ELEMENT_FIRE:

            // �G�̐F��Ԃ�
            SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

            // �ʏ�
            nFinalDamage = nDamage;

            break;

        case ELEMENT_WATER:

            // �G�̐F���
            SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

            // �ʏ�
            nFinalDamage = nDamage;

            break;

        case ELEMENT_LIGHT:

            // �G�̐F�����F��
            SetColor(COLOR_YELLOW);

            // �ʏ�
            nFinalDamage = nDamage;

            break;
        }

        break;
    }

    // �{�X�ɂ́A��_���ʂ����݂���
    switch (m_type)
    {
    case TYPE_BOSS_FOREST:

        // ���Ȃ�
        if (m_nWhereHit == 0)
        {
            // ��_�_���[�W
            nFinalDamage = (int)((float)nFinalDamage * WEAK_HIT_DAMAGE_UP_RATE);
            m_nLife -= nFinalDamage;
        }
        else
        {
            // �_���[�W
            m_nLife -= nFinalDamage;
        }

        break;

    case TYPE_BOSS_DRAGON:

        // ��Ȃ�
        if (m_nWhereHit == 0)
        {
            // ��_�_���[�W
            nFinalDamage = (int)((float)nFinalDamage * WEAK_HIT_DAMAGE_UP_RATE);
            m_nLife -= nFinalDamage;
        }
        else
        {
            // �_���[�W
            m_nLife -= nFinalDamage;
        }

        break;

    case TYPE_BOSS_BLAZE:

        // ��Ȃ�
        if (m_nWhereHit == 0)
        {
            // ��_�_���[�W
            nFinalDamage = (int)((float)nFinalDamage * WEAK_HIT_DAMAGE_UP_RATE);
            m_nLife -= nFinalDamage;
        }
        else
        {
            // �_���[�W
            m_nLife -= nFinalDamage;
        }

        break;

    default:

        // �_���[�W
        m_nLife -= nFinalDamage;

        break;
    }

    // ��_�Ȃ�
    if (bWeak == true)
    {
        // �_���[�W�\��
        CScore *pScore = CGame::GetScore();
        pScore->SetDamage(nFinalDamage, pos, SCORE_DEFEAT_WITH_WEAK_COLOR);
    }

    // �����Ȃ�
    if (bHalf == true)
    {
        // �_���[�W�\��
        CScore *pScore = CGame::GetScore();
        pScore->SetDamage(nFinalDamage, pos, SCORE_DEFEAT_HALF_COLOR);
    }

    // �ʏ�Ȃ�
    if (bWeak == false && bHalf == false)
    {
        // �_���[�W�\��
        CScore *pScore = CGame::GetScore();
        pScore->SetDamage(nFinalDamage, pos, DEFAULT_COLOR);
    }
}

//====================================================
// �G�l�~�[�����ꂽ���ǂ���
//====================================================
bool CEnemy::DefeatEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    bool bUse = true;               // �G���g�����ǂ���
    int nScore = 0;                 // �X�R�A
    D3DXCOLOR col = DEFAULT_COLOR;  // �X�R�A�̕\���F

    // ���C�t��0�ȉ��ɂȂ�����
    if (m_nLife <= 0)
    {
        // �������Đ�
        CSound *pSound = CManager::GetSound();
        pSound->Play(CSound::LABEL_SE_EXPLOSION);

        // �唚���G�t�F�N�g (�T�C�Y�͔{)
        CEffect::Create(pos, size + size,
            DEFAULT_COLOR, CEffect::TYPE_BIG_EXPLOSION);

        // �������Ƃ̉ΉԃG�t�F�N�g
        switch (m_element)
        {
        case ELEMENT_FIRE:

            // �ԉΉԃG�t�F�N�g (�ʒu�͂�����Ɖ��A�T�C�Y��1.5�{)
            CEffect::Create(pos + D3DXVECTOR3(size.x / 2, -(size.y / 4), 0.0f), size + size / 2,
                DEFAULT_COLOR, CEffect::TYPE_RED_SPARK);

            break;

        case ELEMENT_WATER:

            // �ΉԃG�t�F�N�g (�ʒu�͂�����Ɖ��A�T�C�Y��1.5�{)
            CEffect::Create(pos + D3DXVECTOR3(size.x / 2, -(size.y / 4), 0.0f), size + size / 2,
                DEFAULT_COLOR, CEffect::TYPE_BLUE_SPARK);

            break;

        case ELEMENT_LIGHT:

            // ���ΉԃG�t�F�N�g (�ʒu�͂�����Ɖ��A�T�C�Y��1.5�{)
            CEffect::Create(pos + D3DXVECTOR3(size.x / 2, -(size.y / 4), 0.0f), size + size / 2,
                DEFAULT_COLOR, CEffect::TYPE_BLACK_SPARK);

            break;

        case ELEMENT_GRASS:

            // �ΉΉԃG�t�F�N�g (�ʒu�͂�����Ɖ��A�T�C�Y��1.5�{)
            CEffect::Create(pos + D3DXVECTOR3(size.x / 2, -(size.y / 4), 0.0f), size + size / 2,
                DEFAULT_COLOR, CEffect::TYPE_GREEN_SPARK);

            break;

        case ELEMENT_MULTI:

            // ���ΉԃG�t�F�N�g (�ʒu�͂�����Ɖ��A�T�C�Y��1.5�{)
            CEffect::Create(pos + D3DXVECTOR3(size.x / 2, -(size.y / 4), 0.0f), size + size / 2,
                DEFAULT_COLOR, CEffect::TYPE_BLACK_SPARK);

            break;
        }

        //==================================================================
        // �X�R�A���Z
        // ��ނɉ������ꍇ����
        switch (m_type)
        {
        case CEnemy::TYPE_FLY:

            nScore = ENEMY_FLY_SCORE;

            break;

        case CEnemy::TYPE_SKELETON:

            nScore = ENEMY_SKELETON_SCORE;

            break;

        case CEnemy::TYPE_GREEN_BIRD:

            // �o���A�A�C�e���𐶐�
            CItem::Create(pos, ITEM_SIZE, CItem::TYPE_BARRIER);

            if (m_bMoveUp == false)
            {// �ʏ펞
                nScore = ENEMY_GREEN_BIRD_SCORE;
            }
            else
            {// �S�b�h�o�[�h��
                nScore = ENEMY_GREEN_BIRD_SCORE * 4;

                // �{�[�i�X�|�C���g�\�L
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y + BONUS_POINT_ADD_POS_Y, 0.0f),
                    BONUS_POINT_SIZE, DEFAULT_COLOR, CEffect::TYPE_BONUS_POINT);
            }

            break;

        case CEnemy::TYPE_CROW:

            // �X�g�b�N�A�C�e���𐶐�
            CItem::Create(pos, ITEM_SIZE, CItem::TYPE_STOCK);

            nScore = ENEMY_CROW_SCORE;

            break;

        case CEnemy::TYPE_BLUE_BIRD:

            // �o���A�A�C�e���𐶐�
            CItem::Create(pos, ITEM_SIZE, CItem::TYPE_BARRIER);

            nScore = ENEMY_BLUE_BIRD_SCORE;

            break;

        case CEnemy::TYPE_BOSS_FOREST:

            // �X�̂��������
            CBg::EraseForest();

            // �{�XBGM���~�߂�
            pSound->Stop(CSound::LABEL_BGM_BOSS1);

            // ���N���A
            CUI::Create(CLEAR_POS, CLEAR_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f), CUI::TYPE_CLEAR_A);

            // �c�����c��
            CAfterimage::Create(pos, size, 0.0f, DEFAULT_COLOR, CAfterimage::TYPE_BOSS_FOREST);

            // �Q�[���̃J�E���^���~�߂�
            CGame::StopGameCount();

            // ���@�𖳓G��
            CGame::SetInvinciblePlayer();

            // ��_���ʂœ|�������ǂ����ŁA����X�R�A��ς���
            if (m_nWhereHit == ENEMY_BOSS_FOREST_WEEKNESS)
            {
                nScore = ENEMY_BOSS_FOREST_SCORE + ENEMY_BOSS_FOREST_WEEKNESS_ADD_SCORE;

                // �{�[�i�X�|�C���g�\�L
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y + BONUS_POINT_ADD_POS_Y, 0.0f),
                    BONUS_POINT_SIZE, DEFAULT_COLOR, CEffect::TYPE_BONUS_POINT);
            }
            else
            {
                nScore = ENEMY_BOSS_FOREST_SCORE;
            }

            break;

        case CEnemy::TYPE_CATERPILLAR:

            // �C�����V�́A�o�E���h����قǃX�R�A���オ��
            nScore = ENEMY_CATERPILLAR_SCORE * m_nBound;

            break;

        case CEnemy::TYPE_GUSOKU:

            // �X�g�b�N�A�C�e���𐶐�
            CItem::Create(pos, ITEM_SIZE, CItem::TYPE_STOCK);

            nScore = ENEMY_GUSOKU_SCORE;

            break;

        case CEnemy::TYPE_SARDINE:

            nScore = ENEMY_SARDINE_SCORE;

            break;

        case CEnemy::TYPE_CANNON:

            nScore = ENEMY_CANNON_SCORE;

            break;

        case CEnemy::TYPE_TORPEDO:

            // �����Ă���X�e�[�W�ł̋����Ȃ�
            if (m_bMoveUp == true)
            {
                // �o���A�A�C�e���𐶐�
                CItem::Create(pos, ITEM_SIZE, CItem::TYPE_BARRIER);
            }

            // �{�X�o�g�����̓X�R�A���Ⴂ
            if (CGame::GetBossBattle() == false)
            {
                nScore = ENEMY_TORPEDO_SCORE;
            }
            else
            {
                nScore = ENEMY_TORPEDO_SCORE_IN_BOSS;
            }

            break;

        case CEnemy::TYPE_BOSS_DRAGON:

            // �{�XBGM���~�߂�
            pSound->Stop(CSound::LABEL_BGM_BOSS2);

            // ���N���A
            CUI::Create(CLEAR_POS, CLEAR_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f), CUI::TYPE_CLEAR_B);

            // �c�����c��
            CAfterimage::Create(pos, size, 0.0f, DEFAULT_COLOR, CAfterimage::TYPE_BOSS_DRAGON);

            // �Q�[���̃J�E���^���~�߂�
            CGame::StopGameCount();

            // ���@�𖳓G��
            CGame::SetInvinciblePlayer();

            // �v���C���[�̃V���b�N��Ԃ�����
            CGame::SetShockPlayer(false);

            // ��_���ʂœ|�������ǂ����ŁA����X�R�A��ς���
            if (m_nWhereHit == ENEMY_BOSS_DRAGON_WEEKNESS)
            {
                nScore = ENEMY_BOSS_DRAGON_SCORE + ENEMY_BOSS_DRAGON_WEEKNESS_ADD_SCORE;

                // �{�[�i�X�|�C���g�\�L
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y + BONUS_POINT_ADD_POS_Y, 0.0f),
                    BONUS_POINT_SIZE, DEFAULT_COLOR, CEffect::TYPE_BONUS_POINT);
            }
            else
            {
                nScore = ENEMY_BOSS_DRAGON_SCORE;
            }

            break;

        case CEnemy::TYPE_RED_BIRD:

            if (m_bMoveUp == false)
            {// �ʏ펞
                nScore = ENEMY_RED_BIRD_SCORE;
            }
            else
            {// �S�b�h�o�[�h��
                nScore = ENEMY_RED_BIRD_SCORE * 4;

                // �{�[�i�X�|�C���g�\�L
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y + BONUS_POINT_ADD_POS_Y, 0.0f),
                    BONUS_POINT_SIZE, DEFAULT_COLOR, CEffect::TYPE_BONUS_POINT);
            }

            break;

        case CEnemy::TYPE_BAT:

            nScore = ENEMY_BAT_SCORE;

            break;

        case CEnemy::TYPE_MULTI_BIRD:

            // �o���A�A�C�e���𐶐�
            CItem::Create(pos, ITEM_SIZE, CItem::TYPE_BARRIER);

            // �X�g�b�N�A�C�e���𐶐�
            CItem::Create(pos, ITEM_SIZE, CItem::TYPE_STOCK);

            nScore = ENEMY_MULTI_BIRD_SCORE;

            break;

        case CEnemy::TYPE_BOSS_BLAZE:

            // �{�XBGM���~�߂�
            pSound->Stop(CSound::LABEL_BGM_BOSS3);

            // ���N���A
            CUI::Create(CLEAR_POS, CLEAR_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f), CUI::TYPE_CLEAR_C);

            // �c�����c��
            CAfterimage::Create(pos, size, 0.0f, DEFAULT_COLOR, CAfterimage::TYPE_BOSS_BLAZE);

            // �Q�[���̃J�E���^���~�߂�
            CGame::StopGameCount();

            // ���@�𖳓G��
            CGame::SetInvinciblePlayer();

            // ��_���ʂœ|�������ǂ����ŁA����X�R�A��ς���
            if (m_nWhereHit == ENEMY_BOSS_BLAZE_WEEKNESS)
            {
                // �_�����[�h���ǂ����ŁA����X�R�A��ς���
                if (m_bMoveUp == false)
                {
                    nScore = ENEMY_BOSS_BLAZE_SCORE + ENEMY_BOSS_BLAZE_WEEKNESS_ADD_SCORE;
                }
                else
                {
                    nScore = (ENEMY_BOSS_BLAZE_SCORE * 2) + ENEMY_BOSS_BLAZE_WEEKNESS_ADD_SCORE;
                }

                // �{�[�i�X�|�C���g�\�L
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y + BONUS_POINT_ADD_POS_Y, 0.0f),
                    BONUS_POINT_SIZE, DEFAULT_COLOR, CEffect::TYPE_BONUS_POINT);
            }
            else
            {
                // �_�����[�h���ǂ����ŁA����X�R�A��ς���
                if (m_bMoveUp == false)
                {
                    nScore = ENEMY_BOSS_BLAZE_SCORE;
                }
                else
                {
                    nScore = ENEMY_BOSS_BLAZE_SCORE * 2;
                }
            }

            break;
        }
        //==================================================================

        // �ꔭ�œ|�������ǂ����ŏꍇ����
        if (m_bDefeatOneHit == true)
        {// �ꔭ

            // �X�R�A3�{
            nScore = nScore * 3;

            // �u���C�Y�Ȃ�A�X�g�b�N�ƃo���A���̃X�R�A�����Z
            if (m_type == TYPE_BOSS_BLAZE)
            {
                CPlayer *pPlayer = NULL;
                int nPlayerStock = CGame::GetStock();
                int nPlayerBarrier = 0;

                // �v���C���[���������Ă���Ȃ�A�o���A�̏����擾
                if (CGame::GetDispPlayer() == true)
                {
                    // �v���C���[�����擾
                    pPlayer = CGame::GetPlayer();
                    nPlayerBarrier = pPlayer->GetBarrier();
                }

                // �{�[�i�X�X�R�A
                nScore += nPlayerStock * ENEMY_BOSS_BLAZE_SCORE_ADD_STOCK_RATE + nPlayerBarrier * ENEMY_BOSS_BLAZE_SCORE_ADD_BARRIER_RATE;
            }

            // �X�R�A�\���F�����F�ɂ���
            col = SCORE_DEFEAT_ONE_SHOT_COLOR;
        }
        else
        {//�ꔭ�łȂ��Ȃ�

            // ��_�œ|�������ǂ����ŏꍇ����
            if (m_bDefeatWithWeak == false)
            {// ��_�łȂ�

                // �u���C�Y�Ȃ�A�X�g�b�N�ƃo���A���̃X�R�A�����Z
                if (m_type == TYPE_BOSS_BLAZE)
                {
                    CPlayer *pPlayer = NULL;
                    int nPlayerStock = CGame::GetStock();
                    int nPlayerBarrier = 0;

                    // �v���C���[���������Ă���Ȃ�A�o���A�̏����擾
                    if (CGame::GetDispPlayer() == true)
                    {
                        // �v���C���[�����擾
                        pPlayer = CGame::GetPlayer();
                        nPlayerBarrier = pPlayer->GetBarrier();
                    }

                    // �{�[�i�X�X�R�A
                    nScore += nPlayerStock * ENEMY_BOSS_BLAZE_SCORE_ADD_STOCK_RATE + nPlayerBarrier * ENEMY_BOSS_BLAZE_SCORE_ADD_BARRIER_RATE;
                }

                // �X�R�A�\���F�𔒂ɂ���
                col = DEFAULT_COLOR;
            }
            else
            {// ��_�Ȃ�

                // �X�R�A�{
                nScore = nScore * 2;

                // �u���C�Y�Ȃ�A�X�g�b�N�ƃo���A���̃X�R�A�����Z
                if (m_type == TYPE_BOSS_BLAZE)
                {
                    CPlayer *pPlayer = NULL;
                    int nPlayerStock = CGame::GetStock();
                    int nPlayerBarrier = 0;

                    // �v���C���[���������Ă���Ȃ�A�o���A�̏����擾
                    if (CGame::GetDispPlayer() == true)
                    {
                        // �v���C���[�����擾
                        pPlayer = CGame::GetPlayer();
                        nPlayerBarrier = pPlayer->GetBarrier();
                    }

                    // �{�[�i�X�X�R�A
                    nScore += nPlayerStock * ENEMY_BOSS_BLAZE_SCORE_ADD_STOCK_RATE + nPlayerBarrier * ENEMY_BOSS_BLAZE_SCORE_ADD_BARRIER_RATE;
                }

                // �X�R�A�\���F��Ԃɂ���
                col = SCORE_DEFEAT_WITH_WEAK_COLOR;
            }
        }

        // �X�R�A���擾
        CScore *pScore = CGame::GetScore();

        // �X�R�A���Z
        pScore->AddScore(nScore);

        // �v���C���[�����݂��Ă���Ȃ�A�v���C���[�̈ʒu���擾
        D3DXVECTOR3 playerPos = PLAYER_POS + SCORE_DISP_UP;
        if (CGame::GetDispPlayer() == true)
        {
            playerPos = CGame::GetPlayer()->GetPosition() + SCORE_DISP_UP;
        }

        // �U�R�G�̓v���C���[�̏ꏊ�A�{�X�̓{�X�̈ʒu�ɃX�R�A�\��
        switch (m_type)
        {
        case TYPE_BOSS_FOREST:

            // �{�X�̏ꏊ�ɁA�X�R�A�\��
            pScore->SetScore(nScore, pos, col);

            break;

        case TYPE_BOSS_DRAGON:

            // �{�X�̏ꏊ�ɁA�X�R�A�\��
            pScore->SetScore(nScore, pos, col);

            break;

        case TYPE_BOSS_BLAZE:

            // �{�X�̏ꏊ�ɁA�X�R�A�\��
            pScore->SetScore(nScore, pos, col);

            break;

        default:

            // �v���C���[�̏ꏊ�ɁA�X�R�A�\��
            pScore->SetScore(nScore, playerPos, col);

            break;
        }

        // ���g�p��
        bUse = false;
    }

    return bUse;
}

//====================================================
// �G�l�~�[�̔�������
//====================================================
void CEnemy::CounterAttack(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();            // �ʒu���擾
    float fSpeed = 0.0f;                        // �����e�̑��x
    D3DXVECTOR3 sizeBullet = DEFAULT_VECTOR;    // �����e�̑傫��

    // �����̃N�[���^�C����0�Ȃ�
    if (m_nCounterAttackCoolTime <= 0)
    {
        // �����̃N�[���^�C����ݒ�
        m_nCounterAttackCoolTime = ENEMY_COUNTERATTACK_COOL_TIME;

        switch (m_element)
        {
        case ELEMENT_FIRE:

            fSpeed = BULLET_COUNTERATTACK_FIRE_SPEED;       // ���̔����e�̑��x
            sizeBullet = BULLET_COUNTERATTACK_FIRE_SIZE;    // ���̔����e�̑傫��

            // �������̒e�̐���
            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(fSpeed, 0.0f, 0.0f),
                CBullet::TYPE_FIRE, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-fSpeed, 0.0f, 0.0f),
                CBullet::TYPE_FIRE, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(0.0f, fSpeed, 0.0f),
                CBullet::TYPE_FIRE, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(0.0f, -fSpeed, 0.0f),
                CBullet::TYPE_FIRE, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(sinf(D3DX_PI / 4) * fSpeed, -cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_FIRE, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(sinf(D3DX_PI / 4) * fSpeed, cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_FIRE, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-sinf(D3DX_PI / 4) * fSpeed, -cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_FIRE, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-sinf(D3DX_PI / 4) * fSpeed, cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_FIRE, TRIBE_ENEMY);

            break;

        case ELEMENT_WATER:

            fSpeed = BULLET_COUNTERATTACK_WATAR_SPEED;      // ���̔����e�̑��x
            sizeBullet = BULLET_COUNTERATTACK_WATAR_SIZE;   // ���̔����e�̑傫��

            // �������̒e�̐���
            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(fSpeed, 0.0f, 0.0f),
                CBullet::TYPE_WATER, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-fSpeed, 0.0f, 0.0f),
                CBullet::TYPE_WATER, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(0.0f, fSpeed, 0.0f),
                CBullet::TYPE_WATER, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(0.0f, -fSpeed, 0.0f),
                CBullet::TYPE_WATER, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(sinf(D3DX_PI / 4) * fSpeed, -cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_WATER, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(sinf(D3DX_PI / 4) * fSpeed, cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_WATER, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-sinf(D3DX_PI / 4) * fSpeed, -cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_WATER, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-sinf(D3DX_PI / 4) * fSpeed, cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_WATER, TRIBE_ENEMY);

            break;

        case ELEMENT_LIGHT:

            fSpeed = BULLET_COUNTERATTACK_LIGHT_SPEED;      // ���̔����e�̑��x
            sizeBullet = BULLET_COUNTERATTACK_LIGHT_SIZE;   // ���̔����e�̑傫��

            // �������̒e�̐���
            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(fSpeed, 0.0f, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-fSpeed, 0.0f, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(0.0f, fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(0.0f, -fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(sinf(D3DX_PI / 4) * fSpeed, -cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(sinf(D3DX_PI / 4) * fSpeed, cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-sinf(D3DX_PI / 4) * fSpeed, -cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-sinf(D3DX_PI / 4) * fSpeed, cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            break;
        }
    }
}

//====================================================
// �G�l�~�[���猩�����@�ւ̊p�x
//====================================================
float CEnemy::GetAngleToPlayer(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();           // �ʒu���擾
    CPlayer *pPlayer = NULL;                   // �v���C���[���擾
    CScene2D *pPlayerScene2D = NULL;           // �v���C���[���V�[��2D�ɃL���X�g
    D3DXVECTOR3 playerPos = DEFAULT_VECTOR;    // �v���C���[�̈ʒu
    float fTargetPosX = 0.0f;                  // �ڕW��X���W
    float fTargetPosY = 0.0f;                  // �ڕW��Y���W
    float fMyPosX = 0.0f;                      // ���g��X���W
    float fMyPosY = 0.0f;                      // ���g��Y���W
    float fAngle = 0.0f;                       // ���߂�p�x

    // �v���C���[�����݂��Ă���Ȃ�
    if (CGame::GetDispPlayer() == true)
    {
        // �v���C���[�̏����擾
        pPlayer = CGame::GetPlayer();
        pPlayerScene2D = (CScene2D*)pPlayer;
        playerPos = pPlayerScene2D->GetPosition();
    }

    // �ڕW�̍��W�Ǝ��g�̍��W
    fTargetPosX = playerPos.x, fTargetPosY = playerPos.y;
    fMyPosX = pos.x, fMyPosY = pos.y;

    // �p�x�����߂�
    fAngle = atan2f((fMyPosX - fTargetPosX), (fMyPosY - fTargetPosY));

    return fAngle;
}

//====================================================
// ���ɓ����������̃o�E���h
//====================================================
D3DXVECTOR3 CEnemy::Bound(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    D3DXVECTOR3 posBound = pos; // �o�E���h�����ۂ̈ʒu

    // ���̔�����擾
    bool bFloor = false;
    bFloor = CGame::GetFloor();

    // ���Ƃ̓����蔻��
    if (bFloor == true)
    {
        if (pos.y + (size.y / 2) > FLOOR_COLLISION)
        {
            // ���ɂ߂荞�܂Ȃ�
            posBound.y = FLOOR_COLLISION - (size.y / 2);

            // �o�E���h�񐔂����Z
            m_nBound++;

            // �o�E���h�̕������ꍇ����
            if (m_bMoveUp == true)
            {
                // �E�փo�E���h
                m_move = ENEMY_CATERPILLAR_RIGHT_BOUND;
            }
            else
            {
                // ���փo�E���h
                m_move = ENEMY_CATERPILLAR_LEFT_BOUND;
            }
        }
    }

    return posBound;
}

//====================================================
// �{�X�X�̍s��
//====================================================
void CEnemy::ForestMovement(D3DXVECTOR3 playerPos)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();
    int nRandNum = 0;
    float fRandX = 0.0f;
    float fRandY = 0.0f;

    // �ړ����ς�肾���܂ł̃J�E���^�𐔂���
    m_nCntChangeMove++;

    // X�����X�g�b�v����܂ł̃J�E���^
    if (m_nCntChangeMove == ENEMY_BOSS_FOREST_STOP_X)
    {
        m_move.x = 0.0f;
    }
    // Y�����X�g�b�v����܂ł̃J�E���^
    else if (m_nCntChangeMove == ENEMY_BOSS_FOREST_STOP_Y)
    {
        m_move.y = 0.0f;
    }

    // �o�ꂪ�I����Ă���A�J�E���^�̊Ԋu�Ō���
    if (m_move.x == 0.0f && m_nCntChangeMove % ENEMY_BOSS_FOREST_ATTACK_COUNTER == 0)
    {
        // �v���C���[�����݂��Ă���Ȃ�
        if (CGame::GetDispPlayer() == true)
        {
            // �����_���Ȓl�𓾂�
            nRandNum = rand() % 2 + 1;

            // �ŏ��̓C�����V�������A��莞�ԂŃ����S�ɕς���
            if (m_nCntChangeMove < ENEMY_BOSS_FOREST_CHANGE_ATTACK)
            {
                switch (nRandNum)
                {
                case 1:

                    // �E�ɓ]����C�����V
                    CEnemy::Create(D3DXVECTOR3(playerPos.x, ENEMY_BOSS_FOREST_SET_ATTACK_POS_Y, 0.0f), ENEMY_CATERPILLAR_SIZE,
                        0, true, CEnemy::TYPE_CATERPILLAR);

                    break;

                case 2:

                    // ���ɓ]����C�����V
                    CEnemy::Create(D3DXVECTOR3(playerPos.x, ENEMY_BOSS_FOREST_SET_ATTACK_POS_Y, 0.0f), ENEMY_CATERPILLAR_SIZE,
                        0, false, CEnemy::TYPE_CATERPILLAR);

                    break;
                }
            }
            else
            {
                switch (nRandNum)
                {
                case 1:

                    // �E�ɓ]���郊���S
                    CBlock::Create(D3DXVECTOR3(playerPos.x, ENEMY_BOSS_FOREST_SET_ATTACK_POS_Y, 0.0f),
                        BLOCK_APPLE_SIZE, true, CBlock::TYPE_APPLE);

                    break;

                case 2:

                    // ���ɓ]���郊���S
                    CBlock::Create(D3DXVECTOR3(playerPos.x, ENEMY_BOSS_FOREST_SET_ATTACK_POS_Y, 0.0f),
                        BLOCK_APPLE_SIZE, false, CBlock::TYPE_APPLE);

                    break;
                }
            }
        }
    }

    // �ɂ���A�j���[�V����
    if (m_nCounterState > 0)
    {
        // �e�N�X�`�����W���X�V
        SetTexturePlace(2, 2);
    }
    // �ʏ�
    else
    {
        // �e�N�X�`�����W���X�V
        SetTexturePlace(1, 2);
    }

    // ��ԃJ�E���^�ƍU���𓖂Ă�ꂽ�ꏊ�ɂ���āA�t���ς�}���o���܂�
    if (m_nCounterState % ENEMY_BOSS_FOREST_SCATTER == 0)
    {
        switch (m_nWhereHit)
        {
            // �}
        case 0:

            // �����ʒu�������_���Ɏ擾
            fRandX = float(rand() % 7500) / 100.0f - float(rand() % 7500) / 100.0f;
            fRandY = float(rand() % 15000) / 100.0f - float(rand() % 15000) / 100.0f;

            // ���
            CEffect::Create(D3DXVECTOR3(pos.x + fRandX, pos.y + fRandY, 0.0f), EFFECT_BRANCH_SIZE, DEFAULT_COLOR, CEffect::TYPE_BRANCH);

            break;

            // �t����
        case 1:

            // �����ʒu�������_���Ɏ擾
            fRandX = float(rand() % 15000) / 100.0f - float(rand() % 15000) / 100.0f;
            fRandY = float(rand() % 7500) / 100.0f - float(rand() % 7500) / 100.0f;

            // ���
            CEffect::Create(D3DXVECTOR3(pos.x + fRandX, pos.y + fRandY + ENEMY_BOSS_FOREST_SCATTER_LEAF_POS_Y, 0.0f),
                EFFECT_LEAF_SIZE, DEFAULT_COLOR, CEffect::TYPE_LEAF);

            break;
        }
    }
}

//====================================================
// �g�[�s�[�h�̔���
//====================================================
bool CEnemy::TorpedoExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    bool bUse = true;   // �g�p���邩�ǂ���
    float fSpeed = ENEMY_TORPEDO_BULLET_SPEED;  // �����e�̑��x

    // ���̔�����擾
    bool bFloor = false;
    bFloor = CGame::GetFloor();

    // ���Ƃ̓����蔻��
    if (bFloor == true)
    {
        // ���ɓ���������
        if (pos.y + (size.y / 2) > FLOOR_COLLISION)
        {
            // �Ռ��g�G�t�F�N�g
            CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);

            // �����G�t�F�N�g
            CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, EXPLOSION_SIZE,
                DEFAULT_COLOR, CEffect::TYPE_EXPLOSION);

            // �������̒e�̐���
            CBullet::Create(pos, ENEMY_TORPEDO_BULLET_SIZE, D3DXVECTOR3(fSpeed, 0.0f, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, ENEMY_TORPEDO_BULLET_SIZE, D3DXVECTOR3(-fSpeed, 0.0f, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, ENEMY_TORPEDO_BULLET_SIZE, D3DXVECTOR3(0.0f, fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, ENEMY_TORPEDO_BULLET_SIZE, D3DXVECTOR3(0.0f, -fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, ENEMY_TORPEDO_BULLET_SIZE, D3DXVECTOR3(sinf(D3DX_PI / 4) * fSpeed, -cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, ENEMY_TORPEDO_BULLET_SIZE, D3DXVECTOR3(sinf(D3DX_PI / 4) * fSpeed, cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, ENEMY_TORPEDO_BULLET_SIZE, D3DXVECTOR3(-sinf(D3DX_PI / 4) * fSpeed, -cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            CBullet::Create(pos, ENEMY_TORPEDO_BULLET_SIZE, D3DXVECTOR3(-sinf(D3DX_PI / 4) * fSpeed, cosf(D3DX_PI / 4) * fSpeed, 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_ENEMY);

            // ���g�p��
            bUse = false;
        }
    }

    return bUse;
}

//====================================================
// �h���S���̍s��
//====================================================
D3DXVECTOR3 CEnemy::DragonMovement(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    D3DXVECTOR3 movePos = pos;      // �ړ��̈ʒu
    float fAngle = 0.0f;            // �p�x
    float fRadius = 0.0f;           // ���a

    // �v���C���[���̕ϐ��錾
    CPlayer *pPlayer = NULL;                   // �v���C���[���擾
    D3DXVECTOR3 playerPos = PLAYER_POS;        // �v���C���[�̈ʒu
    int nRandNum = 0;                          // �����_���Ȑ�

    // �v���C���[�����݂��Ă���Ȃ�
    if (CGame::GetDispPlayer() == true)
    {
        // �v���C���[�����擾
        pPlayer = CGame::GetPlayer();
        playerPos = pPlayer->GetPosition();
    }

    // �E���痬��Ă����ۂɁA�~�܂�X���W
    if (pos.x <= ENEMY_BOSS_DRAGON_STOP_POS_X)
    {
        // �ړ��ʂ��Ȃ���
        m_move.x = 0.0f;

        // �U���̃N�[���^�C��
        if (m_nCntChangeMove > 0)
        {
            m_nCntChangeMove--;
        }

        // �`���[�W���Ԃ̃J�E���g
        m_fDestAngle += 1.0f;

        // �`���[�W���ԂŁA�`���[�W�̃t���O��true��
        if (m_fDestAngle == DRAGON_CHARGE_TIME_1)
        {
            m_bMoveUp = true;
        }
        else if (m_fDestAngle == DRAGON_CHARGE_TIME_2)
        {
            m_bMoveUp = true;
        }
        else if (m_fDestAngle == DRAGON_CHARGE_TIME_3)
        {
            m_bMoveUp = true;
        }
        else if (m_fDestAngle == DRAGON_CHARGE_TIME_4)
        {
            m_bMoveUp = true;
        }
        else if (m_fDestAngle >= DRAGON_CHARGE_STOP)
        {
            // ���ŁA�`���[�W���Ԃ̃J�E���g���~�߂�
            m_fDestAngle = DRAGON_CHARGE_STOP;
        }
    }

    // �{�X�̍U���̏�Ԃɂ���āA�������ꍇ����
    switch (m_nBound)
    {
    case DRAGON_ATTACK_NONE:

        // �U��
        if (m_nCntChangeMove <= 0)
        {
            // �A�j���[�V�����̃J�E���^�����Z�b�g
            ResetCountAnim();

            // �ʏ�U��
            if (m_bMoveUp == false)
            {
                // ���g���������Ȃ�
                if (m_element == ELEMENT_WATER)
                {
                    // �U���̂��߁A�����_���Ȓl�𓾂�
                    nRandNum = rand() % 4 + 1;

                    switch (nRandNum)
                    {
                    case 1:

                        // �}�C���X�C�[�v
                        m_nBound = DRAGON_ATTACK_MINE_SWEEP;

                        // �U���̑S�̃t���[��
                        m_nCntChangeMove = MINE_SWEEP_COUNTER;

                        break;

                    case 2:

                        // ���C�j�[�o���b�g
                        m_nBound = DRAGON_ATTACK_RAINY_BULLET;

                        // �U���̑S�̃t���[��
                        m_nCntChangeMove = RAINY_BULLET_COUNTER;

                        break;

                    case 3:

                        // �z�[�~���O�V���b�g
                        m_nBound = DRAGON_ATTACK_HOMING_SHOT;

                        // �U���̑S�̃t���[��
                        m_nCntChangeMove = HOMING_SHOT_COUNTER;

                        break;

                    case 4:

                        // ��Η��Ƃ�
                        m_nBound = DRAGON_ATTACK_ROCK_SLIDE;

                        // �U���̑S�̃t���[��
                        m_nCntChangeMove = ROCK_SLIDE_COUNTER;

                        break;
                    }
                }
                // ���ɕω����Ă���Ȃ�A�}�C���X�C�[�v���g��Ȃ�
                else if (m_element == ELEMENT_LIGHT)
                {
                    // �U���̂��߁A�����_���Ȓl�𓾂�
                    nRandNum = rand() % 3 + 1;

                    switch (nRandNum)
                    {
                    case 1:

                        // ���C�j�[�o���b�g
                        m_nBound = DRAGON_ATTACK_RAINY_BULLET;

                        // �U���̑S�̃t���[��
                        m_nCntChangeMove = RAINY_BULLET_COUNTER;

                        break;

                    case 2:

                        // �z�[�~���O�V���b�g
                        m_nBound = DRAGON_ATTACK_HOMING_SHOT;

                        // �U���̑S�̃t���[��
                        m_nCntChangeMove = HOMING_SHOT_COUNTER;

                        break;

                    case 3:

                        // ��Η��Ƃ�
                        m_nBound = DRAGON_ATTACK_ROCK_SLIDE;

                        // �U���̑S�̃t���[��
                        m_nCntChangeMove = ROCK_SLIDE_COUNTER;

                        break;
                    }
                }              
            }
            // �`���[�W����t���O��true�Ȃ�
            else
            {
                // �`���[�W
                m_nBound = DRAGON_ATTACK_CHARGE;

                // �U���̑S�̃t���[��
                m_nCntChangeMove = DRAGON_CHARGE_COUNTER;
            }            
        }

        // �e�N�X�`�����W���X�V
        SetParagraphAnimation(1, 2, 20, 4);

        break;

    case DRAGON_ATTACK_MINE_SWEEP:

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove == MINE_SWEEP_CREATE)
        {
            // �E����~�炷���A������~�炷��
            nRandNum = rand() % 2 + 1;

            switch (nRandNum)
            {
            case 1:

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 325.0f, -100.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, -200.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 625.0f, -300.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 775.0f, -400.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 925.0f, -500.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1075.0f, -600.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                break;

            case 2:

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 475.0f, -600.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 625.0f, -500.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 775.0f, -400.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 925.0f, -300.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1075.0f, -200.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                // �g�[�s�[�h
                CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1225.0f, -100.0f, 0.0f), ENEMY_TORPEDO_SIZE,
                    DONT_CHANGE_MOVE, false, CEnemy::TYPE_TORPEDO);

                break;
            }
        }

        // ����ݒ�
        DragonSetChance(MINE_SWEEP_CHANCE);

        // �e�N�X�`�����W���X�V
        SetParagraphTexturePlace(3, 2, 2, 4);

        break;

    case DRAGON_ATTACK_RAINY_BULLET:

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove == RAINY_BULLET_CREATE)
        {
            // ���g���������Ȃ�
            if (m_element == ELEMENT_WATER)
            {
                CBullet::Create(D3DXVECTOR3(40.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(190.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(340.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(490.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(640.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(790.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(940.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(1090.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(1240.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
            }
            // ���ɕω����Ă���Ȃ�
            else if (m_element == ELEMENT_LIGHT)
            {
                CBullet::Create(D3DXVECTOR3(40.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(190.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(340.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(490.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(640.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(790.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(940.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(1090.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
                CBullet::Create(D3DXVECTOR3(1240.0f, RAINY_BULLET_SET_POS_Y, 0.0f), RAINY_BULLET_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_RAINY, CScene2D::TRIBE_ENEMY);
            }
        }

        // ����ݒ�
        DragonSetChance(RAINY_BULLET_CHANCE);

        // �e�N�X�`�����W���X�V
        SetParagraphTexturePlace(3, 2, 2, 4);

        break;

    case DRAGON_ATTACK_HOMING_SHOT:

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove == HOMING_SHOT_CREATE)
        {
            // ���g���������Ȃ�
            if (m_element == ELEMENT_WATER)
            {
                CBullet::Create(D3DXVECTOR3(pos.x - (size.x / 2) + HOMING_SHOT_SHIFT_POS, pos.y, 0.0f),
                    HOMING_SHOT_SIZE, DEFAULT_VECTOR, CBullet::TYPE_WATAR_HOMING, CScene2D::TRIBE_ENEMY);
            }
            // ���ɕω����Ă���Ȃ�
            else if (m_element == ELEMENT_LIGHT)
            {
                CBullet::Create(D3DXVECTOR3(pos.x - (size.x / 2) + HOMING_SHOT_SHIFT_POS, pos.y, 0.0f),
                    HOMING_SHOT_LIGHT_SIZE, CHANGE_LIGHT, CBullet::TYPE_WATAR_HOMING, CScene2D::TRIBE_ENEMY);
            }
        }

        // ����ݒ�
        DragonSetChance(HOMING_SHOT_CHANCE);

        // �e�N�X�`�����W���X�V
        SetParagraphAnimation(2, 2, 30, 4);

        break;

    case DRAGON_ATTACK_ROCK_SLIDE:

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove == ROCK_SLIDE_CREATE)
        {
            // ��
            CBlock::Create(D3DXVECTOR3(playerPos.x, ROCK_SLIDE_SET_POS_Y, 0.0f),
                BLOCK_ROCK_SIZE, true, CBlock::TYPE_ROCK);
        }

        // ����ݒ�
        DragonSetChance(ROCK_SLIDE_CHANCE);

        // �e�N�X�`�����W���X�V
        SetParagraphTexturePlace(3, 2, 2, 4);

        break;

    case DRAGON_ATTACK_CHARGE:

        //0�`3.14���o��*(0 or 1)*-1�Ő��������߂�
        fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        fRadius = float(rand() % 40000 + 0) / 100.0f;
        D3DXVECTOR3 particlePos = D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius, 0.0f);

        // �`���[�W�̃p�[�e�B�N��
        CEffect::Create(particlePos, DRAGON_CHARGE_SIZE, DEFAULT_COLOR, CEffect::TYPE_REVERSE_CHARGE);

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove == DRAGON_CHARGE_CREATE)
        {
            // �`���[�W�i�K�ɂ���āA���̃`���[�W��
            if (m_fMinAngle == DRAGON_CHARGE_STAGE_3)
            {
                // �t���`���[�W
                m_fMinAngle = DRAGON_CHARGE_FULL;

                // 100��
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y - (size.y / 2), 0.0f),
                    PERCENTAGE_SIZE, PERCENTAGE_COLOR, CEffect::TYPE_100);

                // HP��
                m_nLife += DRAGON_CHARGE_HEAL4;

                // �d�C�^�C�v�ɂȂ�
                m_element = ELEMENT_LIGHT;

                // ���]�����̃I�[��
                CReverse::Create(pos, DEFAULT_VECTOR);

                // �v���C���[���V���b�N��Ԃ�
                CGame::SetShockPlayer(true);
            }
            else if (m_fMinAngle == DRAGON_CHARGE_STAGE_2)
            {
                m_fMinAngle = DRAGON_CHARGE_STAGE_3;

                // 75��
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y - (size.y / 2), 0.0f),
                    PERCENTAGE_SIZE, PERCENTAGE_COLOR, CEffect::TYPE_75);

                // HP��
                m_nLife += DRAGON_CHARGE_HEAL3;
            }
            else if (m_fMinAngle == DRAGON_CHARGE_STAGE_1)
            {
                m_fMinAngle = DRAGON_CHARGE_STAGE_2;

                // 50��
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y - (size.y / 2), 0.0f),
                    PERCENTAGE_SIZE, PERCENTAGE_COLOR, CEffect::TYPE_50);

                // HP��
                m_nLife += DRAGON_CHARGE_HEAL2;
            }
            else if (m_fMinAngle == 0.0f)
            {
                m_fMinAngle = DRAGON_CHARGE_STAGE_1;

                // 25��
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y - (size.y / 2), 0.0f),
                    PERCENTAGE_SIZE, PERCENTAGE_COLOR, CEffect::TYPE_25);

                // HP��
                m_nLife += DRAGON_CHARGE_HEAL1;
            }

            // �`���[�W�̃t���O��false��
            m_bMoveUp = false;
        }

        // ����ݒ�
        DragonSetChance(DRAGON_CHARGE_CHANCE);

        // �e�N�X�`�����W���X�V
        SetParagraphTexturePlace(3, 2, 2, 4);

        break;
    }

    // HP�񕜂������ۂ́A�̗͏��
    if (m_nLife >= ENEMY_BOSS_DRAGON_LIFE)
    {
        m_nLife = ENEMY_BOSS_DRAGON_LIFE;
    }

    // �t���`���[�W�ŁA�I�[������
    if (m_fMinAngle == DRAGON_CHARGE_FULL)
    {
        DragonSetAura(movePos);
    }

    return movePos;
}

//====================================================
// �h���S���̌���ݒ�
//====================================================
void CEnemy::DragonSetChance(int nChanceFrame)
{
    // �U���̏I���
    if (m_nCntChangeMove == 0)
    {
        // �ҋ@��
        m_nBound = DRAGON_ATTACK_NONE;

        // �ҋ@�i���j���Ԃ�ݒ�
        m_nCntChangeMove = nChanceFrame;
    }
}

//====================================================
// �h���S���̃I�[����ݒ�
//====================================================
void CEnemy::DragonSetAura(D3DXVECTOR3 pos)
{
    // �ϐ��錾
    float fAngle = 0.0f;            // �p�x
    float fRadius = 0.0f;           // ���a

    // �����_���Ȋp�x�Ɣ��a���擾
    fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
    fRadius = float(rand() % 22500) / 100.0f;

    // �I�[���G�t�F�N�g
    CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius + ENEMY_BOSS_DRAGON_AURA_SET_POS_Y, 0.0f),
        DRAGON_CHARGE_SIZE, ENEMY_BOSS_DRAGON_AURA_COLOR, CEffect::TYPE_DRAGON_AURA);
}

//====================================================
// �}���`�o�[�h�̍s��
//====================================================
void CEnemy::MultiBird(D3DXVECTOR3 pos)
{
    // �v���C���[���̕ϐ��錾
    CPlayer *pPlayer = NULL;                   // �v���C���[���擾
    D3DXVECTOR3 playerPos = PLAYER_POS;        // �v���C���[�̈ʒu
    int nRandNum = 0;                          // �����_���Ȑ�

    // �v���C���[�����݂��Ă���Ȃ�
    if (CGame::GetDispPlayer() == true)
    {
        // �v���C���[�����擾
        pPlayer = CGame::GetPlayer();
        playerPos = pPlayer->GetPosition();
    }

    // �ړ����ς�肾���܂ł̃J�E���^�𐔂���
    m_nCntChangeMove++;

    // �ړ���ς���܂ł̃J�E���^
    if (m_nCntChangeMove >= ENEMY_MULTI_BIRD_CHANGE_MOVE && m_nCntChangeMove < ENEMY_MULTI_BIRD_LEAVE)
    {
        m_move.y = 0.0f;

        // ���t���[���ŉ��ړ���܂�Ԃ�
        if (m_nCntChangeMove % ENEMY_MULTI_BIRD_RETURN_X == 0)
        {
            m_move.x *= -1;
        }
    }
    // ����܂ł̃J�E���^
    else if (m_nCntChangeMove >= ENEMY_MULTI_BIRD_LEAVE)
    {
        m_move.x = ENEMY_MULTI_BIRD_SPEED;
        m_move.y = -ENEMY_MULTI_BIRD_SPEED;
    }

    // �J�E���^�̊Ԋu�Ō���
    if (m_nCntChangeMove % ENEMY_MULTI_BIRD_ATTACK_COUNTER == 0)
    {
        // �v���C���[�����݂��Ă���Ȃ�
        if (CGame::GetDispPlayer() == true)
        {
            // ���@�̈ʒu���擾���A���̈ʒu�֌���
            float fAngle = GetAngleToPlayer();

            // �U���̂��߁A�����_���Ȓl�𓾂�
            nRandNum = rand() % 3 + 1;

            // �O�F�̒��̍U�����x�[�X�ɁA�e����T�C�Y������
            switch (nRandNum)
            {
            case 1:

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle)*ENEMY_MULTI_BIRD_BULLET_GRASS_SPEED, 
                        -cosf(fAngle)*ENEMY_MULTI_BIRD_BULLET_GRASS_SPEED, 0.0f),
                    CBullet::TYPE_GRASS, TRIBE_ENEMY);

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle + (D3DX_PI / 6))*ENEMY_MULTI_BIRD_BULLET_GRASS_SPEED, 
                        -cosf(fAngle + (D3DX_PI / 6))*ENEMY_MULTI_BIRD_BULLET_GRASS_SPEED, 0.0f),
                    CBullet::TYPE_GRASS, TRIBE_ENEMY);

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle - (D3DX_PI / 6))*ENEMY_MULTI_BIRD_BULLET_GRASS_SPEED,
                        -cosf(fAngle - (D3DX_PI / 6))*ENEMY_MULTI_BIRD_BULLET_GRASS_SPEED, 0.0f),
                    CBullet::TYPE_GRASS, TRIBE_ENEMY);

                break;

            case 2:

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle + (D3DX_PI / 16))*ENEMY_MULTI_BIRD_BULLET_WATER_SPEED, 
                        -cosf(fAngle + (D3DX_PI / 16))*ENEMY_MULTI_BIRD_BULLET_WATER_SPEED, 0.0f),
                    CBullet::TYPE_WATER, TRIBE_ENEMY);

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle - (D3DX_PI / 16))*ENEMY_MULTI_BIRD_BULLET_WATER_SPEED,
                        -cosf(fAngle - (D3DX_PI / 16))*ENEMY_MULTI_BIRD_BULLET_WATER_SPEED, 0.0f),
                    CBullet::TYPE_WATER, TRIBE_ENEMY);

                break;

            case 3:

                // �e�̐���
                CBullet::Create(pos, ENEMY_RED_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle)*ENEMY_RED_BIRD_BULLET_SPEED, -cosf(fAngle)*ENEMY_RED_BIRD_BULLET_SPEED, 0.0f),
                    CBullet::TYPE_FIRE_BURST, TRIBE_ENEMY);

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle + (D3DX_PI / 8))*ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED, 
                        -cosf(fAngle + (D3DX_PI / 8))*ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED, 0.0f),
                    CBullet::TYPE_FIRE, TRIBE_ENEMY);

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle - (D3DX_PI / 8))*ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED, 
                        -cosf(fAngle - (D3DX_PI / 8))*ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED, 0.0f),
                    CBullet::TYPE_FIRE, TRIBE_ENEMY);

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle + (D3DX_PI / 16))*ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED, 
                        -cosf(fAngle + (D3DX_PI / 16))*ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED, 0.0f),
                    CBullet::TYPE_FIRE, TRIBE_ENEMY);

                // �e�̐���
                CBullet::Create(pos, ENEMY_MULTI_BIRD_BULLET_SIZE,
                    D3DXVECTOR3(-sinf(fAngle - (D3DX_PI / 16))*ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED,
                        -cosf(fAngle - (D3DX_PI / 16))*ENEMY_MULTI_BIRD_BULLET_FIRE_SPEED, 0.0f),
                    CBullet::TYPE_FIRE, TRIBE_ENEMY);

                break;
            }
        }
    }

    // �v���C���[�̈ʒu�ɂ���āA����������ς���
    if (playerPos.x <= pos.x)
    {
        // �������Ńe�N�X�`�����W���X�V
        SetAnimation(6, 4);
    }
    else
    {
        // �E�����Ńe�N�X�`�����W���X�V
        SetReverseAnimation(6, 4);
    }
}

//====================================================
// �u���C�Y�̍s��
//====================================================
D3DXVECTOR3 CEnemy::BlazeMovement(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    D3DXVECTOR3 movePos = pos;      // �ړ��̈ʒu
    float fAngle = 0.0f;            // �p�x
    float fRadius = 0.0f;           // ���a

    // �v���C���[���̕ϐ��錾
    CPlayer *pPlayer = NULL;                   // �v���C���[���擾
    D3DXVECTOR3 playerPos = PLAYER_POS;        // �v���C���[�̈ʒu
    int nRandNum = 0;                          // �����_���Ȑ�

    // �v���C���[�����݂��Ă���Ȃ�
    if (CGame::GetDispPlayer() == true)
    {
        // �v���C���[�����擾
        pPlayer = CGame::GetPlayer();
        playerPos = pPlayer->GetPosition();
    }

    // �E���痬��Ă����ۂɁA�~�܂�X���W
    if (pos.x <= ENEMY_BOSS_BLAZE_STOP_POS_X)
    {
        // �u���C�Y�̑ҋ@���Ȃ�
        if (m_nBound == BLAZE_ATTACK_NONE)
        {
            // �ړ��ʂ��Ȃ���
            m_move.x = 0.0f;
        }

        // �U���̃N�[���^�C��
        if (m_nCntChangeMove > 0)
        {
            m_nCntChangeMove--;
        }
    }

    // �ォ�痬��Ă����ۂɁA�~�܂�Y���W
    if (pos.y >= ENEMY_BOSS_BLAZE_STOP_POS_Y)
    {
        // �u���C�Y�̑ҋ@���Ȃ�
        if (m_nBound == BLAZE_ATTACK_NONE)
        {
            // �ړ��ʂ��Ȃ���
            m_move.y = 0.0f;
        }
    }

    // �{�X�̍U���̏�Ԃɂ���āA�������ꍇ����
    switch (m_nBound)
    {
    case BLAZE_ATTACK_NONE:

        // �U��
        if (m_nCntChangeMove <= 0)
        {
            // �A�j���[�V�����̃J�E���^�����Z�b�g
            ResetCountAnim();

            // �U���̂��߁A�����_���Ȓl�𓾂�
            nRandNum = rand() % 4 + 1;

            switch (nRandNum)
            {
            case 1:

                // �o�[�j���O�o���b�g
                m_nBound = BLAZE_ATTACK_BURNING_BULLET;

                // �U���̑S�̃t���[��
                m_nCntChangeMove = BURNING_BULLET_COUNTER;

                break;

            case 2:

                // �E�B���h�o���b�g
                m_nBound = BLAZE_ATTACK_WIND_BULLET;

                // �U���̑S�̃t���[��
                m_nCntChangeMove = WIND_BULLET_COUNTER;

                break;

            case 3:

                // �S�b�h�o�[�h
                m_nBound = BLAZE_ATTACK_GOD_BIRD;

                // �U���̑S�̃t���[��
                m_nCntChangeMove = GOD_BIRD_COUNTER;

                break;

            case 4:

                // ���e�I�X�g���C�N
                m_nBound = BLAZE_ATTACK_METEO_STRIKE;

                // �U���̑S�̃t���[��
                m_nCntChangeMove = METEO_STRIKE_COUNTER;

                break;
            }
        }

        // �e�N�X�`�����W���X�V
        SetAnimation(14,3);

        break;

    case BLAZE_ATTACK_BURNING_BULLET:

        // �\������
        if (m_nCntChangeMove == BURNING_BULLET_COUNTER - 1)
        {
            // �_�ʗ�
            CAfterimage::Create(pos, size, 0.0f, DEFAULT_COLOR, CAfterimage::TYPE_MAGIC);

            // �Ռ��g
            CEffect::Create(pos, EFFECT_DOUBLE_WAVE_BLAZE_SIZE,
                D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CEffect::TYPE_DOUBLE_WAVE);
        }

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove == BURNING_BULLET_CREATE)
        {
            // �����l�㏸
            m_fDestAngle += GOD_FIRE_BLAZE_ATTACK_VALUE;

            // �o�[�j���O�o���b�g
            BurningBullet();
        }

        // ����ݒ�
        BlazeSetChance(BURNING_BULLET_CHANCE);

        // �e�N�X�`�����W���X�V
        SetTexturePlace(1, 3);

        // �I�[���ݒ�
        BlazeSetAura(movePos, ELEMENT_FIRE);

        break;

    case BLAZE_ATTACK_WIND_BULLET:

        // �\������
        if (m_nCntChangeMove == WIND_BULLET_COUNTER - 1)
        {
            // �_�ʗ�
            CAfterimage::Create(pos, size, 0.0f, DEFAULT_COLOR, CAfterimage::TYPE_MAGIC);

            // �Ռ��g
            CEffect::Create(pos, EFFECT_DOUBLE_WAVE_BLAZE_SIZE,
                D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), CEffect::TYPE_DOUBLE_WAVE);
        }

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove == WIND_BULLET_CREATE)
        {
            // �����l�㏸
            m_fDestAngle += GOD_FIRE_BLAZE_ATTACK_VALUE;

            // �E�B���h�o���b�g
            WindBullet();
        }

        // ����ݒ�
        BlazeSetChance(WIND_BULLET_CHANCE);

        // �e�N�X�`�����W���X�V
        SetTexturePlace(1, 3);

        // �I�[���ݒ�
        BlazeSetAura(movePos, ELEMENT_GRASS);

        break;

    case BLAZE_ATTACK_GOD_BIRD:

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove <= GOD_BIRD_CREATE)
        {
            // ������
            m_move.x = -GOD_BIRD_ACCEL_SPEED;

            // �c�����c��
            CAfterimage::Create(pos, size, 0.0f, AFTERIMAGE_PLAYER_COLOR, CAfterimage::TYPE_GOD_BIRD);

            // �e�N�X�`�����W���X�V(�������̎p)
            SetTexturePlace(3, 3);

            // �U���̏I���
            if (m_nCntChangeMove == 0)
            {
                // ����̈ʒu�̏�Ƀ��[�v
                movePos = GOD_BIRD_WARP_POS;

                // �ړ��ʂ��A�ォ��~��Ă��銴���ɕς���
                m_move.x = 0.0f;
                m_move.y = GOD_BIRD_FIRST_SPEED;
            }
        }
        // �ʒu�擾�ҋ@
        else
        {
            // �v���C���[�ւ̊p�x�擾
            fAngle = GetAngleToPlayer();

            // �c�ړ�
            m_move = D3DXVECTOR3(0.0f, -cosf(fAngle)*GOD_BIRD_FIRST_SPEED, 0.0f);

            // �e�N�X�`�����W���X�V(���߂Ă���p)
            SetAnimation(6, 3);
        }

        // �f���W���[�\�L
        if (m_nCntChangeMove == GOD_BIRD_DANGER)
        {
            CUI::Create(D3DXVECTOR3(pos.x - (size.x / 4), pos.y - (size.y / 3), 0.0f), 
                GOD_BIRD_DANGER_SIZE, DEFAULT_COLOR, CUI::TYPE_DANGER);
        }

        // ����ݒ�
        BlazeSetChance(GOD_BIRD_CHANCE);

        break;

    case BLAZE_ATTACK_METEO_STRIKE:

        // �\������
        if (m_nCntChangeMove == METEO_STRIKE_COUNTER - 1)
        {
            // �_�ʗ�
            CAfterimage::Create(pos, size, 0.0f, DEFAULT_COLOR, CAfterimage::TYPE_MAGIC);

            // �Ռ��g
            CEffect::Create(pos, EFFECT_DOUBLE_WAVE_BLAZE_SIZE,
                EFFECT_DOUBLE_WAVE_BLAZE_COLOR, CEffect::TYPE_DOUBLE_WAVE);
        }

        // �N���G�C�g�t���[��
        if (m_nCntChangeMove == METEO_STRIKE_CREATE)
        {
            // ���e�I
            CBlock::Create(D3DXVECTOR3(METEO_STRIKE_SET_POS_X, METEO_STRIKE_SET_POS_Y, 0.0f),
                BLOCK_ROCK_SIZE, false, CBlock::TYPE_METEO);
        }

        // ����ݒ�
        BlazeSetChance(METEO_STRIKE_CHANCE);

        // �e�N�X�`�����W���X�V
        SetTexturePlace(1, 3);

        break;
    }

    // HP�񕜂������ۂ́A�̗͏��
    if (m_nLife >= ENEMY_BOSS_BLAZE_LIFE)
    {
        m_nLife = ENEMY_BOSS_BLAZE_LIFE;
    }

    // �����l���`�F�b�N���A���̒l�ȏ�Ń`���[�W�̒i�K����i�K�グ��
    if (m_fDestAngle >= GOD_FIRE_VALUE_FOR_ONE_CHARGE)
    {
        // �����l�����Z�b�g
        m_fDestAngle = 0.0f;

        // �_�����[�h�łȂ��Ȃ�
        if (m_bMoveUp == false)
        {
            // �`���[�W�i�K�ɂ���āA���̃`���[�W��
            if (m_fMinAngle == GOD_FIRE_STAGE_3)
            {
                // �_�����[�h
                m_bMoveUp = true;

                // �t���`���[�W
                m_fMinAngle = GOD_FIRE_FULL;

                // 100��
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y - (size.y / 3), 0.0f),
                    PERCENTAGE_SIZE, PERCENTAGE_COLOR, CEffect::TYPE_100);
            }
            else if (m_fMinAngle == GOD_FIRE_STAGE_2)
            {
                m_fMinAngle = GOD_FIRE_STAGE_3;

                // 75��
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y - (size.y / 3), 0.0f),
                    PERCENTAGE_SIZE, PERCENTAGE_COLOR, CEffect::TYPE_75);
            }
            else if (m_fMinAngle == GOD_FIRE_STAGE_1)
            {
                m_fMinAngle = GOD_FIRE_STAGE_2;

                // 50��
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y - (size.y / 3), 0.0f),
                    PERCENTAGE_SIZE, PERCENTAGE_COLOR, CEffect::TYPE_50);
            }
            else if (m_fMinAngle == 0.0f)
            {
                m_fMinAngle = GOD_FIRE_STAGE_1;

                // 25��
                CEffect::Create(D3DXVECTOR3(pos.x, pos.y - (size.y / 3), 0.0f),
                    PERCENTAGE_SIZE, PERCENTAGE_COLOR, CEffect::TYPE_25);
            }
        }
    }

    // �_�����[�h�ŁA�����I���A�I�[������
    if (m_bMoveUp == true)
    {
        // �����I��
        m_nCounterAttackCoolTime = GOD_FIRE_STOP_COUNTERATTACK;

        // �I�[������
        BlazeSetAura(movePos, ELEMENT_MULTI);
    }

    return movePos;
}

//====================================================
// �u���C�Y�̌���ݒ�
//====================================================
void CEnemy::BlazeSetChance(int nChanceFrame)
{
    // �U���̏I���
    if (m_nCntChangeMove == 0)
    {
        // �ҋ@��
        m_nBound = BLAZE_ATTACK_NONE;

        // �ҋ@�i���j���Ԃ�ݒ�
        m_nCntChangeMove = nChanceFrame;
    }
}

//====================================================
// �u���C�Y�I�[����ݒ�
//====================================================
void CEnemy::BlazeSetAura(D3DXVECTOR3 pos, ELEMENT element)
{
    // �u���C�Y�̃I�[���Z�b�g�J�E���^
    if (m_nCntChangeMove % ENEMY_BOSS_BLAZE_AURA_SET_COUNT == 0)
    {
        // �ϐ��錾
        float fAngle = 0.0f;            // �p�x
        float fRadius = 0.0f;           // ���a

        // �����_���Ȋp�x�Ɣ��a���擾
        fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        fRadius = float(rand() % 20000) / 100.0f;

        switch (element)
        {
        case ELEMENT_FIRE:
            // �I�[���G�t�F�N�g(��)
            CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius + ENEMY_BOSS_BLAZE_AURA_SET_POS_Y, 0.0f),
                ENEMY_BOSS_BLAZE_AURA_SIZE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.75f), CEffect::TYPE_RED_FIRE);
            break;

        case ELEMENT_GRASS:
            // �I�[���G�t�F�N�g(��)
            CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius + ENEMY_BOSS_BLAZE_AURA_SET_POS_Y, 0.0f),
                ENEMY_BOSS_BLAZE_AURA_SIZE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.75f), CEffect::TYPE_YELLOW_FIRE);
            break;

        case ELEMENT_MULTI:
            // �I�[���G�t�F�N�g(��)
            CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius + ENEMY_BOSS_BLAZE_AURA_SET_POS_Y, 0.0f),
                GOD_FIRE_SIZE, EFFECT_PURPLE_FIRE_FIRST_COLOR_BLAZE, CEffect::TYPE_PURPLE_FIRE);
            break;
        }
    }
}

//====================================================
// �o�[�j���O�o���b�g����
//====================================================
void CEnemy::BurningBullet(void)
{
    // �_�����[�h���ǂ����ŁA�e�̑�����ς���
    if (m_bMoveUp == false)
    {
        // �ʏ�́A������
        // ��
        CBullet::Create(D3DXVECTOR3(40.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(190.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(340.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(490.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(640.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(790.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(940.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(1090.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(1240.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);

        // ��
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 40.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 160.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 280.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 400.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 520.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 640.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);

        // �E
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 40.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 160.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 280.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 400.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 520.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 640.0f, 0.0f), BURNING_BULLET_SIZE, DEFAULT_VECTOR, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
    }
    else
    {
        // �_�����[�h���́A�}���`����
        // ��
        CBullet::Create(D3DXVECTOR3(40.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(190.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(340.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(490.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(640.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(790.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(940.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(1090.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(1240.0f, BURNING_BULLET_SET_POS_Y, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);

        // ��
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 40.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 160.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 280.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 400.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 520.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_LEFT, 640.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);

        // �E
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 40.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 160.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 280.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 400.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 520.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(BURNING_BULLET_SET_POS_RIGHT, 640.0f, 0.0f), BURNING_BULLET_SIZE, CHANGE_MULTI, CBullet::TYPE_BURNING, CScene2D::TRIBE_ENEMY);
    }

}

//====================================================
// �E�B���h�o���b�g����
//====================================================
void CEnemy::WindBullet(void)
{
    // �_�����[�h���ǂ����ŁA�e�̑����ƒe�̔z�u��ς���
    if (m_bMoveUp == false)
    {
        // �ʏ�͑������A�c���
        CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 140.0f, 0.0f), WIND_BULLET_SIZE
            , DEFAULT_VECTOR, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 220.0f, 0.0f), WIND_BULLET_SIZE
            , DEFAULT_VECTOR, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 300.0f, 0.0f), WIND_BULLET_SIZE
            , DEFAULT_VECTOR, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 380.0f, 0.0f), WIND_BULLET_SIZE
            , DEFAULT_VECTOR, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 460.0f, 0.0f), WIND_BULLET_SIZE
            , DEFAULT_VECTOR, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 540.0f, 0.0f), WIND_BULLET_SIZE
            , DEFAULT_VECTOR, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 620.0f, 0.0f), WIND_BULLET_SIZE
            , DEFAULT_VECTOR, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
    }
    else
    {
        // �_�����[�h���́A�}���`�����A�������̏c���
        int nRandNum = 0;
        nRandNum = rand() % 7 + 1;  // 7�̒e�̂����A�ǂꂩ���v���C���[�̂�����錊�ɂȂ�

        if (nRandNum != 1)
        {
            CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 140.0f, 0.0f), WIND_BULLET_SIZE
                , CHANGE_MULTI, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        }

        if (nRandNum != 2)
        {
            CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 220.0f, 0.0f), WIND_BULLET_SIZE
                , CHANGE_MULTI, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        }

        if (nRandNum != 3)
        {
            CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 300.0f, 0.0f), WIND_BULLET_SIZE
                , CHANGE_MULTI, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        }

        if (nRandNum != 4)
        {
            CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 380.0f, 0.0f), WIND_BULLET_SIZE
                , CHANGE_MULTI, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        }

        if (nRandNum != 5)
        {
            CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 460.0f, 0.0f), WIND_BULLET_SIZE
                , CHANGE_MULTI, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        }

        if (nRandNum != 6)
        {
            CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 540.0f, 0.0f), WIND_BULLET_SIZE
                , CHANGE_MULTI, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        }

        if (nRandNum != 7)
        {
            CBullet::Create(D3DXVECTOR3(WIND_BULLET_SET_POS_RIGHT, 620.0f, 0.0f), WIND_BULLET_SIZE
                , CHANGE_MULTI, CBullet::TYPE_WIND, CScene2D::TRIBE_ENEMY);
        }
    }
}
