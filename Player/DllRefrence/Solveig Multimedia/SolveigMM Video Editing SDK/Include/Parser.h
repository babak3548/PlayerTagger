#pragma once

#include <msxml.h>
#include <vector>
#include "propid_editingengine.h"
#define REFERENCE_TIME LONGLONG

#define MAX_CLIPS_IN_TASK	1000
#define MAX_TASKS			1000

enum ParserErrors
{
	PE_NO_ERRORS = 0,
	PE_GROUP_TRACK_OUT_NOT_EQUAL
};

class CParser
{
public:
	CParser(void);
	~CParser(void);
	static HRESULT	GetValueByName		( CString &value, CString name, IXMLDOMNode * node);
	static HRESULT	WriteString			( HANDLE hFile, CString szText);	
	static HRESULT	WriteUnicodeHeader	( HANDLE hFile);
	static CString	EncodeSourceFile	( CString szFileName);

	HRESULT		LoadXTLFile				( CString szFileName);
	HRESULT		GetGroupName			( int nGroup, CString &sName);
	HRESULT		GetTrimmerConfig		( int nGroup, int nTrack, DWORD &dwConfig );
	

	HRESULT		GetClipInfo				( int nGroup, int nTrack, int nClip, SMM_CLIP_INFO &ClipInfo);
	HRESULT		GetGroupsCount			( long * lCount);
	HRESULT		GroupToTask				( int nGroup, SMM_GROUP_TASK *pTack );
	
	HRESULT		GetTracksCount			( int nGroup, long &lTracksNum );
	HRESULT		GetClipsCount			( int nGroup, int nTrack, long &lCount);

	HRESULT		GetAudioStream			( int nGroup, int nTrack, int &nAudio);
	HRESULT		GetVideoStream			( int nGroup, int nTrack, int &nVideo);
	HRESULT		GetTrimmAccurType		( int nGroup, int nTrack, SMM_TrimmAccuracyType &nTrimmAccurType);
	HRESULT		GetMPEG2IdxFile			( int nGroup, int nTrack, CString &strFN );
	HRESULT		GetASInformation		( int nGroup, int nTrack, DWORD &dwMode, LONGLONG &llValue);

	HRESULT		GetTrackOutType			( int nGroup, int nTrack, SMM_OutputTypes &nOutType );
	HRESULT		GetGroupType			( int nGroup, SMM_TaskType & nGrType );
	HRESULT		GetGroupOutputType		(int nGroup, SMM_OutputTypes &nOutputType);


	void		FreeXTLFile				( void );
	HRESULT		WriteXTLFile			( CString szFileName, SMM_GROUP_TASK tasks[], int nTasks);

	static BOOL	IsValidXTLFile			( CString csFile );
	HRESULT		GetListOfInputOutputFiles( std::vector<CString> *csInFiles, std::vector<CString> *csOutFiles );
	ParserErrors GetLastError();
	
protected:		
	HRESULT		WriteGroupPart	( SMM_GROUP_TASK &group );
	HRESULT		WriteTrackPart	( SMM_TRACK_INFO &track );
	HRESULT		WriteClipPart	( SMM_CLIP_INFO &cpli	);
	CString		AddQuotes		( CString str);
	
	HANDLE		m_hFile;

private:
	void SetError(ParserErrors error);

	static CString	DecodeString		( CString szStr);
	LONGLONG		DecodeFileSize		( CString szData);
	SMM_OutputTypes	Str2FT				( CString strFT  );

	static CString ProcessMultiByteEncoding		( LPVOID pBuffer, DWORD dwSize);
	static CString ProcessUnicodeEncoding		( LPVOID pBuffer, DWORD dwSize);
	static CString EncodeUnicodeString			( CString szStr);

	static CString EncodeMultiByteString		( CString szStr);
	static CString PreEncodeMultiByteString		( LPBYTE pBuffer, DWORD dwSize);
	static CString DecodeChar					( LPBYTE pBuffer );

	void GetAbsPath( CString& sName );
	CComPtr<IXMLDOMDocument> spXTL;
	ParserErrors	m_error;
	CString			m_csFileName;
};
