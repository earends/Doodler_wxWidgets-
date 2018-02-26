/***************************************************************
 * Name:      DoodlerTool.cpp
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

#include "DoodlerTool.h"
#include <sstream>
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


BEGIN_EVENT_TABLE(DoodlerTool, wxPanel)
    EVT_COMMAND_SCROLL(idScrollRed,DoodlerTool::OnScrollRed)
    EVT_COMMAND_SCROLL(idScrollGreen,DoodlerTool::OnScrollGreen)
    EVT_COMMAND_SCROLL(idScrollBlue,DoodlerTool::OnScrollBlue)
    EVT_BUTTON(idBtnClear,DoodlerTool::OnClear)
    EVT_BUTTON(idBtnAdd,DoodlerTool::OnAdd)
    EVT_BUTTON(idBtnSave,DoodlerTool::OnSave)
    EVT_BUTTON(idBtnLoad,DoodlerTool::OnLoad)
END_EVENT_TABLE()

DoodlerTool::DoodlerTool(wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
{
    //init values
    redLevel = 0;
    blueLevel = 0;
    greenLevel = 0;
    addClicked = false;

    mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);


}

void DoodlerTool::OnScrollRed(wxScrollEvent& event) {
    /*
    redLevel = event.GetPosition();
    std::stringstream ss;
    ss << event.GetPosition();
    std::string str = ss.str();

    redText->SetLabel(str);
    */
}

void DoodlerTool::OnScrollGreen(wxScrollEvent& event) {
    /*
    greenLevel = event.GetPosition();
    std::stringstream ss;
    ss << event.GetPosition();
    std::string str = ss.str();

    greenText->SetLabel(str);
    */
}

void DoodlerTool::OnScrollBlue(wxScrollEvent& event) {
    /*
    blueLevel = event.GetPosition();
    std::stringstream ss;
    ss << event.GetPosition();
    std::string str = ss.str();

    blueText->SetLabel(str);
    */
}

void DoodlerTool::OnClear(wxCommandEvent& event) {
    /*
    wxClientDC dc(this);
    dc.Clear();
    */
}

void DoodlerTool::OnAdd(wxCommandEvent& event) {
    /*
    if (addClicked) {
        addClicked = false;
        addBtn->SetLabel(wxT("Add"));
    } else {
        addClicked = true;
        addBtn->SetLabel(wxT("~Add"));
    }
    */

}

void DoodlerTool::OnSave(wxCommandEvent& event) {
    /*
    wxBitmap bitmap(600, 500);
    wxClientDC dc(this);
    wxMemoryDC memDC;
    memDC.SelectObject(bitmap);
    memDC.Blit(0, 0, 600, 500, & dc, 0, 0);
    memDC.SelectObject(wxNullBitmap);
    bmap = bitmap;
    wxInitAllImageHandlers();
    bmap.ConvertToImage().SaveFile("test.jpeg",wxBITMAP_TYPE_JPEG);
    */
}

void DoodlerTool::OnLoad(wxCommandEvent& event) {
    /*
    wxClientDC dc(this);
    dc.DrawBitmap(bmap,wxPoint(0,0),true);
    //heigh is 500 width is 600
    */

}

