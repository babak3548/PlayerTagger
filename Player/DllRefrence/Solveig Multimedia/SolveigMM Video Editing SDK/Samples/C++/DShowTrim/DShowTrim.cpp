////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004-2012 Solveig Multimedia
// All rights are reserved. 
//
// Solveig Multimedia reserves the right to make changes without
// notice at any time. Solveig Multimedia makes no warranty,
// expressed, implied or statutory, including but not limited to any implied
// warranty of merchantability of fitness for any particular purpose, or that
// the use will not infringe any third party patent, copyright or trademark.
// Solveig Multimedia must not be liable for any loss or damage
// arising from its use.
// 
//////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "graph.h"

using namespace std;

#define MY_VERSION L"2.0.810.21"

int usage(_TCHAR * myname)
{
	wprintf(L"SolveigMM AVI Trimmer console utility.\n");
	wprintf( (L"Version: %s\n"), MY_VERSION ) ;
	wprintf(L"Parameters:\n");
	wprintf(L"\t -in	:	Input AVI filename with a full file path \n");
	wprintf(L"\t -start :	HH:MM:SS:mmm\n");
	wprintf(L"\t -stop  :	HH:MM:SS:mmm\n");
	return 1;
}

Params ProcessCommandLine( int argc, _TCHAR* argv[] )
{
	Params params; 
	params.bParamsFilled = FALSE;

	int i = 0;

	// 1) User didn't use any arguments. Show USAGE
	if (argc < 6){
		 usage(_T("DShowAVITrim.exe"));
		 return params;
	}

	// 2) User set's flag <-h>: Show USAGE
	CString InFileName;
	CString start;
	CString stop;

	for ( i = 1; i < argc; i++)
	{
		CString val = argv[i];
		
		if (val == "-in"){
			InFileName = argv[ i + 1 ];
		}
		
		if (val == "-start"){
			start = argv[ i + 1 ];
		}

		if (val == "-stop"){
			stop = argv[ i + 1 ];
		}

		if (val == "-h"){
			usage(_T("BatchSplit.exe"));
			return params;
		}

	}
	
	if( 0 == InFileName.GetLength() ||
		0 == start.GetLength() ||
		0 == stop.GetLength())
	{
		wprintf(L"Error. One or more parameters were missed\n\n");
	}
	
	params.in_fn	= InFileName;
	params.out_fn	= InFileName + CString(L"trimmed.avi") ;
	
	params.trim_param.nListSize = 1;
	params.trim_param.trim_list = new __TSTrimInfo[1];
	USES_CONVERSION;
	params.trim_param.trim_list[0].nPieceNum	=0;
	params.trim_param.trim_list[0].llStartPos	= ConvertString2Time(T2A(start));
	params.trim_param.trim_list[0].llStopPos	= ConvertString2Time(T2A(stop));
	params.bParamsFilled = TRUE;

	return params;
}
	   
int _tmain(int argc, _TCHAR* argv[])
{
	CGraph graph;
	
	Params params = ProcessCommandLine(argc, argv);
	
	graph.SetParams(params);
	
	HRESULT hr = graph.Init();
	if(FAILED(hr)){
		return 0;
	}

	hr = graph.Start();
	if(FAILED(hr)){
		return 0;
	}
	
	int nProgr = 0; //%
	while( nProgr < 100 )
	{
		nProgr = graph.GetProgress();
		wprintf(L"Trimming progress - \t%d%\n",nProgr );
		Sleep(2000);
	}

	BOOL bval = graph.WaitForStop();
	if(!bval){
		wprintf(L"Error. Trimming graph was not successfully stopped\n");
		return 0;
	}

	wprintf(L"Trimming was successfully completed\n");
	return 0;
}

