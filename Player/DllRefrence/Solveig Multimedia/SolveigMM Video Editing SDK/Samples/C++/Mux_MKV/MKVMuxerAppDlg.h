
// MKVMuxerAppDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DirectShowGraph.h"

#include <vector>
#include <map>
using namespace std;
// CMKVMuxerAppDlg dialog

class CMKVMuxerAppDlg : public CDialog
{
// Construction
public:
	typedef map<int, CMediaType> STREAMNUM_MEDIATYPE;
	typedef pair<int, CMediaType> STREAMNUM_MEDIATYPEPAIR;
	typedef map<int, CMediaType>::iterator STREAMNUM_MEDIATYPE_IT;

	CMKVMuxerAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MKVMUXERAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	
	void OnStart();
	void OnStop();
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	afx_msg void OnBnClickedStartButton();
	afx_msg void OnBnClickedInputfileButton();
	afx_msg void OnBnClickedOutputfileButton();
	
	afx_msg void OnCbnSelchangeAudioStreamCombo();
	afx_msg void OnCbnSelchangeSubtitleStreamCombo();
	afx_msg void OnCbnSelchangeVideoStreamCombo();
	
	afx_msg void OnCbnSelchangeComboVideoLang();
	afx_msg void OnCbnSelchangeComboAudioLang();
	afx_msg void OnCbnSelchangeComboSubtitleLang();
	afx_msg void OnCbnSelchangeComboOutType();

	afx_msg void OnBnClickedVideoenableCheck();
	afx_msg void OnBnClickedAudioenableCheck();
	afx_msg void OnBnClickedSubtitleenableCheck();
	
	afx_msg void OnEnChangeEditVideoTrackName();
	afx_msg void OnEnChangeEditAudioTrackName();
	afx_msg void OnEnChangeEditSubtitleTrackName();

	afx_msg void OnBnClickedCheckVideoFlagdefault();
	afx_msg void OnBnClickedCheckAudioFlagdefault();
	afx_msg void OnBnClickedCheckSubtitleFlagdefault();

	afx_msg void OnBnClickedCheckVideoFlagforced();
	afx_msg void OnBnClickedCheckAudioFlagforced();
	afx_msg void OnBnClickedCheckSubtitleFlagforced();

	afx_msg void OnBnClickedButtonAdvanced();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy( void );
	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;
private:
	void TermporaryDisableControls(const vector<HWND>& skipControls);
	void RestoreTermporaryDisabledControls();
	HRESULT ReBuildGraph( OutType outType );
	void UpdateStreamsInformation();
	void updateSelStreamProps();
	void updateSelStreamProps(CComboBox& streamCombo, 
							  CButton& streamEnableButton,
							  CButton& streamDefaultButton,
							  CButton& streamForcedButton,
							  CEdit& streamNameEdit,
							  CComboBox& streamLangCombo);
	void updateStartButtonState();
	void setCurSelStreamEnabled(CComboBox& streamCombo, CButton& streamEnableButton);
	void setCurSelStreamLanguage(CComboBox& streamCombo, CComboBox& langCombo);
	void setCurSelStreamName(CComboBox& streamCombo, CEdit& nameEdit);
	void setCurSelStreamDefault(CComboBox& streamCombo, CButton& streamDefaultButton);
	void setCurSelStreamForced(CComboBox& streamCombo, CButton& streamForcedButton);
	void FillStreamsCombo(CComboBox& combo, STREAMNUM_MEDIATYPE& streams);

	void EnableVideoGroupBox(bool bEnable);
	void EnableAudioGroupBox(bool bEnable);
	void EnableSubtitlesGroupBox(bool bEnable);

	CString GetFormatNameBySubType(const GUID& subtype);
	bool fileExists(const CString& fileName);
	CString GetPathFromPathName(const CString& filePathName);


	void FreeItemData( CComboBox& combo );
	void DisconnectOddPins( CComboBox& streams );

	CEdit m_InputFileEdit;
	CEdit m_OutputFileEdit;

	CStatic m_videoGroupBox;
	CStatic m_audioGroupBox;
	CStatic m_subtitlesGroupBox;

	CComboBox m_videoStreams;
	CComboBox m_audioStreams;
	CComboBox m_subtitleStreams;
	CComboBox m_outputType;
	// enable flags
	CButton m_videoEnableCheck;
	CButton m_audioEnableCheck;
	CButton m_subtitleEnableCheck;
	//default flags
	CButton m_videoDefaultCheck;
	CButton m_audioDefaultCheck;
	CButton m_subtitleDefaultCheck;
	//forced flags
	CButton m_videoForcedCheck;
	CButton m_audioForcedCheck;
	CButton m_subtitleForcedCheck;
	// track name
	CEdit m_videoNameEdit;
	CEdit m_audioNameEdit;
	CEdit m_subtitleNameEdit;
	// track lang combo
	CComboBox m_videoLangCombo;
	CComboBox m_audioLangCombo;
	CComboBox m_subtitleLangCombo;

	CProgressCtrl m_progress;
	CDirectShowGraph m_DSGraph;	

	CButton m_startBtn;	
	CButton m_advancedOptionsBtn;
	typedef pair<HWND, bool> HWND_ENABLE_PAIR;
	typedef map<HWND, bool>::iterator OLD_STATE_ITER;
	map<HWND, bool> m_tempDisabledControls;//hwnd + oldstate
};



//Windows Media Guids

static const GUID WMMEDIASUBTYPE_WMV1 =
{0x31564D57, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}};

static const GUID WMMEDIASUBTYPE_WMV2 =
{0x32564D57, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}};

static const GUID WMMEDIASUBTYPE_WMV3 =
{0x33564D57, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}};

static const GUID WMMEDIASUBTYPE_WMAudioV7 =
{0x00000161, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}};

static const GUID WMMEDIASUBTYPE_WMAudioV8 =
{0x00000161, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}};

static const GUID WMMEDIASUBTYPE_WMAudioV9 =
{0x00000162, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}};

static const GUID WMMEDIASUBTYPE_WMSP1 =
{0x0000000A, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}};

typedef struct 
{
  GUID guid;
  TCHAR *szFormat;
} MediaFormat;

