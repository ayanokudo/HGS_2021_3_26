//====================================================================
//
// �T�E���h���� (sound.h)
// Author : �㓡�T�V��
//
//====================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �N���X�錾
//================================================

// �T�E���h�̃N���X
class CSound
{
public:
    typedef enum
    {
        LABEL_BGM_TITLE = 0,	    // BGM �^�C�g��
        LABEL_BGM_GAME1,            // BGM �Q�[��1
        LABEL_BGM_BOSS1,            // BGM �{�X1
        LABEL_BGM_GAME2,            // BGM �Q�[��2
        LABEL_BGM_BOSS2,            // BGM �{�X2
        LABEL_BGM_GAME3,            // BGM �Q�[��3
        LABEL_BGM_BOSS3,            // BGM �{�X3
        LABEL_BGM_RESULT,           // BGM ���U���g
        LABEL_SE_DECISION,          // SE ���艹
        LABEL_SE_SHOT_FIRE,         // SE ���̃V���b�g��
        LABEL_SE_SHOT_WATER,        // SE ���̃V���b�g��
        LABEL_SE_SHOT_LIGHT1,       // SE ���̃V���b�g��1
        LABEL_SE_SHOT_LIGHT2,       // SE ���̃V���b�g��2
        LABEL_SE_HIT,               // SE �q�b�g��
        LABEL_SE_EXPLOSION,         // SE ������
        LABEL_SE_ITEM,              // SE �A�C�e����
        LABEL_SE_WARNING,           // SE �x����
        LABEL_SE_SELECT,            // SE �I����
        LABEL_SE_PAUSE,             // SE �|�[�Y��
        LABEL_MAX,
    } LABEL;
    CSound();
    ~CSound();  // �e�N���X�̃f�X�g���N�^��virtual�����邱�ƂŁA���������[�N��}����
    HRESULT Init(HWND hWnd);
    void Uninit(void);
    HRESULT Play(LABEL label);
    void Stop(LABEL label);
    void StopAll(void);

private:
    typedef struct
    {
        char *pFilename;	// �t�@�C����
        int nCntLoop;		// ���[�v�J�E���g (-1�Ń��[�v�A0�Ń��[�v�Ȃ�)
    }PARAM;
    HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

    IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
    IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
    IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
    BYTE *m_apDataAudio[LABEL_MAX];					    // �I�[�f�B�I�f�[�^
    DWORD m_aSizeAudio[LABEL_MAX];					    // �I�[�f�B�I�f�[�^�T�C�Y
    static PARAM m_aParam[LABEL_MAX];                   // �e���f�ނ̃p�����[�^
};

#endif