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
#include "wx/filedlg.h"
#include <wx/wfstream.h>
#include "DoodlerTool.h"
#include "MyCanvas.h"
#include "wx/effects.h"
#include <sstream>
//helper functions




BEGIN_EVENT_TABLE(DoodlerTool, wxPanel)
    EVT_BUTTON(idBtnClear,DoodlerTool::OnClear)
    EVT_COMMAND_SCROLL(idScrollRed,DoodlerTool::OnScrollRed)
    EVT_COMMAND_SCROLL(idScrollGreen,DoodlerTool::OnScrollGreen)
    EVT_COMMAND_SCROLL(idScrollBlue,DoodlerTool::OnScrollBlue)
    EVT_BUTTON(idBtnLoad,DoodlerTool::OnLoad)
    EVT_BUTTON(idBtnSave,DoodlerTool::OnSave)
    EVT_CHOICE(idChoice,DoodlerTool::OnSelect)
END_EVENT_TABLE()

DoodlerTool::DoodlerTool(wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
{
    // set rgb colors
    redLevel = 0;
    greenLevel = 0;
    blueLevel = 0;
    wxSizer *mainSizer = new wxBoxSizer(wxVERTICAL); // main sizer

    toolSizer = new wxBoxSizer(wxHORIZONTAL); // sizer for tools
    btnClear = new wxButton(this,idBtnClear,wxT("Clear"),wxDefaultPosition,wxDefaultSize);
    //choices for thickeness of pen / eraser
    wxArrayString thickChoices;
    thickChoices.Add("1");
    thickChoices.Add("2");
    thickChoices.Add("3");
    thickChoices.Add("4");
    thickChoices.Add("5");
    thickChoice = new wxChoice(this, wxID_ANY,  wxDefaultPosition, wxDefaultSize, thickChoices);
    thickChoice->SetSelection(0);
    toolSizer->Add(thickChoice,wxSizerFlags().Expand().Border());
    // choices for screen effects
    wxArrayString shapeChoices;
    shapeChoices.Add("Pen");
    shapeChoices.Add("Rectangle");
    shapeChoices.Add("Circle");
    shapeChoices.Add("Line");
    shapeChoices.Add("Gray Scale");
    shapeChoices.Add(("Negative"));
    shapeChoices.Add("Random");
    shapeChoices.Add("Eraser");
    shapeChoices.Add(("Paint Can"));
    shapeChoice = new wxChoice(this, idChoice,  wxDefaultPosition, wxDefaultSize, shapeChoices);
    shapeChoice->SetSelection(0);
    toolSizer->Add(shapeChoice,wxSizerFlags().Expand().Border());
    btnLoad = new wxButton(this,idBtnLoad,wxT("Load"),wxDefaultPosition,wxDefaultSize,wxALIGN_RIGHT);
    toolSizer->Add(btnLoad,wxSizerFlags().Expand().Border());

    btnSave = new wxButton(this,idBtnSave,wxT("Save"),wxDefaultPosition,wxDefaultSize,wxALIGN_RIGHT);
    toolSizer->Add(btnSave,wxSizerFlags().Expand().Border());
    toolSizer ->Add(btnClear,wxSizerFlags().Expand().Border());

    mainSizer->Add(toolSizer,wxSizerFlags().Expand().Border());
    divider1 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL);
    mainSizer->Add(divider1,wxSizerFlags().Expand().Border());

    colorSizer = new wxBoxSizer(wxHORIZONTAL);
    //init dividers
    d3 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxVERTICAL);
    d4 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxVERTICAL);
    d5 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxVERTICAL);
     //add coomponents to event sizer
     // DS: Why are these labels in caps?
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

/**
Sets pointer to MyCanvas class
**/
void DoodlerTool::SetCanvas(MyCanvas* canvas) {
    m_canvas = canvas;
}

