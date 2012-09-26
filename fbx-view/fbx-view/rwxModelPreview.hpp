#ifndef RWX_MODELPREVIEW_HPP
#define RWX_MODELPREVIEW_HPP

#include "recondite.hpp"
#include "rEngine.hpp"

#include "rwxModelView.hpp"

#include <wx/wx.h>

class rwxModelPreview : public wxPanel {
public:
	rwxModelPreview(rEngine* engine, wxWindow* parent, wxWindowID id=wxID_ANY);

private:
	void InitModelPreview();

private:
	rwxModelView* m_view;
	rEngine* m_engine;
};

#endif