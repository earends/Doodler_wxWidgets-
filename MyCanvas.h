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
class MyCanvas: public wxScrolledWindow
{
    public:
        MyCanvas(wxWindow *parent);
        void SetTool(DoodlerTool* tool);
        void SetStatus(DoodlerStatus* status);
        void SetCanX(int x) {winX = x;}; // set window size var
        void SetCanY(int y) {winY = y;}; // set window size var


        int winX; //600
        int winY; //473
        void SaveScreen();
        wxBitmap *b_map;

    protected:
        enum
        {

        };
        DoodlerTool* m_tool;
        DoodlerStatus* m_status;
        int startX; // start of mouse drag y
        int startY; // start of mouse drag y
        wxOverlay m_overlay; // allows square outline



    private:
        void OnPaint(wxPaintEvent& event);
        void OnMotion(wxMouseEvent& event);
        void DrawPen(wxMouseEvent& event);
        void DrawEraser(wxMouseEvent& event);
        void OnMouseUp(wxMouseEvent& event);
        void OnMouseDown(wxMouseEvent& event);
        void OnDraw(wxDC& dc);
        void OnScroll(wxScrollWinEvent& event);



        DECLARE_EVENT_TABLE()
};



#endif // MYCANVAS_H_INCLUDED

