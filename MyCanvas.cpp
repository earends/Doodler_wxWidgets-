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


BEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_MOTION(MyCanvas::OnMotion)
    EVT_LEFT_DOWN (MyCanvas::OnMouseDown)
    EVT_LEFT_UP (MyCanvas::OnMouseUp)
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxWindow *parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{

}

void MyCanvas::OnMotion(wxMouseEvent &event) {
    if (event.Dragging())
        {
            wxClientDC dc(this);
            wxPen pen(wxColor(DoodlerTool::redLevel,DoodlerTool::greenLevel,DoodlerTool::blueLevel),4); // red pen of width 1
            dc.SetPen(pen);
            dc.DrawPoint(event.GetPosition());
            dc.SetPen(wxNullPen);
        }
}

void MyCanvas::OnMouseDown(wxMouseEvent& event) {
    if (DoodlerTool::addClicked) {
        startX = event.GetX();
    }
}

void MyCanvas::OnMouseUp(wxMouseEvent& event) {
    if (DoodlerTool::addClicked) {
        wxClientDC dc(this);
    }
}


