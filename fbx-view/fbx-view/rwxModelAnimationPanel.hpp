#ifndef RWX_MODELANIMATIONPANEL_HPP
#define RWX_MODELANIMATIONPANEL_HPP

#include "rTypes.hpp"

#include <wx/wx.h>

#include "rModel.hpp"

class rwxModelAnimationPanel : public wxPanel{
public:
	rwxModelAnimationPanel(wxWindow* window, wxWindowID id);

	void SetModel(rModel* model);
	wxString GetSelectedAnimation() const;

private:

	void InitAnimPanel();

private:
	rModel* m_model;

	wxChoice* m_animationSelector;
	wxButton* m_playButton;
	wxButton* m_pauseButton;
	wxButton* m_stopButton;

public:
	enum{
		rwxANIM_PLAY_BUTTON = 7777,
		rwxANIM_STOP_BUTTON,
		rwxANIM_PAUSE_BUTTON,
		rwxANIM_ANIMATION_SELECTOR
	};
};

#endif