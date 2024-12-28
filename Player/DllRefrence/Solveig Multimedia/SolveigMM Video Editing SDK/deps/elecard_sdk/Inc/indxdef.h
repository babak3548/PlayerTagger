
#ifndef _MEDIA_INDEX_DEF_H_
#define _MEDIA_INDEX_DEF_H_

//#include <initguid.h>

namespace MpegMIX
{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Index file header defenitions
	typedef struct 
	{
		const WCHAR*    cszCode;
		LPCTSTR		tcsDescription;
	} STREAM_TYPE_CODE;

	const STREAM_TYPE_CODE codeStreamTypeCodes[] = 
	{
		{L"MVOS", TEXT("Mpeg 1,2 Video Only Stream")},
		{L"M1SS", TEXT("Mpeg 1 System")},
		{L"M2PR", TEXT("Mpeg 2 Program")},
		{L"M2TR", TEXT("Mpeg 2 Transport")},
		{L"MPVA", TEXT("PVA with Mpeg payload")},
		{L"LIST", TEXT("Media Stream Sequence List")}
	};

    typedef struct 
	{
		CHAR    cszFileName[256];	// Path of indexed media-file. Example: "//Geek/Media/file.mpg"
		CHAR    codeStreamType[4];  // Code of stream type. See codeStreamTypeCodes;
		WORD	wFormatVersion;		// Version of index file format. 0x0100 for this version.
		WORD	wIndexes;			// Number of indexes contained in this file.
	} MIX_FILE_HEADER; // version 0x100

	// Index file header structure
	typedef struct 
	{        
        WORD	wFormatVersion;		// Version of index file format. 0x0100 for this version.
		WORD	wIndexes;			// Number of indexes contained in this file.
		WCHAR    cszFileName[256];	// Path of indexed media-file. Example: "//Geek/Media/file.mpg"
		WCHAR    codeStreamType[4];  // Code of stream type. See codeStreamTypeCodes;		        
	} MIX_FILE_HEADER_101; // version 0x101



	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Index header defenition

	// Flags
	typedef enum 
	{
		idProgram	= 0x1,
		idPID		= 0x2,
		idESID		= 0x4,
		idSubD		= 0x8
	} VALID_ID;

	// Code index type
	const LPCSTR codeIndexTypes[] = { "I\0\0\0", "IP\0\0", "IPB\0"};

	// Index Type Guids:
	// {E6EC4B79-3952-4bb5-8BE9-826D48A025C8}
	DEFINE_GUID(GUID_MIX_INDEX_ENTRY_1, 0xe6ec4b79, 0x3952, 0x4bb5, 0x8b, 0xe9, 0x82, 0x6d, 0x48, 0xa0, 0x25, 0xc8);
	// {E6EC4B9B-3952-4bb5-8BE9-826D48A025C8}
	DEFINE_GUID(GUID_MIX_INDEX_ENTRY_2, 0xe6ec4b9b, 0x3952, 0x4bb5, 0x8b, 0xe9, 0x82, 0x6d, 0x48, 0xa0, 0x25, 0xc8);
	// {E6EC4BDB-3952-4bb5-8BE9-826D48A025C8}
	DEFINE_GUID(GUID_MIX_DISCONTINUITY_ENTRY, 0xe6ec4bbd, 0x3952, 0x4bb5, 0x8b, 0xe9, 0x82, 0x6d, 0x48, 0xa0, 0x25, 0xc8);
	// {E6EC4BDF-3952-4bb5-8BE9-826D48A025C8}
	DEFINE_GUID(GUID_MIX_EVENT_INFO_ENTRY, 0xe6ec4bdf, 0x3952, 0x4bb5, 0x8b, 0xe9, 0x82, 0x6d, 0x48, 0xa0, 0x25, 0xc8);

	typedef struct 
	{
		WORD		wFormatVersion;		// Version of this structure. // 0x0100 for this version
		GUID		EntryStructGuid;	// GUID which specifies IndexEntry structure.
		CHAR		codeIndexType[4];	// Type of the index. Possible values are specified in codeIndexTypes.
		WORD		wIdFlags;			// Bitmask of valid stream IDs from following four fields. See VALID_ID enum.
		WORD		wProgramNum;		// Program number.
		WORD		wPID;				// PID (for transport stream);
		WORD		wStreamId;			// Elementary Stream ID. 
		WORD		wSubStreamId;		// Private SubStream ID. 
		DWORD		dwIndexEntries;		// Number of following index entries
	} MIX_INDEX_HEADER;

    typedef struct : public MIX_INDEX_HEADER
	{		
        DWORD       dwStreamTypeDataCount;
	} MIX_INDEX_HEADER_101;

    typedef enum 
	{
		stVideoMpeg1,
        stVideoMpeg2,
        stVideoH264_1,
        stVideoH264_2,
        stVideoMPEG4,
        stAudioMpeg,
        stAudioAC3,
        stAudioAAC,
        stAudioLPCM
	} E_MIX_STREAM_TYPE;

    typedef struct 
    {
        WORD wStreamType;
        DWORD dwStreamFormatDataCount;
    } MIX_INDEX_STREAM_INFO;    


	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Access Unit Index entry (full version - 32 bytes size)
	const LPCSTR codeAccessUnitTypes[] = { "I\0\0\0", "P\0\0\0", "B\0\0\0", "IDR\0"};
	typedef struct 
	{
		LONGLONG		rtTime;				// Relative time form begining of the media stream in 100ns units.
		DWORD			dwAccessUnitNum;	// Number of Access Unit
		CHAR			codeEntryType[4];	// Type of of access unit entry. 
		ULONGLONG		ullStartOffset;		// Access unit start offset.
											// If video only - Offset in file of picture header.
											// If multiplexed stream - offset in file of first pack or packet containing picture header.
	} MIX_INDEX_ENTRY_1;

	// Access Unit Index entry (shorter version - 20 bytes size)
	typedef struct 
	{
		LONGLONG		rtTime;				// Relative time form begining of the media stream in 100ns units.
		DWORD			dwAccessUnitNum;	// Number of Access Unit
		ULONGLONG		ullStartOffset;		// Access unit start offset.
											// If video only - Offset in file of picture header.
											// If multiplexed stream - offset in file of first pack or packet containing picture header.
	} MIX_INDEX_ENTRY_2;

	////////////////////////////////////////////////////////////////////////////////////////////// 
	// Discontinuty map index entry
	typedef struct 
	{
		LONGLONG		rtMediaTime;		// Original media time in 100ns units.
		LONGLONG		rtTime;				// Relative time form begining of the media stream in 100ns units.
	} MIX_DISCONTINUITY_ENTRY;

	////////////////////////////////////////////////////////////////////////////////////////////// 
	// Event Info entry
	typedef struct 
	{
		LONGLONG		rtTime;				// Relative time form begining of the media stream in 100ns units.
		WORD			nTypeNameLength;	// Length of cszTypeName field
		WORD			nNameLength;		// Length of cszName field
		WORD			nInfoLength;		// Length of cszInfo field
		LPCSTR			cszTypeName;		// Application defined type of event.
		LPCSTR			cszName;			// Application defined name of event.
		LPCSTR			cszInfo;			// Application defined event info.
	} MIX_EVENT_INFO_ENTRY;
};

#endif _MEDIA_INDEX_DEF_H_
