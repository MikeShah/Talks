// Hello world
// dmd -g -J. main.d ./glad/gl/*.d -L-L/usr/local/lib -L-lglfw3 -of=prog && ./prog
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

Globals g;

/// Global Variables
/// They aren't always great, but when I need them, I wrap them in a struct
struct Globals{

    GLuint mVAO;
    GLuint mVBO;
    GLuint programObject;

    GLFWwindow* window;
    int screenWidth = 640;
    int screenHeight = 480;
}

// Create a basic shader
void BuildBasicShader(){

    // Compile our shaders
    GLuint vertexShader;
    GLuint fragmentShader;

    // Pipeline with vertex and fragment shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader= glCreateShader(GL_FRAGMENT_SHADER);

    string vertexSource = import("./shaders/vert.glsl");
    string fragmentSource = import("./shaders/frag.glsl");

    // Compile vertex shader
    const char* vertSource = vertexSource.ptr;
    glShaderSource(vertexShader, 1, &vertSource, null);
    glCompileShader(vertexShader);
    CheckShaderError(vertexShader);

    // Compile fragment shader
    const char* fragSource = fragmentSource.ptr;
    glShaderSource(fragmentShader, 1, &fragSource, null);
    glCompileShader(fragmentShader);
    CheckShaderError(fragmentShader);

    // Create shader pipeline
    g.programObject = glCreateProgram();

    // Link our two shader programs together.
    // Consider this the equivalent of taking two .cpp files, and linking them into
    // one executable file.
    glAttachShader(g.programObject,vertexShader);
    glAttachShader(g.programObject,fragmentShader);
    glLinkProgram(g.programObject);

    // Validate our program
    glValidateProgram(g.programObject);

    // Once our final program Object has been created, we can
    // detach and then delete our individual shaders.
    glDetachShader(g.programObject,vertexShader);
    glDetachShader(g.programObject,fragmentShader);
    // Delete the individual shaders once we are done
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void CheckShaderError(GLuint shaderObject){
    // Retrieve the result of our compilation
    int result;
    // Our goal with glGetShaderiv is to retrieve the compilation status
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE){
        int length;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
        GLchar[] errorMessages = new GLchar[length];
        glGetShaderInfoLog(shaderObject, length, &length, errorMessages.ptr);
    }
}

/// Setup triangle with OpenGL buffers
void Triangle(){
    // Geometry Data
    const GLfloat[] mVertexData =
        [
       -0.5f,  -0.5f, 0.0f, 	// Left vertex position
        1.0f,   0.0f, 0.0f, 	// color
        0.5f,  -0.5f, 0.0f,  	// right vertex position
        0.0f,   1.0f, 0.0f,  	// color
        0.0f,   0.5f, 0.0f,  	// Top vertex position
        0.0f,   0.0f, 1.0f,  	// color
        ];
    pragma(msg, mVertexData.length);

    // Vertex Arrays Object (VAO) Setup
    glGenVertexArrays(1, &g.mVAO);
    // We bind (i.e. select) to the Vertex Array Object (VAO) that we want to work withn.
    glBindVertexArray(g.mVAO);

    // Vertex Buffer Object (VBO) creation
    glGenBuffers(1, &g.mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, g.mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertexData.length* GLfloat.sizeof, mVertexData.ptr, GL_STATIC_DRAW);

    // Vertex attributes
    // Atribute #0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLfloat.sizeof*6, cast(void*)0);

    // Attribute #1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GLfloat.sizeof*6, cast(GLvoid*)(GLfloat.sizeof*3));

    // Unbind our currently bound Vertex Array Object
    glBindVertexArray(0);
    // Disable any attributes we opened in our Vertex Attribute Arrray,
    // as we do not want to leave them open. 
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}



/// Function to retrieve information confirming OpenGL setup
void glInformation(){
    import std.string;

    // fromStringz is used here to properly convert the C-string
    writeln(fromStringz(cast(const char*)glGetString(GL_VENDOR)));
    writeln(fromStringz(cast(const char*)glGetString(GL_RENDERER)));
    writeln(fromStringz(cast(const char*)glGetString(GL_VERSION)));
    writeln(fromStringz(cast(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
}

/// Setup OpenGL and any libraries
void initialize(){

    // Initialize glfw
    if(!glfwInit()){
        writeln("glfw failed to initialize");
    }

    // Setup
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    g.screenWidth = 640;
    g.screenHeight = 480;
    g.window =  glfwCreateWindow(g.screenWidth,g.screenHeight,"demo 01 - DConf Online 2024",null,null);
    glfwMakeContextCurrent(g.window);

    // Setup extensions
    if(!glad.gl.loader.gladLoadGL()){    
        writeln("Some error: Did you create a window and context first?");
        return;
    }

    // Check OpenGL version
    glInformation();
    // Build a basic shader
    BuildBasicShader();
    // Build a triangle
    Triangle();
}

/// Main application loop
void loop(){

    while(!glfwWindowShouldClose(g.window)){
        glfwPollEvents();

        glClearColor(0.0f,0.6f,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Do opengl drawing
        glUseProgram(g.programObject);

        glBindVertexArray(g.mVAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(g.window);
    }

}

/// Program entry point 
/// NOTE: When debugging, this is '_Dmain'
void main(string[] args){

    // Setup OpenGL libraries
    initialize();

    // Loop
    loop();

    // Cleanup
    glfwDestroyWindow(g.window);
    glfwTerminate();
}
