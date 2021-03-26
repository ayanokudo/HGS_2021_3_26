//===============================================
//
// �c������ (afterimage.cpp)
// Author : �㓡�T�V��
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "afterimage.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "library.h"
#include "game.h"
#include "effect.h"
#include "sound.h"
#include "whiteFade.h"
#include "player.h"
#include "enemy.h"

//=======================================
// �}�N����`
//=======================================

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CAfterimage::m_apTexture[CAfterimage::TYPE_MAX] = {};

//========================================
// �c���̃R���X�g���N�^
//========================================
CAfterimage::CAfterimage() :CScene2D(OBJTYPE::OBJTYPE_AFTERIMAGE)
{
    m_nCntTime = 0;
    m_fAngle = 0.0f;
    m_move = DEFAULT_VECTOR;
    m_col = DEFAULT_COLOR;
    m_type = CAfterimage::TYPE_MAX;
}

//========================================
// �c���̃f�X�g���N�^
//========================================
CAfterimage::~CAfterimage()
{

}

//========================================
// �c���̏���������
//========================================
HRESULT CAfterimage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // ������
    CScene2D::Init(pos, size);

    // �e�N�X�`�������蓖��
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}

//========================================
// �c���̏I������
//========================================
void CAfterimage::Uninit(void)
{
    // �I������
    CScene2D::Uninit();
}

