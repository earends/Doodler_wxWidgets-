/***************************************************************
 * Name:      DoodlerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2018-03-22
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__
#include <sstream>
#include "DoodlerMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


BEGIN_EVENT_TABLE(DoodlerDialog, wxDialog)
    EVT_CLOSE(DoodlerDialog::OnClose)

END_EVENT_TABLE()

/**
constructor:
initializes toolbar, canvas, and status bar
sets up pointers to each class
**/
DoodlerDialog::DoodlerDialog(wxDialog *dlg, const wxString &title)
    : wxDialog(dlg, -1, title)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    m_tool = new DoodlerTool(this);
    mainSizer->Add(m_tool);
    m_canvas = new MyCanvas(this);

    m_status = new DoodlerStatus(this);

    m_tool->SetCanvas(m_canvas);
    mainSizer->Add(m_canvas,1,wxGROW,5);
    mainSizer->SetMinSize(wxSize(600,600));
    m_canvas ->SetTool(m_tool);
    m_canvas->SetStatus(m_status);
    m_canvas->SetBackgroundColour(wxColor(255,255,255));
    mainSizer->Add(m_status);

    this->Layout();
    this->SetSizer(mainSizer);
    mainSizer->Fit(this);
    wxMessageBox(wxT("WELCOME!!\nStart Drawing\nClick the DropDown Labeled Pen for more options\nThickness is for pen and eraser"));
    m_canvas->SetCanX(m_canvas->GetSize().GetX());
    m_canvas->SetCanY(m_canvas->GetSize().GetY());
    m_canvas->SetScrollbars(1,1,m_canvas->GetWinBitWidth(),m_canvas->GetWinBitHeight(),0,0);

}


DoodlerDialog::~DoodlerDialog()
{
}

void DoodlerDialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}


