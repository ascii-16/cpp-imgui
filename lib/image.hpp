#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <imgui_impl_opengl3_loader.h>
#include <iostream>

GLuint LoadPNGTexture(const char *filename) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
    if (!data) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return textureID;
}
