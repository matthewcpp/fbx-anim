#ifndef RWX_MODELVIEW_HPP
#define RWX_MODELVIEW_HPP

#include "recondite.hpp"
#include "rEngine.hpp"
#include "rwx/rwxGlView.hpp"

#include <wx/wx.h>

class rwxModelView : public rwxGLView{
public:
	rwxModelView(rEngine* engine, wxWindow* parent, wxWindowID id=wxID_ANY);

	void DrawScene();

	void OnPaint(wxPaintEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif