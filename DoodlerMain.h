/***************************************************************
 * Name:      DoodlerMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2018-02-26
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DOODLERMAIN_H
#define DOODLERMAIN_H
#include "DoodlerTool.h"
#include "MyCanvas.h"
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "DoodlerApp.h"


#include <wx/button.h>
#include <wx/statline.h>
class DoodlerDialog: public wxDialog
{
    public:
        DoodlerDialog(wxDialog *dlg, const wxString& title);
        ~DoodlerDialog();

        void OnClose(wxCloseEvent& event);
    protected:
        enum
        {

        };
        DoodlerTool *m_tool;
        MyCanvas *m_canvas;

    private:


        DECLARE_EVENT_TABLE()
};

#endif // DOODLERMAIN_H
