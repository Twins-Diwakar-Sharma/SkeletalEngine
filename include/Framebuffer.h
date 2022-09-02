#ifndef H_FR4M3BUFF3R_H
#define H_FR4M3BUFF3R_H

#include "glad/glad.h"
#include <vector>

#define max_color_attachments 3
class Framebuffer
{
private:
    unsigned int fBuffer;
    unsigned int colorAttachments[max_color_attachments];
    unsigned int depthAttachment;
    std::vector<unsigned int> drawAttachments;
    int num_of_color_attachments;
    int screenWidth, screenHeight;
public:
    Framebuffer();
    ~Framebuffer();
    void setWidth(int);
    void setHeight(int);
    void attachColors(int num_of_color_attachments);
    void attachDepthTexture();
    void attachDepthRender();
    void bindViewport();
    void bindTextures();
    void use();
    void unuse();
};

#endif
