#pragma once

// 
// Class that wraps DirectShow pin object
//
class CDirectShowPin : public CComPtr<IPin>
{
public:
	CDirectShowPin(	void	);
	virtual ~CDirectShowPin(	void	);

	// Assigment operator
	CDirectShowPin &	operator = (IPin* pPin);

	// Reference operator
	CDirectShowPin* operator & ( )	{	return	this;	}

	// Check that pin is connected
	BOOL			IsConnected( void );

	// Check that pin is output pin
	BOOL			IsOutput( void );

	// Check that pin is input pin
	BOOL			IsInput( void );

	// Gets connected pin
	HRESULT	GetConnected( CDirectShowPin	&Pin );

	// Gets connection media type of pin and failed if pin is not connected
	HRESULT	GetMediaType( CMediaType	&MediaType );

	
};
