
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
////////////////////////////////////////////////////////////////////////////////
//  author:     Konstantin Kohanenko (mail-to: Kohanenko@elecard.net.ru)
////////////////////////////////////////////////////////////////////////////////

#ifndef __Elecard_XMuxer_Utils_XMuxUtils_h_
#define __Elecard_XMuxer_Utils_XMuxUtils_h_
#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// structure type
#define START_CODE_MUX				0x00006E77
#define START_CODE_DEMUX			0x00006E78
#define START_CODE_REMUX			0x00006E79
#define START_CODE_TRIM				0x00006E7A
#define START_CODE_FILTERS_INFO		0x00006E7B
//
//// trim configurations
//#define TM_LOOK_AT_SAMPLE_TIME		0x00000002
//#define TM_ASF_OUT_FORMAT			0x00000004
//#define TM_ONLY_VIDEO				0x00000008
//#define TM_ONLY_AUDIO				0x00000010
//#define TM_GET_SIZE					0x00000020
//#define TM_INPUTFILE_ASF			0x00000040
//#define TM_ACTIVE_MODE				0x00000080

#include <list>
using namespace std;

#pragma warning(disable:4267 4244)



namespace XMuxerUtils
{

typedef std::basic_string<TCHAR>	CTBString;
// Known input structure start codes
typedef enum _tagTEStartCode
{
	scode_Multiplex			= 0x6E77,
	scode_Demultiplex		= 0x6E78,
	scode_Remultiplex		= 0x6E79

} TEStartCode;

// Output stream type
typedef enum _tagTEStreamType
{
	stype_Program_None		= 0,		// MPEG-2 Program Stream
	stype_Program_SVCD		= 1,		// MPEG-2 Program Stream SVCD Compliant
	stype_Program_DVD		= 2,		// MPEG-2 Program Stream DVD Compliant
	stype_Transport			= 3,		// MPEG-2 Transport Stream
	stype_MP4				= 4,		// MP4 Stream 
	stype_MP4_ISMA			= 5,		// MP4 Stream ISMA Compatible
	stype_MP4_Sony_PSP		= 6,		// MP4 Stream Sony PSP Compatible
	stype_MP4_iPod			= 7,		// MP4 Stream iPod Compatible

} TEStreamType;

// Trim Accuracy
typedef enum _tagTETrimType
{
	ttype_accuracy_GOP		= 0,		// Without trans-coding 
	ttype_accuracy_Frame	= 1,		// Trans-coding part of pieces 
	ttype_accuracy_FrameEx	= 2			// Trans-coding all of pieces 

} TETrimType;

// Elecard MPEG Demultiplexer seeking methods
typedef enum _tagTESeekingMethods
{
	smethod_using_PTS		= 0,
	smethod_using_Bitrate	= 1

} TESeekingMethods;

// Trim parameters
typedef struct _tagTSTrimInfo
{
	INT16		nPieceNum;				// Piece number in general sequences
	LONGLONG	llStartPos;				// Time offset of start trim position
	LONGLONG	llStopPos;				// Time offset of stop trim position

	operator int () const {
		return nPieceNum;
	}

} TSTrimInfo;

typedef list<TSTrimInfo> TLTrimInfo;
typedef list<TSTrimInfo>::iterator TLITrimInfo;

// Pin parameters
typedef struct _tagTSInputPinInfo
{
	// Input 
	DWORD	    dwInStreamID;				
    DWORD	    dwInStreamSubID;			
    DWORD	    dwInStreamPID;			
	// Output
	DWORD		dwOutProgramID;
    DWORD       dwOutProgramNum;        
    DWORD       dwOutStreamID;          
	DWORD		dwOutStreamPESID;
	LONG		lInitTimeShift;

    operator DWORD () const {
        return dwOutProgramNum;
    }

} TSInputPinInfo;

typedef std::list<TSInputPinInfo> TLInputPinInfo;
typedef std::list<TSInputPinInfo>::iterator TLIInputPinInfo;

typedef struct _tagTSOutputPinInfo
{
    DWORD	    dwOutStreamID;			// Elementary Stream ID
    DWORD	    dwOutStreamSubID;		// Private SubStream ID
    DWORD	    dwOutStreamPID;			// PID (for transport stream)
    
    CTBString   sOutFileName;           // Output file name

} TSOutputPinInfo;

typedef std::list<TSOutputPinInfo> TLOutputPinInfo;
typedef std::list<TSOutputPinInfo>::iterator TLIOutputPinInfo;

typedef struct _tagTSMuxFileInfo
{
    CTBString	sFileName;				// Input file name
    
	// Output
	DWORD		dwOutProgramID;
	DWORD       dwOutProgramNum;        
	DWORD       dwOutStreamID;          
	DWORD		dwOutStreamPESID;
	LONG		lInitTimeShift;

    operator DWORD () const {
        return dwOutProgramNum;
    }

} TSMuxFileInfo;

typedef list<TSMuxFileInfo> TLMuxFileInfo;
typedef list<TSMuxFileInfo>::iterator TLIMuxFileInfo;	

typedef list<CTBString> TLFileName;
typedef list<CTBString>::iterator TLIFileName;	

typedef enum 
{
	seeking_Using_PTS = 0,
	seeking_Using_bitrate
} SeekingMethods;

typedef struct 
{
	TLTrimInfo			TrimList;		// list of trim positions
	DWORD				TrimMode;		// trim configurations

} TRIM_PARAM;

//////////////////////////////
//////////////////////////////
//////////////////////////////
//////////////////////////////

//////////////////////////////////////////////////////////////////////////
//

// Remux Mode parameters
typedef struct _tagTSRemuxParam
{
	BOOL				bTrim;				// Trim or cut mode
	TLFileName			FileList;			// List of input files name
    TLInputPinInfo      InPinsInfo;			// List of input pins info
    TLTrimInfo			TrimInfo;			// List of trim positions
	CTBString			sOutFileName;  		// Output file name
	TETrimType			TrimType;			// Trim type
	TESeekingMethods	SeekMethod;			// Demultiplexer seeking method
	TEStreamType		StreamType;			// Output stream type
	// use only if StreamType=stype_Transport
	DWORD				dwOutTransportID;	// Output Transport Stream ID
	LONG				lRequiredBitrate;	// Output bitrate, 0-VBR, other-CBR 
	LONG				lPCRInterval;				
	BOOL				bUsePadding;
} TSRemuxParam;

// Demux Mode parameters
typedef struct _tagTSDemuxParam 
{
	BOOL				bTrim;				// Trim or cut mode
	TLFileName			FileList;			// List of input files name
    TLOutputPinInfo     OutPinsInfo;		// List of output pins info
    TLTrimInfo			TrimInfo;			// List of trim positions
	TETrimType			TrimType;			// Trim type
	TESeekingMethods	SeekMethod;			// Demultiplexer seeking method
	TEStreamType		StreamType;			// Output stream type
} TSDemuxParam;

// Mux Mode parameters
typedef struct _tagTSMuxParam
{	
    TLMuxFileInfo       MuxFileInfo;		// Information about input files
	CTBString			sOutFileName;  		// Output file name
	TEStreamType		StreamType;			// Output stream type
	// use only if StreamType=stype_Transport
	DWORD				dwOutTransportID;	// Output Transport Stream ID
	LONG				lRequiredBitrate;	// Output bitrate, 0-VBR, other-CBR 
	LONG				lPCRInterval;				
	BOOL				bUsePadding;
} TSMuxParam;

//////////////////////////////////////////////////////////////////////////
//
class CBitsStructManager
{
	public:

