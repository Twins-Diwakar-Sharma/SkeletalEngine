#include "HBAORenderer.h"

HBAORenderer::HBAORenderer() : shaderProgram("hbao")
{
    std::uniform_real_distribution<float> randomFloats(0.0, 1.0); // random floats between [0.0, 1.0]
    std::default_random_engine generator;

    unsigned int totalSamples = 16;
    for (unsigned int i = 0; i < totalSamples; ++i)
    {
        Vec3 sample(
            randomFloats(generator) * 2.0 - 1.0, 
            randomFloats(generator) * 2.0 - 1.0, 
            randomFloats(generator)
        );
        float invMag = 1.0f/((float)sample);
        sample  = invMag * sample;
        sample = randomFloats(generator) * sample;
        float scale = (float)i/(float)totalSamples;
        scale = scale*scale;
        float low = 0.1f, high = 1.0f;
        scale = (1.0f - scale)*low + scale*high;
        samples.push_back(sample);  
    }

    std::vector<Vec3> noiseData;
    for (unsigned int i = 0; i < 16; i++)
    {
        noiseData.emplace_back(
            randomFloats(generator) * 2.0 - 1.0, 
            randomFloats(generator) * 2.0 - 1.0, 
            0.0f
        );
    }  

    glGenTextures(1, &noiseTextureID);
    glBindTexture(GL_TEXTURE_2D, noiseTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 4, 4, 0, GL_RGB, GL_FLOAT, &noiseData[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glBindTexture(GL_TEXTURE_2D, 0);

    // shader uniforms
    shaderProgram.mapUniform("gPosition");
    shaderProgram.mapUniform("gNormal");
    shaderProgram.mapUniform("projection");

    shaderProgram.mapUniform("noise");
    shaderProgram.mapUniform("screenSize");

    shaderProgram.mapArrayUniform("samples", samples.size());
    shaderProgram.mapUniform("samplesSize");

    shaderProgram.use();
    shaderProgram.setUniform("samples", samples);
    shaderProgram.setUniform("samplesSize", samples.size());
    shaderProgram.unuse();

    //shaderProgram.mapUniform("kernelSize");
    //shaderProgram.mapUniform("projection");
    //shaderProgram.mapUniform("screenSize");
    //shaderProgram.mapArrayUniform("samples", kernels.size());

    //shaderProgram.use();
   // shaderProgram.setUniform("samples", kernels);
   // shaderProgram.setUniform("noise",2);
   // shaderProgram.unuse();
}

HBAORenderer::~HBAORenderer()
{}

void HBAORenderer::render(Mesh& quad, Framebuffer& deferredShadingFramebuffer)
{
    shaderProgram.use();
    shaderProgram.setUniform("projection", proj::perspective);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, deferredShadingFramebuffer.getColorAttachmentId(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, deferredShadingFramebuffer.getColorAttachmentId(2));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, noiseTextureID);
    shaderProgram.setUniform("gPosition",0);
    shaderProgram.setUniform("gNormal",1);
    shaderProgram.setUniform("noise", 2);
    shaderProgram.setUniform("screenSize", deferredShadingFramebuffer.getWidth(), deferredShadingFramebuffer.getHeight());
    //samples and sampleSize uniforms are already set at constructors
    quad.bind();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, quad.indicesSize(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    quad.unbind();
    shaderProgram.unuse();
}