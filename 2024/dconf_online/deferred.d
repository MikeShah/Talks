module deferred;
// Hello world
// dmd glfw.d deferred.d shader.d triangleOBJect3d.d ./glad/gl/*.d -L-L/usr/local/lib -L-lglfw3 -of=prog
import std.stdio;
import glad.gl.all;
import glad.gl.loader;

import glfw;
import shader;
import object3d;
import rendertarget;

Globals g;

struct Globals{

    Shader basicShader;
    Shader renderTargetShader;
    Object3D triangleOBJ;
	Object3D screenQuad;

	RenderTarget renderTarget;

    GLFWwindow* window;
    int screenWidth = 640;
    int screenHeight = 480;
}

/// Safer way to work with global state
/// module constructors
shared static this(){
    // Initialize glfw
    if(!glfwInit()){
        writeln("glfw failed to initialize");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    g.window = glfwCreateWindow(g.screenWidth,g.screenHeight,"DConf Online 2024",null,null);
    glfwMakeContextCurrent(g.window);

    // Setup extensions
    if(!glad.gl.loader.gladLoadGL()){    
        writeln("Some error: Did you create a window and context first?");
        return;
    }

    glInformation();

	// Initialize our own frame buffer
	g.renderTarget = RenderTarget(g.screenWidth, g.screenHeight);

    g.basicShader = Shader("./shaders/vert.glsl","./shaders/frag.glsl");
    g.triangleOBJ = Object3D("triangleOBJect name");
	g.triangleOBJ.Triangle();

    g.renderTargetShader = Shader("./shaders/renderTargetVert.glsl","./shaders/renderTargetFrag.glsl");
    g.screenQuad= Object3D("screen quad name");
	g.screenQuad.ScreenQuad();
}


/**
* Draw
*/
void Draw(){
	// Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Initialize clear color
    // This is the background of the screen.
    glViewport(0, 0, g.screenWidth, g.screenHeight);
    glClearColor( 0.0f, 0.7f, 0.7f, 1.0f );

    //Clear color buffer and Depth Buffer
  	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Bind to the target that we want to draw to
	g.renderTarget.Bind();
	// Render as normal
    // Select a shader
    g.basicShader.Use();
    // Draw triangleOBJect
    g.triangleOBJ.Draw(3);


	// Bind to a 'default' render target
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	// Draw our sceene to the target
    g.renderTargetShader.Use();
	g.renderTargetShader.SetInt("screenTexture",0);
	// Draw a simple screen quad
	g.screenQuad.Draw(6);;

    // Bind to 'no shader'
    glUseProgram(0);
}



void glInformation(){
    import std.string;

    // fromStringz is used here to properly convert the C-string
    writeln(fromStringz(cast(const char*)glGetString(GL_VENDOR)));
    writeln(fromStringz(cast(const char*)glGetString(GL_RENDERER)));
    writeln(fromStringz(cast(const char*)glGetString(GL_VERSION)));
    writeln(fromStringz(cast(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
}


void loop(){

    while(!glfwWindowShouldClose(g.window)){
        glfwPollEvents();

        // Do opengl stuff
        Draw();

        glfwSwapBuffers(g.window);
    }

    glfwDestroyWindow(g.window);
}


/// Program entry point 
/// NOTE: When debugging, this is '_Dmain'
void main(string[] args){


    loop();

    glfwTerminate();
}
