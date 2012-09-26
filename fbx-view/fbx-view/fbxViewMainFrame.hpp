#ifndef FBXVIEW_MAINFRAME_HPP
#define FBXVIEW_MAINFRAME_HPP

#include "rwx/rwxEngine.hpp"

#include "rwxModelPreview.hpp"

#include <wx/wx.h>

class fbxViewMainFrame : public wxFrame{
public:
	fbxViewMainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize);
	~fbxViewMainFrame();
private:
	void OnFileExit(wxCommandEvent& event);

private:
	void InitFrame();
	void InitMenuBar();

	DECLARE_EVENT_TABLE()

	rwxModelPreview* m_preview;
	rwxEngine* m_engine;
};

#endif