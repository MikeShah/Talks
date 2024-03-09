// Hello world
// dmd deferred.d -L-L/usr/local/lib -L-lglfw3 -of=prog
// dmd glfw.d deferred.d shader.d -L-L/usr/local/lib -L-lglfw3 -of=prog
import std.stdio;
import glad.gl.all;
import glad.gl.loader;

import shader;
import glfw;
import object3d;

Globals g;

/// Safer way to work with global state
/// module constructors
shared static this(){
    g.basicShader = Shader("./shaders/vert.glsl","./shaders/frag.glsl");
    g.obj = Object3D();
}



struct Globals{
    Shader basicShader;
    Object3D obj;
    int screenWidth = 640;
    int screenHeight = 480;
}

void Initialize(){
    // Initialize glfw
    if(!glfwInit()){
        writeln("glfw failed to initialize");
    }
}

void PreDraw(){
	// Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Initialize clear color
    // This is the background of the screen.
    glViewport(0, 0, g.screenWidth, g.screenHeight);
    glClearColor( 0.0f, 0.7f, 0.7f, 1.0f );

    //Clear color buffer and Depth Buffer
  	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

/**
* Draw
*/
void Draw(){
    // Select a shader
    g.basicShader.Use();
    
    // Draw object
    g.obj.Draw();

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(g.screenWidth,g.screenHeight,"DConf Online 2024",null,null);
    glfwMakeContextCurrent(window);

    // Setup extensions
    if(!glad.gl.loader.gladLoadGL()){    
        writeln("Some error: Did you create a window and context first?");
        return;
    }

    glInformation();


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        // Do opengl stuff
        PreDraw();
        Draw();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
}


/// Program entry point 
/// NOTE: When debugging, this is '_Dmain'
void main(string[] args){


    Initialize();

    loop();

    glfwTerminate();
}
