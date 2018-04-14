#ifndef MYCANVAS_H_INCLUDED
#define MYCANVAS_H_INCLUDED

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


#include <wx/button.h>
#include <wx/statline.h>
#include "wx/overlay.h"
class DoodlerTool;
class DoodlerStatus;
class Common;
class MyCanvas: public wxScrolledWindow
{
    public:
        MyCanvas(wxWindow *parent);
        ~MyCanvas();
        void SetTool(DoodlerTool* tool);
        void SetStatus(DoodlerStatus* status);
        void SetCanX(int x) {winX = x;}; // set window size var
        void SetCanY(int y) {winY = y;}; // set window size var
        int GetWinWidth() {return winX;};
        int GetWinHeight() {return winY;};
        int GetWinBitWidth() {return bitmapWidth;};
        int GetWinBitHeight() {return bitmapHeight;};
        int GetAdjustedWidth() {return winX - 18;}; //acount for scroll bar
        int GetAdjustedHeight() {return winY-18;};
        void SaveScreen();
        wxBitmap *b_map;


    protected:
        enum
        {

        };
        DoodlerTool* m_tool;
        DoodlerStatus* m_status;
        Common * m_common;
        int startX; // start of mouse drag y
        int startY; // start of mouse drag y
        wxOverlay m_overlay; // allows square outline
        int winX; //600
        int winY; //473



    private:
        void OnPaint(wxPaintEvent& event);
        void OnMotion(wxMouseEvent& event);
        void DrawPen(wxMouseEvent& event);
        void DrawEraser(wxMouseEvent& event);
        void OnMouseUp(wxMouseEvent& event);
        void OnMouseDown(wxMouseEvent& event);
        void OnDraw(wxDC& dc);
        void OnScroll(wxScrollWinEvent& event);
        const int bitmapHeight = 4730;
        const int bitmapWidth = 6000;
        void DrawRectangle (wxMouseEvent& event);
        void DrawCircle (wxMouseEvent& event);




        DECLARE_EVENT_TABLE()
};



#endif // MYCANVAS_H_INCLUDED

