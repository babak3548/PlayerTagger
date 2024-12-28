
class CRegWork
{
public:
	CRegWork();
	~CRegWork();
		
	DWORD   GetNextNumber();
	HRESULT SetNextNumber();

	DWORD   GetComputerID();
	HRESULT SetComputerID(DWORD dwCompId);

	CString GetOutPath();
	HRESULT SetOutPath(TCHAR * szPath);

	DWORD	GetDateHash();

	DWORD   GetStep();
	HRESULT SetStep(DWORD dwStep);

	DWORD	GetVolume();
	HRESULT SetVolume(DWORD dwVolume);

	HRESULT CheckKeys(bool * bChanged);

	BOOL	IsExtended();
	HRESULT SetExtended(BOOL bExt);

	BOOL	IsLookAtSamplesTimes();
	HRESULT SetLookAtSamplesTimes(BOOL bLook);

private:
	CString GetExecuteble();

	HKEY m_RootKey;
	CString m_szLookAtSamplesTimes;
	CString m_szResult_path;
	CString m_szComputerID;
	CString m_szExtended; 
	CString m_szVolume;
	CString m_szNextID;
	CString m_szDate;
	CString m_szStep;
};
