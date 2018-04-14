/***************************************************************
 * Name:      DoodlerStatus.cpp
 * Purpose:   Code for ToolBar
 * Author:     ()
 * Created:   2018-02-26
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__
#include "wx/filedlg.h"
#include <wx/wfstream.h>
#include "DoodlerStatus.h"
#include "MyCanvas.h"
#include "wx/effects.h"
#include <sstream>
//helper functions


BEGIN_EVENT_TABLE(DoodlerStatus, wxPanel)

END_EVENT_TABLE()

DoodlerStatus::DoodlerStatus(wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
{

    wxBoxSizer * mainSizer = new wxBoxSizer(wxHORIZONTAL);

    m_x_text = new wxStaticText(this,wxID_ANY,wxT("Mouse X: "));

    m_x = new wxStaticText(this,wxID_ANY,wxT("0"),wxDefaultPosition,wxSize(20,20));

    m_y_text = new wxStaticText(this,wxID_ANY,wxT("Mouse Y: "));
    m_y = new wxStaticText(this,wxID_ANY,"0",wxDefaultPosition,wxSize(20,20));

    m_line = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxVERTICAL);
    mainSizer->Add(m_x_text,wxSizerFlags().Expand().Border());
    mainSizer->Add(m_x,wxSizerFlags().Expand().Border());
    mainSizer->Add(m_line,wxSizerFlags().Expand().Border());
    mainSizer->Add(m_y_text,wxSizerFlags().Expand().Border());
    mainSizer->Add(m_y,wxSizerFlags().Expand().Border());
    this->SetSizer(mainSizer);
    mainSizer->Fit(this);
}

DoodlerStatus::~DoodlerStatus() {

}





