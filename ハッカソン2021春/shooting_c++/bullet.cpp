//===============================================
//
// �e���� (bullet.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "effect.h"
#include "enemy.h"
#include "score.h"
#include "player.h"
#include "game.h"
#include "block.h"
#include "helper.h"
#include "bg.h"

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[CBullet::TYPE_MAX] = {};

//========================================
// �e�̃R���X�g���N�^
//========================================
CBullet::CBullet() :CScene2D(OBJTYPE::OBJTYPE_BULLET)
{
    m_posOld = DEFAULT_VECTOR;
    m_move = DEFAULT_VECTOR;
    m_fSpeed = 0.0f;
    m_nLife = 0;
    m_nDamage = 0;
    m_type = CBullet::TYPE_MAX;
    m_element = ELEMENT_MAX;
    m_tribe = TRIBE_MAX;
}

//========================================
// �e�̃f�X�g���N�^
//========================================
CBullet::~CBullet()
{

}

//========================================
// �e�̏���������
//========================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// �e�̏I������
//========================================
void CBullet::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �e�̍X�V����
//========================================
void CBullet::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();    // �ʒu���擾
    D3DXVECTOR3 size = GetSize();       // �T�C�Y���擾
    bool bHit = false;                  // �e���v���C���[��G�ɓ����������ǂ���
    float fAngle = 0.0f;                // �p�x

    // �v���C���[���̕ϐ��錾
    CPlayer *pPlayer = NULL;           // �v���C���[���擾
    int  nPlayerInvincible = 0;        // �v���C���[�̖��G����

    // �v���C���[�����݂��Ă���Ȃ�
    if (CGame::GetDispPlayer() == true)
    {
        // �v���C���[�����擾
        pPlayer = CGame::GetPlayer();
        nPlayerInvincible = pPlayer->GetInvincibleFrame();
    }

    // 1F�O�̈ʒu���L��
    m_posOld = pos;

    // �ړ��ʂ��ʒu�ɉ��Z
    pos += m_move;

    // ��ނɉ������ꍇ����
    switch (m_type)
    {
    case CBullet::TYPE_FIRE:

        // �e�N�X�`�����W���X�V
        SetAnimation(3, 2);

        // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
        CEffect::Create(pos, size + D3DXVECTOR3(15.0f, 15.0f, 0.0f),
            BULLET_FIRE_COLOR, CEffect::TYPE_PARTICLE);

        break;

    case CBullet::TYPE_WATER:

        // �v���C���[�̒e�Ȃ�d�͂ŗ����Ă���
        if (m_tribe == TRIBE_PLAYER)
        {
            m_move.y += GRAVITY;

            // ��̒��ł́A��C��R���󂯂�
            if (CBg::GetInTheSky() == true)
            {
                m_move.x -= BULLET_WATER_AIR_RESISTANCE;
            }
        }

        // �e�N�X�`�����W���X�V
        SetAnimation(2, 5);

        // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
        CEffect::Create(pos, size + D3DXVECTOR3(10.0f, 10.0f, 0.0f),
            BULLET_WATER_COLOR, CEffect::TYPE_PARTICLE);

        break;

    case CBullet::TYPE_HELPER_WATER:

        // �e�N�X�`�����W���X�V
        SetAnimation(2, 5);

        // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
        CEffect::Create(pos, size + D3DXVECTOR3(10.0f, 10.0f, 0.0f),
            BULLET_WATER_COLOR, CEffect::TYPE_PARTICLE);

        break;

    case CBullet::TYPE_LIGHT:

        // �e�N�X�`�����W���X�V
        SetAnimation(2, 5);

        // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
        CEffect::Create(pos, size + D3DXVECTOR3(10.0f, 10.0f, 0.0f),
            BULLET_LIGHT_COLOR, CEffect::TYPE_PARTICLE);

        break;

    case CBullet::TYPE_GRASS:

        // �e�N�X�`�����W���X�V
        SetAnimation(2, 5);

        // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
        CEffect::Create(pos, size + D3DXVECTOR3(15.0f, 15.0f, 0.0f),
            D3DXCOLOR(0.0f, 1.0f, 0.0f,1.0f), CEffect::TYPE_PARTICLE);

        break;

    case CBullet::TYPE_RAINY:

        // �v���C���[�ւ̊p�x�擾
        fAngle = GetAngleToPlayer();
        
        // �v���C���[�����݂���Ȃ�
        if (CGame::GetDispPlayer() == true)
        {
            // �ŏ��͂������
            if (m_nLife > BULLET_RAINY_LIFE_ACCEL)
            {
                m_move = D3DXVECTOR3(-sinf(fAngle)*BULLET_RAINY_FIRST_SPEED, -cosf(fAngle)*BULLET_RAINY_FIRST_SPEED, 0.0f);
            }
            // �������ς��1F�̂݁A�ړ��ʂ��擾
            else if (m_nLife == BULLET_RAINY_LIFE_ACCEL)
            {
                m_move = D3DXVECTOR3(-sinf(fAngle)*BULLET_RAINY_ACCEL_SPEED, -cosf(fAngle)*BULLET_RAINY_ACCEL_SPEED, 0.0f);
            }
        }
        // ���݂��Ȃ��Ȃ�A�����^���ɍs��
        else
        {
            // �ŏ��͂������
            if (m_nLife > BULLET_RAINY_LIFE_ACCEL)
            {
                m_move = D3DXVECTOR3(0.0f, BULLET_RAINY_FIRST_SPEED, 0.0f);
            }
            // ����ȍ~�͐^���ɉ���
            else
            {
                m_move = D3DXVECTOR3(0.0f, BULLET_RAINY_ACCEL_SPEED, 0.0f);
            }
        }

        // �e�N�X�`�����W���X�V
        SetAnimation(2, 5);

        // �����Z�b�g����J�E���^
        if (m_nLife % BULLET_SET_FIRE_EFFECT_COUNT == 0)
        {
            // ���̃G�t�F�N�g
            if (m_element == ELEMENT_WATER)
            {
                // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
                CEffect::Create(pos, size + D3DXVECTOR3(10.0f, 10.0f, 0.0f),
                    BULLET_BULE_FIRE_COLOR, CEffect::TYPE_BLUE_FIRE);
            }
            // ���̃G�t�F�N�g
            else if (m_element == ELEMENT_LIGHT)
            {
                // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
                CEffect::Create(pos, size + D3DXVECTOR3(20.0f, 20.0f, 0.0f),
                    BULLET_LIGHT_COLOR, CEffect::TYPE_PARTICLE_JPG);
            }
        }

        break;

    case CBullet::TYPE_WATAR_HOMING:

        // �v���C���[�ւ̊p�x�擾
        fAngle = GetAngleToPlayer();

        // �ړ��ʂ�ς���̂́A�v���C���[�̖��G���Ԃ��Ȃ����̂�
        if (nPlayerInvincible <= 0)
        {
            // �v���C���[�����݂���Ȃ�
            if (CGame::GetDispPlayer() == true)
            {
                // �z�[�~���O����߂�܂ŁA�ړ��̌������擾
                if (m_nLife > BULLET_HOMING_LIFE_STOP_HOMING)
                {
                    m_move = D3DXVECTOR3(-sinf(fAngle)*BULLET_HOMING_WATAR_SPEED, -cosf(fAngle)*BULLET_HOMING_WATAR_SPEED, 0.0f);
                }
            }
            // ���݂��Ȃ��Ȃ�
            else
            {
                // ���ֈړ�
                m_move = D3DXVECTOR3(-BULLET_HOMING_WATAR_SPEED, 0.0f, 0.0f);
            }
        }
        // ���G���ԂȂ�
        else
        {
            // ���ֈړ�
            m_move = D3DXVECTOR3(-BULLET_HOMING_WATAR_SPEED, 0.0f, 0.0f);
        }

        // �e�N�X�`�����W���X�V
        SetAnimation(2, 5);

        // �����Z�b�g����J�E���^
        if (m_nLife % BULLET_SET_FIRE_EFFECT_COUNT == 0)
        {
            // ���̃G�t�F�N�g
            if (m_element == ELEMENT_WATER)
            {
                // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
                CEffect::Create(pos, size + D3DXVECTOR3(10.0f, 10.0f, 0.0f),
                    BULLET_BULE_FIRE_COLOR, CEffect::TYPE_BLUE_FIRE);
            }
            // ���̃G�t�F�N�g
            else if (m_element == ELEMENT_LIGHT)
            {
                // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
                CEffect::Create(pos, size + D3DXVECTOR3(20.0f, 20.0f, 0.0f),
                    BULLET_LIGHT_COLOR, CEffect::TYPE_PARTICLE_JPG);
            }
        }

        break;

    case CBullet::TYPE_FIRE_BURST:

        // �v���C���[�ւ̊p�x�擾
        fAngle = GetAngleToPlayer();

        // ����
        m_fSpeed -= BULLET_FIRE_BURST_DECELERATE;

        // �X�s�[�h��0��艺���Ȃ��悤�ɂ���
        if (m_fSpeed < 0.0f)
        {
            m_fSpeed = 0.0f;
        }

        // �v���C���[�����݂���Ȃ�
        if (CGame::GetDispPlayer() == true)
        {
            m_move = D3DXVECTOR3(-sinf(fAngle)*m_fSpeed, -cosf(fAngle)*m_fSpeed, 0.0f);
        }

        // ��莞�ԂŁA�o�[�X�g����
        if (m_nLife <= BULLET_FIRE_BURST_LIFE_ACCEL)
        {
            // ���o�[�X�g
            FireBurst(pos);

            // ����
            m_nLife = -1;
        }

        // �e�N�X�`�����W���X�V
        SetAnimation(3, 2);

        // �����Z�b�g����J�E���^
        if (m_nLife % BULLET_SET_FIRE_EFFECT_COUNT == 0)
        {
            // �G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
            CEffect::Create(pos, size + D3DXVECTOR3(15.0f, 15.0f, 0.0f),
                EFFECT_RED_FIRE_FIRST_COLOR, CEffect::TYPE_RED_FIRE);
        }

        break;

    case CBullet::TYPE_BURNING:

        // �v���C���[�ւ̊p�x�擾
        fAngle = GetAngleToPlayer();

        // �v���C���[�����݂���Ȃ�
        if (CGame::GetDispPlayer() == true)
        {
            // �ŏ��͂������
            if (m_nLife > BULLET_BURNING_LIFE_ACCEL)
            {
                m_move = D3DXVECTOR3(-sinf(fAngle)*BULLET_BURNING_FIRST_SPEED, -cosf(fAngle)*BULLET_BURNING_FIRST_SPEED, 0.0f);
            }
            // �������ς��1F�̂݁A�ړ��ʂ��擾
            else if (m_nLife == BULLET_BURNING_LIFE_ACCEL)
            {
                m_move = D3DXVECTOR3(-sinf(fAngle)*BULLET_BURNING_ACCEL_SPEED, -cosf(fAngle)*BULLET_BURNING_ACCEL_SPEED, 0.0f);
            }
        }
        // ���݂��Ȃ��Ȃ�A�������ɉ������邾��
        else
        {
            m_move = D3DXVECTOR3(-BULLET_BURNING_ACCEL_SPEED, 0.0f, 0.0f);
        }

        // �e�N�X�`�����W���X�V
        SetAnimation(3, 2);

        // �������Ȃ�
        if (m_element == ELEMENT_FIRE)
        {
            // �ԉ��G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
            CEffect::Create(pos, size + D3DXVECTOR3(15.0f, 15.0f, 0.0f),
                D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), CEffect::TYPE_RED_FIRE);
        }
        // �}���`�����Ȃ�
        else if (m_element == ELEMENT_MULTI)
        {
            // �����G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
            CEffect::Create(pos, size + D3DXVECTOR3(15.0f, 15.0f, 0.0f),
                EFFECT_PURPLE_FIRE_FIRST_COLOR, CEffect::TYPE_PURPLE_FIRE);
        }

        break;

    case CBullet::TYPE_WIND:

        // ��莞�ԂŁA�}��������
        if (m_nLife > BULLET_WIND_LIFE_ACCEL)
        {
            // ����
            m_fSpeed -= BULLET_WIND_DECELERATE;

            // �X�s�[�h��0��艺���Ȃ��悤�ɂ���
            if (m_fSpeed < 0.0f)
            {
                m_fSpeed = 0.0f;
            }

            // �ړ��ʂ����߂�
            m_move = D3DXVECTOR3(-m_fSpeed, 0.0f, 0.0f);
        }
        else
        {
            // �}����
            m_fSpeed = BULLET_WIND_ACCEL_SPEED;

            // �ړ��ʂ����߂�
            m_move = D3DXVECTOR3(-m_fSpeed, 0.0f, 0.0f);
        }

        // �e�N�X�`�����W���X�V
        SetAnimation(2, 5);

        // �������Ȃ�
        if (m_element == ELEMENT_GRASS)
        {
            // �Ή��G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
            CEffect::Create(pos, size + D3DXVECTOR3(15.0f, 15.0f, 0.0f),
                D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.4f), CEffect::TYPE_YELLOW_FIRE);
        }
        // �}���`�����Ȃ�
        else if (m_element == ELEMENT_MULTI)
        {
            // �����G�t�F�N�g�𐶐�(�T�C�Y�͈���傫��)
            CEffect::Create(pos, size + D3DXVECTOR3(15.0f, 15.0f, 0.0f),
                EFFECT_PURPLE_FIRE_FIRST_COLOR, CEffect::TYPE_PURPLE_FIRE);
        }

        break;
    }

    // �ʒu�𔽉f
    SetPosition(pos);

    // ���_���W��ύX
    SetVertex();

    // �����蔻��
    for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
    {
        // �V�[�����擾
        CScene *pScene = GetScene(nCntScene);

        // ���g������Ȃ�
        if (pScene != NULL)
        {
            // �^�C�v���擾
            OBJTYPE objType = pScene->GetObjType();

            // �G�l�~�[�Ȃ�A
            if (objType == CScene::OBJTYPE_ENEMY)
            {
                // �e���v���C���[�̂��̂Ȃ�A
                if (m_tribe == TRIBE_PLAYER)
                {
                    // �ʒu�ƏՓ˃T�C�Y�𓾂邽�߁A�G�l�~�[�ɃL���X�g
                    CEnemy *pEnemy = (CEnemy*)pScene;

                    // ��ʓ��Ȃ�
                    if (OutScreen2D(&pEnemy->GetPosition(), &pEnemy->GetSize()) == false)
                    {
                        // �����蔻��̐�����
                        for (int nCntCollision = 0; nCntCollision < pEnemy->GetCntCollision(); nCntCollision++)
                        {
                            D3DXVECTOR3 posCollision = pEnemy->GetPosition() + pEnemy->GetCollision(nCntCollision).posToShift;
                            D3DXVECTOR3 sizeCollision = pEnemy->GetCollision(nCntCollision).size;

                            // �����蔻����v�Z
                            if (RectangleCollision2D(&pos, &posCollision,
                                &size, &sizeCollision) == true)
                            {
                                // �q�b�g�̃t���O��true��
                                bHit = true;

                                // �������ƂɃq�b�g�G�t�F�N�g�Ə�ԃJ�E���^��ς���
                                switch (m_element)
                                {
                                case ELEMENT_FIRE:

                                    // �Ռ��g�G�t�F�N�g
                                    CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                        BULLET_FIRE_COLOR, CEffect::TYPE_WAVE);

                                    // �����G�t�F�N�g
                                    CEffect::Create(pos, EXPLOSION_SIZE,
                                        DEFAULT_COLOR, CEffect::TYPE_EXPLOSION);

                                    // �G�ւ̃q�b�g����
                                    pEnemy->Hit(pos, BULLET_FIRE_CHANGE_ENEMY_COLOR_FRAME, m_nDamage, nCntCollision, m_element);

                                    break;

                                case ELEMENT_WATER:

                                    // �w���p�[�̒e�Ȃ�
                                    if (m_type == TYPE_HELPER_WATER)
                                    {
                                        // �Ռ��g�G�t�F�N�g
                                        CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                            BULLET_WATER_COLOR, CEffect::TYPE_WAVE);

                                        // �������G�t�F�N�g
                                        CEffect::Create(pos, WATAR_EXPLOSION_SIZE,
                                            D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), CEffect::TYPE_WATER_EXPLOSION);

                                        // �ђʂ��l�����Ȃ��A�G�ւ̃q�b�g����
                                        pEnemy->Hit(pos, DONT_GO_THROUGH, m_nDamage, nCntCollision, m_element);
                                    }
                                    else
                                    {
                                        // ��ԃJ�E���^�ŁA�ђʂ̍ۂ̑��i�q�b�g�������
                                        if (pEnemy->GetCountHitWater() <= 0)
                                        {
                                            // �Ռ��g�G�t�F�N�g
                                            CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                                BULLET_WATER_COLOR, CEffect::TYPE_WAVE);

                                            // �������G�t�F�N�g
                                            CEffect::Create(pos, WATAR_EXPLOSION_SIZE,
                                                D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), CEffect::TYPE_WATER_EXPLOSION);

                                            // �G�ւ̃q�b�g����
                                            pEnemy->Hit(pos, BULLET_WATER_CHANGE_ENEMY_COLOR_FRAME, m_nDamage, nCntCollision, m_element);
                                        }
                                    }

                                    break;

                                case ELEMENT_LIGHT:

                                    // �w���p�[�̒e�Ȃ�
                                    if (size == HELPER_BULLET_SIZE)
                                    {
                                        // ���͏Ռ��g���d�Ɍ�����
                                        // �Ռ��g�G�t�F�N�g
                                        CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                            BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);
                                        // �Ռ��g�G�t�F�N�g
                                        CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                            BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);

                                        // �d���G�t�F�N�g(�_���[�W�ɂ���āA�傫����ς���)
                                        CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3((float)m_nDamage * 1.5f, (float)m_nDamage * 1.5f, 0.0f),
                                            DEFAULT_COLOR, CEffect::TYPE_SHOCK);

                                        // �ђʂ��l�����Ȃ��A�G�ւ̃q�b�g����
                                        pEnemy->Hit(pos, DONT_GO_THROUGH, m_nDamage, nCntCollision, m_element);
                                    }
                                    // �v���C���[�̒e�Ȃ�
                                    else
                                    {
                                        // �ő�`���[�W�Ȃ�
                                        if (m_nDamage == BULLET_LIGHT_MAX_DAMAGE)
                                        {
                                            // ��ԃJ�E���^�ŁA�ђʂ̍ۂ̑��i�q�b�g�������
                                            if (pEnemy->GetCountHitLight() <= 0)
                                            {
                                                // ���͏Ռ��g���d�Ɍ�����
                                                // �Ռ��g�G�t�F�N�g
                                                CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                                    BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);
                                                // �Ռ��g�G�t�F�N�g
                                                CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                                    BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);

                                                // �d���G�t�F�N�g(�_���[�W�ɂ���āA�傫����ς���)
                                                CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3((float)m_nDamage * 1.5f, (float)m_nDamage * 1.5f, 0.0f),
                                                    DEFAULT_COLOR, CEffect::TYPE_SHOCK);

                                                // �ђʂ��l�������G�ւ̃q�b�g����
                                                pEnemy->Hit(pos, BULLET_LIGHT_CHANGE_ENEMY_COLOR_FRAME, m_nDamage, nCntCollision, m_element);
                                            }
                                        }
                                        else
                                        {
                                            // ���͏Ռ��g���d�Ɍ�����
                                            // �Ռ��g�G�t�F�N�g
                                            CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                                BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);
                                            // �Ռ��g�G�t�F�N�g
                                            CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                                                BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);

                                            // �d���G�t�F�N�g(�_���[�W�ɂ���āA�傫����ς���)
                                            CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3((float)m_nDamage * 1.5f, (float)m_nDamage * 1.5f, 0.0f),
                                                DEFAULT_COLOR, CEffect::TYPE_SHOCK);

                                            // �ђʂ��l�����Ȃ��A�G�ւ̃q�b�g����
                                            pEnemy->Hit(pos, DONT_GO_THROUGH, m_nDamage, nCntCollision, m_element);
                                        }
                                    }

                                    break;
                                }

                                // �������ƂɊђʂ̎d�l��ς���
                                switch (m_element)
                                {
                                case ELEMENT_WATER:

                                    // �������͏�Ɋђ�
                                    bHit = false;

                                    break;

                                case ELEMENT_LIGHT:

                                    // ���͍ő�`���[�W�̂݁A�ђ�
                                    if (m_nDamage == BULLET_LIGHT_MAX_DAMAGE)
                                    {
                                        bHit = false;
                                    }

                                    break;
                                }

                                // �w���p�[�̒e�͊ђʂ��Ȃ�
                                if (m_type == TYPE_HELPER_WATER)
                                {
                                    bHit = true;
                                }

                                //// �����q�b�g���Ȃ��悤��for�𔲂���
                                //break;
                            }
                        }
                    }
                }
            }
            // �v���C���[�Ȃ�A
            else if (objType == CScene::OBJTYPE_PLAYER)
            {
                // �e���G�l�~�[�̂��̂Ȃ�A
                if (m_tribe == TRIBE_ENEMY)
                {
                    // �V�[��2D�ɃL���X�g
                    CScene2D *pScene2D = (CScene2D*)pScene;

                    // �v���C���[�̓����蔻������
                    D3DXVECTOR3 playerCollisionSize = PLAYER_COLLISION_SIZE;

                    // �����蔻����v�Z
                    if (RectangleCollision2D(&pos, &pScene2D->GetPosition(),
                        &size, &playerCollisionSize) == true)
                    {
                        // ���@�ւ̃q�b�g����
                        CPlayer *pPlayer = (CPlayer*)pScene;
                        pPlayer->Hit();

                        // �����q�b�g���Ȃ��悤��for�𔲂���
                        break;
                    }
                }
            }
            // �w���p�[�Ȃ�A
            else if (objType == CScene::OBJTYPE_HELPER)
            {
                // �e���G�l�~�[�̂��̂Ȃ�A
                if (m_tribe == TRIBE_ENEMY)
                {
                    // �V�[��2D�ɃL���X�g
                    CScene2D *pScene2D = (CScene2D*)pScene;

                    // �w���p�[�̓����蔻������
                    D3DXVECTOR3 helperCollisionSize = HELPER_COLLISION_SIZE;

                    // �����蔻����v�Z
                    if (RectangleCollision2D(&pos, &pScene2D->GetPosition(),
                        &size, &helperCollisionSize) == true)
                    {
                        // �w���p�[�ւ̃q�b�g����
                        CHelper *pHelper = (CHelper*)pScene;
                        pHelper->Hit(m_posOld);

                        // �����q�b�g���Ȃ��悤��for�𔲂���
                        break;
                    }
                }
            }
            // �u���b�N�Ȃ�A
            else if (objType == CScene::OBJTYPE_BLOCK)
            {
                // �u���b�N�ɃL���X�g
                CBlock *pBlock = (CBlock*)pScene;

                // �����蔻����v�Z
                if (RectangleCollision2D(&pos, &pBlock->GetPosition(),
                    &size, &pBlock->GetCollisionSize()) == true)
                {
                    // �q�b�g�̃t���O��true��
                    bHit = true;

                    // �������ƂɃq�b�g�G�t�F�N�g��ς���
                    switch (m_element)
                    {
                    case ELEMENT_FIRE:

                        // �Ռ��g�G�t�F�N�g
                        CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                            BULLET_FIRE_COLOR, CEffect::TYPE_WAVE);

                        // �����G�t�F�N�g
                        CEffect::Create(pos, EXPLOSION_SIZE,
                            DEFAULT_COLOR, CEffect::TYPE_EXPLOSION);

                        break;

                    case ELEMENT_WATER:

                        // �Ռ��g�G�t�F�N�g
                        CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                            BULLET_WATER_COLOR, CEffect::TYPE_WAVE);

                        // �������G�t�F�N�g
                        CEffect::Create(pos, WATAR_EXPLOSION_SIZE,
                            D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), CEffect::TYPE_WATER_EXPLOSION);

                        break;

                    case ELEMENT_LIGHT:

                        // �Ռ��g�G�t�F�N�g
                        CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                            BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);

                        // �d���G�t�F�N�g(�_���[�W�ɂ���āA�傫����ς���)
                        CEffect::Create(D3DXVECTOR3(pos.x + (size.x / 2), pos.y, 0.0f), D3DXVECTOR3((float)m_nDamage * 1.5f, (float)m_nDamage * 1.5f, 0.0f),
                            DEFAULT_COLOR, CEffect::TYPE_SHOCK);

                        break;
                    }

                    // �����q�b�g���Ȃ��悤��for�𔲂���
                    break;
                }
            }
            // �e�Ȃ�
            else if (objType == CScene::OBJTYPE_BULLET)
            {
                // ���g�����@�̒e�Ȃ�
                if (m_tribe == TRIBE_PLAYER)
                {
                    // �o���b�g�ɃL���X�g
                    CBullet *pBullet = (CBullet*)pScene;

                    // �Ώۂ��G�̒e�Ȃ�
                    if (pBullet->GetTribe() == TRIBE_ENEMY)
                    {
                        // ��_���ǂ����̃t���O
                        bool bWeak = false;

                        // �������ƂɁA��_���ǂ����̌v�Z
                        switch (m_element)
                        {
                        case ELEMENT_FIRE:

                            if (pBullet->GetElement() == ELEMENT_GRASS)
                            {
                                bWeak = true;
                            }

                            break;

                        case ELEMENT_WATER:

                            if (pBullet->GetElement() == ELEMENT_FIRE)
                            {
                                bWeak = true;
                            }

                            break;

                        case ELEMENT_LIGHT:

                            if (pBullet->GetElement() == ELEMENT_WATER)
                            {
                                bWeak = true;
                            }

                            break;
                        }

                        // ��_�Ȃ�
                        if (bWeak == true)
                        {
                            // �V�[��2D�ɃL���X�g
                            CScene2D *pScene2D = (CScene2D*)pScene;

                            // �����蔻����v�Z
                            if (RectangleCollision2D(&pos, &pScene2D->GetPosition(),
                                &size, &pScene2D->GetSize()) == true)
                            {
                                // �X�R�A���擾
                                CScore *pScore = CGame::GetScore();

                                // �v���C���[�̈ʒu���擾
                                D3DXVECTOR3 playerPos = PLAYER_POS + SCORE_DISP_UP;

                                // �v���C���[�����݂��Ă���Ȃ�
                                if (CGame::GetDispPlayer() == true)
                                {
                                    playerPos = CGame::GetPlayer()->GetPosition() + SCORE_DISP_UP;
                                }

                                // �ł��������e�ɂ���āA����X�R�A��ς���
                                switch (m_element)
                                {
                                case ELEMENT_FIRE:

                                    // �X�R�A���Z
                                    pScore->AddScore(BULLET_COUNTERATTACK_GRASS_SCORE);

                                    // �X�R�A�\��(���F�ɂ���)
                                    pScore->SetScore(BULLET_COUNTERATTACK_GRASS_SCORE, playerPos, SCORE_DEFEAT_ONE_SHOT_COLOR);

                                    break;

                                case ELEMENT_WATER:

                                    // ���o�[�X�g��3�{
                                    if (pBullet->GetType() == TYPE_FIRE_BURST)
                                    {
                                        // �X�R�A���Z
                                        pScore->AddScore(BULLET_FIRE_BURST_SCORE);

                                        // �X�R�A�\��(���F�ɂ���)
                                        pScore->SetScore(BULLET_FIRE_BURST_SCORE, playerPos, SCORE_DEFEAT_ONE_SHOT_COLOR);
                                    }
                                    // �o�[�j���O��2�{
                                    else if (pBullet->GetType() == TYPE_BURNING)
                                    {
                                        // �X�R�A���Z
                                        pScore->AddScore(BULLET_BURNING_BURST_SCORE);

                                        // �X�R�A�\��(���F�ɂ���)
                                        pScore->SetScore(BULLET_BURNING_BURST_SCORE, playerPos, SCORE_DEFEAT_ONE_SHOT_COLOR);
                                    }
                                    // �ʏ�
                                    else
                                    {
                                        // �X�R�A���Z
                                        pScore->AddScore(BULLET_COUNTERATTACK_FIRE_SCORE);

                                        // �X�R�A�\��(���F�ɂ���)
                                        pScore->SetScore(BULLET_COUNTERATTACK_FIRE_SCORE, playerPos, SCORE_DEFEAT_ONE_SHOT_COLOR);
                                    }

                                    break;

                                case ELEMENT_LIGHT:

                                    // �X�R�A���Z
                                    pScore->AddScore(BULLET_COUNTERATTACK_WATAR_SCORE);

                                    // �X�R�A�\��(���F�ɂ���)
                                    pScore->SetScore(BULLET_COUNTERATTACK_WATAR_SCORE, playerPos, SCORE_DEFEAT_ONE_SHOT_COLOR);

                                    break;
                                }

                                // �G�̒e������
                                pBullet->Uninit();

                                //// �����q�b�g���Ȃ��悤��for�𔲂���
                                //break;
                            }
                        }                   
                    }
                }
                // ���g���G�̒e�Ȃ�
                else if (m_tribe == TRIBE_ENEMY)
                {
                    // �o���b�g�ɃL���X�g
                    CBullet *pBullet = (CBullet*)pScene;

                    // �Ώۂ����@�̒e�Ȃ�
                    if (pBullet->GetTribe() == TRIBE_PLAYER)
                    {
                        // ��_���ǂ����̃t���O
                        bool bWeak = false;

                        // ���g�̑������ƂɁA��_���ǂ����̌v�Z
                        switch (m_element)
                        {
                        case ELEMENT_WATER:

                            if (pBullet->GetElement() == ELEMENT_FIRE)
                            {
                                bWeak = true;
                            }

                            break;

                        case ELEMENT_LIGHT:

                            if (pBullet->GetElement() == ELEMENT_WATER)
                            {
                                bWeak = true;
                            }

                            break;

                        case ELEMENT_GRASS:

                            if (pBullet->GetElement() == ELEMENT_WATER)
                            {
                                bWeak = true;
                            }

                            break;

                        case ELEMENT_MULTI:

                            // �}���`�����́A�ⓚ���p�Ŏ��@�̒e������
                            bWeak = true;

                            break;
                        }

                        // ��_�Ȃ�
                        if (bWeak == true)
                        {
                            // �V�[��2D�ɃL���X�g
                            CScene2D *pScene2D = (CScene2D*)pScene;

                            // �����蔻����v�Z
                            if (RectangleCollision2D(&pos, &pScene2D->GetPosition(),
                                &size, &pScene2D->GetSize()) == true)
                            {
                                // ������
                                SmallExplosion(pScene2D->GetPosition(), pScene2D->GetSize());

                                // ���@�̒e������
                                pBullet->Uninit();

                                // �����q�b�g���Ȃ��悤��for�𔲂���
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // �e�̃��C�t�����炷
    m_nLife--;

    // ���Ƃ̓����蔻��
    bool bHitFloor = HitFloor(pos,size);

    // �e�̎������Ȃ��Ȃ�A�܂��͉�ʊO�ɏo�������
    if (m_nLife <= 0 || OutScreen2D(&pos, &size) == true || bHit == true || bHitFloor == true)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//========================================
// �e�̕`�揈��
//========================================
void CBullet::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �e�̉摜���[�h����
//========================================
HRESULT CBullet::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &m_apTexture[CBullet::TYPE_FIRE]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet001.png", &m_apTexture[CBullet::TYPE_WATER]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet001.png", &m_apTexture[CBullet::TYPE_HELPER_WATER]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet002.png", &m_apTexture[CBullet::TYPE_LIGHT]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet003.png", &m_apTexture[CBullet::TYPE_GRASS]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet001.png", &m_apTexture[CBullet::TYPE_RAINY]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet001.png", &m_apTexture[CBullet::TYPE_WATAR_HOMING]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &m_apTexture[CBullet::TYPE_FIRE_BURST]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &m_apTexture[CBullet::TYPE_BURNING]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet003.png", &m_apTexture[CBullet::TYPE_WIND]);

    return S_OK;
}

//========================================
// �e�̉摜�j������
//========================================
void CBullet::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CBullet::TYPE_MAX ; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// �e�̍쐬
//================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CBullet::TYPE type, CScene2D::TRIBE tribe)
{
    CBullet *pBullet = NULL;

    // ���������m��
    pBullet = new CBullet;

    // �^�C�v�̂݁A�e�N�X�`�����蓖�Ă̂��߂Ɍ��т��Ă���
    pBullet->m_type = type;

    // ������
    pBullet->Init(pos, size);

    // �����o�ϐ������т���
    pBullet->m_posOld = pos;
    pBullet->m_move = move;
    pBullet->m_tribe = tribe;

    // �e�̎�ނɂ���āA�Œ�̒l�����т���
    switch (pBullet->m_type)
    {
    case CBullet::TYPE_FIRE:

        pBullet->m_element = ELEMENT_FIRE;
        pBullet->m_nLife = BULLET_FIRE_LIFE;
        pBullet->m_nDamage = BULLET_FIRE_DAMAGE;

        // �G�̒e�̃��C�t�͉�ʊO�ɏo��܂�
        if (pBullet->m_tribe == TRIBE_ENEMY)
        {
            pBullet->m_nLife = BULLET_COUNTERATTACK_LIFE;
        }

        break;

    case CBullet::TYPE_WATER:

        pBullet->m_element = ELEMENT_WATER;
        pBullet->m_nLife = BULLET_WATER_LIFE;
        pBullet->m_nDamage = BULLET_WATER_DAMAGE;

        // �G�̒e�̃��C�t�͉�ʊO�ɏo��܂�
        if (pBullet->m_tribe == TRIBE_ENEMY)
        {
            pBullet->m_nLife = BULLET_COUNTERATTACK_LIFE;
        }

        break;

    case CBullet::TYPE_HELPER_WATER:

        pBullet->m_element = ELEMENT_WATER;
        pBullet->m_nLife = BULLET_WATER_LIFE;
        pBullet->m_nDamage = BULLET_WATAR_HELPER_DAMAGE;

        // �G�̒e�̃��C�t�͉�ʊO�ɏo��܂�
        if (pBullet->m_tribe == TRIBE_ENEMY)
        {
            pBullet->m_nLife = BULLET_COUNTERATTACK_LIFE;
        }

        break;

    case CBullet::TYPE_LIGHT:

        pBullet->m_element = ELEMENT_LIGHT;
        pBullet->m_nLife = BULLET_LIGHT_LIFE;
        pBullet->m_nDamage = (int)size.x;   // ���̒e�̃_���[�W�̓T�C�Y�ˑ�

        // �w���p�[�̒e�Ȃ�A�_���[�W�͒�߂�
        if (size == HELPER_BULLET_SIZE)
        {
            pBullet->m_nDamage = BULLET_LIGHT_HELPER_DAMAGE;
        }
        // �ő�`���[�W�̒e�Ȃ�A�ő�_���[�W�ŌŒ�
        else if (size.x == BULLET_LIGHT_MAX_SIZE)
        {
            pBullet->m_nDamage = BULLET_LIGHT_MAX_DAMAGE;
        }

        // �G�̒e�̃��C�t�͉�ʊO�ɏo��܂�
        if (pBullet->m_tribe == TRIBE_ENEMY)
        {
            pBullet->m_nLife = BULLET_COUNTERATTACK_LIFE;
        }

        break;

    case CBullet::TYPE_GRASS:

        pBullet->m_element = ELEMENT_GRASS;
        pBullet->m_nLife = BULLET_GRASS_LIFE;
        pBullet->m_nDamage = BULLET_GRASS_DAMAGE;

        // �G�̒e�̃��C�t�͉�ʊO�ɏo��܂�
        if (pBullet->m_tribe == TRIBE_ENEMY)
        {
            pBullet->m_nLife = BULLET_COUNTERATTACK_LIFE;
        }

        break;

    case CBullet::TYPE_RAINY:

        pBullet->m_element = ELEMENT_WATER;
        pBullet->m_nLife = BULLET_LIFE_COUNTER;
        pBullet->m_nDamage = BULLET_GRASS_DAMAGE;

        // ���ω��̈����Ȃ�
        if (move == CHANGE_LIGHT)
        {
            // ��������
            pBullet->m_element = ELEMENT_LIGHT;
        }

        break;

    case CBullet::TYPE_WATAR_HOMING:

        pBullet->m_element = ELEMENT_WATER;
        pBullet->m_nLife = BULLET_LIFE_COUNTER;
        pBullet->m_nDamage = BULLET_GRASS_DAMAGE;

        // ���ω��̈����Ȃ�
        if (move == CHANGE_LIGHT)
        {
            // ��������
            pBullet->m_element = ELEMENT_LIGHT;
        }

        break;

    case CBullet::TYPE_FIRE_BURST:

        pBullet->m_element = ELEMENT_FIRE;
        pBullet->m_nLife = BULLET_FIRE_LIFE;
        pBullet->m_nDamage = BULLET_FIRE_DAMAGE;

        pBullet->m_fSpeed = BULLET_FIRE_BURST_SPEED;

        break;

    case CBullet::TYPE_BURNING:

        pBullet->m_element = ELEMENT_FIRE;
        pBullet->m_nLife = BULLET_LIFE_COUNTER;
        pBullet->m_nDamage = BULLET_GRASS_DAMAGE;

        // �}���`�ω��̈����Ȃ�
        if (move == CHANGE_MULTI)
        {
            // �}���`������
            pBullet->m_element = ELEMENT_MULTI;
        }

        break;

    case CBullet::TYPE_WIND:

        pBullet->m_element = ELEMENT_GRASS;
        pBullet->m_nLife = BULLET_GRASS_LIFE;
        pBullet->m_nDamage = BULLET_GRASS_DAMAGE;

        pBullet->m_fSpeed = BULLET_WIND_FIRST_SPEED;

        // �}���`�ω��̈����Ȃ�
        if (move == CHANGE_MULTI)
        {
            // �}���`������
            pBullet->m_element = ELEMENT_MULTI;
        }

        break;
    }

    return pBullet;
}

//================================
// ���Ƃ̓����蔻��
//================================
bool CBullet::HitFloor(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �ϐ��錾
    bool bHit = false;  // ���ɓ����������ǂ���

    // ���̔�����擾
    bool bFloor = false;
    bFloor = CGame::GetFloor();

    // ���Ƃ̓����蔻��
    if (bFloor == true)
    {
        // �e�̒��S������艺�ɂȂ�����
        if (pos.y >= FLOOR_COLLISION)
        {
            // ���������t���O��true��
            bHit = true;

            // �G�t�F�N�g���o��(�����ʒu�́A�ړ���������߂��Ă���)
            // �������ƂɏՌ��g�̐F��ς���
            switch (m_element)
            {
            case ELEMENT_FIRE:

                // �Ռ��g�G�t�F�N�g
                CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                    BULLET_FIRE_COLOR, CEffect::TYPE_WAVE);

                // �����G�t�F�N�g
                CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, EXPLOSION_SIZE,
                    DEFAULT_COLOR, CEffect::TYPE_EXPLOSION);

                break;

            case ELEMENT_WATER:

                // �Ռ��g�G�t�F�N�g
                CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                    BULLET_WATER_COLOR, CEffect::TYPE_WAVE);

                // �������G�t�F�N�g
                CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, WATAR_EXPLOSION_SIZE,
                    D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), CEffect::TYPE_WATER_EXPLOSION);

                break;

            case ELEMENT_LIGHT:

                // �Ռ��g�G�t�F�N�g
                CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                    BULLET_LIGHT_COLOR, CEffect::TYPE_WAVE);

                // �d���G�t�F�N�g(�_���[�W�ɂ���āA�傫����ς���)
                CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, D3DXVECTOR3((float)m_nDamage * 1.5f, (float)m_nDamage * 1.5f, 0.0f),
                    DEFAULT_COLOR, CEffect::TYPE_SHOCK);

                break;

            case ELEMENT_GRASS:

                // �Ռ��g�G�t�F�N�g
                CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
                    BULLET_GRASS_COLOR, CEffect::TYPE_WAVE);

                // �����G�t�F�N�g
                CEffect::Create(pos + BULLET_HIT_FLOOR_EFFECT_ADD_POS - m_move, EXPLOSION_SIZE,
                    DEFAULT_COLOR, CEffect::TYPE_EXPLOSION);

                break;
            }
        }
    }

    return bHit;
}

