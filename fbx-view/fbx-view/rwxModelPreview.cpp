#include "rwxModelPreview.hpp"

rwxModelPreview::rwxModelPreview(rEngine* engine, wxWindow* parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_engine = engine;

	InitModelPreview();
}

void rwxModelPreview::InitModelPreview(){
	m_view = new rwxModelView(m_engine , this , wxID_ANY);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(m_view , 1 , wxEXPAND);
	SetSizer(mainSizer);
}

void rwxModelPreview::SetModel(rModel* model){
	model->CalculateBoundingBox();

	m_view->SetModel(model);
}