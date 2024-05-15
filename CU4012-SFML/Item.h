#pragma once
#include "Framework/GameObject.h"
class Item : public GameObject
{
    bool editing; // To track editing mode
public:
    Item();


    void handleInput(float dt) override;
    void update(float dt) override;
    void setEditing(bool edit) {
        editing = edit;
    }
    bool isEditing() {
        return editing;
    }
};

