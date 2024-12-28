#if !defined(AFX_MEDIT_H__72C3EDF9_D24D_4AE1_BE4D_AEEDC573BEDD__INCLUDED_)
#define AFX_MEDIT_H__72C3EDF9_D24D_4AE1_BE4D_AEEDC573BEDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <afxtempl.h>	// for CArray class
#include <afxadv.h>		// for CSharedFile class


/////////////////////////////////////////////////////////////////////////////
// CmEditChar class
//		Holds one character for the window's text
//		Knows whether this character is masked or static
//		If it's masked it knows the characters allowed

class CmEditChar
{
// Construction
public:
	CmEditChar() { bMasked = false; chValue = 0; };

// Attributes
public:
	CString strAllowedChars;	// if masked, these chars are allowed
	TCHAR chValue;				// the character


	// whether or not this character is masked (or static/false)
	bool Masked() {return bMasked;};
	// sets this character as masked
	void setMasked(bool bIsMasked = true) { bMasked = bIsMasked; };


private:
	bool bMasked;				// wether or not this char is masked


// Implementation
public:
	virtual ~CmEditChar() {};

}; // end class CmEditChar


/////////////////////////////////////////////////////////////////////////////
// CmEdit window
//		A masked edit control that is based on CEdit
//		allows masks to be on a per-character basis, so you set a mask for
//		each character in the control

class CmEdit : public CEdit
{
// Construction
public:
	CmEdit();

// Attributes
public:
	// sets the character used to indicate a prompt (a masked char w/o any current input)
	void SetPrompt(char prompt);


	// if the mask allows lowercase characters, converts them to uppercase
	// this does not implicitly allow uppercase characters to be typed in!
	void ConverToUpper(bool upper = true) { bUpper = upper; bLower = !upper; };
	// if the mask allows uppercase characters, converts them to lowercase
	// this does not implicitly allow lowercase characters to be typed in!
	void ConverToLower(bool lower = true) { bLower = lower; bUpper = !lower; };


	// indicates that GetData() should return the static characters too
	// the class defaults to false
	void CopyNonMasked(bool copyall = true) { bCopyAll = copyall; };

	
	// sets the character to use for passworded text
	void SetPasswordChar(TCHAR ch);
	// returns the current password character
	TCHAR GetPasswordChar() { return chPassword; };


private:
	CArray<CmEditChar, CmEditChar> arrChars;	// the contents of the edit box
	TCHAR chPrompt;								// default prompt character
	TCHAR chPassword;							// password character

	bool bLower, bUpper;						// convert chars to lower, or upper
	bool bCopyAll;								// copy static chars in GetData()

	bool isShift;								// used internally to indicate if the shift key is down
	bool isCtrl;								// used internally to indicate if the ctrl key is down


	// starting at begin, it will find the first masked char and select until the first non-masked char
	void SetMaskedSel(int begin);


// Operations
public:
	// sets the mask to use
	// masked chars are listed between [] brackets
	// character ranges can be indicated using a -, example a-z will allow all chars a to z
	// if you wish to include ] or - in your allowed mask, preceed that char with \\, for example \\] or \\-
	void SetMask(CString mask);


	// returns the contents of the box from start for len chars
	CString GetData(int start = 0, int len = -1);

	// acts as if the user had typed this string into the box, starting at char 0
	void SetData(CString data);


	// overridden: this will generate the window's text using the internal array
	void SetWindowText(LPCTSTR lpszString);

	// overridden: returns the window's text
	void GetWindowText(CString &rString) { rString = GetData(); };
	// overridden: returns the window's text
	void GetWindowText(LPTSTR lpszStringBuf, int nMaxCount) { _tcscpy(lpszStringBuf, GetData(0, nMaxCount)); };

	// overridden: returns the length of the window's text
	int GetWindowTextLength() { return GetData().GetLength(); };



	// selects a range of text
	// if end is less than start, then it will find the first masked char to the left of start and select 0 chars (moves the cursor)
	// if start equals end, it finds the first masked char (moving right) and moves cursor there
	void SetSel(int nStartChar, int nEndChar, BOOL bNoScroll = FALSE);
	
	// replaces the currently selected text with newtext or inserts if no selection
	void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);


	// clears the edit box (resets it using the initial mask)
	void Clear();
	// pastes data into the box as if the user typed each character
	// starts at the current position and replaces characters until the paste is done
	// or the end of the box occurs
	void Paste();
	// copies the select text using GetData() to find the text
	void Copy();
	// copies the select text using GetData() to find the text and then resets masked
	// chars in the selection to the default prompt
	void Cut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CmEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CmEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CmEdit)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CmEdit)
}; // end class CmEdit : public CEdit

/////////////////////////////////////////////////////////////////////////////
void AFXAPI DDX_CmEdit(CDataExchange* pDX, int nIDC, CmEdit& rControl, CString& data);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIT_H__72C3EDF9_D24D_4AE1_BE4D_AEEDC573BEDD__INCLUDED_)
