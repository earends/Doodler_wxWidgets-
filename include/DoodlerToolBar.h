#ifndef DOODLERTOOLBAR_H
#define DOODLERTOOLBAR_H


#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "DoodlerApp.h"


#include <wx/button.h>
#include <wx/statline.h>

class DoodlerToolBar: public wxDialog
{
    public:
        DoodlerToolBar();
        virtual ~DoodlerToolBar();

    protected:

    private:
};

#endif // DOODLERTOOLBAR_H
