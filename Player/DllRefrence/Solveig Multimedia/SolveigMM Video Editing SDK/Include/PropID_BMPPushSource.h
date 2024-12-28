//Object GUIDS
//Filter GUID
static const GUID CLSID_BMPPushSource =
{ 0x234D4D5F, 0x5F42, 0x4D50, {0x50, 0x75, 0x73, 0x68, 0x53, 0x6F, 0x72, 0x73} };
//PropertyPage GUID
static const GUID CLSID_BMPPushSource_Props =
{ 0x234D4D5F, 0x5F42, 0x4D51, {0x50, 0x75, 0x73, 0x68, 0x53, 0x6F, 0x72, 0x73} };

//Parameters GUIDS can be found in a FULL version of SDK


typedef struct StreamParams
{
	LONG			lWidth;			//Frame width
	LONG			lHeight;		//Frame height
	REFERENCE_TIME	rtFrameLenght;	//One frame duration
	LONGLONG		llTotalFrames;	//Total number of frames
	DWORD			dwCompression;	//Used compression
}StreamParameters;