//========================================
// �c���̍X�V����
//========================================
void CAfterimage::Update(void)
{
    // �ϐ��錾
    D3DXVECTOR3 pos = GetPosition();                   // �ʒu���擾
    D3DXVECTOR3 size = GetSize();                      // �T�C�Y���擾
    float fAngle = 0.0f;                               // �p�x
    float fRadius = 0.0f;                              // ���a
    float fAfterimageAngle = 0.0f;                     // �c���̊p�x

    // �����擾
    CSound *pSound = CManager::GetSound();

    // ��ނɉ������ꍇ����
    switch (m_type)
    {
        // �v���C���[
    case CAfterimage::TYPE_PLAYER:

        // ���񂾂񓧖���
        m_col.a -= AFTERIMAGE_PLAYER_FADE_RATE;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �v���C���[�z�u
    case CAfterimage::TYPE_PLAYER_DISP:

        // �����ʒu�ɋ߂Â���
        pos.x += PLAYER_SPEED_2;

        // �����ʒu�ɓ��B������
        if (pos.x >= PLAYER_START_POS_X)
        {
            // �v���C���[�����X�|�[��
            CGame::RespawnPlayer();

            // �����ɂ���
            m_col.a = -1.0f;
        }

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �{�X�X
    case CAfterimage::TYPE_BOSS_FOREST:

        // �J�E���^���Z
        m_nCntTime++;

        // ���񂾂񓧖���
        m_col.a -= AFTERIMAGE_BOSS_FADE_RATE;

        // �e�N�X�`�����W��ɂ����ɍX�V
        SetTexturePlace(2, 2);

        // �F��ύX(�Ԃł��񂾂񓧖�)
        CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, m_col.a));

        // �J�E���^�����ƂɁA�G�t�F�N�g��ݒ肷��
        if (m_nCntTime % AFTERIMAGE_BOSS_SET_EFFECT == 0)
        {
            // �G�t�F�N�g�p�ɁA�p�x�Ɣ��a�����߂�
            fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
            fRadius = float(rand() % AFTERIMAGE_BOSS_RADIUS + 0) / 100.0f;

            // �������Đ�
            pSound->Play(CSound::LABEL_SE_EXPLOSION);

            // �唚���G�t�F�N�g (�T�C�Y�͔{)
            CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius, 0.0f), 
                AFTERIMAGE_BOSS_EXPLOSION_SIZE,
                DEFAULT_COLOR, CEffect::TYPE_BIG_EXPLOSION);
        }

        // �����x��������؂�����A���t�F�[�h��ݒ�
        if (m_col.a < 0)
        {
            CWhiteFade::Create(WHITE_FADE_POS, WHITE_FADE_SIZE, WHITE_FADE_END_TIME, 
                D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f), CWhiteFade::TYPE_��);
        }

        break;

        // �{�X�h���S��
    case CAfterimage::TYPE_BOSS_DRAGON:

        // �J�E���^���Z
        m_nCntTime++;

        // ���񂾂񓧖���
        m_col.a -= AFTERIMAGE_BOSS_FADE_RATE;

        // �e�N�X�`�����W���U�����̂��̂ɍX�V
        SetParagraphTexturePlace(3, 2, 2, 4);

        // �F��ύX(�Ԃł��񂾂񓧖�)
        CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, m_col.a));

        // �J�E���^�����ƂɁA�G�t�F�N�g��ݒ肷��
        if (m_nCntTime % AFTERIMAGE_BOSS_SET_EFFECT == 0)
        {
            // �G�t�F�N�g�p�ɁA�p�x�Ɣ��a�����߂�
            fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
            fRadius = float(rand() % AFTERIMAGE_BOSS_RADIUS) / 100.0f;

            // �������Đ�
            pSound->Play(CSound::LABEL_SE_EXPLOSION);

            // �唚���G�t�F�N�g (�T�C�Y�͔{)
            CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius, 0.0f),
                AFTERIMAGE_BOSS_EXPLOSION_SIZE,
                DEFAULT_COLOR, CEffect::TYPE_BIG_EXPLOSION);
        }

        // �����x��������؂�����A���t�F�[�h��ݒ�
        if (m_col.a < 0)
        {
            CWhiteFade::Create(WHITE_FADE_POS, WHITE_FADE_SIZE, WHITE_FADE_END_TIME,
                D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f), CWhiteFade::TYPE_��);
        }

        break;

        // �{�X�u���C�Y
    case CAfterimage::TYPE_BOSS_BLAZE:

        // �J�E���^���Z
        m_nCntTime++;

        // ���񂾂񓧖���
        m_col.a -= AFTERIMAGE_BOSS_FADE_RATE;

        // �e�N�X�`�����W���U�����̂��̂ɍX�V
        SetTexturePlace(1, 3);

        // �F��ύX(�Ԃł��񂾂񓧖�)
        CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, m_col.a));

        // �J�E���^�����ƂɁA�G�t�F�N�g��ݒ肷��
        if (m_nCntTime % AFTERIMAGE_BOSS_SET_EFFECT == 0)
        {
            // �G�t�F�N�g�p�ɁA�p�x�Ɣ��a�����߂�
            fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
            fRadius = float(rand() % AFTERIMAGE_BOSS_RADIUS) / 100.0f;

            // �������Đ�
            pSound->Play(CSound::LABEL_SE_EXPLOSION);

            // �唚���G�t�F�N�g (�T�C�Y�͔{)
            CEffect::Create(D3DXVECTOR3(pos.x - sinf(fAngle)*fRadius, pos.y - cosf(fAngle)*fRadius, 0.0f),
                AFTERIMAGE_BOSS_EXPLOSION_SIZE,
                DEFAULT_COLOR, CEffect::TYPE_BIG_EXPLOSION);
        }

        // �����x��������؂�����A�Q�[���N���A��ݒ�
        if (m_col.a < 0)
        {
            // �Q�[���N���A
            CGame::SetGameClear();
        }

        break;

        // �S�b�h�o�[�h
    case CAfterimage::TYPE_GOD_BIRD:

        // ���񂾂񓧖���
        m_col.a -= AFTERIMAGE_PLAYER_FADE_RATE;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �_�ʗ�
    case CAfterimage::TYPE_MAGIC:

        // �T�C�Y�g��A���񂾂񓧖���
        size.x += MAGIC_EXTEND_RATE;
        size.y += MAGIC_EXTEND_RATE;
        m_col.a -= MAGIC_FADE_OUT_RATE;

        // �F��ύX
        CScene2D::SetColor(m_col);

        break;

        // �O�\�N���V
    case CAfterimage::TYPE_RANK_GUSOKU:

        // �e�N�X�`�����W���X�V
        SetAnimation(6, 2);

        // �E���獶��
        pos.x -= ENEMY_GUSOKU_SPEED;

        // �����L���O��ʂł̏���
        RankingFadeOut(pos);

        break;

        // ���J���X
    case CAfterimage::TYPE_RANK_CROW:

        // �e�N�X�`�����W���X�V
        SetAnimation(6, 3);

        // �E���獶��
        pos.x -= ENEMY_CROW_SPEED;

        // �����L���O��ʂł̏���
        RankingFadeOut(pos);

        break;

        // �Β�
    case CAfterimage::TYPE_RANK_GREEN:

        // �E���獶��
        pos.x -= ENEMY_GREEN_BIRD_GOD_SPEED;

        // �����L���O��ʂł̏���
        RankingFadeOut(pos);

        // �J�E���^���Z
        m_nCntTime++;

        // �J�E���^�ɂ���āA�G�t�F�N�g�𐶐�
        if (m_nCntTime % ENEMY_GREEN_BIRD_SET_EFFECT_COUNT == 0)
        {
            // �G�t�F�N�g�𐶐�(�T�C�Y�͈��菬����)
            CEffect::Create(pos + m_move, size - D3DXVECTOR3(-10.0f, -10.0f, 0.0f),
                EFFECT_YELLOW_FIRE_FIRST_COLOR, CEffect::TYPE_YELLOW_FIRE);
        }

        break;

        // ��
    case CAfterimage::TYPE_RANK_BLUE:

        // �E���獶��
        pos.x -= ENEMY_GREEN_BIRD_GOD_SPEED;

        // �����L���O��ʂł̏���
        RankingFadeOut(pos);

        // �J�E���^���Z
        m_nCntTime++;

        // �J�E���^�ɂ���āA�G�t�F�N�g�𐶐�
        if (m_nCntTime % ENEMY_GREEN_BIRD_SET_EFFECT_COUNT == 0)
        {
            // �G�t�F�N�g�𐶐�(�T�C�Y�͈��菬����)
            CEffect::Create(pos + m_move, size - D3DXVECTOR3(-10.0f, -10.0f, 0.0f),
                EFFECT_BLUE_FIRE_FIRST_COLOR, CEffect::TYPE_BLUE_FIRE);
        }

        break;

        // �Ԓ�
    case CAfterimage::TYPE_RANK_RED:

        // �E���獶��
        pos.x -= ENEMY_GREEN_BIRD_GOD_SPEED;

        // �����L���O��ʂł̏���
        RankingFadeOut(pos);

        // �J�E���^���Z
        m_nCntTime++;

        // �J�E���^�ɂ���āA�G�t�F�N�g�𐶐�
        if (m_nCntTime % ENEMY_GREEN_BIRD_SET_EFFECT_COUNT == 0)
        {
            // �G�t�F�N�g�𐶐�(�T�C�Y�͈��菬����)
            CEffect::Create(pos + m_move, size - D3DXVECTOR3(-10.0f, -10.0f, 0.0f),
                EFFECT_RED_FIRE_FIRST_COLOR, CEffect::TYPE_RED_FIRE);
        }

        break;
    }

    // �ʒu�𔽉f
    SetPosition(pos);

    // �T�C�Y�𔽉f
    SetSize(size);

    // �v���C���[�n�̎c���̂݁A��]����\��������
    if (m_type == TYPE_PLAYER || m_type == TYPE_PLAYER_DISP)
    {
        fAfterimageAngle = m_fAngle * (-1);   // -1�������邱�ƂŁA�p�x�����Z����قǍ��ɉ��悤��
        SetRotVertex(fAfterimageAngle);
    }
    else
    {
        // ���_���W��ύX
        SetVertex();
    }

    // �����Ȃ����
    if (m_col.a < 0)
    {
        Uninit(); // �����艺�ɃR�[�h�͏����Ȃ�
    }
}

