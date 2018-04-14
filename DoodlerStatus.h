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
        ~DoodlerStatus();
        wxStaticText* m_y; // mouse x value
        wxStaticText* m_x; // mouse y value
    protected:




    private:
        wxStaticText* m_x_text;
        wxStaticText* m_y_text;
        wxStaticLine *m_line; // divider line for inbetween canvas-status bar
        DECLARE_EVENT_TABLE()
};




#endif // DOODLERSTATUS_H_INCLUDED
