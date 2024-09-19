module rendertarget;

import std.stdio;

import bindbc.sdl;
import bindbc.opengl;

/// 3D Objects
struct RenderTarget{
    GLuint mHandle;
    uint mWidth;
    uint mHeight;

    this(uint width, uint height){
        // TODO: May want to consider some assertion if the width an height of the framebuffer are not
        //       the same a a window. We could otherwise 'stretch' the framebuffer to fit if we needed.
        mWidth = width;
        mHeight = height;

        // Generate a framebuffer
        glGenFramebuffers(1, &mHandle);
        glBindFramebuffer(GL_FRAMEBUFFER,mHandle);

        // Create a Texture that we'll draw to
        GLuint renderedTexture;
        glGenTextures(1, &renderedTexture);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, null);
        // TODO: Verify that it is important to use a poor filtering method so we get the exact values back
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Optional Depth Buffer
        GLuint depthrenderbuffer;
        glGenRenderbuffers(1, &depthrenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

        // Configure framebuffer
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

        // Set the list of draw buffers
        const GLenum[1] DrawBuffers = [GL_COLOR_ATTACHMENT0];
        glDrawBuffers(1, DrawBuffers.ptr);

        // Almost always a good idea to check framebuffer status
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            writeln("error with glframebuffer not being complete!");
        }
    }

	// Select the current framebuffer
    void Bind(){
        glBindFramebuffer(GL_FRAMEBUFFER, mHandle);
        glViewport(0,0,mWidth, mHeight);
    }

}
