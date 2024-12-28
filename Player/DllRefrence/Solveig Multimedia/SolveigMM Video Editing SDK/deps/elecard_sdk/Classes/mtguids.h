
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

#ifndef __MEDIA_TYPE_GUIDS__
#define __MEDIA_TYPE_GUIDS__

///////////////////////////////////////////////
//				MP4 TYPES UIDS
///////////////////////////////////////////////

// {93C6E675-EBA1-476C-BFAA-545C7F691CAC}
DEFINE_GUID(MEDIATYPE_3GP,
			0x93C6E675, 0xEBA1, 0x476C, 0xbf, 0xaa, 0x54, 0x5c, 0x7f, 0x69, 0x1c, 0xac);

// {7634706D-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_mp4v,
			0x7634706d, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// {7634704D-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_MP4V,
			0x5634504d, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// {A963763D-B0A4-4f81-A296-C43199C389B4}
DEFINE_GUID(MEDIASUBTYPE_DIVX, 
			0xa963763d, 0xb0a4, 0x4f81, 0xa2, 0x96, 0xc4, 0x31, 0x99, 0xc3, 0x89, 0xb4);

// {33564944-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_Div3,
			0x33564944, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);

// {58564944-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_Div4,
			0x58564944, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);

// {78766964-0000-0010-8000-00AA00389B71}
DEFINE_GUID(CLSID_DivX, 
			0x78766964, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

///////////////////////////////////////////////
//				H263 TYPES UIDS
///////////////////////////////////////////////

// {33363268-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_h263, 
			0x33363268, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
// {33363248-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_H263, 
			0x33363248, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

///////////////////////////////////////////////
//				H264 TYPES UIDS
///////////////////////////////////////////////

// {8D2D71CB-243F-45E3-B2D8-5FD7967EC09B}
DEFINE_GUID(MEDIASUBTYPE_h264, 
			0x8d2d71cb, 0x243f, 0x45e3, 0xb2, 0xd8, 0x5f, 0xd7, 0x96, 0x7e, 0xc0, 0x9b);
// {31435641-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_H264_NERO,
			0x31435641, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
DEFINE_GUID(CLSID_H264_QT_NALU, 
			0x31637661, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
// fourcc vssh
DEFINE_GUID(CLSID_H264_VIDEO_SOFT, 
			0x48535356, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
// fourcc h264
DEFINE_GUID(CLSID_H264_FCC_H264, 
			0x34363248, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);

///////////////////////////////////////////////
//				DV100 TYPES UIDS
///////////////////////////////////////////////

DEFINE_GUID(MEDIASUBTYPE_DV100_720P,
			0x31645641, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);


///////////////////////////////////////////////
//				SOUND TYPES UIDS
///////////////////////////////////////////////

// AAC
// Be compatible with 3ivx
#define WAVE_FORMAT_AAC 0x00FF

////////////////////////////////////////////////////////////
// MS registered aac wave formats
#define WAVE_FORMAT_MC_MPEG2AAC		0x0180 // Fraunhofer
#define WAVE_FORMAT_MC_AAC			0xA106 // ISO/MPEG-4 advanced audio Coding
#define WAVE_FORMAT_LATMAAC			0x01FF // LATM

// MP3
#define WAVE_FORMAT_MP3				0x0050

// Be compatible with ffdshow
#define WAVE_FORMAT_AMR				0x7A21



// {000000FF-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_AAC,
			WAVE_FORMAT_AAC, 0x000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
// tempory MC defined 
// {00000180-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_AAC_MPEG2,
			WAVE_FORMAT_MC_MPEG2AAC, 0x000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// {000001FF-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_LATMAAC,
			WAVE_FORMAT_LATMAAC, 0x000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// tempory MC defined 
// {0000A106-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_AAC_MPEG4,
			WAVE_FORMAT_MC_AAC, 0x000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// {00000055-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_MP3,
			0x00000055, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// {4134504D-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_AAC_NERO,
			0x4134504D, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);

// {99C00BDC-3BF1-4889-9873-F1178D3C5679}
DEFINE_GUID(MEDIASUBTYPE_AMR, 
			0x99c00bdc, 0x3bf1, 0x4889, 0x98, 0x73, 0xf1, 0x17, 0x8d, 0x3c, 0x56, 0x79);


// {CA9A0EDC-38B0-4FA6-B34A-3019543A0C57}
DEFINE_GUID(MEDIASUBTYPE_AMR_MPEGABLE,
			0xca9a0edc, 0x38b0, 0x4fa6, 0xb3, 0x4a, 0x30, 0x19, 0x54, 0x3a, 0x0c, 0x57);

// {000000FE-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_AMR_FFDSHOW,
			0x000000fe, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// {4134504D-0000-0010-8000-00AA00389B71}
DEFINE_GUID(MEDIASUBTYPE_AMR_NERO,
			0x4134504D, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

#endif // __MEDIA_TYPE_GUIDS__