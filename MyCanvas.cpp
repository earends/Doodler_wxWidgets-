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
    EVT_LEFT_DOWN (MyCanvas::OnMouseDown)
    EVT_LEFT_UP (MyCanvas::OnMouseUp)
    EVT_ENTER_WINDOW(MyCanvas::OnEnter)
    EVT_LEAVE_WINDOW(MyCanvas::OnLeave)
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxWindow *parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    eraser = false;
    square = false;
    countMotion = 0;
    pt_count = 0;
}

void MyCanvas::OnMotion(wxMouseEvent &event) {
    countMotion += 1;
    wxClientDC dc(this);
    if (event.Dragging() && !DoodlerTool::addClicked)
        {
            //
            wxPen pen(wxColor(DoodlerTool::redLevel,DoodlerTool::greenLevel,DoodlerTool::blueLevel),4); // red pen of width 1
            dc.SetPen(pen);
            dc.DrawPoint(event.GetPosition());
            dc.SetPen(wxNullPen);

        }
    if (DoodlerTool::addClicked && eraser ) {
        //wxClientDC dc(this);
        dc.SetBrush(wxColor(255,255,255));
        dc.SetPen(wxColor(255,255,255));
        dc.DrawCircle(wxPoint(event.GetX(),event.GetY()),wxCoord(4));
    }

    if (DoodlerTool::addClicked && m_tool->shapeChoice->GetSelection() == 1 && event.Dragging()) {
        dc.DrawRectangle(startX,startY,(event.GetX() - startX),(event.GetY() - startY));
    }
    if (DoodlerTool::addClicked && m_tool->shapeChoice->GetSelection() == 2 && event.Dragging()) {
            dc.DrawCircle(startX,startY,(event.GetX()-startX));
    }



}

void MyCanvas::OnMouseDown(wxMouseEvent& event) {
    if (m_tool->shapeChoice->GetSelection() == 8) {

        if (pt_count == 3) {
            wxSize sze = this->GetSize();

            int index_top_left = 0;
            int index_top_right = 0;
            int index_bott_left = 0;
            int index_bott_right = 0;
            float dist_top_left = sqrt(pt_x[0]^2 + pt_y[0]^2);
            float dist_top_right = sqrt((sze.x-pt_x[0]^2) + pt_y[0]^2);
            float dist_bott_left = sqrt(pt_x[0]^2 + (sze.y-pt_y[0]^2));
            float dist_bott_right = sqrt((sze.x-pt_x[0]^2) + (sze.y-pt_y[0]^2));

            for (int i = 1; i < 4; i ++) {
                int temp_top_left = sqrt(pt_x[i]^2 + pt_y[i]^2);
                int temp_top_right = sqrt((sze.x-pt_x[i]^2) + pt_y[i]^2);
                int temp_bott_left = sqrt(pt_x[i]^2 + (sze.y-pt_y[i]^2));
                int temp_bott_right = sqrt((sze.x-pt_x[i]^2) + (sze.y-pt_y[i]^2));
                if (temp_top_left < dist_top_left) {
                    dist_top_left = temp_top_left;
                    index_top_left = i;
                }
                if (temp_top_right < dist_top_right) {
                    dist_top_right = temp_top_right;
                    index_top_right = i;
                }
                if (temp_bott_left < dist_bott_left) {
                    dist_bott_left = temp_bott_left;
                    index_bott_left = i;
                }
                if (temp_bott_right < dist_bott_right) {
                    dist_bott_right = temp_bott_right;
                    index_bott_right = i;
                }
            }

            int sz_x = pt_x[index_top_right] - pt_x[index_top_left];
            int sz_y =  pt_y[index_bott_left]-pt_y[index_top_left];

            wxClientDC dc(this);
            dc.SetBrush(wxColor(DoodlerTool::redLevel,DoodlerTool::greenLevel,DoodlerTool::blueLevel));
            dc.DrawRectangle(pt_x[index_top_left],pt_y[index_top_left],sz_x,sz_y);
            pt_count = 0;

        } else {


            pt_x[pt_count] = event.GetX();
            pt_y[pt_count] = event.GetY();
            pt_count += 1;
        }
    }

    if (DoodlerTool::addClicked) {
        startX = event.GetX();
        startY = event.GetY();
    }

}

void MyCanvas::OnMouseUp(wxMouseEvent& event) {
    endX = event.GetX();
    endY = event.GetY();
    if (DoodlerTool::addClicked) {
        wxClientDC dc(this);
        dc.SetBrush(wxColor(DoodlerTool::redLevel,DoodlerTool::greenLevel,DoodlerTool::blueLevel));

        if (m_tool->shapeChoice->GetSelection() == 1) {

            dc.DrawRectangle(startX,startY,(endX - startX),(endY - startY));
        }
        if (m_tool->shapeChoice->GetSelection() == 2) {

            //double d = sqrt(((endX-startX)^2) + ((endY-startY)^2));
            dc.DrawCircle(startX,startY,(endX-startX));
        }
        if (m_tool ->shapeChoice->GetSelection() == 3) {
            dc.DrawLine(startX,startY,endX,endY);

        }



    }

}

