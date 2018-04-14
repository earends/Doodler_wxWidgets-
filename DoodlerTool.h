#ifndef DOODLERTOOL_H_INCLUDED
#define DOODLERTOOL_H_INCLUDED

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif




#include <wx/button.h>
#include <wx/statline.h>
class MyCanvas;
class Common;
class DoodlerTool: public wxPanel
{
    public:
        DoodlerTool(wxWindow *parent);
        ~DoodlerTool();
        void SetCanvas(MyCanvas* canvas);
        int redLevel;
        int blueLevel;
        int greenLevel;

        int GetShapeChoice() {return shapeChoice->GetCurrentSelection();};
        int GetThickChoice() {return thickChoice->GetCurrentSelection();};


    protected:
        enum
        {
            idBtnAdd, // switch between pen and stamp
            idBtnClear, // clear screen
            idBtnSave, // save screen button
            idBtnLoad, // load screen button
            idScrollRed,
            idScrollBlue,
            idScrollGreen,
            idChoice,
        };
        Common *m_common;
        MyCanvas* m_canvas;
        //SIZERS
        wxBoxSizer* mainSizer; // overall box
        wxBoxSizer* colorSizer; // rgb scroll bars
        wxBoxSizer* toolSizer; // tool bar for shapes, load/save ..etc
        //buttons
        wxButton* btnAdd;
        wxButton* btnClear;
        wxButton* btnSave;
        wxButton* btnLoad;

        wxStaticLine* divider1;
        wxStaticLine* divider2;

        wxStaticLine* d3;
        wxStaticLine* d4;
        wxStaticLine* d5;

        wxStaticText* redText;
        wxStaticText* blueText;
        wxStaticText* greenText;




        wxScrollBar* redScroll;
        wxScrollBar* greenScroll;
        wxScrollBar* blueScroll;

    private:
        void OnScrollRed(wxScrollEvent& event);
        void OnScrollGreen(wxScrollEvent& event);
        void OnScrollBlue(wxScrollEvent& event);
        void OnClear(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnLoad(wxCommandEvent& event);
        void OnSelect(wxCommandEvent& event);
        void ConvertToGrey();
        void ConvertToNegative();
        void ConvertToRandom();
        void PaintCan();
        wxChoice* shapeChoice;
        wxChoice* thickChoice;


        DECLARE_EVENT_TABLE()
};



#endif // DOODLERTOOL_H_INCLUDED

