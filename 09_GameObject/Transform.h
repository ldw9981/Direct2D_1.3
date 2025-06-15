#pragma once
struct Transform
{
    D2D1_VECTOR_2F Translation;  // ��ġ
    float Rotation;     // ȸ�� (degree)    
    D2D1_VECTOR_2F Scale;  // ������ 
    bool LocalDirty = true;
    D2D1::Matrix3x2F CachedLocal;
    Transform* Parent = nullptr;
};