//========================================
// �c���̕`�揈��
//========================================
void CAfterimage::Draw(void)
{
    // �`�揈��
    CScene2D::Draw();
}

//========================================
// �c���̉摜���[�h����
//========================================
HRESULT CAfterimage::Load(void)
{
    // �����_���[����f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player000.png", &m_apTexture[CAfterimage::TYPE_PLAYER]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player000.png", &m_apTexture[CAfterimage::TYPE_PLAYER_DISP]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/afterimage000.png", &m_apTexture[CAfterimage::TYPE_BOSS_FOREST]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy011.png", &m_apTexture[CAfterimage::TYPE_BOSS_DRAGON]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy015.png", &m_apTexture[CAfterimage::TYPE_BOSS_BLAZE]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/afterimage001.png", &m_apTexture[CAfterimage::TYPE_GOD_BIRD]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/magic.png", &m_apTexture[CAfterimage::TYPE_MAGIC]);

    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy007.png", &m_apTexture[CAfterimage::TYPE_RANK_GUSOKU]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy003.png", &m_apTexture[CAfterimage::TYPE_RANK_CROW]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/afterimage002.png", &m_apTexture[CAfterimage::TYPE_RANK_GREEN]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/afterimage003.png", &m_apTexture[CAfterimage::TYPE_RANK_BLUE]);
    D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/afterimage004.png", &m_apTexture[CAfterimage::TYPE_RANK_RED]);

    return S_OK;
}

//========================================
// �c���̉摜�j������
//========================================
void CAfterimage::Unload(void)
{
    // �e�N�X�`���̔j��
    for (int nCntTexture = 0; nCntTexture < CAfterimage::TYPE_MAX; nCntTexture++)
    {
        if (m_apTexture[nCntTexture] != NULL)
        {
            m_apTexture[nCntTexture]->Release();
            m_apTexture[nCntTexture] = NULL;
        }
    }
}

//================================
// �c���̍쐬
//================================
CAfterimage *CAfterimage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXCOLOR col, CAfterimage::TYPE type)
{
    CAfterimage *pAfterimage = NULL;

    // ���������m��
    pAfterimage = new CAfterimage;

    // �^�C�v�̂݁A�e�N�X�`�������蓖�Ă̂��߂Ɍ��т��Ă���
    pAfterimage->m_type = type;

    // ������
    pAfterimage->Init(pos, size);

    // �����o�ϐ������т���
    pAfterimage->m_col = col;
    pAfterimage->m_fAngle = fAngle;

    return pAfterimage;
}

//================================
// �����L���O��ʂŁA�����鏈��
//================================
void CAfterimage::RankingFadeOut(D3DXVECTOR3 pos)
{
    // ���ɗ��ꂫ������
    if (pos.x <= AFTERIMAGE_RANKING_FADE_OUT_POS_X)
    {
        // ������
        m_col.a = -1.0f;
    }
}
