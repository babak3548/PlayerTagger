#pragma once


class CPlayer : public CGraphManager
{
public:
	CPlayer();
	~CPlayer();

	HRESULT		SetPosition 	( REFERENCE_TIME rtPos, REFERENCE_TIME rtEndPos = 0 );
	void		Reset			( void );
	HRESULT		Run				( void );
	HRESULT		Pause			( void );
	HRESULT		Stop			( void );
	HRESULT		RenderMediaFile	( CTBString szFileName, int * pnErr );
	CTBString	GetInput		( void );
	HRESULT		SetVolume		( long iVolume );
    HRESULT		AttachWindow	( CWnd * wnd, CWnd * frame, int iDefaultHeight );
    DWORD		GetAvgFrameTime ( void );
	HRESULT		BuildGraph		( int * pnErr );
	HRESULT		AddNullRenderer	( CPinWrapper pPinWrapper );
	
	REFERENCE_TIME GetCurrentPos( void );

private:
	CComPtr<IVideoWindow>	  m_pIVideoWindow;
	CComPtr<IBasicAudio>      m_pIBasicAudio;
	
	CTBString	m_InputFile;
    int			m_mashtabX;   
    int			m_mashtabY;   
};