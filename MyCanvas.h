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


    protected:
        enum
        {

        };


    private:
        void OnMotion(wxMouseEvent& event);
        DECLARE_EVENT_TABLE()
};



#endif // MYCANVAS_H_INCLUDED
