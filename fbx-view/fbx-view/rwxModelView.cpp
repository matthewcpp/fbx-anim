#include "rwxModelView.hpp"

BEGIN_EVENT_TABLE(rwxModelView , rwxGLView)
	EVT_PAINT(rwxModelView::OnPaint)
END_EVENT_TABLE()

rwxModelView::rwxModelView(rEngine* engine, wxWindow* parent, wxWindowID id)
	:rwxGLView(engine, parent, id)
{
	m_model = NULL;
}

void rwxModelView::OnPaint(wxPaintEvent& event){
	wxPaintDC(this);
	DrawScene();
}

void rwxModelView::DrawScene(){

	PrepareToDraw();

	if (m_model){
		DrawModelBox();
		DrawModelSkeleton();
	}

	SwapBuffers();
}

void rwxModelView::DrawModelBox(){
	rAlignedBox3 b = m_model->BoundingBox();
	m_engine->GraphicsDevice()->DrawWireBox(b, *wxRED);
}

void rwxModelView::DrawModelSkeleton(){
	rSkeleton* skeleton = m_model->GetSkeleton();
	if (skeleton){
		rBoneList bones;
		skeleton->GetBones(bones);
		DrawSkeletonPositions(bones);
		DrawSkeletonBones(bones);
	}
}

void rwxModelView::DrawSkeletonBones(rBoneList& bones){
	rVertex3Array positions;
	rBone* b = NULL;

	for (size_t i = 0; i < bones.size(); i++){
		b = bones[i];
		
		for (size_t c = 0; c < b->NumChildren(); c++){
			positions.push_back(b->m_initialPosition);
			positions.push_back(b->GetChild(c)->m_initialPosition);
		}
	}

	m_engine->GraphicsDevice()->DrawLines3(positions, *wxWHITE);
}

void rwxModelView::DrawSkeletonPositions(rBoneList& bones){
	rVertex3Array positions;

	size_t numBones = bones.size();
	for (size_t i = 0; i < numBones; i++)
		positions.push_back(bones[i]->m_initialPosition);

	m_engine->GraphicsDevice()->DrawPoints3(positions, *wxGREEN);
}

void rwxModelView::CalculateCameraDefaultPosition(const rAlignedBox3& box){
	//todo this is just basic now...
	rVector3 center = box.Center();
	m_camera->SetPosition(rVector3(center.x, center.y, box.Depth() * 3.0f));
}

void rwxModelView::SetModel(rModel* model){
	m_model = model;

	if (m_model){
		rAlignedBox3 b = m_model->BoundingBox();
		CalculateCameraDefaultPosition(b);
	}
	else{
		m_camera->SetPosition(rVector3::ZeroVector);
	}

	Refresh();
}
