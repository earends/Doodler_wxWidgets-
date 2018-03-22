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
#include "wx/dcbuffer.h"
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

}

void MyCanvas::SetTool(DoodlerTool* tool) {
    m_tool = tool;
}

void MyCanvas::OnMotion(wxMouseEvent& event) {
    int s = m_tool->shapeChoice->GetSelection();
    if (event.Dragging() && s == 0) {
        DrawPen(event);
    }
    if (event.Dragging() && s == 7) {
        DrawEraser(event);
    }
    if (event.Dragging() && s == 1) {
        wxClientDC dc(this);
        PrepareDC(dc);
        wxDCOverlay overlaydc( m_overlay, &dc );
        overlaydc.Clear();
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        dc.SetPen(color);
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
        dc.DrawRectangle(startX,startY,event.GetX() - startX,event.GetY()-startY);
    }
    if (event.Dragging() && s == 2) {
        wxClientDC dc(this);
        PrepareDC(dc);
        wxDCOverlay overlaydc( m_overlay, &dc );
        overlaydc.Clear();
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        dc.SetPen(color);
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
        dc.DrawCircle(startX,startY,(event.GetX()-startX));
    }


}

void MyCanvas::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
}

void MyCanvas::DrawPen(wxMouseEvent& event) {
        wxClientDC dc(this);
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        if (m_tool->thickChoice->GetSelection() == 0) {
            wxPen pen(color,1); // red pen of width 1
            dc.SetPen(pen);
            dc.DrawPoint(event.GetPosition());
            dc.SetPen(wxNullPen);
        } else {

            wxPen pen(color,1); // red pen of width 1
            dc.SetPen(pen);
            dc.SetBrush(color);
            dc.DrawCircle(wxPoint(event.GetX(),event.GetY()),wxCoord(m_tool->thickChoice->GetSelection()));
            dc.SetPen(wxNullPen);
        }

}

void MyCanvas::DrawEraser(wxMouseEvent& event) {
    wxClientDC dc(this);
        wxColor color = wxColor(255,255,255);
            wxPen pen(color,1); // red pen of width 1
            dc.SetPen(pen);
            dc.SetBrush(color);
            dc.DrawRectangle(event.GetX(),event.GetY(),m_tool->thickChoice->GetSelection() + 5,m_tool->thickChoice->GetSelection() + 5);
            dc.SetPen(wxNullPen);


}

void MyCanvas::OnMouseUp(wxMouseEvent& event) {
    int s = m_tool->shapeChoice->GetSelection();
    wxClientDC dc(this);
    if (s == 1) {

        m_overlay.Reset();
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        dc.SetPen(color);
        dc.SetBrush(color);
        dc.DrawRectangle(startX,startY,event.GetX() - startX,event.GetY()-startY);
    }
    if (s==2) {

        m_overlay.Reset();
        wxColor color = wxColor(m_tool->redLevel,m_tool->greenLevel,m_tool->blueLevel);
        dc.SetPen(color);
        dc.SetBrush(color);
        dc.DrawCircle(startX,startY,(event.GetX()-startX));
    }
    if (s==3) {
        dc.DrawLine(startX,startY,event.GetX(),event.GetY());
    }

}

void MyCanvas::OnMouseDown(wxMouseEvent& event) {
    startX = event.GetX();
    startY = event.GetY();
}

void MyCanvas::DrawRectangle() {


}

void MyCanvas::DrawCircle() {

}

void MyCanvas::DrawLine() {

}





