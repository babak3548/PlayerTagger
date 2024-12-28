
/////////////////////////////////////////////////////////////////////////////////
//
//	   Copyright (c) 2005 Elecard Ltd.
//	   All rights are reserved.  Reproduction in whole or in part is prohibited
//	   without the written consent of the copyright owner.
//
//	   Elecard Ltd. reserves the right to make changes without
//	   notice at any time. Elecard Ltd. makes no warranty, expressed,
//	   implied or statutory, including but not limited to any implied
//	   warranty of merchantability of fitness for any particular purpose,
//	   or that the use will not infringe any third party patent, copyright
//	   or trademark.
//
//	   Elecard Ltd. must not be liable for any loss or damage arising
//	   from its use.
//
/////////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_STREAMINFO_H__31E551FC_DBE6_49A4_8E4C_A43D3CF64175__INCLUDED_)
#define AFX_STREAMINFO_H__31E551FC_DBE6_49A4_8E4C_A43D3CF64175__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Elements.h"

enum stream_Type
{
	stream_type_Unknown = 0,
	stream_type_Video,
	stream_type_Audio
};

enum stream_Format
{
	format_Unknown = 0,

	format_Auto,
	format_PAL,
	format_NTSC,
	format_SECAM,
	
	format_video_MPEG1,
	format_video_MPEG2,
	format_video_MPEG4,
	format_video_H264,
	format_video_H263,
	format_video_DV,
	format_video_DIVX,
	format_video_DIVX3,
	format_video_DIVX4,
	format_video_DIVX5,
	format_video_XVID,
	format_video_MJPG,

	format_subtitles,
	
	format_audio_AC3,
	format_audio_LPCM,
	format_audio_MP3,
	format_audio_AAC,
	format_audio_MPEG1,
	format_audio_MPEG2,
	format_audio_MPEG25,
	format_audio_AMR,
	format_audio_LATMAAC
};

enum CHANNEL
{
	CHANNEL_Unknow	= 0,
	CHANNEL_AC3_1_1_Dual,
	CHANNEL_AC3_1_1_Dual_LFE,
	CHANNEL_AC3_1_0_Center,
	CHANNEL_AC3_1_0_Center_LFE,
	CHANNEL_AC3_2_0_Stereo,
	CHANNEL_AC3_2_0_Stereo_LFE,
	CHANNEL_AC3_3_0_Front,
	CHANNEL_AC3_3_0_Front_LFE,
	CHANNEL_AC3_2_1_Surround,
	CHANNEL_AC3_2_1_Surround_LFE,
	CHANNEL_AC3_3_1_Surround,
	CHANNEL_AC3_3_1_Surround_LFE,
	CHANNEL_AC3_2_2_Quadro,
	CHANNEL_AC3_2_2_Quadro_LFE,
	CHANNEL_AC3_3_2_5Channels,
	CHANNEL_AC3_3_2_5Channels_LFE,
	CHANNEL_MPEG_SingleChannel,
	CHANNEL_MPEG_DualChannel,		
	CHANNEL_MPEG_JointStereo,
	CHANNEL_MPEG_Stereo		
};

enum audio_Mode
{
	MODE_Unknow = 0,
	MODE_MPEG_Layer1,
	MODE_MPEG_Layer2,
	MODE_MPEG_Layer3,
	MODE_AAC_Main,
	MODE_AAC_LC,
	MODE_AAC_SSR,
	MODE_AAC_LTP,
	MODE_AAC_Scalable,
	MODE_AAC_TwinVQ,
	MODE_AAC_CELP,
	MODE_AAC_HVXC,
	MODE_AAC_TTSI,
	MODE_AAC_Main_Synthetic,
	MODE_AAC_Wavetable_Synthesis,
	MODE_AAC_General_MIDI,
	MODE_AAC_Algorithmic_Syntesis_and_Audio_FX,
	MODE_AAC_ER_LC,
	MODE_AAC_ER_LTP,
	MODE_AAC_ER_Scalable,
	MODE_AAC_ER_TwinEQ,
	MODE_AAC_ER_BSAC,
	MODE_AAC_ER_LD,
	MODE_AAC_ER_HVXC,
	MODE_AAC_ER_CELP,
	MODE_AAC_ER_HILN,
	MODE_AAC_ER_Parametric
};

typedef struct _tagTSVideo_addition
{
	DWORD		dwProfile;
	DWORD		dwLevel;
	DWORD		dwInterlace;

} TSVideo_addition;

typedef struct _tagTSAudio_addition
{
	DWORD		dwMode;
	DWORD		dwChannelConfig;
	DWORD		dwBitStreamID;
	DWORD		dwQuantization;
	DWORD		dwNumberChannel;
	DWORD		dwBitrateMode;

} TSAudio_addition;

typedef struct _tagTSAudio_base
{
	DWORD				dwFormatTag;
	DWORD				dwBitPerSample;
	DWORD				dwAvgBitPerSec;
	DWORD				dwSampleRate;
	DWORD				dwBlockAlign;
	DWORD				dwChannels;
	
	DWORD				cbSize;
	TSAudio_addition	dwAddition;

} TSAudio_base;

typedef struct _tagTSVideo_base
{
	DWORD				dwSizeX;
	DWORD				dwSizeY;
	DWORD				dwAspectX;
	DWORD				dwAspectY;
	DWORD				dwBitRate;
	DWORD				dwFrameRate;

	DWORD				cbSize;
	TSVideo_addition	dwAddition;

} TSVideo_base;

class CStreamInfo  
{
public:	

	CStreamInfo();
	CStreamInfo(CPinWrapper& pin);
	CStreamInfo(const CStreamInfo& info);
	virtual ~CStreamInfo();

	HRESULT			GetCopy(const CStreamInfo& info);

	HRESULT			SetInfoPin(CPinWrapper& pin);

	long			GetType() const			{ return m_type;	}
	long			GetStreamFormat() const	{ return m_format;	}
	CPinWrapper&	GetInfoPin()			{ return m_Pin;		}
	
	HRESULT			InfoPin(CPinWrapper& pin) const
	{
		if(m_Pin.Valid())
			pin = m_Pin;
		else
			return E_FAIL;
		return S_OK;
	}

	virtual HRESULT	GetInfo(void** pData, DWORD& dwLen) const;
	virtual HRESULT	UpdateInfo();
	virtual HRESULT	UpdateInfoByFilter(IBaseFilter* pConfig);

	void			SetMainFlag(BOOL bSet = TRUE) {	m_bMain = bSet; }
	BOOL			IsMain() const	{ return m_bMain;	}

	void			Reset();
	BOOL			Valid() const;

protected:

	CPinWrapper		m_Pin;
	
	long			m_type;
	long			m_format;

	BOOL			m_bMain;

	TSVideo_base	m_VData;
	TSAudio_base	m_AData;

	BOOL			m_bInit;
	DWORD			m_dwLen;

	virtual HRESULT		SetVideoInfoByFormat(GUID format, LPBYTE pbFormat, TSVideo_base& video);
	virtual void		ResetData();
};

#endif // !defined(AFX_STREAMINFO_H__31E551FC_DBE6_49A4_8E4C_A43D3CF64175__INCLUDED_)
