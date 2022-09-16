#include "Framebuffer.h"

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, &fBuffer);
}

Framebuffer::~Framebuffer()
{}

void Framebuffer::attachColorTexture(int internalFormat, int texelFormat)
{
     glBindFramebuffer(GL_FRAMEBUFFER, fBuffer);
    int i = num_of_color_attachments;
    glGenTextures(1, &colorAttachments[i]);
    glBindTexture(GL_TEXTURE_2D, colorAttachments[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, screenWidth, screenHeight, 0, texelFormat, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachments[i], 0);
    num_of_color_attachments++;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::setDrawBuffers()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fBuffer);
    if(num_of_color_attachments > 0)
    {
        unsigned int* drawAttachments = new unsigned int[num_of_color_attachments];
        for(int i=0; i<num_of_color_attachments; i++)
            drawAttachments[i] = GL_COLOR_ATTACHMENT0 + i;
        glDrawBuffers(num_of_color_attachments, drawAttachments);
        delete [] drawAttachments;
    }
    else
    {
        glDrawBuffer(GL_NONE);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Framebuffer::attachDepthTexture()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fBuffer);
    glGenTextures(1, &depthAttachment);
    glBindTexture(GL_TEXTURE_2D, depthAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screenWidth, screenHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachDepthRender()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fBuffer);
    glGenRenderbuffers(1, &depthAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, depthAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, screenWidth, screenHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthAttachment);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bindViewport()
{
    glViewport(0, 0, screenWidth, screenHeight);
}

void Framebuffer::bindAllTextures()
{
    for(int i=0; i<num_of_color_attachments; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, colorAttachments[i]);
    }
}

unsigned int Framebuffer::getColorAttachmentId(unsigned int index)
{
    return colorAttachments[index];
}

void Framebuffer::setWidth(int width)
{
    screenWidth = width;
}

void Framebuffer::setHeight(int height)
{
    screenHeight = height;
}

void Framebuffer::use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fBuffer);
}

void Framebuffer::unuse()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}