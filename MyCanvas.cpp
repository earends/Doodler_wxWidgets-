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




BEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_MOTION(MyCanvas::OnMotion)
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxWindow *parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{

}

void MyCanvas::OnMotion(wxMouseEvent &event) {
    if (event.Dragging())
        {
            wxClientDC dc(this);
            wxPen pen(*wxRED,4); // red pen of width 1
            dc.SetPen(pen);
            dc.DrawPoint(event.GetPosition());
            dc.SetPen(wxNullPen);
        }
}

