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
        DoodlerTool* m_tool;
        MyCanvas* m_canvas;

        wxStaticText* m_x_text; //

        wxStaticText* m_y_text;
        wxStaticLine *l;



    private:
        std::string IntToStr(int *num);
        DECLARE_EVENT_TABLE()
};




#endif // DOODLERSTATUS_H_INCLUDED
