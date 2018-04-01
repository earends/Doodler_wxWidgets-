#ifndef DOODLERTOOL_H_INCLUDED
#define DOODLERTOOL_H_INCLUDED

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif




#include <wx/button.h>
#include <wx/statline.h>
class MyCanvas;
class DoodlerTool: public wxPanel
{
    public:
        DoodlerTool(wxWindow *parent);
        void SetCanvas(MyCanvas* canvas);

        // DS: Any time you have a public variable, you are telling users
        // of your class that they should feel free to change the variables
        // as much as they want.
        wxChoice* shapeChoice;
        wxChoice* thickChoice;
        wxString imgLoadPath;
        wxString imgSavePath;
        int redLevel;
        int blueLevel;
        int greenLevel;

        // DS: Functions like this shouldn't be part of any specific class,
        // especially if you have multiple places where you have the same
        // function implemented.  I usually have functions like this in a
        // header/cpp file named common.cpp and common.h, and I don't have
        // them as part of a class because it really doesn't make sense
        std::string IntToStr(int num);

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

        // DS: Are you using the m_ convention for local variables or not?
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

        DECLARE_EVENT_TABLE()
};



#endif // DOODLERTOOL_H_INCLUDED