/**
clears client area of screen on button push
**/
void DoodlerTool::OnClear(wxCommandEvent& event) {
    wxClientDC* clientDC = NULL;

    clientDC = new wxClientDC(m_canvas);


    clientDC->Clear();
    if (clientDC)
        delete clientDC;
    m_canvas->SaveScreen();
}

/**
Change red label to display red color value
**/
void DoodlerTool::OnScrollRed(wxScrollEvent& event) {

    redLevel = event.GetPosition();

    redText->SetLabel(IntToStr(event.GetPosition()));

}

/**
Change green label to display green color value
**/
void DoodlerTool::OnScrollGreen(wxScrollEvent& event) {

    greenLevel = event.GetPosition();
    greenText->SetLabel(IntToStr(event.GetPosition()));

}

/**
Cahnge blue label to display blue color value
**/
void DoodlerTool::OnScrollBlue(wxScrollEvent& event) {

    blueLevel = event.GetPosition();
    blueText->SetLabel(IntToStr(event.GetPosition()));

}

/**
Opens a open file dialog box
loads a desired bitmap file from a selected directory
prints bitmap on screen
activates on load button push
**/
void DoodlerTool::OnLoad(wxCommandEvent& event) {
    wxClientDC dc(m_canvas);
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif");
    wxString defaultDir = wxT("c:\\temp");
    wxString defaultFilename = wxEmptyString;
    wxString path;
    wxFileDialog dialog(this, caption, defaultDir, defaultFilename,wildcard);
    if (dialog.ShowModal() == wxID_OK)
    {
    path = dialog.GetPath();
    int filterIndex = dialog.GetFilterIndex();
    }
    if (path == "") {
        wxMessageBox(wxT("No Path Selected"));
    } else {
        dc.DrawBitmap(wxBitmap(path, wxBITMAP_TYPE_BMP),wxPoint(0,0),true);
        m_canvas->SaveScreen();
    }



}

/**
opens file dialog box
prompts user to pick a name and a path
captures contents of client portion of screen
saves it at desired location and with file name in form of a .bmp
**/
void DoodlerTool::OnSave(wxCommandEvent& event) {
        wxClientDC dc(m_canvas);
        wxFileDialog saveFileDialog(this, _("Save BMP file"), "", "","BMP files (*.bmp)|*.bmp", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_CANCEL)
            return;     // the user changed idea...

        // save the current contents in the file;
        // this can be done with e.g. wxWidgets output streams:
        wxFileOutputStream output_stream(saveFileDialog.GetPath());
        imgSavePath = saveFileDialog.GetPath();
        if (!output_stream.IsOk())
        {
            wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
            return;
        }

        wxSize sze = m_canvas->GetSize();
        wxBitmap bitmap(sze.x, sze.y);
        //wxClientDC dc(this);
        wxMemoryDC memDC;
        memDC.SelectObject(bitmap);
        memDC.Blit(0, 0, sze.x, sze.y, & dc, 0, 0);
        memDC.SelectObject(wxNullBitmap);
        wxInitAllImageHandlers();
        bitmap.ConvertToImage().SaveFile(imgSavePath,wxBITMAP_TYPE_BMP);
}

/**
Switch case to handle different choice commands for the shapeChoice choices
**/
void DoodlerTool::OnSelect(wxCommandEvent& event) {
    switch (event.GetSelection())
    {
        case 2:
            wxMessageBox(wxT("Size your image by dragging left or right"));
            break;
        case 3:
            wxMessageBox(wxT("Your line wont appear as you drag :(\n"));
            break;
        case 4:
            ConvertToGrey();
            break;
        case 5:
            ConvertToNegative();
            break;
        case 6:
            ConvertToRandom();
            break;
        case 8:
            PaintCan();
            break;
        default:
            break;
    }
    m_canvas->SaveScreen();
}

