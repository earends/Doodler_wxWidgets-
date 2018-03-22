/***************************************************************
 * Name:      DoodlerApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2018-03-02
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "DoodlerApp.h"
#include "DoodlerMain.h"

IMPLEMENT_APP(DoodlerApp);

bool DoodlerApp::OnInit()
{

    DoodlerDialog* dlg = new DoodlerDialog(0L, _("Evan's Amazing Doodler"));
    dlg->SetIcon(wxICON(aaaa)); // To Set App Icon
    dlg->Show();
    return true;
}