//====================================================
// �o���b�g���猩�����@�ւ̊p�x
//====================================================
float CBullet::GetAngleToPlayer(void)
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
// ���o�[�X�g
//====================================================
void CBullet::FireBurst(D3DXVECTOR3 pos)
{
    float fSpeed = BULLET_FIRE_BURST_CREATE_BULLET_SPEED;             // �o�[�X�g�Ő�������鉊�̒e�̑��x
    D3DXVECTOR3 sizeBullet = BULLET_FIRE_BURST_CREATE_BULLET_SIZE;    // �o�[�X�g�Ő�������鉊�̒e�̑傫��

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

    CBullet::Create(pos, sizeBullet, D3DXVECTOR3(sinf(D3DX_PI / 8) * fSpeed, -cosf(D3DX_PI / 8) * fSpeed, 0.0f),
        CBullet::TYPE_FIRE, TRIBE_ENEMY);

    CBullet::Create(pos, sizeBullet, D3DXVECTOR3(sinf(D3DX_PI / 8) * fSpeed, cosf(D3DX_PI / 8) * fSpeed, 0.0f),
        CBullet::TYPE_FIRE, TRIBE_ENEMY);

    CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-sinf(D3DX_PI / 8) * fSpeed, -cosf(D3DX_PI / 8) * fSpeed, 0.0f),
        CBullet::TYPE_FIRE, TRIBE_ENEMY);

    CBullet::Create(pos, sizeBullet, D3DXVECTOR3(-sinf(D3DX_PI / 8) * fSpeed, cosf(D3DX_PI / 8) * fSpeed, 0.0f),
        CBullet::TYPE_FIRE, TRIBE_ENEMY);
}

//====================================================
// ������
//====================================================
void CBullet::SmallExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �G�t�F�N�g�p�̕ϐ��錾
    float fAngle = 0.0f;                // �p�x
    float fRadius = 0.0f;               // ���a
    float fSize = 0.0f;                 // �傫��

    // �����̃p�[�e�B�N������x�ɏo��
    for (int nCnt = 0; nCnt < EFFECT_SMALL_EXPLOSION_COUNT_LOOP; nCnt++)
    {
        // �����_���Ȋp�x�Ɣ��a���擾
        fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        fRadius = float(rand() % (int)size.x) / 20.0f;
        fSize = float(rand() % (int)size.x + (int)(size.x / 2));

        // �����G�t�F�N�g
        CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius, 0.0f),
            D3DXVECTOR3(fSize, fSize, 0.0f), EFFECT_SMALL_EXPLOSION_COLOR, CEffect::TYPE_SMALL_EXPLOSION);
    }
}