/**
Captures contents of screen
Saves contents into an image file
manipulates image pixels to reflect
a gray scale manipulation
re paints image on screen
**/
void DoodlerTool::ConvertToGrey() {
    wxSize sze = m_canvas->GetSize();
    wxBitmap bitmap(sze.x, sze.y);
    wxClientDC dc(m_canvas);

    wxMemoryDC memDC;
    memDC.SelectObject(bitmap);
    memDC.Blit(0,0,582,455,&dc,0,0);
    memDC.SelectObject(wxNullBitmap);

    wxImage image = bitmap.ConvertToImage();
    double red2Gray = 0.297;
    double green2Gray = 0.589;
    double blue2Gray = 0.114;
    int w = image.GetWidth(), h = image.GetHeight();
    unsigned char *data = image.GetData();
    int x,y;
    for (y = 0; y < h; y++)
    for (x = 0; x < w; x++)
    {
    long pos = (y * w + x) * 3;
    char g = (char) (data[pos]*red2Gray + data[pos+1]*green2Gray + data[pos+2]*blue2Gray);
    data[pos] = data[pos+1] = data[pos+2] = g;
    }
    dc.DrawBitmap(wxBitmap(image),wxPoint(0,0),true);
}

/**
Captures contents of screen
Saves contents into an image file
manipulates image pixels to reflect
a negative manipulation
re paints image on screen
**/
void DoodlerTool::ConvertToNegative() {


    wxSize sze = m_canvas->GetSize();
    wxBitmap bitmap(sze.x-18, sze.y-18);
    wxClientDC dc(m_canvas);

    wxMemoryDC memDC;
    memDC.SelectObject(bitmap);
    memDC.Blit(0,0,582,455,&dc,0,0);
    memDC.SelectObject(wxNullBitmap);


    wxImage image = bitmap.ConvertToImage();
    int w = image.GetWidth(), h = image.GetHeight();
    unsigned char *data = image.GetData();
    int x,y;
    for (y = 0; y < h; y++)
    for (x = 0; x < w; x++)
    {
    long pos = (y * w + x) * 3;
    //char g = (char) (0) + (0) + (0);
    data[pos] = 255 - data[pos];
    data[pos+1] = 255 -data[pos + 1];
    data[pos+2] = 255 - data[pos + 2];
    }
    dc.DrawBitmap(wxBitmap(image),wxPoint(0,0),true);
}

/**
Captures contents of screen
Saves contents into an image file
manipulates image pixels to reflect
a 1-10 random change in r,g,b value
**/
void DoodlerTool::ConvertToRandom() {
    wxSize sze = m_canvas->GetSize();
    wxBitmap bitmap(sze.x, sze.y);
    wxClientDC dc(m_canvas);
    wxMemoryDC memDC;
    memDC.SelectObject(bitmap);
    memDC.Blit(0,0,582,455,&dc,0,0);
    memDC.SelectObject(wxNullBitmap);

    wxImage image = bitmap.ConvertToImage();
    int w = image.GetWidth(), h = image.GetHeight();
    unsigned char *data = image.GetData();
    int x,y,r,g,b;
    for (y = 0; y < h; y++)
    for (x = 0; x < w; x++)
    {
    long pos = (y * w + x) * 3;

    char g = (char) ((r) + (g) + (b));
    data[pos] = data[pos+(rand() % 10)] = data[pos+(rand() % 10)] = g;
    }
    dc.DrawBitmap(wxBitmap(image),wxPoint(0,0),true);
}

/**
Paints a square over client portion of screen
with color based on RGB meter
**/
void DoodlerTool::PaintCan() {
    wxClientDC dc(m_canvas);
    PrepareDC(dc);
    dc.SetBrush(wxColor(redLevel,greenLevel,blueLevel));
    dc.SetPen(*wxTRANSPARENT_PEN);
    wxSize sze = m_canvas->GetSize();
    dc.DrawRectangle(0,0,sze.GetX(),sze.GetY());
}


/**
Helper Function
**/
std::string DoodlerTool::IntToStr(int num) {
    std::stringstream ss;
    ss << num;
    std::string str = ss.str();
    return str;
}
