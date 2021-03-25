//===============================================
//
// �G�t�F�N�g���� (effect.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "effect.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "library.h"
#include "player.h"
#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include "bg.h"

//=======================================
// �}�N����`
//=======================================
#define ESCAPE_CHARGE_LOOP 1000 // �v���C���[���`���[�W���Ȃ�����ꂽ���́A�`���[�W�̃��[�v�𔲂���

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[CEffect::TYPE_MAX] = {};

//========================================
// �G�t�F�N�g�̃R���X�g���N�^
//========================================
CEffect::CEffect() :CScene2D(OBJTYPE::OBJTYPE_EFFECT)
{
    m_move = DEFAULT_VECTOR;
    m_col = DEFAULT_COLOR;
    m_nLife = 1;    // 0���Ə����邽��
    m_type = CEffect::TYPE_MAX;
    m_bAlphaDown = false;

    m_fAngle = 0.0f;
    m_fRotSpeed = 0.0f;
}

//========================================
// �G�t�F�N�g�̃f�X�g���N�^
//========================================
CEffect::~CEffect()
{

}

//========================================
// �G�t�F�N�g�̏���������
//========================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// �G�t�F�N�g�̏I������
//========================================
void CEffect::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �G�t�F�N�g�̍X�V����
//========================================
void CEffect::Update(void)
{
    // �L�[�{�[�h���擾
    CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

    // �R���g���[�����擾
    CInputJoypad *pInputJoypad = CManager::GetInputJoypad();
    DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();                   // �ʒu���擾
    D3DXVECTOR3 size = GetSize();                      // �T�C�Y���擾
    float fTargetPosX = 0.0f, fTargetPosY = 0.0f;      // �ڕW�̍��W
    float fMyPosX = 0.0f, fMyPosY = 0.0f;		       // �����̍��W
    float fAngle = 0.0f;							   // �p�x
    D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // �ړ���
    bool bUse = true;                                  // �g�p���Ă��邩�ǂ���

    // �v���C���[�֘A�̕ϐ��錾
    CPlayer *pPlayer = NULL;                        // �v���C���[���擾
    CScene2D *pPlayerScene2D = NULL;                // �v���C���[���V�[��2D�ɃL���X�g
    D3DXVECTOR3 playerPos = pos;                    // �v���C���[�̈ʒu(�`���[�W���Ȃ�����ꂽ���̂��߁A�G�t�F�N�g�̈ʒu�ŏ���������)
    D3DXVECTOR3 playerSize = DEFAULT_VECTOR;        // �v���C���[�̑傫��
    int nPlayerChargeTime = ESCAPE_CHARGE_LOOP;     // �v���C���[�̃`���[�W����
    float fPlayerAngle = 0.0f;                      // �v���C���[�̊p�x

    // �Q�[���Ȃ�
    if (CManager::GetMode() == CManager::MODE_GAME)
    {
        // ��̒��Ȃ�A�v���C���[�̊p�x�̒l��ς��Ă���
        if (CBg::GetInTheSky() == true)
        {
            fPlayerAngle = D3DX_PI / 4;
        }

        // �v���C���[�����݂��Ă���Ȃ�
        if (CGame::GetDispPlayer() == true)
        {
            // �v���C���[�̏����擾
            pPlayer = CGame::GetPlayer();
            pPlayerScene2D = (CScene2D*)pPlayer;
            playerPos = pPlayerScene2D->GetPosition();
            playerSize = pPlayerScene2D->GetSize();
            nPlayerChargeTime = pPlayer->GetChargeTime();
            fPlayerAngle = pPlayer->GetPlayerAngle();

            // �v���C���[�������Ȃ��Ȃ�
            if (CGame::GetMovePlayer() == false)
            {
                nPlayerChargeTime = ESCAPE_CHARGE_LOOP; // �`���[�W�������I�ɔ���
            }

            // �Ó]����
            if (CGame::GetDarkening() == true)
            {
                nPlayerChargeTime = ESCAPE_CHARGE_LOOP; // �`���[�W�������I�ɔ���
            }
        }
    }

    // ��ނɉ������ꍇ����
    switch (m_type)
    {
        // �p�[�e�B�N��
    case CEffect::TYPE_PARTICLE:

        // �T�C�Y�����񂾂�k��
        size.x -= 5.0f;
        size.y -= 5.0f;

        // ���񂾂񓧖���
        m_col.a -= 0.1f;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �E�F�[�u
    case CEffect::TYPE_WAVE:

        // �T�C�Y�����񂾂�g��
        size.x += 3.0f;
        size.y += 3.0f;

        // ���񂾂񓧖���
        m_col.a -= 0.015f;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ����
    case CEffect::TYPE_EXPLOSION:

        // �T�C�Y�����񂾂�g��
        size.x += 5.0f;
        size.y += 5.0f;

        // �A�j���[�V������ݒ�
        if (SetAnimation(3, 8) == true)
        {
            // �A�j���[�V���������������A���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �`���[�W
    case CEffect::TYPE_CHARGE:

        // �T�C�Y��ς��A���@�Ɉʒu�����т���
        size.x += CHARGE_RATE_SIZE;
        size.y += CHARGE_RATE_SIZE;
        pos = playerPos;

        // �T�C�Y�͍ő�l�𒴂����炻��ŌŒ�
        if (size.x > CHARGE_SIZE)
        {
            size.x = CHARGE_SIZE;
            size.y = CHARGE_SIZE;
        }

        // �ő�`���[�W�ɂȂ�����A�_��
        if (nPlayerChargeTime == MAX_CHARGE_TIME)
        {
            // �J�E���^�[��i�߂āA�p�^�[����؂�ւ���
            int nPatternAnim = CountAnimation(2, 2);

            // �����x��2�p�^�[���Ő؂�ւ���
            if (nPatternAnim == 1)
            {
                CScene2D::SetColor(D3DXCOLOR(m_col.r, m_col.g, m_col.b, 0.7f));
            }
            else
            {
                CScene2D::SetColor(D3DXCOLOR(m_col.r, m_col.g, m_col.b, 0.9f));
            }
        }
        else
        {
            // �F��ύX
            CScene2D::SetColor(m_col);
        }

        // �e��ł��I������珙�X�ɓ����ɂ���t���O��true��
        if (nPlayerChargeTime == 0)
        {
            m_bAlphaDown = true;
        }
        // �`���[�W���Ȃ�����ꂽ��A��������
        else if (nPlayerChargeTime == ESCAPE_CHARGE_LOOP)
        {
            m_col.a = -0.1f;
            CScene2D::SetColor(m_col);
        }

        // �e��ł��I������珙�X�ɓ�����
        if (m_bAlphaDown == true)
        {
            m_col.a -= 0.05f;
            CScene2D::SetColor(m_col);
        }

        break;

        // �`���[�W�̃p�[�e�B�N��
    case CEffect::TYPE_CHARGE_PART:

        // �T�C�Y�k���A���񂾂񓧖���
        size.x -= 0.5f;
        size.y -= 0.5f;
        m_col.a -= 0.1f;

        // �ڕW�̍��W�Ǝ��g�̍��W
        fTargetPosX = playerPos.x, fTargetPosY = playerPos.y;
        fMyPosX = pos.x, fMyPosY = pos.y;

        // �p�x�����߂�
        fAngle = atan2f((fMyPosX - fTargetPosX), (fMyPosY - fTargetPosY));

        // �ړ��ʂ����߂�
        move = D3DXVECTOR3(-sinf(fAngle)*CHARGE_PART_SPEED, -cosf(fAngle)*CHARGE_PART_SPEED, 0.0f);

        // �ʒu�Ɉړ��ʂ𑫂�
        pos.x += move.x;
        pos.y += move.y;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ���o���b�g
    case CEffect::TYPE_LIGHT_BULLET:

        // �T�C�Y�g�債�A���@�Ɉʒu�����т���(���@�̊p�x���l��)
        size.x += BULLET_LIGHT_EXTEND_RATE;
        size.y += BULLET_LIGHT_EXTEND_RATE;
        pos = D3DXVECTOR3(playerPos.x + (cosf(fPlayerAngle) *playerSize.x), 
            playerPos.y - (sinf(fPlayerAngle) *(playerSize.y)), 0.0f);

        // �T�C�Y�͍ő�l�𒴂����炻��ŌŒ�
        if (size.x > BULLET_LIGHT_MAX_SIZE)
        {
            size.x = BULLET_LIGHT_MAX_SIZE;
            size.y = BULLET_LIGHT_MAX_SIZE;
        }

        // �J�E���^�[��i�߂āA�p�^�[����؂�ւ���
        SetAnimation(2, 5);

        // �������甭��(�`���[�W���Ȃ�����ꂽ��������)(�|�[�Y�{�^���ł�����)
        if (pInputKeyboard->GetKeyboardRelease(DIK_B) || pInputJoypad->GetJoypadRelease(PLAYER_1, CInputJoypad::BUTTON_Y) ||
            nPlayerChargeTime == ESCAPE_CHARGE_LOOP || nPlayerChargeTime == 0
            || pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
        {
            // ���̒e
            CBullet::Create(pos, size, 
                D3DXVECTOR3(cosf(fPlayerAngle) * BULLET_LIGHT_SPEED, sinf(fPlayerAngle) * (-BULLET_LIGHT_SPEED), 0.0f),
                CBullet::TYPE_LIGHT, TRIBE_PLAYER);

            // ���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �d��
    case CEffect::TYPE_SHOCK:

        // �T�C�Y�g��
        size.x += 5.0f;
        size.y += 5.0f;

        // �A�j���[�V������ݒ�
        if (SetAnimation(3, 8) == true)
        {
            // �A�j���[�V���������������A���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �唚��
    case CEffect::TYPE_BIG_EXPLOSION:

        // �A�j���[�V������ݒ�
        if (SetAnimation(3, 10) == true)
        {
            // �A�j���[�V���������������A���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �ԉΉ�
    case CEffect::TYPE_RED_SPARK:

        // �A�j���[�V������ݒ�
        if (SetAnimation(4, 10) == true)
        {
            // �A�j���[�V���������������A���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �ΉΉ�
    case CEffect::TYPE_GREEN_SPARK:

        // �A�j���[�V������ݒ�
        if (SetAnimation(4, 10) == true)
        {
            // �A�j���[�V���������������A���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �Ή�
    case CEffect::TYPE_BLUE_SPARK:

        // �A�j���[�V������ݒ�
        if (SetAnimation(4, 10) == true)
        {
            // �A�j���[�V���������������A���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ���Ή�
    case CEffect::TYPE_BLACK_SPARK:

        // �A�j���[�V������ݒ�
        if (SetAnimation(4, 10) == true)
        {
            // �A�j���[�V���������������A���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ������
    case CEffect::TYPE_WATER_EXPLOSION:

        // �A�j���[�V������ݒ�
        if (SetAnimation(3, 8) == true)
        {
            // �A�j���[�V���������������A���g�p��
            bUse = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ���]�`���[�W
    case CEffect::TYPE_REVERSE_CHARGE:

        fAngle = GetAngleToDragon();

        // �ړ��ʂ����߂�
        move = D3DXVECTOR3(-sinf(fAngle)*CHARGE_PART_SPEED, -cosf(fAngle)*CHARGE_PART_SPEED, 0.0f);

        // �T�C�Y�k��
        size.x -= 2.0f;
        size.y -= 2.0f;

        // �ʒu�Ɉړ��ʂ𑫂�
        pos.x += move.x;
        pos.y += move.y;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �h���S���I�[��
    case CEffect::TYPE_DRAGON_AURA:

        // �ړ��ʕ��A���
        pos.y -= m_move.y;

        // ���񂾂񓧖���
        m_col.a -= 0.02f;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ��d�E�F�[�u
    case CEffect::TYPE_DOUBLE_WAVE:

        // �T�C�Y�g��A���񂾂񓧖���
        size.x += EFFECT_DOUBLE_WAVE_EXTEND_RATE;
        size.y += EFFECT_DOUBLE_WAVE_EXTEND_RATE;
        m_col.a -= EFFECT_DOUBLE_WAVE_FADE_OUT_RATE;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �p�[�e�B�N��(jpg)
    case CEffect::TYPE_PARTICLE_JPG:

        // ���񂾂񓧖���
        m_col.a -= 0.1f;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ��
    case CEffect::TYPE_FIRE:

        if (m_bAlphaDown == true)
        {
            // ���񂾂񓧖���
            m_col.a -= EFFECT_FIRE_FADE_OUT_RATE;

            // �ړ��ʕ��A���
            pos.y -= m_move.y;

        }
        else
        {
            // ���񂾂񌩂���悤��
            m_col.a += EFFECT_FIRE_FADE_IN_RATE;

            if (m_col.a >= EFFECT_FIRE_ALPHA_START_MOVE)
            {
                // �ړ��ʕ��A���
                pos.y -= m_move.y;
            }
        }

        // �Ԃɋ߂Â��Ă���
        m_col.g -= EFFECT_FIRE_TO_RED_RATE;

        // ���̒l�œ����x���������true��
        if (m_col.a >= EFFECT_FIRE_ALPHA_START_FADE_OUT)
        {
            m_bAlphaDown = true;
        }

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �}�O�}
    case CEffect::TYPE_MAGMA:

        // �ړ��ʂ𔽉f
        pos.x += m_move.x;

        // ��̒��ɂ���Ȃ�
        if (CBg::GetInTheSky() == true)
        {
            pos.y += FLOWING_STAGE;
        }

        if (m_bAlphaDown == true)
        {
            // �Ԃɋ߂Â��Ă���
            m_col.g -= m_fRotSpeed;

        }
        else
        {
            // ���ɋ߂Â��Ă���
            m_col.g += m_fRotSpeed;
        }

        if (m_col.g >= 1.0f)
        {
            m_bAlphaDown = true;
        }
        else if (m_col.g <= 0.0f)
        {
            m_bAlphaDown = false;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �t����
    case CEffect::TYPE_LEAF:

        // ���񂾂����
        m_col.a -= EFFECT_LEAF_FADE_RATE;

        // �d��(�����y��)
        m_move.y += GRAVITY / 2;

        // �ړ��ʔ��f
        pos += m_move;

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �}
    case CEffect::TYPE_BRANCH:

        // ���񂾂����
        m_col.a -= EFFECT_BRANCH_FADE_RATE;

        // �d��(�����y��)
        m_move.y += GRAVITY / 2;

        // �ړ��ʔ��f
        pos += m_move;

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �Ԃ���
    case CEffect::TYPE_RED_FIRE:

        // ���񂾂񓧖���
        m_col.a -= EFFECT_RED_FIRE_FADE_OUT_RATE;

        // �ړ��ʕ��A���
        pos.y -= m_move.y;

        // �Ԃɋ߂Â��Ă���
        m_col.g -= EFFECT_YELLOW_FIRE_TO_RED_RATE;

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ����
    case CEffect::TYPE_BLUE_FIRE:

        // ���񂾂񓧖���
        m_col.a -= EFFECT_BLUE_FIRE_FADE_OUT_RATE;

        // �ړ��ʕ��A���
        pos.y -= m_move.y;

        // �ɋ߂Â��Ă���
        m_col.g -= EFFECT_WHITE_FIRE_TO_BLUE_RATE;
        m_col.r -= EFFECT_WHITE_FIRE_TO_BLUE_RATE;

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ���F����
    case CEffect::TYPE_YELLOW_FIRE:

        // ���񂾂񓧖���
        m_col.a -= EFFECT_YELLOW_FIRE_FADE_OUT_RATE;

        // �ړ��ʕ��A���
        pos.y -= m_move.y;

        // �΂ɋ߂Â��Ă���
        m_col.r -= EFFECT_YELLOW_FIRE_TO_GREEN_RATE;

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ���̉�
    case CEffect::TYPE_PURPLE_FIRE:

        // ���񂾂񓧖���
        m_col.a -= EFFECT_PURPLE_FIRE_FADE_OUT_RATE;

        // �ړ��ʕ��A���
        pos.y -= m_move.y;

        // ���ɋ߂Â��Ă���
        m_col.r -= EFFECT_WHITE_FIRE_TO_PURPLE_RATE_R;
        m_col.g -= EFFECT_WHITE_FIRE_TO_PURPLE_RATE_G;

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �p�[�e�B�N���ɂ�锚��
    case CEffect::TYPE_PART_EXPLOSION:

        // ���񂾂񓧖���
        m_col.a -= EFFECT_EXPLOSION_FADE_OUT_RATE;

        // �ړ��ʕ��A���
        pos.y -= m_move.y;

        // �Ԃɋ߂Â��Ă���
        m_col.g -= EFFECT_EXPLOSION_TO_RED_RATE;
        m_col.b -= EFFECT_EXPLOSION_TO_RED_RATE;

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // ������
    case CEffect::TYPE_SMALL_EXPLOSION:

        // ���񂾂񓧖���
        m_col.a -= EFFECT_SMALL_EXPLOSION_FADE_OUT_RATE;

        // �ړ��ʕ��A���
        pos.y -= m_move.y;

        // ��]
        m_fAngle += m_fRotSpeed;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �_
    case CEffect::TYPE_CLOUD:

        // �ړ��ʂ����Z
        pos += m_move;

        // ��]
        m_fAngle += m_fRotSpeed;

        // ���[�A���[�ɒB�����瓧���x��������
        if (pos.x <= 0.0f || pos.y >= SCREEN_HEIGHT)
        {
            m_col.a -= EFFECT_CLOUD_FADE_OUT_RATE;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �{�[�i�X�|�C���g
    case CEffect::TYPE_BONUS_POINT:

        // ���X�ɏ��
        pos.y -= BONUS_POINT_MOVE_RATE;

        // ���񂾂񓧖���
        m_col.a -= BONUS_POINT_FADE_RATE;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;
    }

    // ���\���̏���
    if (m_type == TYPE_25 || m_type == TYPE_50 || m_type == TYPE_75 || m_type == TYPE_100)
    {
        // ���l��������t���O��false�Ȃ牺����Atrue�Ȃ�グ��
        if (m_bAlphaDown == false)
        {
            m_col.a += PERCENTAGE_FADE_RATE;
        }
        else
        {
            m_col.a -= PERCENTAGE_FADE_RATE;
        }

        // �ő�܂ŕ\��������A���l��������
        if (m_col.a >= 1.0f)
        {
            m_col.a = 1.0f;
            m_bAlphaDown = true;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);
    }

    // �ʒu�𔽉f
    SetPosition(pos);

    // �T�C�Y�𔽉f
    SetSize(size);

    // ���_���W��ύX
    // ��]�Ƃ����łȂ����̂ŕ�����(�^�C�g���̉��n�́A���ǉ�]�����Ă��Ȃ�)
    if (m_type == TYPE_FIRE || m_type == TYPE_LEAF || m_type == TYPE_BRANCH 
        || m_type == TYPE_CLOUD || m_type == TYPE_PART_EXPLOSION || m_type == TYPE_SMALL_EXPLOSION)
    {
        SetRotVertex(m_fAngle);
    }
    else
    {
        SetVertex();
    }

    // �T�C�Y���Ȃ��Ȃ�A�����ɂȂ�A���C�t���Ȃ��Ȃ����疢�g�p��
    if (size.x < 0 || size.y < 0 || m_col.a < 0 || m_nLife <= 0)
    {
        bUse = false;
    }

    // ���̒e�A�X�e�[�W3�̉��A�_�ȊO�́A��ʊO�Ŗ��g�p��
    if (m_type == TYPE_LIGHT_BULLET || m_type == TYPE_FIRE || m_type == TYPE_CLOUD)
    {
        // �Q�[���O�Ȃ�
        if (OutGame2D(&pos, &size) == true)
        {
            // ���g�p��
            bUse = false;
        }
    }
    else
    {
        // ��ʊO�Ȃ�
        if (OutScreen2D(&pos, &size) == true)
        {
            // ���g�p��
            bUse = false;
        }
    }

    // �g�p�̃t���O��false�Ȃ����
    if (bUse == false)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//========================================
// �G�t�F�N�g�̕`�揈��
//========================================
void CEffect::Draw(void)
{
    switch (m_type)
    {
        // �p�[�e�B�N���͉��Z����
    case CEffect::TYPE_PARTICLE:

        SetAdditiveSynthesis();

        break;

        // �`���[�W�͉��Z����&���e�X�g
    case CEffect::TYPE_CHARGE:

        SetAdditiveSynthesis();
        SetAlphaTest();

        break;

        // �`���[�W�̃p�[�e�B�N���͉��Z����
    case CEffect::TYPE_CHARGE_PART:

        SetAdditiveSynthesis();

        break;

        // ���]�`���[�W�͔��]����
    case CEffect::TYPE_REVERSE_CHARGE:

        SetNega();

        break;

        // �h���S���I�[���͉��Z����
    case CEffect::TYPE_DRAGON_AURA:

        SetAdditiveSynthesis();

        break;

        // ��d�E�F�[�u�͉��Z����
    case CEffect::TYPE_DOUBLE_WAVE:

        SetAdditiveSynthesis();

        break;

        // ���p�[�e�B�N��(JPG)�͉��Z����
    case CEffect::TYPE_PARTICLE_JPG:

        SetAdditiveSynthesis();

        break;

        // ���͉��Z����
    case CEffect::TYPE_FIRE:

        SetAdditiveSynthesis();

        break;

        // �}�O�}�͉��Z����
    case CEffect::TYPE_MAGMA:

        SetAdditiveSynthesis();

        break;

        // �Ԃ����͉��Z����
    case CEffect::TYPE_RED_FIRE:

        SetAdditiveSynthesis();

        break;

        // �����͉��Z����
    case CEffect::TYPE_BLUE_FIRE:

        SetAdditiveSynthesis();

        break;

        // ���F�����͉��Z����
    case CEffect::TYPE_YELLOW_FIRE:

        SetAdditiveSynthesis();

        break;

        // ���̉��͉��Z����
    case CEffect::TYPE_PURPLE_FIRE:

        SetAdditiveSynthesis();

        break;

        // �_�͉��Z����
    case CEffect::TYPE_CLOUD:

        SetAdditiveSynthesis();

        break;

        // �p�[�e�B�N���ɂ�锚���͉��Z����
    case CEffect::TYPE_PART_EXPLOSION:

        SetAdditiveSynthesis();

        break;

        // �������͉��Z����
    case CEffect::TYPE_SMALL_EXPLOSION:

        SetAdditiveSynthesis();

        break;
    }

    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �G�t�F�N�g�̉摜���[�h����
//========================================
HRESULT CEffect::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //�e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/particle001.png", &m_apTexture[CEffect::TYPE_PARTICLE]);	    // �p�[�e�B�N��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect001.png", &m_apTexture[CEffect::TYPE_WAVE]);	            // �Ռ��g
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect002.png", &m_apTexture[CEffect::TYPE_EXPLOSION]);	    // ����
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/particle002.png", &m_apTexture[CEffect::TYPE_CHARGE]);	        // �`���[�W
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/particle001.png", &m_apTexture[CEffect::TYPE_CHARGE_PART]);    // �`���[�W�̃p�[�e�B�N��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet002.png", &m_apTexture[CEffect::TYPE_LIGHT_BULLET]);	    // ���o���b�g
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect004.png", &m_apTexture[CEffect::TYPE_SHOCK]);	        // �d��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect005.png", &m_apTexture[CEffect::TYPE_BIG_EXPLOSION]);    // �唚��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect006.png", &m_apTexture[CEffect::TYPE_RED_SPARK]);        // �ԉΉ�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect007.png", &m_apTexture[CEffect::TYPE_GREEN_SPARK]);      // �ΉΉ�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect008.png", &m_apTexture[CEffect::TYPE_BLUE_SPARK]);       // �Ή�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect009.png", &m_apTexture[CEffect::TYPE_BLACK_SPARK]);      // ���Ή�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect010.png", &m_apTexture[CEffect::TYPE_WATER_EXPLOSION]);  // ������
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/reverse000.png", &m_apTexture[CEffect::TYPE_REVERSE_CHARGE]);	// ���]�`���[�W
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect011.png", &m_apTexture[CEffect::TYPE_25]);               // 25��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect012.png", &m_apTexture[CEffect::TYPE_50]);               // 50��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect013.png", &m_apTexture[CEffect::TYPE_75]);               // 75��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect014.png", &m_apTexture[CEffect::TYPE_100]);              // 100��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/particle001.png", &m_apTexture[CEffect::TYPE_DRAGON_AURA]);	// �h���S���I�[��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect101.jpg", &m_apTexture[CEffect::TYPE_DOUBLE_WAVE]);	    // ��d�E�F�[�u
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_apTexture[CEffect::TYPE_PARTICLE_JPG]);	    // �p�[�e�B�N��(jpg)
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect100.jpg", &m_apTexture[CEffect::TYPE_FIRE]);	            // ��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_apTexture[CEffect::TYPE_MAGMA]);	        // �}�O�}
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect015.png", &m_apTexture[CEffect::TYPE_LEAF]);             // �t����
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect016.png", &m_apTexture[CEffect::TYPE_BRANCH]);           // �}
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect100.jpg", &m_apTexture[CEffect::TYPE_RED_FIRE]);	        // �Ԃ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect100.jpg", &m_apTexture[CEffect::TYPE_BLUE_FIRE]);	    // ����
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect100.jpg", &m_apTexture[CEffect::TYPE_YELLOW_FIRE]);	    // ���F����
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect100.jpg", &m_apTexture[CEffect::TYPE_PURPLE_FIRE]);	    // ���̉�
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect100.jpg", &m_apTexture[CEffect::TYPE_PART_EXPLOSION]);	// �p�[�e�B�N���ɂ�锚��
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect100.jpg", &m_apTexture[CEffect::TYPE_SMALL_EXPLOSION]);	// ������
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect100.jpg", &m_apTexture[CEffect::TYPE_CLOUD]);	        // �_
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect017.png", &m_apTexture[CEffect::TYPE_BONUS_POINT]);      // �{�[�i�X�|�C���g

    return S_OK;
}

//========================================
// �G�t�F�N�g�̉摜�j������
//========================================
void CEffect::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CEffect::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// �G�t�F�N�g�̍쐬
//================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CEffect::TYPE type)
{
    // �ϐ��錾
    CEffect *pEffect = NULL;

    // ���������m��
    pEffect = new CEffect;

    // �^�C�v�̂݁A�e�N�X�`�������蓖�Ă̂��߂Ɍ��т��Ă���
    pEffect->m_type = type;

    // ������
    pEffect->Init(pos, size);

    // �����o�ϐ������т���
    pEffect->m_col = col;

    // ��ނ��ƂɁA�����_���Ȉړ��ʂ��擾
    float fSpeedX = 0.0f;
    float fSpeedY = 0.0f;
    switch (type)
    {
    case TYPE_DRAGON_AURA:

        // �c�ړ��̒l�����߂�
        fSpeedY = float(rand() % 800 + 300) / 100.0f;

        // �ړ��ʂɌ��т���
        pEffect->m_move.y = fSpeedY;

        break;

    case TYPE_FIRE:

        // �c�ړ��̒l�����߂�
        fSpeedY = float(rand() % 150 + 100) / 100.0f;

        // �ړ��ʂɌ��т���
        pEffect->m_move.y = fSpeedY;

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 100) / 1000.0f - float(rand() % 100) / 1000.0f;

        break;

    case TYPE_MAGMA:

        // �ړ��ʂɌ��т���
        pEffect->m_move.x = -FLOWING_STAGE;

        // �Ԃɋ߂Â��邽��
        pEffect->m_bAlphaDown = true;

        // �t�F�[�h�������A�����_���Ɏ擾
        pEffect->m_fRotSpeed = float(rand() % 1000) / 20000.0f;

        break;

    case TYPE_LEAF:

        // �ړ��̒l�����߂�
        fSpeedX = float(rand() % 700 + 200) / 100.0f;
        fSpeedY = float(rand() % 500 + 300) / 100.0f;
        pEffect->m_move.x = -fSpeedX;   // �E���獶�֔�΂����߁A�}�C�i�X
        pEffect->m_move.y = -fSpeedY;   // �������ɔ�΂����߁A�}�C�i�X

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 100) / 1000.0f - float(rand() % 100) / 1000.0f;

        break;

    case TYPE_BRANCH:

        // �ړ��̒l�����߂�
        fSpeedX = float(rand() % 700 + 200) / 100.0f;
        fSpeedY = float(rand() % 500 + 300) / 100.0f;
        pEffect->m_move.x = -fSpeedX;   // �E���獶�֔�΂����߁A�}�C�i�X
        pEffect->m_move.y = -fSpeedY;   // �������ɔ�΂����߁A�}�C�i�X

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 100) / 1000.0f - float(rand() % 100) / 1000.0f;

        break;

    case TYPE_RED_FIRE:

        // �T�C�Y�g��
        size.x += EFFECT_RED_FIRE_EXTEND_RATE;
        size.y += EFFECT_RED_FIRE_EXTEND_RATE;

        // �c�ړ��̒l�����߂�
        fSpeedY = float(rand() % 150 + 100) / 100.0f;

        // �ړ��ʂɌ��т���
        pEffect->m_move.y = fSpeedY;

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 100) / 1000.0f - float(rand() % 100) / 1000.0f;

        break;


    case TYPE_BLUE_FIRE:

        // �c�ړ��̒l�����߂�
        fSpeedY = float(rand() % 150 + 100) / 100.0f;

        // �ړ��ʂɌ��т���
        pEffect->m_move.y = fSpeedY;

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 100) / 1000.0f - float(rand() % 100) / 1000.0f;

        break;


    case TYPE_YELLOW_FIRE:

        // �c�ړ��̒l�����߂�
        fSpeedY = float(rand() % 150 + 100) / 100.0f;

        // �ړ��ʂɌ��т���
        pEffect->m_move.y = fSpeedY;

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 100) / 1000.0f - float(rand() % 100) / 1000.0f;

        break;

    case TYPE_PURPLE_FIRE:

        // �c�ړ��̒l�����߂�
        fSpeedY = float(rand() % 150 + 100) / 100.0f;

        // �ړ��ʂɌ��т���
        pEffect->m_move.y = fSpeedY;

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 100) / 1000.0f - float(rand() % 100) / 1000.0f;

        break;

    case TYPE_PART_EXPLOSION:

        // �c�ړ��̒l�����߂�
        fSpeedY = float(rand() % 150 + 100) / 100.0f;

        // �ړ��ʂɌ��т���
        pEffect->m_move.y = fSpeedY;

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 25) / 1000.0f - float(rand() % 25) / 1000.0f;

        break;

    case TYPE_SMALL_EXPLOSION:

        // �T�C�Y�ɂ���āA�㏸����X�s�[�h��ς���
        if (size.x < EFFECT_SMALL_EXPLOSION_BORDER_SIZE_THAT_CHANGE_SPEED)
        {
            // �c�ړ��̒l�����߂�
            fSpeedY = float(rand() % 75 + 50) / 100.0f;
        }
        else
        {
            // �c�ړ��̒l�����߂�
            fSpeedY = float(rand() % 150 + 100) / 100.0f;
        }

        // �ړ��ʂɌ��т���
        pEffect->m_move.y = fSpeedY;

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 100) / 1000.0f - float(rand() % 100) / 1000.0f;

        break;

    case TYPE_CLOUD:

        // ��̒��Ȃ�
        if (CBg::GetInTheSky() == true)
        {
            // �����ɗ����
            pEffect->m_move.x = -sinf(D3DX_PI / 4) * EFFECT_CLOUD_FLOWING_SPEED;
            pEffect->m_move.y = cosf(D3DX_PI / 4) * EFFECT_CLOUD_FLOWING_SPEED;
        }
        // ����ȊO��
        else
        {
            // �{�X�펞���ǂ����ő��x��ς���
            if (CGame::GetBossBattle() == false)
            {
                // �ʏ�́A���֗����
                pEffect->m_move.x = -EFFECT_CLOUD_FLOWING_SPEED;
            }
            else
            {
                // �{�X�펞�́A���ւ�����藬���
                pEffect->m_move.x = -EFFECT_CLOUD_FLOWING_SPEED_BOSS;
            }
        }

        // �����_���ɉ�]
        pEffect->m_fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
        pEffect->m_fRotSpeed = float(rand() % 25) / 1000.0f - float(rand() % 25) / 1000.0f;

        break;
    }

    return pEffect;
}

//====================================================
// �G�t�F�N�g���猩���h���S���ւ̊p�x
//====================================================
float CEffect::GetAngleToDragon(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();           // �ʒu���擾
    float fTargetPosX = 0.0f;                  // �ڕW��X���W
    float fTargetPosY = 0.0f;                  // �ڕW��Y���W
    float fMyPosX = 0.0f;                      // ���g��X���W
    float fMyPosY = 0.0f;                      // ���g��Y���W
    float fAngle = 0.0f;                       // ���߂�p�x

    // �ڕW�̍��W�Ǝ��g�̍��W
    fTargetPosX = ENEMY_BOSS_DRAGON_STOP_POS_X - 10.0f, fTargetPosY = ENEMY_BOSS_DRAGON_STOP_POS_Y;
    fMyPosX = pos.x, fMyPosY = pos.y;

    // �p�x�����߂�
    fAngle = atan2f((fMyPosX - fTargetPosX), (fMyPosY - fTargetPosY));

    return fAngle;
}
