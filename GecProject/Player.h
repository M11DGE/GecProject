#pragma once
#include "Entity.h"
#include <iostream>
class Player :
    public Entity
{
private:

public:
    void Update();
    void Inputs();
};

