/***************************************************************
 * Name:      MyCanvas.cpp
 * Purpose:   Code for Canvas
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

#include "MyCanvas.h"
#include "DoodlerTool.h"
#include "DoodlerStatus.h"
#include "wx/dcbuffer.h"
#include "wx/effects.h"
#include <sstream>
#include <math.h>

BEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_MOTION(MyCanvas::OnMotion)
    EVT_PAINT(MyCanvas::OnPaint)
    EVT_LEFT_UP(MyCanvas::OnMouseUp)
    EVT_LEFT_DOWN(MyCanvas::OnMouseDown)


END_EVENT_TABLE()

MyCanvas::MyCanvas(wxWindow *parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    b_map =  new wxBitmap(600*10,473*10);
    wxMemoryDC memDC;
    memDC.SelectObject(*b_map);
    memDC.SetBackground(*wxWHITE);
    memDC.Clear();
    memDC.SelectObject(wxNullBitmap);
    Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollWinEventHandler(MyCanvas::OnScroll), NULL, this);

}

/**
Sets up pointer to Doodler Tool class
**/
void MyCanvas::SetTool(DoodlerTool* tool) {
    m_tool = tool;

}

/**
Function: On Motion
Description: Handles all motion related functionality
that happens as the user has a mouse over this window
**/
void MyCanvas::OnMotion(wxMouseEvent& event) {

    m_status->m_x->SetLabel(m_tool->IntToStr(event.GetX()));
    m_status->m_y->SetLabel(m_tool->IntToStr(event.GetY()));

    int s = m_tool->shapeChoice->GetSelection();
    //based on DoodlerTool shapechoice - window screen effects
    if (event.Dragging() && s == 0) { // draw pen
        DrawPen(event);

    }
    if (event.Dragging() && s == 7) { // draw eraser
        DrawEraser(event);

    }
    if (event.Dragging() && s == 1) { // draw a square
        wxClientDC dc(this);
        wxDCOverlay overlaydc( m_overlay, &dc ); // store screen into overlay
        overlaydc.Clear(); // clear overlay
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        dc.SetPen(color);
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
        dc.DrawRectangle(startX,startY,event.GetX() - startX,event.GetY()-startY); // continuously draw square

    }
    if (event.Dragging() && s == 2) {
        wxClientDC dc(this);
        wxDCOverlay overlaydc( m_overlay, &dc );
        overlaydc.Clear();
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        dc.SetPen(color);
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
        dc.DrawCircle(startX,startY,(event.GetX()-startX));

    }


}

/**
Prepare screen
**/
void MyCanvas::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    PrepareDC(dc);
}

/**
Does drawing to reflect that of a pen dragged over a peice of paper
Draws an actual wxPen if the thickenss is a 1
Then enlarged circles based on thickness user has desired
**/
void MyCanvas::DrawPen(wxMouseEvent& event) {
        wxClientDC dc(this);
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        if (m_tool->thickChoice->GetSelection() == 0) {
            wxPen pen(color,1); // red pen of width 1
            dc.SetPen(pen);
            dc.DrawPoint(event.GetPosition());
            dc.SetPen(wxNullPen);
        } else {
            wxMemoryDC memDC;
            memDC.SelectObject(*b_map);
            memDC.SetPen(color);
            memDC.DrawCircle(wxPoint(GetScrollPos(wxHORIZONTAL)*4,GetScrollPos(wxVERTICAL)),wxCoord(m_tool->thickChoice->GetSelection()));
            memDC.SelectObject(wxNullBitmap);
            dc.SetPen(color);
            dc.SetBrush(color);
            dc.DrawCircle(wxPoint(event.GetX(),event.GetY()),wxCoord(m_tool->thickChoice->GetSelection()));
        }
        SaveScreen(); // save to bitmap

}

/**
Draws a white square continuously over the screen to simulate eraser
**/
void MyCanvas::DrawEraser(wxMouseEvent& event) {
            wxClientDC dc(this);

            wxColor color = wxColor(255,255,255);
            wxPen pen(color,1); // red pen of width 1
            dc.SetPen(pen);
            dc.SetBrush(color);
            dc.DrawRectangle(event.GetX(),event.GetY(),m_tool->thickChoice->GetSelection() + 5,m_tool->thickChoice->GetSelection() + 5);
            dc.SetPen(wxNullPen);


}

/**
Handles final drawing of square,circle, and line
after the user has finished sizing and positioning
**/
void MyCanvas::OnMouseUp(wxMouseEvent& event) {
    int s = m_tool->shapeChoice->GetSelection();
    wxClientDC dc(this);
    //rectangle

    if (s == 1) {

        m_overlay.Reset();
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        dc.SetPen(color);
        dc.SetBrush(color);
        dc.DrawRectangle(startX,startY,event.GetX() - startX,event.GetY()-startY);
        SaveScreen(); // save to bitmap
    }
    //circle
    if (s==2) {

        m_overlay.Reset();
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        dc.SetPen(color);
        dc.SetBrush(color);
        dc.DrawCircle(startX,startY,(event.GetX()-startX));
        SaveScreen(); // save to bitmap
    }
    if (s==3) {
        dc.DrawLine(startX,startY,event.GetX(),event.GetY());
        SaveScreen(); // save to bitmap
    }


}

/**
Grabs the initial coordinates of the user upon pressing left click
**/
void MyCanvas::OnMouseDown(wxMouseEvent& event) {
    SaveScreen(); // save to bitmap
    startX = event.GetX();
    startY = event.GetY();
}

/**
If initial bitmap is loaded draw it on screen
**/
void MyCanvas::OnDraw(wxDC& dc) {

    wxMessageBox(wxT("hello"));
    PrepareDC(dc);
    dc.DrawBitmap(*b_map, 0, 0, false);
}

/**
Redraw bitmap on to screen every time user scrolls
**/
void MyCanvas::OnScroll(wxScrollWinEvent& event) {
    wxClientDC dc(this);
    PrepareDC(dc);
    dc.DrawBitmap(*b_map,0,0);
}

/**
Captures contents of screen and paints them on to
a stored bitmap in the correct position based on size of screen
**/
void MyCanvas::SaveScreen() {
        wxMemoryDC memDC;
        wxClientDC dc(this);
        memDC.SelectObject(*b_map);
        ///1st num, x,y on bitmap, last two x,y on dc
        memDC.Blit(GetScrollPos(wxHORIZONTAL),GetScrollPos(wxVERTICAL),winX-18,winY-18,&dc,0,0);
        memDC.SelectObject(wxNullBitmap);
        wxInitAllImageHandlers();

}


// Sets pointer to Doodler Status
void MyCanvas::SetStatus(DoodlerStatus* status) {
    m_status = status;
}





