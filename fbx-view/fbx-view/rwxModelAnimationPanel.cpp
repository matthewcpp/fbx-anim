#include "rwxModelAnimationPanel.hpp"

rwxModelAnimationPanel::rwxModelAnimationPanel(wxWindow* window, wxWindowID id)
	:wxPanel(window, id)
{
	m_model = NULL;
	
	InitAnimPanel();
}

void rwxModelAnimationPanel::SetModel(rModel* model){
	m_model = model;

	m_animationSelector->Clear();

	if (m_model){
		rSkeleton* skeleton = m_model->GetSkeleton();
		
		if (skeleton && skeleton->NumAnimations()){
			rArrayString animNames;
			skeleton->GetAnimationNames(animNames);
			m_animationSelector->Append(animNames);
		}
	}
}

void rwxModelAnimationPanel::InitAnimPanel(){
	m_animationSelector = new wxChoice(this, rwxModelAnimationPanel::rwxANIM_ANIMATION_SELECTOR);
	m_playButton = new wxBitmapButton(this, rwxModelAnimationPanel::rwxANIM_PLAY_BUTTON, wxBitmap("content/play.png", wxBITMAP_TYPE_PNG));
	m_pauseButton = new wxBitmapButton(this, rwxModelAnimationPanel::rwxANIM_PAUSE_BUTTON, wxBitmap("content/pause.png", wxBITMAP_TYPE_PNG));	
	m_stopButton = new wxBitmapButton(this, rwxModelAnimationPanel::rwxANIM_STOP_BUTTON, wxBitmap("content/stop.png", wxBITMAP_TYPE_PNG));

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	mainSizer->Add(m_animationSelector,0,wxLEFT, 5);
	mainSizer->Add(m_playButton,0,wxLEFT, 5);
	mainSizer->Add(m_pauseButton,0,wxLEFT, 5);
	mainSizer->Add(m_stopButton,0,wxLEFT, 5);

	SetSizer(mainSizer);
}

wxString rwxModelAnimationPanel::GetSelectedAnimation() const{
	return m_animationSelector->GetStringSelection();
}