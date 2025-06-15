#pragma once
#include <vector>
#include "Component.h"

class Component;
class GameObject {
private:
    std::vector<Component*> components;

public:
    ~GameObject() {
        for (Component* comp : components)
            delete comp;    // ���漱�����δ� ����Ҹ��� ȣ���Ҽ�����. ��ü���� ������ include �ʿ�

        components.clear();
    }

    // Class T�� �����ϴ� �Լ� , ���ڱ��� �����Ѵ�.
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) 
    {
        // ������ ������ T�� Component�� ��ӹ��� Ŭ���� ���� Ȯ��
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        // ���ڱ��� �����ϸ鼭 ����
        T* comp = new T(std::forward<Args>(args)...);
        comp->owner = this;
        components.push_back(comp);
        return comp;
    }

    template<typename T>
    std::vector<T*> GetComponents() {
        std::vector<T*> result;
        for (Component* comp : components) {
            // ���൵��(Runtime)�� comp�� ����Ű�� �ν��Ͻ��� RTTI������ �̿��Ͽ� 
            // T�̰ų� T�� �ڽ� Ŭ���� �̸� �ּҸ� �����Ѵ�.
            if (auto casted = dynamic_cast<T*>(comp))
                result.push_back(casted);
        }
        return result;
    }

    template<typename T>
    bool RemoveComponent(T* target) {
        for (auto it = components.begin(); it != components.end(); ++it) {
            if (*it == target) {
                delete* it;
                components.erase(it);
                return true;
            }
        }
        return false;
    }
};