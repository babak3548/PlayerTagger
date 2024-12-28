#pragma once
#include "DirectShowGraphBase.h"
#include <vector>
using namespace std;
enum OutType
{
	OT_MKV = 0,
	OT_MP4,
	OT_MOV
};
struct TrackData
{
	DWORD dwNumber;
	INT nEnabled;
	TrackData( DWORD _dwNumber )
	{
		dwNumber = _dwNumber;
		nEnabled = -1;
	}
};
class CDirectShowGraph:public CDirectShowGraphBase
{
public:
	CDirectShowGraph(void);
	~CDirectShowGraph(void);
	HRESULT Init(const CString& inputFile, const CString& outputFile, OutType outType);
	virtual HRESULT		Start	( void );
	virtual HRESULT		Cancel	( void );
	HRESULT GetState(FILTER_STATE& fs);
	bool isRunning();
	int GetStreamsCount();
	void GetStreamsMediaTypes(vector<CMediaType>& types/*output*/);

	bool GetStreamProps(int index, TRACK_PROPS& tp/*out*/);
	bool GetStreamPropsMP4(int index,  TRACK_PROPS& tp/*out*/);
	HRESULT SetStreamEnabled(int index, bool bEnabled);
	HRESULT SetStreamLanguage(int index,const CString& langEnglishName);
	HRESULT SetStreamName(int index, const CString& name);
	HRESULT SetStreamDefault(int index, bool bDefault);
	HRESULT SetStreamForced(int index, bool bForced);
	bool isInitialized();
	int GetProgress();
	HRESULT RestoreMuxerSettings();
	HRESULT SaveMuxerSettings();
	void ClearMuxerSettings();
	HRESULT	ShowMKVProps( HWND	hWnd );
	OutType GetOutType() {return m_OutputType;}
	void DisconnectMuxerPin(int nNum);
protected:
	virtual void Reset();
	virtual HRESULT QueryInterfaces();
private:
	HRESULT	CheckGraphEvents( void );

	// streams information on muxer input pins
	void FillStreamsInformation();
	vector<CMediaType> m_streamMediaTypes;
	// obligate filters
	CDirectShowFilter m_fMuxer;
	CDirectShowFilter m_ffileWriter;
	// muxer config
	CComPtr<IModuleConfig> m_pMuxConfig;
	// graph ifaces
	CComPtr<IMediaControl>	m_pMC;
	CComPtr<IMediaSeeking>	m_pMS;
	CComPtr<IMediaFilter>	m_pMF;
	CComPtr<IMediaEvent>    m_pMEx;

	OutType m_OutputType;
	bool bInited;
	vector<TRACK_PROPS> m_savedTrackProps;
};