		CBitsStructManager() {};
		~CBitsStructManager() {};

		HRESULT		GetStartCode(PBYTE pData, LONG lSize, TEStartCode& nCode);
		LONG		CalculateSize(TEStartCode nCode, PVOID pStruct);	
	
		HRESULT		BitDataToStruct(PBYTE pData, LONG lSize, PVOID pStruct);
		HRESULT		StructToBitData(TEStartCode nCode, PVOID pStruct, PBYTE pData, LONG lSize);
};

//////////////////////////////////////////////////////////////////////////
//
class CBitsBuffer  
{	
	public:

		typedef enum _tagTEOperationMode
		{
			mode_Unknown	= 0,
			mode_Read		= 1,
			mode_Write		= 2,				

		} TEOperationMode;

		CBitsBuffer();
		~CBitsBuffer();

		void			SetMode(TEOperationMode mode);
		
		// Information methods
		BYTE*			GetBuffer()			const { return m_pBuffer;	};
		UINT64			GetBufferSize()		const { return m_nSize;		};
		UINT64			GetReadBitsCount()	const { return m_nBitsRead; };
		UINT64			GetWriteBitsCount() const { return m_nBitsWrite;};

		// Initialization methods
		HRESULT			SetBufferSize(const UINT32 nBytesCount);
		HRESULT			SetBuffer(const PBYTE pBuffer, const UINT32 nBytesCount);
		
		// Writing methods		
		HRESULT			WriteBit(const BOOL nValue);	
		HRESULT			Write8Bits(const UINT8 nValue);
		HRESULT			Write16Bits(const UINT16 nValue);
		HRESULT			Write32Bits(const UINT32 nValue);	
		HRESULT			Write64Bits(const UINT64 nValue);	
		HRESULT			WriteString(const CTBString sString, const UINT32 nBytesCount);
		HRESULT			WriteBits(UINT32 nBitsCount, UINT32 nValue);		

		// Reading methods
		HRESULT			Read8Bits(INT8 &nValue);		
		HRESULT			Read16Bits(INT16 &nValue);
		HRESULT			Read32Bits(INT32 &nValue);		
		HRESULT			Read64Bits(INT64 &nValue);
		HRESULT			ReadString(CTBString &sString, const UINT32 nBytesCount);
		HRESULT			ReadBits(INT32 &nValue, const UINT32 nBitsCount);

	private:
		void			ResetAllParameters();
		HRESULT			WriteByte();

	private:
		///////////////////////////////////////////
		// Class members
		BYTE			*m_pBuffer;		
		BYTE			m_nCurrByte;		

		UINT8			m_nBit;
		UINT64			m_nSize;
		UINT64			m_nBitsRead;
		UINT64			m_nBitsWrite;

		TEOperationMode	m_CurMode;
};
//Added
typedef struct 
{
	CTBString	szFilterName;		// necessary filter name
	BYTE		nState;				// was the filter registered
	CTBString	szFilterVersion;	// filter version

} NECESSARY_FILTER_INFO;

typedef list<NECESSARY_FILTER_INFO> TLFilterInfo;
typedef list<NECESSARY_FILTER_INFO>::iterator TLIFilterInfo;

}
//
//typedef struct __tagTSTrimInfo
//{
//	INT16		nPieceNum;				// Piece number in general sequences
//	LONGLONG	llStartPos;				// Time offset of start trim position
//	LONGLONG	llStopPos;				// Time offset of stop trim position
//
//	operator int () const {
//		return nPieceNum;
//	}
//
//} __TSTrimInfo;
//
//struct TrimInfoList
//{
//	UINT nListSize;
//	__TSTrimInfo * trim_list;
//};

#endif // __Elecard_XMuxer_Utils_XMuxUtils_h_