void MyCanvas::SetTool(DoodlerTool* tool) {
    m_tool = tool;
}

void MyCanvas::OnEnter(wxMouseEvent& event) {
    //convert to black and white
    wxClientDC dc(this);
    if (m_tool->shapeChoice->GetSelection() == 4) {
        wxSize sze = this->GetSize();
        wxBitmap bitmap(sze.x, sze.y);
        //wxClientDC dc(this);
        wxMemoryDC memDC;
        memDC.SelectObject(bitmap);
        memDC.Blit(0, 0, sze.x, sze.y, & dc, 0, 0);
        memDC.SelectObject(wxNullBitmap);
        dc.DrawBitmap(convertToGray(bitmap),wxPoint(0,0),true);
    }
    if (m_tool->shapeChoice->GetSelection() == 5) {
        wxSize sze = this->GetSize();
        wxBitmap bitmap(sze.x, sze.y);
        //wxClientDC dc(this);
        wxMemoryDC memDC;
        memDC.SelectObject(bitmap);
        memDC.Blit(0, 0, sze.x, sze.y, & dc, 0, 0);
        memDC.SelectObject(wxNullBitmap);
        dc.DrawBitmap(convertToNegative(bitmap),wxPoint(0,0),true);
    }
    if (m_tool->shapeChoice->GetSelection() == 6) {
        wxSize sze = this->GetSize();
        wxBitmap bitmap(sze.x, sze.y);
        //wxClientDC dc(this);
        wxMemoryDC memDC;
        memDC.SelectObject(bitmap);
        memDC.Blit(0, 0, sze.x, sze.y, & dc, 0, 0);
        memDC.SelectObject(wxNullBitmap);
        dc.DrawBitmap(convertToRandom(bitmap),wxPoint(0,0),true);
    }
    if (m_tool->shapeChoice->GetSelection() == 7) {
        eraser = true;
    }
    if (m_tool->shapeChoice->GetSelection() == 9) {
        dc.SetBrush(wxColor(DoodlerTool::redLevel,DoodlerTool::greenLevel,DoodlerTool::blueLevel));
        wxSize sze = this->GetSize();

        dc.DrawRectangle(0,0,sze.x,sze.y);
    }


    if (DoodlerTool::clearClicked) {
        //wxClientDC dc(this);
        dc.Clear();
        DoodlerTool::clearClicked = false;
        this->SetBackgroundColour(wxColor(255,255,255));



    }
    if (DoodlerTool::saveClicked) {
        wxSize sze = this->GetSize();
        wxBitmap bitmap(sze.x, sze.y);
        //wxClientDC dc(this);
        wxMemoryDC memDC;
        memDC.SelectObject(bitmap);
        memDC.Blit(0, 0, sze.x, sze.y, & dc, 0, 0);
        memDC.SelectObject(wxNullBitmap);
        b_map = bitmap;
        wxInitAllImageHandlers();
        b_map.ConvertToImage().SaveFile(m_tool->imgSavePath,wxBITMAP_TYPE_BMP);
        DoodlerTool::saveClicked = false;
    }
    if (DoodlerTool::loadClicked) {
        //wxClientDC dc(this);
        dc.DrawBitmap(wxBitmap(m_tool->imgLoadPath, wxBITMAP_TYPE_BMP),wxPoint(0,0),true);
        DoodlerTool::loadClicked = false;
    }
}

void MyCanvas::OnLeave(wxMouseEvent& event) {

}

wxBitmap MyCanvas::convertToGray(wxBitmap bmap) {
    wxImage image = bmap.ConvertToImage();
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
    return wxBitmap(image);

}

wxBitmap MyCanvas::convertToNegative(wxBitmap bmap) {
    wxImage image = bmap.ConvertToImage();
    int w = image.GetWidth(), h = image.GetHeight();
    unsigned char *data = image.GetData();
    int x,y;
    for (y = 0; y < h; y++)
    for (x = 0; x < w; x++)
    {
    long pos = (y * w + x) * 3;
    char g = (char) ((255- data[pos]) + (255 - data[pos+1]) + (255-data[pos+2]));
    data[pos] = data[pos+1] = data[pos+2] = g;
    }
    return wxBitmap(image);
}

wxBitmap MyCanvas::convertToRandom(wxBitmap bmap) {
    wxImage image = bmap.ConvertToImage();
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
    return wxBitmap(image);
}

void MyCanvas::OnClear() {
    wxClientDC dc(this);
    dc.Clear();
}



