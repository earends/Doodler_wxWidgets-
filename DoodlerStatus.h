#ifndef DOODLERSTATUS_H_INCLUDED
#define DOODLERSTATUS_H_INCLUDED


#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/button.h>
#include <wx/statline.h>
#include <sstream>

class MyCanvas;
class DoodlerTool;
class DoodlerStatus: public wxPanel
{
    public:
        DoodlerStatus(wxWindow *parent);
        void SetCanvas(MyCanvas* canvas);
        void SetTool(DoodlerTool* tool);
        wxStaticText* m_y; // mouse x value
        wxStaticText* m_x; // mouse y value
    protected:
        enum
        {

        };

        // DS: Does the status bar need pointers to the tool and canvas?
        // In other words, will the toolbar ever be responsible for
        // updating information in either the tool or the canvas?
        DoodlerTool* m_tool;
        MyCanvas* m_canvas;

        wxStaticText* m_x_text; //

        wxStaticText* m_y_text;

        // DS: Not a great variable name.  You seem to be using the m_
        // convention for class members, so it would at least make sense
        // to follow that.
        wxStaticLine *l;



    private:
        // DS: Why are you taking 'num' by pointer instead of by value?
        std::string IntToStr(int *num);
        DECLARE_EVENT_TABLE()
};




#endif // DOODLERSTATUS_H_INCLUDED
