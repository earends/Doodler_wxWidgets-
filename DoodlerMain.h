/***************************************************************
 * Name:      DoodlerMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2018-03-22
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DOODLERMAIN_H
#define DOODLERMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "DoodlerApp.h"


#include <wx/button.h>
#include <wx/statline.h>
#include "DoodlerTool.h"
#include "DoodlerStatus.h"
#include "MyCanvas.h"

class DoodlerDialog: public wxDialog
{
    public:
        DoodlerDialog(wxDialog *dlg, const wxString& title);
        ~DoodlerDialog();

    protected:
        enum
        {

        };

        MyCanvas* m_canvas;
        DoodlerTool* m_tool;
        DoodlerStatus* m_status;
    private:
        void OnClose(wxCloseEvent& event);

        DECLARE_EVENT_TABLE()
};

#endif // DOODLERMAIN_H
