/***************************************************************
 * Name:      DoodlerMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2018-03-02
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DOODLERMAIN_H
#define DOODLERMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "DoodlerApp.h"
#include "DoodlerTool.h"
#include "MyCanvas.h"

#include <wx/button.h>
#include <wx/statline.h>
class DoodlerDialog: public wxDialog
{
    public:
        DoodlerDialog(wxDialog *dlg, const wxString& title);
        ~DoodlerDialog();

    protected:
        enum
        {

        };
        DoodlerTool *m_tool;
        MyCanvas *m_canvas;

    private:
        void OnClose(wxCloseEvent& event);

        DECLARE_EVENT_TABLE()
};

#endif // DOODLERMAIN_H
