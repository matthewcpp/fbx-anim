#include "rwxModelView.hpp"

BEGIN_EVENT_TABLE(rwxModelView , rwxGLView)
	EVT_PAINT(rwxModelView::OnPaint)
END_EVENT_TABLE()

rwxModelView::rwxModelView(rEngine* engine, wxWindow* parent, wxWindowID id)
	:rwxGLView(engine, parent, id)
{

}

void rwxModelView::OnPaint(wxPaintEvent& event){
	wxPaintDC(this);
	DrawScene();
}

void rwxModelView::DrawScene(){
	PrepareToDraw();

	SwapBuffers();
}
