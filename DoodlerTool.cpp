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

int DoodlerTool::redLevel = 0;
int DoodlerTool::greenLevel = 0;
int DoodlerTool::blueLevel = 0;
bool DoodlerTool::addClicked = false;

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



    mainSizer = new wxBoxSizer(wxVERTICAL); // main sizer

    toolSizer = new wxBoxSizer(wxHORIZONTAL); // sizer for tools
    btnClear = new wxButton(this,idBtnClear,wxT("Clear"),wxDefaultPosition,wxDefaultSize);
    toolSizer ->Add(btnClear,wxSizerFlags().Expand().Border());

    btnAdd = new wxButton(this,idBtnAdd,wxT("Add"),wxDefaultPosition,wxDefaultSize);
    toolSizer->Add(btnAdd,wxSizerFlags().Expand().Border());

    wxArrayString shapeChoices;
    shapeChoices.Add("Shapes");
    shapeChoices.Add("Rectangle");
    shapeChoices.Add("Circle");
    shapeChoices.Add("Line");
    shapeChoice = new wxChoice(this, wxID_ANY,  wxDefaultPosition, wxDefaultSize, shapeChoices);
    shapeChoice->SetSelection(0);
    toolSizer->Add(shapeChoice,wxSizerFlags().Expand().Border());
    btnLoad = new wxButton(this,idBtnLoad,wxT("Load"),wxDefaultPosition,wxDefaultSize,wxALIGN_RIGHT);
    toolSizer->Add(btnLoad,wxSizerFlags().Expand().Border());

    btnSave = new wxButton(this,idBtnSave,wxT("Save"),wxDefaultPosition,wxDefaultSize,wxALIGN_RIGHT);
    toolSizer->Add(btnSave,wxSizerFlags().Expand().Border());


    mainSizer->Add(toolSizer,wxSizerFlags().Expand().Border());
    divider1 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL);
    mainSizer->Add(divider1,wxSizerFlags().Expand().Border());

    colorSizer = new wxBoxSizer(wxHORIZONTAL);
    //init dividers
    d3 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxVERTICAL);
    d4 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxVERTICAL);
    d5 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxVERTICAL);
     //add coomponents to event sizer
    redText = new wxStaticText(this,-1,wxT("RED"),wxDefaultPosition,wxDefaultSize);
    greenText = new wxStaticText(this,-1,wxT("GREEN"),wxDefaultPosition,wxDefaultSize);
    blueText = new wxStaticText(this,-1,wxT("BLUE"),wxDefaultPosition,wxDefaultSize);
    redScroll = new wxScrollBar(this,idScrollRed,wxDefaultPosition,wxDefaultSize,wxSB_HORIZONTAL);
    redScroll->SetScrollbar(0,1,255,1);
    greenScroll = new wxScrollBar(this,idScrollGreen,wxDefaultPosition,wxDefaultSize,wxSB_HORIZONTAL);
    greenScroll->SetScrollbar(0,1,255,1);
    blueScroll = new wxScrollBar(this,idScrollBlue,wxDefaultPosition,wxDefaultSize,wxSB_HORIZONTAL);
    blueScroll->SetScrollbar(0,1,255,1);
    //add
    colorSizer->Add(redText,wxSizerFlags().Expand());
    colorSizer->Add(d3,wxSizerFlags().Expand().Border());
    colorSizer->Add(redScroll,wxSizerFlags().Expand());
    colorSizer->Add(greenText,wxSizerFlags().Expand());
    colorSizer->Add(d4,wxSizerFlags().Expand().Border());
    colorSizer->Add(greenScroll,wxSizerFlags().Expand());
    colorSizer->Add(blueText,wxSizerFlags().Expand());
    colorSizer->Add(d5,wxSizerFlags().Expand().Border());
    colorSizer->Add(blueScroll,wxSizerFlags().Expand());

    mainSizer->Add(colorSizer,wxSizerFlags().Expand().Border());
    divider2 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL);
    mainSizer->Add(divider2,wxSizerFlags().Expand().Border());

    this->SetSizer(mainSizer);

    mainSizer->Fit(this);


}

void DoodlerTool::OnScrollRed(wxScrollEvent& event) {

    DoodlerTool::redLevel = event.GetPosition();
    std::stringstream ss;
    ss << event.GetPosition();
    std::string str = ss.str();

    redText->SetLabel(str);

}

void DoodlerTool::OnScrollGreen(wxScrollEvent& event) {

    greenLevel = event.GetPosition();
    std::stringstream ss;
    ss << event.GetPosition();
    std::string str = ss.str();

    greenText->SetLabel(str);

}

void DoodlerTool::OnScrollBlue(wxScrollEvent& event) {

    blueLevel = event.GetPosition();
    std::stringstream ss;
    ss << event.GetPosition();
    std::string str = ss.str();

    blueText->SetLabel(str);

}

void DoodlerTool::OnClear(wxCommandEvent& event) {

    wxClientDC dc(this);
    dc.Clear();

}

void DoodlerTool::OnAdd(wxCommandEvent& event) {

    if (addClicked) {
        addClicked = false;
        btnAdd->SetLabel(wxT("Add"));
    } else {
        addClicked = true;
        btnAdd->SetLabel(wxT("~Add"));
    }


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