const  MediaFormat  g_pVF[] = 
{
	{ MEDIASUBTYPE_MPEG2_VIDEO, _T("MPEG-2 Video")},
	{ MEDIASUBTYPE_H264_ANNEXB,_T("H.264 Video")},
	{ MEDIASUBTYPE_H264_2,_T("H.264 Video")},
	{ MEDIASUBTYPE_H264_3,_T("H.264 Video")},
	{ MEDIASUBTYPE_H264_4,_T("H.264 Video")},
	{ MEDIASUBTYPE_MPEG4,_T("MPEG-4 Video")},
	{ MEDIASUBTYPE_dvsd,_T("DV Video")},
	{ MEDIASUBTYPE_DIVX,_T("DivX Video")},
	{ MEDIASUBTYPE_DIVX_2, _T("DivX Video")},
	{ MEDIASUBTYPE_DIVX_3,_T( "DivX Video")},
	{ MEDIASUBTYPE_XVID,_T("XVid Video")},
	{ MEDIASUBTYPE_RGB8,_T("RGB 8") }, 
	{ MEDIASUBTYPE_RGB555,_T("RGB 555") }, 
	{ MEDIASUBTYPE_RGB565,_T("RGB 565") }, 
	{ MEDIASUBTYPE_RGB24,_T("RGB 24") }, 
	{ MEDIASUBTYPE_RGB32,_T("RGB 32") },
	{ MEDIASUBTYPE_YUY2,_T("YUY2") },
	{ MEDIASUBTYPE_UYVY,_T("UYVY") },
	{ MEDIASUBTYPE_YUYV,_T("YUYV") },
	{ WMMEDIASUBTYPE_WMV1,_T("Windows Media Video v7") },
	{ WMMEDIASUBTYPE_WMV2,_T("Windows Media Video v8") },
	{ WMMEDIASUBTYPE_WMV3,_T("Windows Media Video v9") }

};

