#ifndef __SMM_PROFILE_PARSER__
#define __SMM_PROFILE_PARSER__

#include <ModuleConfig.h>
#include <PropID_EditingEngine.h>
#include <CReg.h>

// MainConcept
#include <empgdmx.inc>        // CLSID_EMPGDMX
#include <em2vd.h>            // CLSID_EM2VD
#include <em2ve.h>            // CLSID_EM2VE_STD
#include <emuxer.inc>
#include <emuxer.h>

#include <mpgindexator.h>   // CLSID_MpgFileIndexator

#include <mediaindexdef.h>

// Elecard
#include <empegmux.inc>
#include <empegmux.h>
#include <em2venc_hd.inc>
#include <em2venc.h>

// #include <empgdmx.h> - uses the same methods and guids as Mainconcept's
// No need to include it again


#include <eavcdec.inc>
#include <eavcdec_sd.inc>
#include <eavcenc.h>
#include <eavcenc_hd.inc>
#include <eavcenc_sd.inc>

#include <emp4demux.h>
#include <emp4demux.inc>
#include <emp4mux.h>
#include <emp4mux.inc>

#include <PropID_MatroskaMuxer.h>
#include <PropID_MatroskaDemuxer.h>
#include <PropID_MP4Muxer.h>
#include <PropID_MP4Demuxer.h>


///CLSID_CWMVEncMediaObject2 custom encoder for wmv complex profile
static const GUID CLSID_CWMVEncMediaObject2_custom = 
{ 0x96b57cdd, 0x8966, 0x410c, { 0xbb, 0x1f, 0xc9, 0x7e, 0xea, 0x76, 0x5c, 0x04 } };

class ProfileParser
{
public:
	ProfileParser(CString profile);
	virtual ~ProfileParser();
	static ProfileParser& Instance(CString profile);
	typedef enum { Id_Demuxer = 0x0, Id_Muxer, Id_Encoder, Id_Decoder, Id_IndexReader, Id_Indexator, Id_Last} fId;// filter Id's
	typedef enum { prmVES = 0x0, prmCONTAINER, prmRESOLUTION, prmVERSION } fParam;   // generic filter parameters
	typedef enum { vesMPEG2 = 0x0, vesAVC } tVES;   // codec's
	typedef enum { cMPEG2 = 0x0, cMP4, cMKV, cAVI } tContainer;   // muxer's
	typedef enum { rSD = 0x0, rCIF, rHD,rUnknown } tResolution;   // encoder resolution type
	typedef enum { v0 = 0x0, v1, v2 } tVersion;   // generic filter version
	typedef CList<long, long&> ResultList;

	static CString GetFltrSlntPath( CString RegtoCmpnts, GUID FltGuid );
	GUID GetFilterCLSID( fId filter, fParam prm, long value );
	CodecDeveloper GetDeveloperName( fId filter, fParam prm, long value );
	tResolution ProfileParser::GetResolutionType(fId filterID, tVES codec);
	CString GetFilterName(GUID &g);
	ResultList& QueryFilters ( fId filter, fParam prm );


protected:

	virtual int FindNextStartPos( fId filter );
	virtual CString GetFilterParamSpec();

	typedef CMapStringToString FilterParamMap;
	virtual long QueryFilterValueType( fId filter, fParam prm );
	virtual BOOL QueryFilterMatch( fId filter, fParam prm, long value );
	

	virtual FilterParamMap& GetFilterParams();
	virtual void AddFilterParam( CString str, FilterParamMap &p );
	virtual long GetParam( FilterParamMap &p, fParam prm );
	virtual CString FormatFilterName( fId filter );
	GUID EL_GetFilterCLSID( fId filter, fParam prm, long value );
	GUID MC_GetFilterCLSID( fId filter, fParam prm, long value );
	GUID SM_GetFilterCLSID( fId filter, fParam prm, long value );
	CString ConvertGUID(GUID &g);

private:
	CString m_profile;
	int m_iPos;
	FilterParamMap m_gsmap;
};



#endif