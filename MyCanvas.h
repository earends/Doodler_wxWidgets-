#ifndef MYCANVAS_H_INCLUDED
#define MYCANVAS_H_INCLUDED

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


#include <wx/button.h>
#include <wx/statline.h>
#include "wx/overlay.h"
class DoodlerTool;
class MyCanvas: public wxScrolledWindow
{
    public:
        MyCanvas(wxWindow *parent);
        void SetTool(DoodlerTool* tool);


    protected:
        enum
        {

        };
        DoodlerTool* m_tool;
        int startX;
        int startY;
        wxOverlay m_overlay;

    private:
        void OnPaint(wxPaintEvent& event);
        void OnMotion(wxMouseEvent& event);
        void DrawPen(wxMouseEvent& event);
        void DrawEraser(wxMouseEvent& event);
        void OnMouseUp(wxMouseEvent& event);
        void OnMouseDown(wxMouseEvent& event);
        void DrawRectangle();
        void DrawCircle();
        void DrawLine();
        DECLARE_EVENT_TABLE()
};



#endif // MYCANVAS_H_INCLUDED

