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
            idBtnPtr, // switch between pen and stamp
            idBtnClear, // clear screen
            idBtnSave, // save screen button
            idBtnLoad, // load screen button
            idScrollRed,
            idScrollBlue,
            idScrollGreen,

        };

        //SIZERS
        wxBoxSizer* mainSizer; // overall box
        wxBoxSizer* colorSizer; // rgb scroll bars
        wxBoxSizer* toolSizer; // tool bar for shapes, load/save ..etc
        //buttons
        wxButton* btnPtr;
        wxButton* btnClear;
        wxButton* btnSave;
        wxButton* btnLoad;

        wxStaticLine* divider1;
        wxStaticLine* divider2;

        wxStaticText* redText;
        wxStaticText* blueText;
        wxStaticText* greenText;

        wxScrollBar* redScroll;
        wxScrollBar* greenScroll;
        wxScrollBar* blueScroll;

        int redLevel;
        int blueLevel;
        int greenLevel;

        bool addClicked;

        wxChoice* shapeChoice;


    private:
        void OnScrollRed(wxScrollEvent& event);
        void OnScrollGreen(wxScrollEvent& event);
        void OnScrollBlue(wxScrollEvent& event);
        void OnClear(wxCommandEvent& event);
        void OnAdd(wxCommandEvent& event);

        DECLARE_EVENT_TABLE()
};



#endif // DOODLERTOOL_H_INCLUDED