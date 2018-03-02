#ifndef MYCANVAS_H_INCLUDED
#define MYCANVAS_H_INCLUDED

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif



#include <wx/button.h>
#include <wx/statline.h>

class MyCanvas: public wxScrolledWindow
{
    public:
        MyCanvas(wxWindow *parent);
        wxCoord startX;
        wxCoord startY;
        wxCoord endX;
        wxCoord endY;
    protected:
        enum
        {

        };


    private:
        void OnMotion(wxMouseEvent& event);
        void OnMouseDown(wxMouseEvent& event);
        void OnMouseUp(wxMouseEvent& event);

        DECLARE_EVENT_TABLE()
};



#endif // MYCANVAS_H_INCLUDED
