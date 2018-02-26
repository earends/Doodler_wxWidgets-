#ifndef DOODLERTOOL_H_INCLUDED
#define DOODLERTOOL_H_INCLUDED

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif



#include <wx/button.h>
#include <wx/statline.h>

class DoodlerTool: public wxPanel
{
    public:
        DoodlerTool(wxWindow *parent);


    protected:
        enum
        {

        };


    private:
        DECLARE_EVENT_TABLE()
};



#endif // DOODLERTOOL_H_INCLUDED
