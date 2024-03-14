module rendertarget;

import std.stdio;
import glad.gl.all;
import glad.gl.loader;

/// 3D Objects
struct RenderTarget{
    GLuint handle;
    uint mWidth;
    uint mHeight;

    this(uint width, uint height){
        mWidth = width;
        mHeight = height;

        // Generate a framebuffer
        glGenFramebuffers(1, &handle);
        glBindFramebuffer(GL_FRAMEBUFFER,handle);

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

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            writeln("error with glframebuffer not being complete!");
        }
    }

    void Bind(){
        glBindFramebuffer(GL_FRAMEBUFFER, handle);
        glViewport(0,0,mWidth, mHeight);
    }

}
