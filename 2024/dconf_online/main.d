// dmd main.d -L-L/usr/local/lib -L-lglfw3 -of=prog
import std.stdio;
import glad.gl.all;
import glad.gl.loader;

/// GLFW Bindings
/// When we link in the library, we need to have what you'd think of as the header
/// available here.
extern(C){
    // Forward declare structures
    struct GLFWmonitor;
    struct GLFWwindow;

    enum{ GLFW_CONTEXT_VERSION_MAJOR = 0x00022002,
          GLFW_CONTEXT_VERSION_MINOR = 0x00022003,
          GLFW_OPENGL_PROFILE =  0x00022008,
          GLFW_OPENGL_CORE_PROFILE  = 0x00032001,
          GLFW_OPENGL_FORWARD_COMPAT =  0x00022006,
    }

    // Types
    alias GLFWglproc = void* function(const char*);

    // Functions
    int glfwInit();
    GLFWwindow* glfwCreateWindow(int,int,const char*, GLFWmonitor*, GLFWwindow*);
    void glfwDestroyWindow (GLFWwindow *window);
    void glfwTerminate();
    int  glfwWindowShouldClose (GLFWwindow *window);
    void glfwPollEvents ();
    int  glfwWindowShouldClose(GLFWwindow *    window);
    void glfwSwapBuffers (GLFWwindow *window);
    void glfwMakeContextCurrent (GLFWwindow *window);
    void glfwWindowHint (int hint, int value);

    GLFWglproc  glfwGetProcAddress (const char *procname);
}

void loop(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800,600,"window",null,null);
    glfwMakeContextCurrent(window);

    // Setup extensions
    if(!glad.gl.loader.gladLoadGL()){    
        writeln("Some error: Did you create a window and context first?");
        return;
    }

    glInformation();

    import std.demangle;
    pragma(msg,(demangle("_D4glad2gl6loader10gladLoadGLFZb")));

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        glClearColor(0.0f,1.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Do opengl stuff

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
}

void glInformation(){
    import std.string;

    // fromStringz is used here to properly convert the C-string
    writeln(fromStringz(cast(const char*)glGetString(GL_VENDOR)));
    writeln(fromStringz(cast(const char*)glGetString(GL_RENDERER)));
    writeln(fromStringz(cast(const char*)glGetString(GL_VERSION)));
    writeln(fromStringz(cast(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
}

/// Program entry point 
/// NOTE: When debugging, this is '_Dmain'
void main(string[] args){

    // Initialize glfw
    if(!glfwInit()){
        writeln("glfw failed to initialize");
    }

    loop();

    glfwTerminate();
}
