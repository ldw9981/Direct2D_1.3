#include "Transform.h"
#include <assert.h>

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