const	 MediaFormat		g_pAF[] =
{
	{ MEDIASUBTYPE_PCM,_T("PCM") },
	{ MEDIASUBTYPE_MPEG1Packet, _T("MPEG-1 Audio") },
	{ MEDIASUBTYPE_MPEG1Payload, _T("MPEG-1 Audio") },
	{ MEDIASUBTYPE_MPEG2_AUDIO , _T("MPEG-2 Audio") },
	{ MEDIASUBTYPE_DVD_LPCM_AUDIO,_T("DVD Audio")},
	{ MEDIASUBTYPE_DOLBY_AC3 ,_T("Dolby AC3 Audio")},
	{ MEDIASUBTYPE_AC3 ,_T("AC3 Audio")},
	{ MEDIASUBTYPE_AAC ,_T("AAC Audio")},
	{ MEDIASUBTYPE_MP3,_T("MP3 Audio (MPEG-1)")},
	{ MEDIASUBTYPE_VOXWARE_AUDIO,_T("Voxware Audio")},
	{ WMMEDIASUBTYPE_WMAudioV7,_T("Windows Media Audio")},
	{ WMMEDIASUBTYPE_WMAudioV8,_T("Windows Media Audio")},
	{ WMMEDIASUBTYPE_WMAudioV9,_T("Windows Media Audio v9")},
	{ WMMEDIASUBTYPE_WMSP1,_T("Windows Media Audio")}
};
#define lang_iso_count 566
static char* lang_iso[lang_iso_count][5]={
{"Abkhazian","Abkhazian","abkhaze","abk","ab",},
{"Achinese","Achinese","aceh","ace","",},
{"Acoli","Acoli","acoli","ach","",},
{"Adangme","Adangme","adangme","ada","",},
{"Adygei","Adyghe; Adygei","adygh�","ady","",},
{"Adyghe","Adyghe; Adygei","adygh�","ady","",},
{"Afar","Afar","afar","aar","aa",},
{"Afrihili","Afrihili","afrihili","afh","",},
{"Afrikaans","Afrikaans","afrikaans","afr","af",},
{"Afro-Asiatic languages","Afro-Asiatic languages","afro-asiatiques, langues","afa","",},
{"Ainu","Ainu","a�nou","ain","",},
{"Akan","Akan","akan","aka","ak",},
{"Akkadian","Akkadian","akkadien","akk","",},
{"Albanian","Albanian","albanais","alb/sqi","sq",},
{"Alemannic","Swiss German; Alemannic; Alsatian","suisse al�manique; al�manique; alsacien","gsw","",},
{"Aleut","Aleut","al�oute","ale","",},
{"Algonquian languages","Algonquian languages","algonquines, langues","alg","",},
{"Alsatian","Swiss German; Alemannic; Alsatian","suisse al�manique; al�manique; alsacien","gsw","",},
{"Altaic languages","Altaic languages","alta�ques, langues","tut","",},
{"Amharic","Amharic","amharique","amh","am",},
{"Angika","Angika","angika","anp","",},
{"Apache languages","Apache languages","apaches, langues","apa","",},
{"Arabic","Arabic","arabe","ara","ar",},
{"Aragonese","Aragonese","aragonais","arg","an",},
{"Arapaho","Arapaho","arapaho","arp","",},
{"Arawak","Arawak","arawak","arw","",},
{"Armenian","Armenian","arm�nien","arm/hye","hy",},
{"Aromanian","Aromanian; Arumanian; Macedo-Romanian","aroumain; mac�do-roumain","rup","",},
{"Artificial languages","Artificial languages","artificielles, langues","art","",},
{"Arumanian","Aromanian; Arumanian; Macedo-Romanian","aroumain; mac�do-roumain","rup","",},
{"Assamese","Assamese","assamais","asm","as",},
{"Asturian","Asturian; Bable; Leonese; Asturleonese","asturien; bable; l�onais; asturol�onais","ast","",},
{"Asturleonese","Asturian; Bable; Leonese; Asturleonese","asturien; bable; l�onais; asturol�onais","ast","",},
{"Athapascan languages","Athapascan languages","athapascanes, langues","ath","",},
{"Australian languages","Australian languages","australiennes, langues","aus","",},
{"Austronesian languages","Austronesian languages","austron�siennes, langues","map","",},
{"Avaric","Avaric","avar","ava","av",},
{"Avestan","Avestan","avestique","ave","ae",},
{"Awadhi","Awadhi","awadhi","awa","",},
{"Aymara","Aymara","aymara","aym","ay",},
{"Azerbaijani","Azerbaijani","az�ri","aze","az",},
{"Bable","Asturian; Bable; Leonese; Asturleonese","asturien; bable; l�onais; asturol�onais","ast","",},
{"Balinese","Balinese","balinais","ban","",},
{"Baltic languages","Baltic languages","baltes, langues","bat","",},
{"Baluchi","Baluchi","baloutchi","bal","",},
{"Bambara","Bambara","bambara","bam","bm",},
{"Bamileke languages","Bamileke languages","bamil�k�, langues","bai","",},
{"Banda languages","Banda languages","banda, langues","bad","",},
{"Bantu languages","Bantu languages","bantou, langues","bnt","",},
{"Basa","Basa","basa","bas","",},
{"Bashkir","Bashkir","bachkir","bak","ba",},
{"Basque","Basque","basque","baq/eus","eu",},
{"Batak languages","Batak languages","batak, langues","btk","",},
{"Bedawiyet","Beja; Bedawiyet","bedja","bej","",},
{"Beja","Beja; Bedawiyet","bedja","bej","",},
{"Belarusian","Belarusian","bi�lorusse","bel","be",},
{"Bemba","Bemba","bemba","bem","",},
{"Bengali","Bengali","bengali","ben","bn",},
{"Berber languages","Berber languages","berb�res, langues","ber","",},
{"Bhojpuri","Bhojpuri","bhojpuri","bho","",},
{"Bihari languages","Bihari languages","langues biharis","bih","bh",},
{"Bikol","Bikol","bikol","bik","",},
{"Bilin","Blin; Bilin","blin; bilen","byn","",},
{"Bini","Bini; Edo","bini; edo","bin","",},
{"Bislama","Bislama","bichlamar","bis","bi",},
{"Blin","Blin; Bilin","blin; bilen","byn","",},
{"Bliss","Blissymbols; Blissymbolics; Bliss","symboles Bliss; Bliss","zbl","",},
{"Blissymbolics","Blissymbols; Blissymbolics; Bliss","symboles Bliss; Bliss","zbl","",},
{"Blissymbols","Blissymbols; Blissymbolics; Bliss","symboles Bliss; Bliss","zbl","",},
{"Bokm�l, Norwegian","Bokm�l, Norwegian; Norwegian Bokm�l","norv�gien bokm�l","nob","nb",},
{"Bosnian","Bosnian","bosniaque","bos","bs",},
{"Braj","Braj","braj","bra","",},
{"Breton","Breton","breton","bre","br",},
{"Buginese","Buginese","bugi","bug","",},
{"Bulgarian","Bulgarian","bulgare","bul","bg",},
{"Buriat","Buriat","bouriate","bua","",},
{"Burmese","Burmese","birman","bur/mya","my",},
{"Caddo","Caddo","caddo","cad","",},
{"Castilian","Spanish; Castilian","espagnol; castillan","spa","es",},
{"Catalan","Catalan; Valencian","catalan; valencien","cat","ca",},
{"Caucasian languages","Caucasian languages","caucasiennes, langues","cau","",},
{"Cebuano","Cebuano","cebuano","ceb","",},
{"Celtic languages","Celtic languages","celtiques, langues; celtes, langues","cel","",},
{"Central American Indian languages","Central American Indian languages","am�rindiennes de l'Am�rique centrale,  langues","cai","",},
{"Central Khmer","Central Khmer","khmer central","khm","km",},
{"Chagatai","Chagatai","djaghata�","chg","",},
{"Chamic languages","Chamic languages","chames, langues","cmc","",},
{"Chamorro","Chamorro","chamorro","cha","ch",},
{"Chechen","Chechen","tch�tch�ne","che","ce",},
{"Cherokee","Cherokee","cherokee","chr","",},
{"Chewa","Chichewa; Chewa; Nyanja","chichewa; chewa; nyanja","nya","ny",},
{"Cheyenne","Cheyenne","cheyenne","chy","",},
{"Chibcha","Chibcha","chibcha","chb","",},
{"Chichewa","Chichewa; Chewa; Nyanja","chichewa; chewa; nyanja","nya","ny",},
{"Chinese","Chinese","chinois","chi/zho","zh",},
{"Chinook jargon","Chinook jargon","chinook, jargon","chn","",},
{"Chipewyan","Chipewyan; Dene Suline","chipewyan","chp","",},
{"Choctaw","Choctaw","choctaw","cho","",},
{"Chuang","Zhuang; Chuang","zhuang; chuang","zha","za",},
{"Church Slavic","Church Slavic; Old Slavonic; Church Slavonic; Old Bulgarian; Old Church Slavonic","slavon d'�glise; vieux slave; slavon liturgique; vieux bulgare","chu","cu",},
{"Church Slavonic","Church Slavic; Old Slavonic; Church Slavonic; Old Bulgarian; Old Church Slavonic","slavon d'�glise; vieux slave; slavon liturgique; vieux bulgare","chu","cu",},
{"Chuukese","Chuukese","chuuk","chk","",},
{"Chuvash","Chuvash","tchouvache","chv","cv",},
{"Classical Nepal Bhasa","Classical Newari; Old Newari; Classical Nepal Bhasa","newari classique","nwc","",},
{"Classical Newari","Classical Newari; Old Newari; Classical Nepal Bhasa","newari classique","nwc","",},
{"Classical Syriac","Classical Syriac","syriaque classique","syc","",},
{"Cook Islands Maori","Rarotongan; Cook Islands Maori","rarotonga; maori des �les Cook","rar","",},
{"Coptic","Coptic","copte","cop","",},
{"Cornish","Cornish","cornique","cor","kw",},
{"Corsican","Corsican","corse","cos","co",},
{"Cree","Cree","cree","cre","cr",},
{"Creek","Creek","muskogee","mus","",},
{"Creoles and pidgins","Creoles and pidgins","cr�oles et pidgins","crp","",},
{"Creoles and pidgins, English based","Creoles and pidgins, English based","cr�oles et pidgins bas�s sur l'anglais","cpe","",},
{"Creoles and pidgins, French-based","Creoles and pidgins, French-based","cr�oles et pidgins bas�s sur le fran�ais","cpf","",},
{"Creoles and pidgins, Portuguese-based","Creoles and pidgins, Portuguese-based","cr�oles et pidgins bas�s sur le portugais","cpp","",},
{"Crimean Tatar","Crimean Tatar; Crimean Turkish","tatar de Crim�","crh","",},
{"Crimean Turkish","Crimean Tatar; Crimean Turkish","tatar de Crim�","crh","",},
{"Croatian","Croatian","croate","hrv","hr",},
{"Cushitic languages","Cushitic languages","couchitiques,  langues","cus","",},
{"Czech","Czech","tch�que","cze/ces","cs",},
{"Dakota","Dakota","dakota","dak","",},
{"Danish","Danish","danois","dan","da",},
{"Dargwa","Dargwa","dargwa","dar","",},
{"Delaware","Delaware","delaware","del","",},
{"Dene Suline","Chipewyan; Dene Suline","chipewyan","chp","",},
{"Dhivehi","Divehi; Dhivehi; Maldivian","maldivien","div","dv",},
{"Dimili","Zaza; Dimili; Dimli; Kirdki; Kirmanjki; Zazaki","zaza; dimili; dimli; kirdki; kirmanjki; zazaki","zza","",},
{"Dimli","Zaza; Dimili; Dimli; Kirdki; Kirmanjki; Zazaki","zaza; dimili; dimli; kirdki; kirmanjki; zazaki","zza","",},
{"Dinka","Dinka","dinka","din","",},
{"Divehi","Divehi; Dhivehi; Maldivian","maldivien","div","dv",},
{"Dogri","Dogri","dogri","doi","",},
{"Dogrib","Dogrib","dogrib","dgr","",},
{"Dravidian languages","Dravidian languages","dravidiennes,  langues","dra","",},
{"Duala","Duala","douala","dua","",},
{"Dutch","Dutch; Flemish","n�erlandais; flamand","dut/nld","nl",},
{"Dutch, Middle (ca.1050-1350)","Dutch, Middle (ca.1050-1350)","n�erlandais moyen (ca. 1050-1350)","dum","",},
{"Dyula","Dyula","dioula","dyu","",},
{"Dzongkha","Dzongkha","dzongkha","dzo","dz",},
{"Eastern Frisian","Eastern Frisian","frison oriental","frs","",},
{"Edo","Bini; Edo","bini; edo","bin","",},
{"Efik","Efik","efik","efi","",},
{"Egyptian (Ancient)","Egyptian (Ancient)","�gyptien","egy","",},
{"Ekajuk","Ekajuk","ekajuk","eka","",},
{"Elamite","Elamite","�lamite","elx","",},
{"English","English","anglais","eng","en",},
{"English, Middle (1100-1500)","English, Middle (1100-1500)","anglais moyen (1100-1500)","enm","",},
{"English, Old (ca.450-1100)","English, Old (ca.450-1100)","anglo-saxon (ca.450-1100)","ang","",},
{"Erzya","Erzya","erza","myv","",},
{"Esperanto","Esperanto","esp�ranto","epo","eo",},
{"Estonian","Estonian","estonien","est","et",},
{"Ewe","Ewe","�w�","ewe","ee",},
{"Ewondo","Ewondo","�wondo","ewo","",},
{"Fang","Fang","fang","fan","",},
{"Fanti","Fanti","fanti","fat","",},
{"Faroese","Faroese","f�ro�en","fao","fo",},
{"Fijian","Fijian","fidjien","fij","fj",},
{"Filipino","Filipino; Pilipino","filipino; pilipino","fil","",},
{"Finnish","Finnish","finnois","fin","fi",},
{"Finno-Ugrian languages","Finno-Ugrian languages","finno-ougriennes,  langues","fiu","",},
{"Flemish","Dutch; Flemish","n�erlandais; flamand","dut/nld","nl",},
{"Fon","Fon","fon","fon","",},
{"French","French","fran�ais","fre","fr",},
{"French","French","fran�ais","fra","fr",},
{"French, Middle (ca.1400-1600)","French, Middle (ca.1400-1600)","fran�ais moyen (1400-1600)","frm","",},
{"French, Old (842-ca.1400)","French, Old (842-ca.1400)","fran�ais ancien (842-ca.1400)","fro","",},
{"Friulian","Friulian","frioulan","fur","",},
{"Fulah","Fulah","peul","ful","ff",},
{"Ga","Ga","ga","gaa","",},
{"Gaelic","Gaelic; Scottish Gaelic","ga�lique; ga�lique �cossais","gla","gd",},
{"Galibi Carib","Galibi Carib","karib; galibi; carib","car","",},
{"Galician","Galician","galicien","glg","gl",},
{"Ganda","Ganda","ganda","lug","lg",},
{"Gayo","Gayo","gayo","gay","",},
{"Gbaya","Gbaya","gbaya","gba","",},
{"Geez","Geez","gu�ze","gez","",},
{"Georgian","Georgian","g�orgien","geo/kat","ka",},
{"German","German","allemand","ger","de",},
{"German","German","allemand","deu","de",},
{"German, Low","Low German; Low Saxon; German, Low; Saxon, Low","bas allemand; bas saxon; allemand, bas; saxon, bas","nds","",},
{"German, Middle High (ca.1050-1500)","German, Middle High (ca.1050-1500)","allemand, moyen haut (ca. 1050-1500)","gmh","",},
{"German, Old High (ca.750-1050)","German, Old High (ca.750-1050)","allemand, vieux haut (ca. 750-1050)","goh","",},
{"Germanic languages","Germanic languages","germaniques, langues","gem","",},
{"Gikuyu","Kikuyu; Gikuyu","kikuyu","kik","ki",},
{"Gilbertese","Gilbertese","kiribati","gil","",},
{"Gondi","Gondi","gond","gon","",},
{"Gorontalo","Gorontalo","gorontalo","gor","",},
{"Gothic","Gothic","gothique","got","",},
{"Grebo","Grebo","grebo","grb","",},
{"Greek, Ancient (to 1453)","Greek, Ancient (to 1453)","grec ancien (jusqu'� 1453)","grc","",},
{"Greek, Modern (1453-)","Greek, Modern (1453-)","grec moderne (apr�s 1453)","gre/ell","el",},
{"Greenlandic","Kalaallisut; Greenlandic","groenlandais","kal","kl",},
{"Guarani","Guarani","guarani","grn","gn",},
{"Gujarati","Gujarati","goudjrati","guj","gu",},
{"Gwich'in","Gwich'in","gwich'in","gwi","",},
{"Haida","Haida","haida","hai","",},
{"Haitian","Haitian; Haitian Creole","ha�tien; cr�ole ha�tien","hat","ht",},
{"Haitian Creole","Haitian; Haitian Creole","ha�tien; cr�ole ha�tien","hat","ht",},
{"Hausa","Hausa","haoussa","hau","ha",},
{"Hawaiian","Hawaiian","hawa�en","haw","",},
{"Hebrew","Hebrew","h�breu","heb","he",},
{"Herero","Herero","herero","her","hz",},
{"Hiligaynon","Hiligaynon","hiligaynon","hil","",},
{"Himachali languages","Himachali languages; Western Pahari languages","langues himachalis; langues paharis occidentales","him","",},
{"Hindi","Hindi","hindi","hin","hi",},
{"Hiri Motu","Hiri Motu","hiri motu","hmo","ho",},
{"Hittite","Hittite","hittite","hit","",},
{"Hmong","Hmong; Mong","hmong","hmn","",},
{"Hungarian","Hungarian","hongrois","hun","hu",},
{"Hupa","Hupa","hupa","hup","",},
{"Iban","Iban","iban","iba","",},
{"Icelandic","Icelandic","islandais","ice/isl","is",},
{"Ido","Ido","ido","ido","io",},
{"Igbo","Igbo","igbo","ibo","ig",},
{"Ijo languages","Ijo languages","ijo, langues","ijo","",},
{"Iloko","Iloko","ilocano","ilo","",},
{"Imperial Aramaic (700-300 BCE)","Official Aramaic (700-300 BCE); Imperial Aramaic (700-300 BCE)","aram�en d'empire (700-300 BCE)","arc","",},
{"Inari Sami","Inari Sami","sami d'Inari","smn","",},
{"Indic languages","Indic languages","indo-aryennes, langues","inc","",},
{"Indo-European languages","Indo-European languages","indo-europ�ennes, langues","ine","",},
{"Indonesian","Indonesian","indon�sien","ind","id",},
{"Ingush","Ingush","ingouche","inh","",},
{"Interlingua (International Auxiliary Language Association)","Interlingua (International Auxiliary Language Association)","interlingua (langue auxiliaire internationale)","ina","ia",},
{"Interlingue","Interlingue; Occidental","interlingue","ile","ie",},
{"Inuktitut","Inuktitut","inuktitut","iku","iu",},
{"Inupiaq","Inupiaq","inupiaq","ipk","ik",},
{"Iranian languages","Iranian languages","iraniennes, langues","ira","",},
{"Irish","Irish","irlandais","gle","ga",},
{"Irish, Middle (900-1200)","Irish, Middle (900-1200)","irlandais moyen (900-1200)","mga","",},
{"Irish, Old (to 900)","Irish, Old (to 900)","irlandais ancien (jusqu'� 900)","sga","",},
{"Iroquoian languages","Iroquoian languages","iroquoises, langues","iro","",},
{"Italian","Italian","italien","ita","it",},
{"Japanese","Japanese","japonais","jpn","ja",},
{"Javanese","Javanese","javanais","jav","jv",},
{"Jingpho","Kachin; Jingpho","kachin; jingpho","kac","",},
{"Judeo-Arabic","Judeo-Arabic","jud�o-arabe","jrb","",},
{"Judeo-Persian","Judeo-Persian","jud�o-persan","jpr","",},
{"Kabardian","Kabardian","kabardien","kbd","",},
{"Kabyle","Kabyle","kabyle","kab","",},
{"Kachin","Kachin; Jingpho","kachin; jingpho","kac","",},
{"Kalaallisut","Kalaallisut; Greenlandic","groenlandais","kal","kl",},
{"Kalmyk","Kalmyk; Oirat","kalmouk; o�rat","xal","",},
{"Kamba","Kamba","kamba","kam","",},
{"Kannada","Kannada","kannada","kan","kn",},
{"Kanuri","Kanuri","kanouri","kau","kr",},
{"Kapampangan","Pampanga; Kapampangan","pampangan","pam","",},
{"Kara-Kalpak","Kara-Kalpak","karakalpak","kaa","",},
{"Karachay-Balkar","Karachay-Balkar","karatchai balkar","krc","",},
{"Karelian","Karelian","car�lien","krl","",},
{"Karen languages","Karen languages","karen, langues","kar","",},
{"Kashmiri","Kashmiri","kashmiri","kas","ks",},
{"Kashubian","Kashubian","kachoube","csb","",},
{"Kawi","Kawi","kawi","kaw","",},
{"Kazakh","Kazakh","kazakh","kaz","kk",},
{"Khasi","Khasi","khasi","kha","",},
{"Khoisan languages","Khoisan languages","kho�san, langues","khi","",},
{"Khotanese","Khotanese; Sakan","khotanais; sakan","kho","",},
{"Kikuyu","Kikuyu; Gikuyu","kikuyu","kik","ki",},
{"Kimbundu","Kimbundu","kimbundu","kmb","",},
{"Kinyarwanda","Kinyarwanda","rwanda","kin","rw",},
{"Kirdki","Zaza; Dimili; Dimli; Kirdki; Kirmanjki; Zazaki","zaza; dimili; dimli; kirdki; kirmanjki; zazaki","zza","",},
{"Kirghiz","Kirghiz; Kyrgyz","kirghiz","kir","ky",},
{"Kirmanjki","Zaza; Dimili; Dimli; Kirdki; Kirmanjki; Zazaki","zaza; dimili; dimli; kirdki; kirmanjki; zazaki","zza","",},
{"Klingon","Klingon; tlhIngan-Hol","klingon","tlh","",},
{"Komi","Komi","kom","kom","kv",},
{"Kongo","Kongo","kongo","kon","kg",},
{"Konkani","Konkani","konkani","kok","",},
{"Korean","Korean","cor�en","kor","ko",},
{"Kosraean","Kosraean","kosrae","kos","",},
{"Kpelle","Kpelle","kpell�","kpe","",},
{"Kru languages","Kru languages","krou, langues","kro","",},
{"Kuanyama","Kuanyama; Kwanyama","kuanyama; kwanyama","kua","kj",},
{"Kumyk","Kumyk","koumyk","kum","",},
{"Kurdish","Kurdish","kurde","kur","ku",},
{"Kurukh","Kurukh","kurukh","kru","",},
{"Kutenai","Kutenai","kutenai","kut","",},
{"Kwanyama","Kuanyama; Kwanyama","kuanyama; kwanyama","kua","kj",},
{"Kyrgyz","Kirghiz; Kyrgyz","kirghiz","kir","ky",},
{"Ladino","Ladino","jud�o-espagnol","lad","",},
{"Lahnda","Lahnda","lahnda","lah","",},
{"Lamba","Lamba","lamba","lam","",},
{"Land Dayak languages","Land Dayak languages","dayak, langues","day","",},
{"Lao","Lao","lao","lao","lo",},
{"Latin","Latin","latin","lat","la",},
{"Latvian","Latvian","letton","lav","lv",},
{"Leonese","Asturian; Bable; Leonese; Asturleonese","asturien; bable; l�onais; asturol�onais","ast","",},
{"Letzeburgesch","Luxembourgish; Letzeburgesch","luxembourgeois","ltz","lb",},
{"Lezghian","Lezghian","lezghien","lez","",},
{"Limburgan","Limburgan; Limburger; Limburgish","limbourgeois","lim","li",},
{"Limburger","Limburgan; Limburger; Limburgish","limbourgeois","lim","li",},
{"Limburgish","Limburgan; Limburger; Limburgish","limbourgeois","lim","li",},
{"Lingala","Lingala","lingala","lin","ln",},
{"Lithuanian","Lithuanian","lituanien","lit","lt",},
{"Lojban","Lojban","lojban","jbo","",},
{"Low German","Low German; Low Saxon; German, Low; Saxon, Low","bas allemand; bas saxon; allemand, bas; saxon, bas","nds","",},
{"Low Saxon","Low German; Low Saxon; German, Low; Saxon, Low","bas allemand; bas saxon; allemand, bas; saxon, bas","nds","",},
{"Lower Sorbian","Lower Sorbian","bas-sorabe","dsb","",},
{"Lozi","Lozi","lozi","loz","",},
{"Luba-Katanga","Luba-Katanga","luba-katanga","lub","lu",},
{"Luba-Lulua","Luba-Lulua","luba-lulua","lua","",},
{"Luiseno","Luiseno","luiseno","lui","",},
{"Lule Sami","Lule Sami","sami de Lule","smj","",},
{"Lunda","Lunda","lunda","lun","",},
{"Luo (Kenya and Tanzania)","Luo (Kenya and Tanzania)","luo (Kenya et Tanzanie)","luo","",},
{"Lushai","Lushai","lushai","lus","",},
{"Luxembourgish","Luxembourgish; Letzeburgesch","luxembourgeois","ltz","lb",},
{"Macedo-Romanian","Aromanian; Arumanian; Macedo-Romanian","aroumain; mac�do-roumain","rup","",},
{"Macedonian","Macedonian","mac�donien","mac/mkd","mk",},
{"Madurese","Madurese","madourais","mad","",},
{"Magahi","Magahi","magahi","mag","",},
{"Maithili","Maithili","maithili","mai","",},
{"Makasar","Makasar","makassar","mak","",},
{"Malagasy","Malagasy","malgache","mlg","mg",},
{"Malay","Malay","malais","may/msa","ms",},
{"Malayalam","Malayalam","malayalam","mal","ml",},
{"Maldivian","Divehi; Dhivehi; Maldivian","maldivien","div","dv",},
{"Maltese","Maltese","maltais","mlt","mt",},
{"Manchu","Manchu","mandchou","mnc","",},
{"Mandar","Mandar","mandar","mdr","",},
{"Mandingo","Mandingo","mandingue","man","",},
{"Manipuri","Manipuri","manipuri","mni","",},
{"Manobo languages","Manobo languages","manobo, langues","mno","",},
{"Manx","Manx","manx; mannois","glv","gv",},
{"Maori","Maori","maori","mao/mri","mi",},
{"Mapuche","Mapudungun; Mapuche","mapudungun; mapuche; mapuce","arn","",},
{"Mapudungun","Mapudungun; Mapuche","mapudungun; mapuche; mapuce","arn","",},
{"Marathi","Marathi","marathe","mar","mr",},
{"Mari","Mari","mari","chm","",},
{"Marshallese","Marshallese","marshall","mah","mh",},
{"Marwari","Marwari","marvari","mwr","",},
{"Masai","Masai","massa�","mas","",},
{"Mayan languages","Mayan languages","maya, langues","myn","",},
{"Mende","Mende","mend�","men","",},
{"Mi'kmaq","Mi'kmaq; Micmac","mi'kmaq; micmac","mic","",},
{"Micmac","Mi'kmaq; Micmac","mi'kmaq; micmac","mic","",},
{"Minangkabau","Minangkabau","minangkabau","min","",},
{"Mirandese","Mirandese","mirandais","mwl","",},
{"Mohawk","Mohawk","mohawk","moh","",},
{"Moksha","Moksha","moksa","mdf","",},
{"Moldavian","Romanian; Moldavian; Moldovan","roumain; moldave","rum/ron","ro",},
{"Moldovan","Romanian; Moldavian; Moldovan","roumain; moldave","rum/ron","ro",},
{"Mon-Khmer languages","Mon-Khmer languages","m�n-khmer, langues","mkh","",},
{"Mong","Hmong; Mong","hmong","hmn","",},
{"Mongo","Mongo","mongo","lol","",},
{"Mongolian","Mongolian","mongol","mon","mn",},
{"Mossi","Mossi","mor�","mos","",},
{"Multiple languages","Multiple languages","multilingue","mul","",},
{"Munda languages","Munda languages","mounda, langues","mun","",},
{"N'Ko","N'Ko","n'ko","nqo","",},
{"Nahuatl languages","Nahuatl languages","nahuatl, langues","nah","",},
{"Nauru","Nauru","nauruan","nau","na",},
{"Navaho","Navajo; Navaho","navaho","nav","nv",},
{"Navajo","Navajo; Navaho","navaho","nav","nv",},
{"Ndebele, North","Ndebele, North; North Ndebele","nd�b�l� du Nord","nde","nd",},
{"Ndebele, South","Ndebele, South; South Ndebele","nd�b�l� du Sud","nbl","nr",},
{"Ndonga","Ndonga","ndonga","ndo","ng",},
{"Neapolitan","Neapolitan","napolitain","nap","",},
{"Nepal Bhasa","Nepal Bhasa; Newari","nepal bhasa; newari","new","",},
{"Nepali","Nepali","n�palais","nep","ne",},
{"Newari","Nepal Bhasa; Newari","nepal bhasa; newari","new","",},
{"Nias","Nias","nias","nia","",},
{"Niger-Kordofanian languages","Niger-Kordofanian languages","nig�ro-kordofaniennes, langues","nic","",},
{"Nilo-Saharan languages","Nilo-Saharan languages","nilo-sahariennes, langues","ssa","",},
{"Niuean","Niuean","niu�","niu","",},
{"No linguistic content","No linguistic content; Not applicable","pas de contenu linguistique; non applicable","zxx","",},
{"Nogai","Nogai","noga�; nogay","nog","",},
{"Norse, Old","Norse, Old","norrois, vieux","non","",},
{"North American Indian languages","North American Indian languages","nord-am�rindiennes, langues","nai","",},
{"North Ndebele","Ndebele, North; North Ndebele","nd�b�l� du Nord","nde","nd",},
{"Northern Frisian","Northern Frisian","frison septentrional","frr","",},
{"Northern Sami","Northern Sami","sami du Nord","sme","se",},
{"Northern Sotho","Pedi; Sepedi; Northern Sotho","pedi; sepedi; sotho du Nord","nso","",},
{"Norwegian","Norwegian","norv�gien","nor","no",},
{"Norwegian Bokm�l","Bokm�l, Norwegian; Norwegian Bokm�l","norv�gien bokm�l","nob","nb",},
{"Norwegian Nynorsk","Norwegian Nynorsk; Nynorsk, Norwegian","norv�gien nynorsk; nynorsk, norv�gien","nno","nn",},
{"Not applicable","No linguistic content; Not applicable","pas de contenu linguistique; non applicable","zxx","",},
{"Nubian languages","Nubian languages","nubiennes, langues","nub","",},
{"Nuosu","Sichuan Yi; Nuosu","yi de Sichuan","iii","ii",},
{"Nyamwezi","Nyamwezi","nyamwezi","nym","",},
{"Nyanja","Chichewa; Chewa; Nyanja","chichewa; chewa; nyanja","nya","ny",},
{"Nyankole","Nyankole","nyankol�","nyn","",},
{"Nynorsk, Norwegian","Norwegian Nynorsk; Nynorsk, Norwegian","norv�gien nynorsk; nynorsk, norv�gien","nno","nn",},
{"Nyoro","Nyoro","nyoro","nyo","",},
{"Nzima","Nzima","nzema","nzi","",},
{"Occidental","Interlingue; Occidental","interlingue","ile","ie",},
{"Occitan (post 1500)","Occitan (post 1500)","occitan (apr�s 1500)","oci","oc",},
{"Occitan, Old (to 1500)","Proven�al, Old (to 1500);Occitan, Old (to 1500)","proven�al ancien (jusqu'� 1500); occitan ancien (jusqu'� 1500)","pro","",},
{"Official Aramaic (700-300 BCE)","Official Aramaic (700-300 BCE); Imperial Aramaic (700-300 BCE)","aram�en d'empire (700-300 BCE)","arc","",},
{"Oirat","Kalmyk; Oirat","kalmouk; o�rat","xal","",},
{"Ojibwa","Ojibwa","ojibwa","oji","oj",},
{"Old Bulgarian","Church Slavic; Old Slavonic; Church Slavonic; Old Bulgarian; Old Church Slavonic","slavon d'�glise; vieux slave; slavon liturgique; vieux bulgare","chu","cu",},
{"Old Church Slavonic","Church Slavic; Old Slavonic; Church Slavonic; Old Bulgarian; Old Church Slavonic","slavon d'�glise; vieux slave; slavon liturgique; vieux bulgare","chu","cu",},
{"Old Newari","Classical Newari; Old Newari; Classical Nepal Bhasa","newari classique","nwc","",},
{"Old Slavonic","Church Slavic; Old Slavonic; Church Slavonic; Old Bulgarian; Old Church Slavonic","slavon d'�glise; vieux slave; slavon liturgique; vieux bulgare","chu","cu",},
{"Oriya","Oriya","oriya","ori","or",},
{"Oromo","Oromo","galla","orm","om",},
{"Osage","Osage","osage","osa","",},
{"Ossetian","Ossetian; Ossetic","oss�te","oss","os",},
{"Ossetic","Ossetian; Ossetic","oss�te","oss","os",},
{"Otomian languages","Otomian languages","otomi, langues","oto","",},
{"Pahlavi","Pahlavi","pahlavi","pal","",},
{"Palauan","Palauan","palau","pau","",},
{"Pali","Pali","pali","pli","pi",},
{"Pampanga","Pampanga; Kapampangan","pampangan","pam","",},
{"Pangasinan","Pangasinan","pangasinan","pag","",},
{"Panjabi","Panjabi; Punjabi","pendjabi","pan","pa",},
{"Papiamento","Papiamento","papiamento","pap","",},
{"Papuan languages","Papuan languages","papoues, langues","paa","",},
{"Pashto","Pushto; Pashto","pachto","pus","ps",},
{"Pedi","Pedi; Sepedi; Northern Sotho","pedi; sepedi; sotho du Nord","nso","",},
{"Persian","Persian","persan","per/fas","fa",},
{"Persian, Old (ca.600-400 B.C.)","Persian, Old (ca.600-400 B.C.)","perse, vieux (ca. 600-400 av. J.-C.)","peo","",},
{"Philippine languages","Philippine languages","philippines, langues","phi","",},
{"Phoenician","Phoenician","ph�nicien","phn","",},
{"Pilipino","Filipino; Pilipino","filipino; pilipino","fil","",},
{"Pohnpeian","Pohnpeian","pohnpei","pon","",},
{"Polish","Polish","polonais","pol","pl",},
{"Portuguese","Portuguese","portugais","por","pt",},
{"Prakrit languages","Prakrit languages","pr�krit, langues","pra","",},
{"Proven�al, Old (to 1500)","Proven�al, Old (to 1500);Occitan, Old (to 1500)","proven�al ancien (jusqu'� 1500); occitan ancien (jusqu'� 1500)","pro","",},
{"Punjabi","Panjabi; Punjabi","pendjabi","pan","pa",},
{"Pushto","Pushto; Pashto","pachto","pus","ps",},
{"Quechua","Quechua","quechua","que","qu",},
{"Rajasthani","Rajasthani","rajasthani","raj","",},
{"Rapanui","Rapanui","rapanui","rap","",},
{"Rarotongan","Rarotongan; Cook Islands Maori","rarotonga; maori des �les Cook","rar","",},
{"Reserved for local use","Reserved for local use","r�serv�e � l'usage local","qaa-qtz","",},
{"Romance languages","Romance languages","romanes, langues","roa","",},
{"Romanian","Romanian; Moldavian; Moldovan","roumain; moldave","rum/ron","ro",},
{"Romansh","Romansh","romanche","roh","rm",},
{"Romany","Romany","tsigane","rom","",},
{"Rundi","Rundi","rundi","run","rn",},
{"Russian","Russian","russe","rus","ru",},
{"Sakan","Khotanese; Sakan","khotanais; sakan","kho","",},
{"Salishan languages","Salishan languages","salishennes, langues","sal","",},
{"Samaritan Aramaic","Samaritan Aramaic","samaritain","sam","",},
{"Sami languages","Sami languages","sames, langues","smi","",},
{"Samoan","Samoan","samoan","smo","sm",},
{"Sandawe","Sandawe","sandawe","sad","",},
{"Sango","Sango","sango","sag","sg",},
{"Sanskrit","Sanskrit","sanskrit","san","sa",},
{"Santali","Santali","santal","sat","",},
{"Sardinian","Sardinian","sarde","srd","sc",},
{"Sasak","Sasak","sasak","sas","",},
{"Saxon, Low","Low German; Low Saxon; German, Low; Saxon, Low","bas allemand; bas saxon; allemand, bas; saxon, bas","nds","",},
{"Scots","Scots","�cossais","sco","",},
{"Scottish Gaelic","Gaelic; Scottish Gaelic","ga�lique; ga�lique �cossais","gla","gd",},
{"Selkup","Selkup","selkoupe","sel","",},
{"Semitic languages","Semitic languages","s�mitiques, langues","sem","",},
{"Sepedi","Pedi; Sepedi; Northern Sotho","pedi; sepedi; sotho du Nord","nso","",},
{"Serbian","Serbian","serbe","srp","sr",},
{"Serer","Serer","s�r�re","srr","",},
{"Shan","Shan","chan","shn","",},
{"Shona","Shona","shona","sna","sn",},
{"Sichuan Yi","Sichuan Yi; Nuosu","yi de Sichuan","iii","ii",},
{"Sicilian","Sicilian","sicilien","scn","",},
{"Sidamo","Sidamo","sidamo","sid","",},
{"Sign Languages","Sign Languages","langues des signes","sgn","",},
{"Siksika","Siksika","blackfoot","bla","",},
{"Sindhi","Sindhi","sindhi","snd","sd",},
{"Sinhala","Sinhala; Sinhalese","singhalais","sin","si",},
{"Sinhalese","Sinhala; Sinhalese","singhalais","sin","si",},
{"Sino-Tibetan languages","Sino-Tibetan languages","sino-tib�taines, langues","sit","",},
{"Siouan languages","Siouan languages","sioux, langues","sio","",},
{"Skolt Sami","Skolt Sami","sami skolt","sms","",},
{"Slave (Athapascan)","Slave (Athapascan)","esclave (athapascan)","den","",},
{"Slavic languages","Slavic languages","slaves, langues","sla","",},
{"Slovak","Slovak","slovaque","slo/slk","sk",},
{"Slovenian","Slovenian","slov�ne","slv","sl",},
{"Sogdian","Sogdian","sogdien","sog","",},
{"Somali","Somali","somali","som","so",},
{"Songhai languages","Songhai languages","songhai, langues","son","",},
{"Soninke","Soninke","sonink�","snk","",},
{"Sorbian languages","Sorbian languages","sorabes, langues","wen","",},
{"Sotho, Northern","Pedi; Sepedi; Northern Sotho","pedi; sepedi; sotho du Nord","nso","",},
{"Sotho, Southern","Sotho, Southern","sotho du Sud","sot","st",},
{"South American Indian languages","South American Indian languages","sud-am�rindiennes, langues","sai","",},
{"South Ndebele","Ndebele, South; South Ndebele","nd�b�l� du Sud","nbl","nr",},
{"Southern Altai","Southern Altai","altai du Sud","alt","",},
{"Southern Sami","Southern Sami","sami du Sud","sma","",},
{"Spanish","Spanish; Castilian","espagnol; castillan","spa","es",},
{"Sranan Tongo","Sranan Tongo","sranan tongo","srn","",},
{"Sukuma","Sukuma","sukuma","suk","",},
{"Sumerian","Sumerian","sum�rien","sux","",},
{"Sundanese","Sundanese","soundanais","sun","su",},
{"Susu","Susu","soussou","sus","",},
{"Swahili","Swahili","swahili","swa","sw",},
{"Swati","Swati","swati","ssw","ss",},
{"Swedish","Swedish","su�dois","swe","sv",},
{"Swiss German","Swiss German; Alemannic; Alsatian","suisse al�manique; al�manique; alsacien","gsw","",},
{"Syriac","Syriac","syriaque","syr","",},
{"Tagalog","Tagalog","tagalog","tgl","tl",},
{"Tahitian","Tahitian","tahitien","tah","ty",},
{"Tai languages","Tai languages","tai, langues","tai","",},
{"Tajik","Tajik","tadjik","tgk","tg",},
{"Tamashek","Tamashek","tamacheq","tmh","",},
{"Tamil","Tamil","tamoul","tam","ta",},
{"Tatar","Tatar","tatar","tat","tt",},
{"Telugu","Telugu","t�lougou","tel","te",},
{"Tereno","Tereno","tereno","ter","",},
{"Tetum","Tetum","tetum","tet","",},
{"Thai","Thai","tha�","tha","th",},
{"Tibetan","Tibetan","tib�tain","tib/bod","bo",},
{"Tigre","Tigre","tigr�","tig","",},
{"Tigrinya","Tigrinya","tigrigna","tir","ti",},
{"Timne","Timne","temne","tem","",},
{"Tiv","Tiv","tiv","tiv","",},
{"tlhIngan-Hol","Klingon; tlhIngan-Hol","klingon","tlh","",},
{"Tlingit","Tlingit","tlingit","tli","",},
{"Tok Pisin","Tok Pisin","tok pisin","tpi","",},
{"Tokelau","Tokelau","tokelau","tkl","",},
{"Tonga (Nyasa)","Tonga (Nyasa)","tonga (Nyasa)","tog","",},
{"Tonga (Tonga Islands)","Tonga (Tonga Islands)","tongan (�les Tonga)","ton","to",},
{"Tsimshian","Tsimshian","tsimshian","tsi","",},
{"Tsonga","Tsonga","tsonga","tso","ts",},
{"Tswana","Tswana","tswana","tsn","tn",},
{"Tumbuka","Tumbuka","tumbuka","tum","",},
{"Tupi languages","Tupi languages","tupi, langues","tup","",},
{"Turkish","Turkish","turc","tur","tr",},
{"Turkish, Ottoman (1500-1928)","Turkish, Ottoman (1500-1928)","turc ottoman (1500-1928)","ota","",},
{"Turkmen","Turkmen","turkm�ne","tuk","tk",},
{"Tuvalu","Tuvalu","tuvalu","tvl","",},
{"Tuvinian","Tuvinian","touva","tyv","",},
{"Twi","Twi","twi","twi","tw",},
{"Udmurt","Udmurt","oudmourte","udm","",},
{"Ugaritic","Ugaritic","ougaritique","uga","",},
{"Uighur","Uighur; Uyghur","ou�gour","uig","ug",},
{"Ukrainian","Ukrainian","ukrainien","ukr","uk",},
{"Umbundu","Umbundu","umbundu","umb","",},
{"Uncoded languages","Uncoded languages","langues non cod�es","mis","",},
{"Undetermined","Undetermined","ind�termin�e","und","",},
{"Upper Sorbian","Upper Sorbian","haut-sorabe","hsb","",},
{"Urdu","Urdu","ourdou","urd","ur",},
{"Uyghur","Uighur; Uyghur","ou�gour","uig","ug",},
{"Uzbek","Uzbek","ouszbek","uzb","uz",},
{"Vai","Vai","va�","vai","",},
{"Valencian","Catalan; Valencian","catalan; valencien","cat","ca",},
{"Venda","Venda","venda","ven","ve",},
{"Vietnamese","Vietnamese","vietnamien","vie","vi",},
{"Volap�k","Volap�k","volap�k","vol","vo",},
{"Votic","Votic","vote","vot","",},
{"Wakashan languages","Wakashan languages","wakashanes, langues","wak","",},
{"Walloon","Walloon","wallon","wln","wa",},
{"Waray","Waray","waray","war","",},
{"Washo","Washo","washo","was","",},
{"Welsh","Welsh","gallois","wel/cym","cy",},
{"Western Frisian","Western Frisian","frison occidental","fry","fy",},
{"Western Pahari languages","Himachali languages; Western Pahari languages","langues himachalis; langues paharis occidentales","him","",},
{"Wolaitta","Wolaitta; Wolaytta","wolaitta; wolaytta","wal","",},
{"Wolaytta","Wolaitta; Wolaytta","wolaitta; wolaytta","wal","",},
{"Wolof","Wolof","wolof","wol","wo",},
{"Xhosa","Xhosa","xhosa","xho","xh",},
{"Yakut","Yakut","iakoute","sah","",},
{"Yao","Yao","yao","yao","",},
{"Yapese","Yapese","yapois","yap","",},
{"Yiddish","Yiddish","yiddish","yid","yi",},
{"Yoruba","Yoruba","yoruba","yor","yo",},
{"Yupik languages","Yupik languages","yupik, langues","ypk","",},
{"Zande languages","Zande languages","zand�, langues","znd","",},
{"Zapotec","Zapotec","zapot�que","zap","",},
{"Zaza","Zaza; Dimili; Dimli; Kirdki; Kirmanjki; Zazaki","zaza; dimili; dimli; kirdki; kirmanjki; zazaki","zza","",},
{"Zazaki","Zaza; Dimili; Dimli; Kirdki; Kirmanjki; Zazaki","zaza; dimili; dimli; kirdki; kirmanjki; zazaki","zza","",},
{"Zenaga","Zenaga","zenaga","zen","",},
{"Zhuang","Zhuang; Chuang","zhuang; chuang","zha","za",},
{"Zulu","Zulu","zoulou","zul","zu",},
{"Zuni","Zuni","zuni","zun","",},
};
