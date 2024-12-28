
/////////////////////////////////////////////////////////////////////////////////
//
//	   Copyright (c) 2005 Elecard Ltd.
//	   All rights are reserved.  Reproduction in whole or in part is prohibited
//	   without the written consent of the copyright owner.
//
//	   Elecard Ltd. reserves the right to make changes without
//	   notice at any time. Elecard Ltd. makes no warranty, expressed,
//	   implied or statutory, including but not limited to any implied
//	   warranty of merchantability of fitness for any particular purpose,
//	   or that the use will not infringe any third party patent, copyright
//	   or trademark.
//
//	   Elecard Ltd. must not be liable for any loss or damage arising
//	   from its use.
//
////////////////////////////////////////////////////////////////////////////////
//  author:     Konstantin Kohanenko (mail-to: Kohanenko@elecard.net.ru)
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMuxUtils.h"

namespace XMuxerUtils {

//////////////////////////////////////////////////////////////////////////
// CBitsStructManager class implementation

// Get binaries data start code 
HRESULT CBitsStructManager::GetStartCode(PBYTE pData, LONG lSize, TEStartCode& nCode)
{
	HRESULT hr = S_OK;

	if (!pData)
		return E_POINTER; 
	
	CBitsBuffer buff;
	buff.SetMode(CBitsBuffer::mode_Read);
	buff.SetBuffer(pData, lSize);

	INT16 nValue;
	if (FAILED(hr = buff.Read16Bits(nValue)))
		return hr;
	
	nCode = (TEStartCode)nValue;

	return hr;
}

// Calculation amount of bytes necessary to convert structure to binaries buffer 
LONG CBitsStructManager::CalculateSize(TEStartCode nCode, PVOID pStruct)
{
	LONG lSize = 0;

	switch (nCode) 
	{
		case scode_Multiplex: 
		{
			lSize = 40;
			TSMuxParam *pParam = static_cast<TSMuxParam*>(pStruct);

			if (pParam->MuxFileInfo.size() > 0)
			{
				lSize += 104;
				TLIMuxFileInfo it = pParam->MuxFileInfo.begin();
				for (; it != pParam->MuxFileInfo.end(); ++it)
				{
					lSize += 192;
					lSize += (*it).sFileName.size() * 8;
				}
			}

			lSize += 40;
			lSize += pParam->sOutFileName.size() * 8;

			break;
		}
							 
		case scode_Demultiplex: 
		{
			lSize = 40;
			TSDemuxParam *pParam = static_cast<TSDemuxParam*>(pStruct);

			TLIFileName itfl = pParam->FileList.begin();
			for (; itfl != pParam->FileList.end(); ++itfl) 
			{
				lSize += 32;
				lSize += (*itfl).size() * 8;
			}

			lSize += 16;
			TLIOutputPinInfo itpi(pParam->OutPinsInfo.begin());
			for (; itpi != pParam->OutPinsInfo.end(); ++itpi) 
			{
				lSize += 128;
				lSize += (*itpi).sOutFileName.size() * 8;
			}

			lSize += 16;
			lSize += 144 * pParam->TrimInfo.size();

			lSize += 8;

			break;
		}

		case scode_Remultiplex: 
		{
			lSize = 40;
			TSRemuxParam *pParam = static_cast<TSRemuxParam*>(pStruct);

			TLIFileName itfl = pParam->FileList.begin();
			for (; itfl!=pParam->FileList.end(); ++itfl) 
			{
				lSize += 32;
				lSize += (*itfl).size() * 8;
			}

			lSize += 16;

			if (pParam->InPinsInfo.size() > 0)
			{
				lSize += 104;
				lSize += 256 * pParam->InPinsInfo.size();
			}            

			lSize += 16;
			lSize += 144 * pParam->TrimInfo.size();

			lSize += 32;
			lSize += pParam->sOutFileName.size() * 8;
			lSize += 8;

			break;
		}

		default:
			return 0;
	}

	return lSize/8;
}

// Convert binaries data to structure
HRESULT CBitsStructManager::BitDataToStruct(PBYTE pData, LONG lSize, PVOID pStruct)
{
	HRESULT hr = S_OK;

	if (!pData || !pStruct)
		return E_POINTER; 

	CBitsBuffer buff;
	buff.SetMode(CBitsBuffer::mode_Read);
	buff.SetBuffer(pData, lSize);

	INT16 nCode = 0;
	if (SUCCEEDED(buff.Read16Bits(nCode))) 
	{
		switch (nCode) 
		{
			case scode_Multiplex:
			{
				// Reserve bits
				INT8 nValue;				
				if (FAILED(hr = buff.Read8Bits(nValue))) return hr;

				// Get input stream info
				INT16 nCount;
				if (FAILED(hr = buff.Read16Bits(nCount))) return hr;
					
				if (nCount > 0)
				{
					if (FAILED(hr = buff.Read32Bits((INT32&)static_cast<TSMuxParam*>(pStruct)->dwOutTransportID)))  return hr;
					if (FAILED(hr = buff.Read32Bits((INT32&)static_cast<TSMuxParam*>(pStruct)->lRequiredBitrate)))  return hr;
					if (FAILED(hr = buff.Read32Bits((INT32&)static_cast<TSMuxParam*>(pStruct)->lPCRInterval)))		return hr;				
					if (FAILED(hr = buff.Read8Bits((INT8&)static_cast<TSMuxParam*>(pStruct)->bUsePadding)))			return hr;

					for (int i = 0; i < nCount; i++) 
					{                        
						INT32 nLength;
						if (FAILED(hr = buff.Read32Bits(nLength))) return hr;

						TSMuxFileInfo finfo;
						if (FAILED(hr = buff.ReadString(finfo.sFileName, nLength)))       return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)finfo.dwOutProgramID)))   return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)finfo.dwOutProgramNum)))  return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)finfo.dwOutStreamID)))    return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)finfo.dwOutStreamPESID))) return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)finfo.lInitTimeShift)))   return hr;

						static_cast<TSMuxParam*>(pStruct)->MuxFileInfo.push_back(finfo);
					}
				}

				INT8 nType;
				if (FAILED(hr = buff.Read8Bits(nType))) return hr;
				static_cast<TSMuxParam*>(pStruct)->StreamType = (TEStreamType)nType;

				// Get output stream info
				INT32 nLength;
				if (FAILED(hr = buff.Read32Bits(nLength))) return hr;	
				if (FAILED(hr = buff.ReadString(static_cast<TSMuxParam*>(pStruct)->sOutFileName, nLength))) 
					return hr;

				break;
			}
			
			case scode_Demultiplex:
			{
				INT32 nValue;				
				if (FAILED(hr = buff.ReadBits(nValue, 1))) return hr;
				static_cast<TSDemuxParam*>(pStruct)->bTrim = nValue;

				if (FAILED(hr = buff.ReadBits(nValue, 2))) return hr;
				static_cast<TSDemuxParam*>(pStruct)->TrimType = (TETrimType)nValue;
				
				if (FAILED(hr = buff.ReadBits(nValue, 2))) return hr;
				static_cast<TSDemuxParam*>(pStruct)->SeekMethod = (TESeekingMethods)nValue;

				if (FAILED(hr = buff.ReadBits(nValue, 3))) return hr;
				
				// Get input stream info
				INT16 nCount;
				if (FAILED(hr = buff.Read16Bits(nCount))) return hr;
				
				for (int i = 0; i < nCount; i++) 
				{
					INT32 nLength;
					if (FAILED(hr = buff.Read32Bits(nLength))) return hr;
					
					CTBString sFileName;
					if (FAILED(hr = buff.ReadString(sFileName, nLength))) 
						return hr;

					static_cast<TSDemuxParam*>(pStruct)->FileList.push_back(sFileName);
				}

				// Get pins info
				if (FAILED(hr = buff.Read16Bits(nCount))) return hr;

				for (i = 0; i < nCount; i++) 
				{
					INT32 nValue;
                    TSOutputPinInfo pin;
			
                    if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwOutStreamID)))    return hr;
					if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwOutStreamSubID))) return hr;
					if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwOutStreamPID)))   return hr;
					if (FAILED(hr = buff.Read32Bits(nValue)))                       return hr;
					if (FAILED(hr = buff.ReadString(pin.sOutFileName, nValue)))     return hr;
					
					static_cast<TSDemuxParam*>(pStruct)->OutPinsInfo.push_back(pin);
				}

				// Get trim info
				if (FAILED(hr = buff.Read16Bits(nCount))) return hr;	

				for (i = 0; i < nCount; i++) 
				{
					TSTrimInfo trim;
					
					if (FAILED(hr = buff.Read64Bits(trim.llStartPos))) return hr;
					if (FAILED(hr = buff.Read64Bits(trim.llStopPos)))  return hr;				
					if (FAILED(hr = buff.Read16Bits(trim.nPieceNum)))  return hr;

					static_cast<TSDemuxParam*>(pStruct)->TrimInfo.push_back(trim);
				}
				
				INT8 nType;
				if (FAILED(hr = buff.Read8Bits(nType))) return hr;

				static_cast<TSDemuxParam*>(pStruct)->StreamType = (TEStreamType)nType;

				break;
			}

			case scode_Remultiplex:
			{
				INT32 nValue;				

				if (FAILED(hr = buff.ReadBits(nValue, 2))) return hr;
				static_cast<TSRemuxParam*>(pStruct)->TrimType = (TETrimType)nValue;
				
				if (FAILED(hr = buff.ReadBits(nValue, 2))) return hr;
				static_cast<TSRemuxParam*>(pStruct)->SeekMethod = (TESeekingMethods)nValue;

				if (FAILED(hr = buff.ReadBits(nValue, 1))) return hr;
				static_cast<TSRemuxParam*>(pStruct)->bTrim = nValue;

				if (FAILED(hr = buff.ReadBits(nValue, 3))) return hr;
				
				// Get input stream info
				INT16 nCount;
				if (FAILED(hr = buff.Read16Bits(nCount))) return hr;
				
				for (int i = 0; i < nCount; i++) 
				{
					INT32 nLength;
					if (FAILED(hr = buff.Read32Bits(nLength))) return hr;
					
					CTBString sFileName;
					if (FAILED(hr = buff.ReadString(sFileName, nLength))) 
						return hr;

					static_cast<TSRemuxParam*>(pStruct)->FileList.push_back(sFileName);
				}
				
				// Get pins info
				if (FAILED(hr = buff.Read16Bits(nCount))) return hr;

				if (nCount > 0)
				{
					if (FAILED(hr = buff.Read32Bits((INT32&)static_cast<TSRemuxParam*>(pStruct)->dwOutTransportID))) return hr;
					if (FAILED(hr = buff.Read32Bits((INT32&)static_cast<TSRemuxParam*>(pStruct)->lRequiredBitrate))) return hr;
					if (FAILED(hr = buff.Read32Bits((INT32&)static_cast<TSRemuxParam*>(pStruct)->lPCRInterval)))	 return hr;				
					
					INT8 nVal;
					if (FAILED(hr = buff.Read8Bits(nVal)))	 return hr;
					static_cast<TSRemuxParam*>(pStruct)->bUsePadding = (BOOL)nVal;
					
					for (i = 0; i < nCount; i++) 
					{
						TSInputPinInfo pin;

						if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwInStreamID)))     return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwInStreamSubID)))  return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwInStreamPID)))    return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwOutProgramID)))   return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwOutProgramNum)))  return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwOutStreamID)))    return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)pin.dwOutStreamPESID))) return hr;
						if (FAILED(hr = buff.Read32Bits((INT32&)pin.lInitTimeShift)))	return hr;

						static_cast<TSRemuxParam*>(pStruct)->InPinsInfo.push_back(pin);
					}
				}

				// Get piece info
				if (FAILED(hr = buff.Read16Bits(nCount))) return hr;	

				for (i=0; i<nCount; i++) 
				{
					TSTrimInfo trim;
					
					if (FAILED(hr = buff.Read64Bits(trim.llStartPos))) return hr;
					if (FAILED(hr = buff.Read64Bits(trim.llStopPos)))  return hr;				
					if (FAILED(hr = buff.Read16Bits(trim.nPieceNum)))  return hr;

					static_cast<TSRemuxParam*>(pStruct)->TrimInfo.push_back(trim);
				}
				
				// Get output stream info
				INT32 nLength;
				if (FAILED(hr = buff.Read32Bits(nLength))) return hr;	
				if (FAILED(hr = buff.ReadString(static_cast<TSRemuxParam*>(pStruct)->sOutFileName, nLength))) 
					return hr;
				
				INT8 nType;
				if (FAILED(hr = buff.Read8Bits(nType))) return hr;
                static_cast<TSRemuxParam*>(pStruct)->StreamType = (TEStreamType)nType;

				break;
			}
		}

	} else
		return E_INVALIDARG;

	return S_OK;
}

