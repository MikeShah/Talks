// Hello world
// dmd deferred.d -L-L/usr/local/lib -L-lglfw3 -of=prog
import std.stdio;
import glad.gl.all;
import glad.gl.loader;

// ---------------------------------------------------------------------------
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
// ---------------------------------------------------------------------------


Globals g;
/// Safer way to work with global state
/// module constructors
shared static this(){
}




struct Globals{
    GLuint graphicsPipelineShaderProgram = 0;
    GLuint vertexArrayObject		     = 0;
    GLuint vertexBufferObject			 = 0;
    int screenWidth 						= 640;
    int screenHeight 						= 480;
}




/**
  appender allows for more efficient allocations
*/
const(char*)[] LoadShaderAsStrings(const string filename){
    import std.file;
    import std.array;
    import std.conv;
    import std.string;

    auto file = File(filename);
    const(char*)[] lines;

    foreach(line; file.byLine()){
        lines ~= line.ptr;
    }
    

    writeln(lines);

    const(char*)[] linez;
    foreach(l ; lines){
        linez ~= l;
    }
    // Convert to match OpenGL API

    return linez;
}


/**
* CompileShader will compile any valid vertex, fragment, geometry, tesselation, or compute shader.
* e.g.
*	    Compile a vertex shader: 	CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
*       Compile a fragment shader: 	CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
*
* @param type We use the 'type' field to determine which shader we are going to compile.
* @param source : The shader source code.
* @return id of the shaderObject
*/
GLuint CompileShader(GLuint type, const(char*)* source){
	// Compile our shaders
	GLuint shaderObject;

	// Based on the type passed in, we create a shader object specifically for that
	// type.
	if(type == GL_VERTEX_SHADER){
		shaderObject = glCreateShader(GL_VERTEX_SHADER);
	}else if(type == GL_FRAGMENT_SHADER){
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	}

	// The source of our shader
	glShaderSource(shaderObject, 1, source, null);
	// Now compile our shader
	glCompileShader(shaderObject);

	// Retrieve the result of our compilation
	int result;
	// Our goal with glGetShaderiv is to retrieve the compilation status
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE){
		int length;
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
		GLchar[] errorMessages = new GLchar[length];
        writeln("failed: ",length);
		glGetShaderInfoLog(shaderObject, length, &length, errorMessages.ptr);

		if(type == GL_VERTEX_SHADER){
			writeln("ERROR: GL_VERTEX_SHADER compilation failed!\n", errorMessages, "\n");
		}else if(type == GL_FRAGMENT_SHADER){
			writeln("ERROR: GL_FRAGMENT_SHADER compilation failed!\n", errorMessages, "\n");
		}

		// Delete our broken shader
		glDeleteShader(shaderObject);

		return 0;
	}
  return shaderObject;
}



/**
* Creates a graphics program object (i.e. graphics pipeline) with a Vertex Shader and a Fragment Shader
*
* @param vertexShaderSource Vertex source code as a string
* @param fragmentShaderSource Fragment shader source code as a string
* @return id of the program Object
*/
GLuint CreateShaderProgram(const(char*)[] vertexShaderSource, const(char*)[] fragmentShaderSource){

    // Create a new program object
    GLuint programObject = glCreateProgram();

    // Compile our shaders
    GLuint myVertexShader   = CompileShader(GL_VERTEX_SHADER, vertexShaderSource.ptr);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.ptr);

    // Link our two shader programs together.
	// Consider this the equivalent of taking two .cpp files, and linking them into
	// one executable file.
    glAttachShader(programObject,myVertexShader);
    glAttachShader(programObject,myFragmentShader);
    glLinkProgram(programObject);

    // Validate our program
    glValidateProgram(programObject);

    // Once our final program Object has been created, we can
	// detach and then delete our individual shaders.
    glDetachShader(programObject,myVertexShader);
    glDetachShader(programObject,myFragmentShader);
	// Delete the individual shaders once we are done
    glDeleteShader(myVertexShader);
    glDeleteShader(myFragmentShader);

    return programObject;
}


/**
* Create the graphics pipeline
*
* @return void
*/
void CreateGraphicsPipeline(){

    const(char*)[] vertexShaderSource      = LoadShaderAsStrings("./shaders/vert.glsl");
    const(char*)[] fragmentShaderSource    = LoadShaderAsStrings("./shaders/frag.glsl");

	g.graphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource,fragmentShaderSource);
}


void VertexSpecification(){

	// Geometry Data
	const GLfloat[] vertexData =
    [
	   -0.5f,  -0.5f, 0.0f, 	// Left vertex position
		1.0f,   0.0f, 0.0f, 	// color
		0.5f,  -0.5f, 0.0f,  	// right vertex position
		0.0f,   1.0f, 0.0f,  	// color
		0.0f,   0.5f, 0.0f,  	// Top vertex position
		0.0f,   0.0f, 1.0f,  	// color
    ];


	// Vertex Arrays Object (VAO) Setup
	glGenVertexArrays(1, &g.vertexArrayObject);
	// We bind (i.e. select) to the Vertex Array Object (VAO) that we want to work withn.
	glBindVertexArray(g.vertexArrayObject);

	// Vertex Buffer Object (VBO) creation
	glGenBuffers(1, &g.vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, g.vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertexData.length* GLfloat.sizeof, vertexData.ptr, GL_STATIC_DRAW);

    pragma(msg,vertexData.length);

    // Vertex attributes
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLfloat.sizeof*6, cast(void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GLfloat.sizeof*6, cast(GLvoid*)(GLfloat.sizeof*3));

	// Unbind our currently bound Vertex Array Object
	glBindVertexArray(0);
	// Disable any attributes we opened in our Vertex Attribute Arrray,
	// as we do not want to leave them open. 
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}


void PreDraw(){
	// Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Initialize clear color
    // This is the background of the screen.
    glViewport(0, 0, g.screenWidth, g.screenHeight);
    glClearColor( 1.0f, 1.0f, 0.0f, 1.0f );

    //Clear color buffer and Depth Buffer
  	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Use our shader
	glUseProgram(g.graphicsPipelineShaderProgram);
}



/**
* Draw
* The render function gets called once per loop.
* Typically this includes 'glDraw' related calls, and the relevant setup of buffers
* for those calls.
*
* @return void
*/
void Draw(){
    // Enable our attributes
	glBindVertexArray(g.vertexArrayObject);

	// Select the vertex buffer object we want to enable
    glBindBuffer(GL_ARRAY_BUFFER, g.vertexBufferObject);

    //Render data
    glDrawArrays(GL_TRIANGLES,0,3);

	// Stop using our current graphics pipeline
	// Note: This is not necessary if we only have one graphics pipeline.
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

    VertexSpecification();
    CreateGraphicsPipeline();

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

    // Initialize glfw
    if(!glfwInit()){
        writeln("glfw failed to initialize");
    }

    loop();

    glfwTerminate();
}
