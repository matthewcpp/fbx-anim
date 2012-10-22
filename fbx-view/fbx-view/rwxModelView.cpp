#include "rwxModelView.hpp"

BEGIN_EVENT_TABLE(rwxModelView , rwxGLView)
	EVT_PAINT(rwxModelView::OnPaint)
	EVT_CHAR(rwxModelView::OnChar)
	EVT_LEFT_DOWN(rwxModelView::OnMouseDown)
	EVT_MOTION(rwxModelView::OnMouseMotion)
END_EVENT_TABLE()

rwxModelView::rwxModelView(rEngine* engine, wxWindow* parent, wxWindowID id)
	:rwxGLView(engine, parent, id)
{
	m_model = NULL;
	m_selectedBone = NULL;
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
			positions.push_back(b->GetGlobalPosition());
			positions.push_back(b->GetChild(c)->GetGlobalPosition());
		}
	}

	m_engine->GraphicsDevice()->DrawLines3(positions, *wxWHITE);
}

void rwxModelView::DrawSkeletonPositions(rBoneList& bones){
	rVertex3Array bonePositions, selectedBonePositions;

	size_t numBones = bones.size();
	for (size_t i = 0; i < numBones; i++){
		if (bones[i] == m_selectedBone)
			selectedBonePositions.push_back(bones[i]->GetGlobalPosition());
		else
			bonePositions.push_back(bones[i]->GetGlobalPosition());
	}

	m_engine->GraphicsDevice()->DrawPoints3(bonePositions, *wxGREEN);
	m_engine->GraphicsDevice()->DrawPoints3(selectedBonePositions, wxColor(0,0,255));
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

void rwxModelView::SetSelectedBone(rBone* bone){
	m_selectedBone = bone;
	Refresh();
}

void rwxModelView::OnChar(wxKeyEvent& event){
	int keycode = event.GetKeyCode();
	bool refresh = false;

	switch (keycode){
	case WXK_UP:
	case 'w':
		m_camera->MoveForward(2.0f);
		refresh = true;
		break;
	case WXK_DOWN:
	case 's':
		m_camera->MoveBackward(2.0f);
		refresh = true;
		break;
	case WXK_LEFT:
	case 'a':
		m_camera->MoveLeft(2.0f);
		refresh = true;
		break;
	case WXK_RIGHT:
	case 'd':
		m_camera->MoveRight(2.0f);
		refresh = true;
		break;
	};

	if (refresh)
		Refresh();
}

void rwxModelView::OnMouseDown(wxMouseEvent& event){
	m_prevPoint = event.GetPosition();
	SetFocus();
}

void rwxModelView::OnMouseMotion(wxMouseEvent& event){
	wxPoint currentPos = event.GetPosition();

	if (event.Dragging()){
		wxPoint delta = currentPos - m_prevPoint;
		float rot = delta.x > 0 ? -1.0f : 1.0f;
		m_camera->IncrementRotation(rVector3(0.0f, rot, 0.0f));
		Refresh();
	}

	m_prevPoint = currentPos;
}