// Convert structure to binaries buffer.
HRESULT CBitsStructManager::StructToBitData(TEStartCode nCode, PVOID pStruct, PBYTE pData, LONG lSize)
{
	if (!pData || !pStruct) 
		return E_POINTER; 

	LONG lRealSize = CalculateSize(nCode, pStruct);
	if (lSize < lRealSize) 
		return E_PENDING;  
	
	// write data
	CBitsBuffer buff;
	buff.SetMode(CBitsBuffer::mode_Write);
	buff.SetBufferSize(lRealSize);
	buff.Write16Bits(nCode);

	switch (nCode) 
	{
		case scode_Multiplex: 
		{
			TSMuxParam *pParam = static_cast<TSMuxParam*>(pStruct);

			buff.Write8Bits(1);
			buff.Write16Bits(pParam->MuxFileInfo.size());

			if (pParam->MuxFileInfo.size() > 0)
			{			
				buff.Write32Bits(pParam->dwOutTransportID);
				buff.Write32Bits(pParam->lRequiredBitrate);
				buff.Write32Bits(pParam->lPCRInterval);
				buff.Write8Bits(pParam->bUsePadding);

				TLIMuxFileInfo it = pParam->MuxFileInfo.begin();

				for (; it != pParam->MuxFileInfo.end(); ++it)
				{
					buff.Write32Bits((*it).sFileName.size());
					buff.WriteString((*it).sFileName, (*it).sFileName.size());
					buff.Write32Bits((*it).dwOutProgramID);
					buff.Write32Bits((*it).dwOutProgramNum);
					buff.Write32Bits((*it).dwOutStreamID);
					buff.Write32Bits((*it).dwOutStreamPESID);
					buff.Write32Bits((*it).lInitTimeShift);
				}
			}

			buff.Write8Bits(pParam->StreamType);

			buff.Write32Bits(pParam->sOutFileName.size());			
			buff.WriteString(pParam->sOutFileName, pParam->sOutFileName.size());

			break;							 
		}

		case scode_Demultiplex:
		{
			TSDemuxParam *pParam = static_cast<TSDemuxParam*>(pStruct);

			buff.WriteBit(pParam->bTrim);
			buff.WriteBits(2, pParam->TrimType);
			buff.WriteBits(2, pParam->SeekMethod);
			buff.WriteBits(3, 0);

			buff.Write16Bits(pParam->FileList.size());

			TLIFileName itfl;
			for (itfl = pParam->FileList.begin(); itfl != pParam->FileList.end(); ++itfl)
			{
				buff.Write32Bits((*itfl).size());
				buff.WriteString(*itfl, (*itfl).size());
			}

			buff.Write16Bits(pParam->OutPinsInfo.size());

            TLIOutputPinInfo itpi;
			for (itpi = pParam->OutPinsInfo.begin(); itpi != pParam->OutPinsInfo.end(); ++itpi)
			{
				buff.Write32Bits((*itpi).dwOutStreamID);
				buff.Write32Bits((*itpi).dwOutStreamSubID);
				buff.Write32Bits((*itpi).dwOutStreamPID);
				buff.Write32Bits((*itpi).sOutFileName.size());
				buff.WriteString((*itpi).sOutFileName, (*itpi).sOutFileName.size());
			}
			
			buff.Write16Bits(pParam->TrimInfo.size());
			
			TLITrimInfo itti;
			for (itti = pParam->TrimInfo.begin(); itti != pParam->TrimInfo.end(); ++itti)
			{
				buff.Write64Bits((*itti).llStartPos);
				buff.Write64Bits((*itti).llStopPos);
				buff.Write16Bits((*itti).nPieceNum);
			}

			buff.Write8Bits(pParam->StreamType);
			
			break;
		}

		case scode_Remultiplex: 
		{
			TSRemuxParam *pParam = static_cast<TSRemuxParam*>(pStruct);				
			
			buff.WriteBits(2, pParam->TrimType);
			buff.WriteBits(2, pParam->SeekMethod);
			buff.WriteBit(pParam->bTrim);
			buff.WriteBits(3, 0);

			buff.Write16Bits(pParam->FileList.size());
			
			TLIFileName itfl;
			for (itfl = pParam->FileList.begin(); itfl!=pParam->FileList.end(); itfl++)
			{
				buff.Write32Bits((*itfl).size());
				buff.WriteString(*itfl, (*itfl).size());
			}

			buff.Write16Bits(pParam->InPinsInfo.size());

			if (pParam->InPinsInfo.size() > 0)
			{
				buff.Write32Bits(pParam->dwOutTransportID);
				buff.Write32Bits(pParam->lRequiredBitrate);
				buff.Write32Bits(pParam->lPCRInterval);
				buff.Write8Bits(pParam->bUsePadding);

				TLIInputPinInfo itpi;
				for (itpi = pParam->InPinsInfo.begin(); itpi != pParam->InPinsInfo.end(); ++itpi)
				{
					buff.Write32Bits((*itpi).dwInStreamID);
					buff.Write32Bits((*itpi).dwInStreamSubID);
					buff.Write32Bits((*itpi).dwInStreamPID);
					buff.Write32Bits((*itpi).dwOutProgramID);
					buff.Write32Bits((*itpi).dwOutProgramNum);
					buff.Write32Bits((*itpi).dwOutStreamID);
					buff.Write32Bits((*itpi).dwOutStreamPESID);
					buff.Write32Bits((*itpi).lInitTimeShift);
				}
			}
			
			buff.Write16Bits(pParam->TrimInfo.size());			
			
			TLITrimInfo itti;
			for (itti = pParam->TrimInfo.begin(); itti!=pParam->TrimInfo.end(); ++itti)
			{
				buff.Write64Bits((*itti).llStartPos);
				buff.Write64Bits((*itti).llStopPos);
				buff.Write16Bits((*itti).nPieceNum);
			}

			buff.Write32Bits(pParam->sOutFileName.size());			
			buff.WriteString(pParam->sOutFileName, pParam->sOutFileName.size());

			buff.Write8Bits(pParam->StreamType);

			break;
		}

		default :
			return E_INVALIDARG;
	}

	memcpy(pData, buff.GetBuffer(), buff.GetBufferSize());

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// CBitsBuffer class implementation

CBitsBuffer::CBitsBuffer()
		: m_pBuffer(NULL)
		, m_CurMode(mode_Unknown)
		, m_nBit(8)
		, m_nBitsRead(0)
		, m_nBitsWrite(0)
		, m_nSize(0)
{
}

CBitsBuffer::~CBitsBuffer()
{
	ResetAllParameters();
}

void CBitsBuffer::ResetAllParameters()
{
	if (m_pBuffer) 
	{
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}

	m_nCurrByte	 = 0;
	m_nBit		 = 8;
	m_nBitsRead	 = 0;
	m_nBitsWrite = 0;
	m_nSize		 = 0;
}

void CBitsBuffer::SetMode(TEOperationMode mode)
{
	ResetAllParameters();
	m_CurMode = mode;
}

HRESULT	CBitsBuffer::SetBufferSize(const UINT32 nBytesCount)
{
	if (m_CurMode != mode_Write)
		return E_FAIL; 
		
	ResetAllParameters();

	m_pBuffer = new BYTE[nBytesCount];
	memset(m_pBuffer, 0, nBytesCount);
	m_nSize = nBytesCount;
	
	return S_OK;
}

HRESULT CBitsBuffer::SetBuffer(const PBYTE pBuffer, const UINT32 nBytesCount)
{
	if (m_CurMode != mode_Read)
		return E_FAIL;

	ResetAllParameters();
	
	m_pBuffer = new BYTE[nBytesCount];
	memcpy(m_pBuffer, pBuffer, nBytesCount);
	m_nSize = nBytesCount;

	return S_OK;
}

HRESULT CBitsBuffer::WriteBit(const BOOL nValue)
{
	HRESULT hr = S_OK;

	static nBits = 0;

	if (m_CurMode != mode_Write)
		return E_FAIL;

	if (m_nSize * 8 < m_nBitsWrite+1) 
		return E_FAIL; 

	m_nBitsWrite ++;
	m_nCurrByte <<= 1;

	if (nValue & 0x1)
		m_nCurrByte |= 1;
  
	m_nBit--;
	if (m_nBit == 0) 
		hr = WriteByte();

	return hr;
}

HRESULT CBitsBuffer::WriteByte()
{
	m_pBuffer[m_nBitsWrite/8-1] = m_nCurrByte;
	m_nBit = 8;

	return S_OK;
}

HRESULT CBitsBuffer::WriteBits(UINT32 nBitsCount, UINT32 nValue)
{
	HRESULT hr = S_OK;

	if (nBitsCount>32)
		return E_INVALIDARG;
	
	if (m_nSize * 8 < m_nBitsWrite + nBitsCount) 
		return E_PENDING; 

	UINT32 i, mask;

	mask = 1 << (nBitsCount - 1); 
	for (i = 0; i < nBitsCount; i++)
	{
		m_nBitsWrite++;
		m_nCurrByte <<= 1;
		
		if (nValue & mask)
			m_nCurrByte |= 1;
		
		mask >>= 1; 
		m_nBit--;
		
		if (m_nBit == 0) 
			hr = WriteByte();
	}

	return hr;
}

HRESULT CBitsBuffer::Write8Bits(const UINT8 nValue)
{
	return WriteBits(8, nValue);
}

HRESULT CBitsBuffer::Write16Bits(const UINT16 nValue)
{
	BYTE pBuff[2];

	pBuff[0] = (nValue & 0xFF00) >> 8;
	pBuff[1] = (nValue & 0xFF);
	
	WriteBits(8, pBuff[0]);
	WriteBits(8, pBuff[1]);
	
	return S_OK; 
}

HRESULT CBitsBuffer::Write32Bits(const UINT32 nValue)
{
	BYTE pBuff[4];
	
	pBuff[0] = (nValue & 0xFF000000) >> 24;
	pBuff[1] = (nValue & 0xFF0000) >> 16;
	pBuff[2] = (nValue & 0xFF00) >> 8;
	pBuff[3] = (nValue & 0xFF);

	WriteBits(8, pBuff[0]);
	WriteBits(8, pBuff[1]);
	WriteBits(8, pBuff[2]);
	WriteBits(8, pBuff[3]);

	return S_OK; 
}

HRESULT CBitsBuffer::Write64Bits(const UINT64 nValue)
{
    if (m_nSize*8 < m_nBitsWrite+64)
        return E_PENDING;

	BYTE pBuff[8];

    UINT64 _nValue = nValue;
	
	for (int i = 7; i >= 0; i--) 
	{
		pBuff[i] = _nValue & 0xFF;
		_nValue >>= 8;
	}	

	for (i = 0; i < 8; i++)
	{
		m_nBitsWrite += 8;
		m_nCurrByte = pBuff[i];
		WriteByte();
	}

	m_nBit = 8;

	return S_OK;
}

HRESULT	CBitsBuffer::WriteString(const CTBString sString, const UINT32 nBytesCount)
{
	if (m_nSize * 8 < m_nBitsWrite + nBytesCount * 8)
		return E_FAIL;

	CTBString sTemp = sString;

	CTBString::iterator it;
	for (it = sTemp.begin(); it != sTemp.end(); ++it) 
		Write8Bits(*it);
	
	return S_OK;
}

HRESULT	CBitsBuffer::ReadBits(INT32 &nValue, const UINT32 nBitsCount)
{
	if (nBitsCount > m_nSize * 8 - m_nBitsRead)
		return E_FAIL;

	UINT32 masks[8] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
	
	UINT32 _nValue = 0, j = 0;
	UINT32 i = nBitsCount;

	if ((m_nBit == 8) && ((nBitsCount & 7) == 0))
	{
		i = nBitsCount >> 3;

		while (i > 0)
		{
			_nValue = (_nValue << 8) | m_pBuffer[m_nBitsRead/8];
			m_nBitsRead += 8;
			i--;
		}
	} else
	{
		while (i > 0)
		{
			j=(m_pBuffer[m_nBitsRead/8] & masks[m_nBit - 1]) >> (m_nBit-1);
			m_nBitsRead++;
			m_nBit--;

			if (!m_nBit)
				m_nBit = 8;

			_nValue = (_nValue << 1) | j;
			i--;
		}
	}
	
	nValue = _nValue;

	return S_OK;
}

HRESULT CBitsBuffer::Read8Bits(INT8 &nValue)
{
	HRESULT hr = S_OK;

	if (m_nSize * 8 - m_nBitsRead < 8)
		return E_PENDING;
	
	INT32 _nValue;
	if (SUCCEEDED(hr = ReadBits(_nValue, 8)))
		nValue = _nValue;

	return hr;
}

HRESULT CBitsBuffer::Read16Bits(INT16 &nValue)
{
	HRESULT hr = S_OK;

	if (m_nSize * 8 - m_nBitsRead < 16)
		return E_PENDING;
	
	INT32 _nValue;
	if (SUCCEEDED(hr = ReadBits(_nValue, 16)))
		nValue = _nValue;

	return hr;
}

HRESULT CBitsBuffer::Read32Bits(INT32 &nValue)
{
	if (m_nSize * 8 - m_nBitsRead < 32)
		return E_PENDING;
	
	return ReadBits(nValue, 32);
}

HRESULT CBitsBuffer::Read64Bits(INT64 &nValue)
{	
	HRESULT hr = S_OK;

	if (m_nSize*  8 - m_nBitsRead < 64)
		return E_PENDING;

	INT32 hiValue, lowValue;
	
	if (FAILED(hr = Read32Bits(hiValue)))
		return hr;

	if (FAILED(hr = Read32Bits(lowValue)))
		return hr;

	((INT32*)&nValue)[0] = lowValue; 
	((INT32*)&nValue)[1] = hiValue;
	
	return hr;
}

HRESULT CBitsBuffer::ReadString(CTBString &sString, const UINT32 nBytesCount)
{
	if (m_nSize*8 - m_nBitsRead < nBytesCount*8)
		return E_PENDING;

	for (UINT i = 0; i < nBytesCount; i++)
	{	
		TCHAR tchTemp;
		Read8Bits((INT8&)tchTemp);

		sString.append(&tchTemp, 1);
	}

	return S_OK;
}
}