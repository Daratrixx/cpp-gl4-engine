
#include "FrameBuffer.h"

FrameBuffer_Multipass::FrameBuffer_Multipass() : FrameBuffer() {
}

FrameBuffer_Multipass::~FrameBuffer_Multipass() {
}

bool FrameBuffer_Multipass::load() {
    clear();

    // frame buffer
    glGenFramebuffers(1, &m_idFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_idFrameBuffer);

    // depth buffer
    glGenRenderbuffers(1, &m_idDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_idDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // color buffers
    addColorBuffer(m_width, m_height); // COLOR
    addColorBuffer(m_width, m_height); // NORMAL
    addColorBuffer(m_width, m_height); // EMISSION
    for (unsigned int i = 0; i < m_colorBufferCount; i++) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_colorBuffer[i]->getID(), 0);
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_idDepthBuffer);

    // unlock
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // check error
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        clear();
        std::cout << "Erreur : le FBO est mal construit" << std::endl;
        return false;
    }

    std::cout << "FrameBuffer ok" << std::endl;
    return true;
}
