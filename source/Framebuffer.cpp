#include "Framebuffer.h"

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, &fBuffer);
}

Framebuffer::~Framebuffer()
{}

void Framebuffer::attachColors(int num_of_color_attachments)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fBuffer);
    for(unsigned int i = 0; i<num_of_color_attachments; i++)
    {
        glGenTextures(1, &colorAttachments[i]);
        glBindTexture(GL_TEXTURE_2D, colorAttachments[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachments[i], 0);
        drawAttachments.push_back(GL_COLOR_ATTACHMENT0 + i);
    }

    if(num_of_color_attachments > 0)
        glDrawBuffers(num_of_color_attachments, &drawAttachments[0]);
    else
        glDrawBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    this->num_of_color_attachments = num_of_color_attachments;
}

void Framebuffer::attachDepthTexture()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fBuffer);
    glGenTextures(1, &depthAttachment);
    glBindTexture(GL_TEXTURE_2D, depthAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screenWidth, screenHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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

void Framebuffer::bindTextures()
{
    for(int i=0; i<num_of_color_attachments; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, colorAttachments[i]);
    }
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