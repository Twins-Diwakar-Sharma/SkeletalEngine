#ifndef H_FR4M3BUFF3R_H
#define H_FR4M3BUFF3R_H

#include "glad/glad.h"
#include <vector>

#define max_color_attachments 6
class Framebuffer
{
private:
    unsigned int fBuffer;
    unsigned int colorAttachments[max_color_attachments];
    unsigned int depthAttachment;
    int num_of_color_attachments=0;
    int screenWidth, screenHeight;
public:
    Framebuffer();
    ~Framebuffer();
    void setWidth(int);
    void setHeight(int);
    void attachDepthTexture();
    void attachDepthRender();
    void bindViewport();
    void bindAllTextures();
    unsigned int getColorAttachmentId(unsigned int index);
    void use();
    void unuse();

    void setDrawBuffers();
    void attachColorTexture(int internalFormat, int texelFormat);
};

#endif
