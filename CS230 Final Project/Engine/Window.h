/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16 spring
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "Vec.h"

namespace CS230
{
    class Window 
    {
    public:
        void Init(std::string windowName);
        void Update();
        void Resize(int newWidth, int newHeight);
        math::ivec2 GetSize();
        void Clear(unsigned int color);
    private:
        math::ivec2 windowSize;
    };
}