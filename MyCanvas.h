#ifndef MYCANVAS_H_INCLUDED
#define MYCANVAS_H_INCLUDED

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


#include <wx/button.h>
#include <wx/statline.h>
class DoodlerTool;
class MyCanvas: public wxScrolledWindow
{
    public:
        MyCanvas(wxWindow *parent);
        wxCoord startX;
        wxCoord startY;
        wxCoord endX;
        wxCoord endY;
        void SetTool(DoodlerTool* tool);
        void OnClear();

    protected:
        enum
        {

        };

        DoodlerTool* m_tool;
        wxBitmap b_map;
        bool eraser;
        bool square;
        int countMotion;
        int pt_x[4];
        int pt_y[4];
        int pt_count;
    private:
        void OnMotion(wxMouseEvent& event);
        void OnMouseDown(wxMouseEvent& event);
        void OnMouseUp(wxMouseEvent& event);
        void OnEnter(wxMouseEvent& event);
        void OnLeave(wxMouseEvent& event);

        wxBitmap convertToGray(wxBitmap bmap);
        wxBitmap convertToNegative(wxBitmap bmap);
        wxBitmap convertToRandom(wxBitmap bmap);

        DECLARE_EVENT_TABLE()
};



#endif // MYCANVAS_H_INCLUDED
