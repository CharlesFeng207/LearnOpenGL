//
// Created by Charles on 11/22/2020.
//

#ifndef LEARN_OPENGL_GUIMANAGER_H
#define LEARN_OPENGL_GUIMANAGER_H

#include <GLFW/glfw3.h>

class GUIManager {
public:
    static bool Init(GLFWwindow *window);

    static bool Update();

    static bool Draw();

    static bool Destroy();
};


#endif //LEARN_OPENGL_GUIMANAGER_H
