#include "Transform.h"
#include <assert.h>



void Transform::SetTranslation(float x, float y)
{
	LocalDirty = true;
	Translation.x = x; Translation.y = y;
	MarkWorldDirty();
}

void Transform::SetRotation(float InRotation)
{
	LocalDirty = true;  Rotation = InRotation;
	MarkWorldDirty();
}

void Transform::SetScale(float scaleX, float scaleY)
{
	LocalDirty = true;  Scale.x = scaleX; Scale.y = scaleY;
	MarkWorldDirty();
}

// ������� ������ �����ϸ鼭 ������ �Ұ�
const D2D1::Matrix3x2F& Transform::GetLocalMatrix()
{
	if (LocalDirty)
	{
		//     CachedLocal = D2D1::Matrix3x2F::Scale(Scale.x, Scale.y) *
		//        D2D1::Matrix3x2F::Rotation(Rotation) *
		//       D2D1::Matrix3x2F::Translation(Translation.x, Translation.y);        
		MakeLocalMatrix();
		LocalDirty = false;
	}
	return CachedLocal;
}

// ������� ������ �����ϸ鼭 ������ �Ұ�
const D2D1::Matrix3x2F& Transform::GetWorldMatrix()
{
	if (WorldDirty || LocalDirty)
	{
		CachedWorld = Parent ? GetLocalMatrix() * Parent->GetWorldMatrix() : GetLocalMatrix();
		WorldDirty = false;
	}
	return CachedWorld;
}

void Transform::SetParent(Transform* Target)
{
	if (Parent == Target) // �̹� ������ ����
		return;

	if (Parent != nullptr) // �̹� �θ� ������ �θ𿡼� ����
		Parent->RemoveChild(this);		
	
	Parent = Target; // �θ� �ٲ����.
	
	if (Parent != nullptr )
		Parent->AddChild(this);	//�θ� ������ �߰�

	// �θ� �������ų� ���� �������� �ڽĿ��� World�ٲٶ�� ����
	MarkWorldDirty();
}

void Transform::Reset()
{
	Scale = { 1.0f, 1.0f };
	Rotation = { 0.0f };
	Translation = { 0.0f, 0.0f };
	LocalDirty = true;
	MarkWorldDirty();
}

void Transform::AddTranslation(float x, float y)
{
	LocalDirty = true;
	Translation.x += x;
	Translation.y += y;

	MarkWorldDirty();
}

void Transform::AddRotation(float degree)
{
	LocalDirty = true;
	Rotation += degree;
	
	MarkWorldDirty();
}

void Transform::AddScale(float x,float y)
{
	LocalDirty = true;
	Scale.x += x;
	Scale.y += y;
	
	MarkWorldDirty();
}

void Transform::MakeLocalMatrix()
{
	float s = sinf(Rotation * DEG2RAD);
	float c = cosf(Rotation * DEG2RAD);

	CachedLocal = D2D1::Matrix3x2F(
		c * Scale.x, -s * Scale.y,
		s * Scale.x, c * Scale.y,
		Translation.x, Translation.y
	);
}

void Transform::AddChild(Transform* target)
{
	Children.push_back(target);
}

void Transform::RemoveChild(Transform* target)
{
	for (auto it = Children.begin(); it != Children.end(); ++it)
	{
		if (*it != target)
			continue;

		it = Children.erase(it);
		break;
	}
}

void Transform::MarkWorldDirty()
{
	WorldDirty = true;
	for (auto it = Children.begin(); it != Children.end(); ++it)
	{
		(*it)->MarkWorldDirty();
	}
}
