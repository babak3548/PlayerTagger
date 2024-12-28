#ifndef __SeekProps_h__
#define __SeekProps_h__

#ifdef __cplusplus
extern "C"{
#endif 

#ifndef __ISeekProps_INTERFACE_DEFINED__
#define __ISeekProps_INTERFACE_DEFINED__

// 82D6E770-5C82-11D4-8E7E-0050040F5390
DEFINE_GUID(IID_ISeekProps, 
	0x82D6E770, 0x5C82, 0x11D4, 0x8E, 0x7E, 0x00, 0x50, 0x04, 0x0F, 0x53, 0x90);

	typedef enum
	{
		seekImposible,
		seekBitrate,
		seekPTS,
		seekWithIndex
	}
	SEEK_METHOD;


#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("82D6E770-5C82-11D4-8E7E-0050040F5390")
    ISeekProps : public IUnknown
    {
    public:
		virtual HRESULT STDMETHODCALLTYPE CanUseSeekMethod(SEEK_METHOD method) = 0;
		virtual HRESULT STDMETHODCALLTYPE UseSeekMethod(SEEK_METHOD method) = 0;
		virtual HRESULT STDMETHODCALLTYPE GetSeekMethod(SEEK_METHOD* pMethod) = 0;
		virtual HRESULT STDMETHODCALLTYPE SetDefaultMethod(SEEK_METHOD Method) = 0;
		virtual HRESULT STDMETHODCALLTYPE GetDefaultMethod(SEEK_METHOD* pMethod) = 0;
    };

#endif // defined(__cplusplus) && !defined(CINTERFACE)

#endif // __ISeekProps_INTERFACE_DEFINED__



#ifndef __IIndexConfig_INTERFACE_DEFINED__
#define __IIndexConfig_INTERFACE_DEFINED__

// 82D6E791-5C82-11D4-8E7E-0050040F5390
DEFINE_GUID(IID_IIndexConfig, 
	0x82D6E791, 0x5C82, 0x11D4, 0x8E, 0x7E, 0x00, 0x50, 0x04, 0x0F, 0x53, 0x90);


#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("82D6E791-5C82-11D4-8E7E-0050040F5390")
    IIndexConfig : public IUnknown
    {
    public:
		virtual HRESULT STDMETHODCALLTYPE UseIndex(IMediaIndex* pIndex) = 0;
		virtual HRESULT STDMETHODCALLTYPE CanUseIndex() = 0;
    };

#endif // defined(__cplusplus) && !defined(CINTERFACE)

#endif // __IIndexConfig_INTERFACE_DEFINED__

#ifdef __cplusplus
}
#endif

#endif


