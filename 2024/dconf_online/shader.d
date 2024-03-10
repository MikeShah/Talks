module shader;

import std.stdio;
import std.conv;
import glad.gl.all;
import glad.gl.loader;

struct Shader{

    GLuint handle;
    /**
     * Create the graphics pipeline
     *
     * @return void
     */
    this(string vertexShaderFile, string fragmentShaderFile){

        char[] vertexShaderSource      = LoadShaderAsString(vertexShaderFile);
        char[] fragmentShaderSource    = LoadShaderAsString(fragmentShaderFile);

        handle = CreateShaderProgram(vertexShaderSource,fragmentShaderSource);
    }

    /**
        Get the shader handle which is returned as an integer
    */
    GLuint Get(){
        return handle;
    }

	/**
		Use the shader program
	*/
    void Use(){
        glUseProgram(handle);
    }

    /**
      appender allows for more efficient allocations
     */
    char[] LoadShaderAsString(string filename){
        import std.file;
        import std.stdio;

        if(exists(filename)){
            auto file = File(filename);

            writeln(file.size);
            char[] bytes = new char[file.size];
            file.rawRead(bytes);

            writeln("bytes:",bytes);

            return bytes;
        }
        return null;
    }

    /**
     * CompileShader will compile any valid vertex, fragment, geometry, tesselation, or compute shader.
     */
    GLuint CompileShader(GLuint type, char[] source){
        import std.string;

        // Compile our shaders
        GLuint shaderObject;

        // Based on the type passed in, we create a shader object specifically for that
        // type.
        if(type == GL_VERTEX_SHADER){
            shaderObject = glCreateShader(GL_VERTEX_SHADER);
        }else if(type == GL_FRAGMENT_SHADER){
            shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
        }

        char* sourceCodePtr = source.ptr;

        glShaderSource(shaderObject, 1, &sourceCodePtr, null);
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
     */
    GLuint CreateShaderProgram(char[] vertexShaderSource, char[] fragmentShaderSource){
        // Create a new program object
        GLuint programObject = glCreateProgram();

        // Compile our shaders
        GLuint myVertexShader   = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

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

	void SetInt(const char* symbol, GLuint value){	
		GLint location = glGetUniformLocation(handle,symbol);

		if(location >=0){
			glUniform1i(location,value);
		}else{
			writeln("Could not find ",symbol.to!string,", maybe a mispelling or symbol was not used in shader\n");
            import core.stdc.stdlib;
            exit(1);
		}
	}

	void SetMat4x4(const char* symbol, GLfloat* value){	
		GLint location = glGetUniformLocation(handle,symbol);

		if(location >=0){
			glUniformMatrix4fv(location,1,GL_FALSE,value);
		}else{
			writeln("Could not find ",symbol.to!string,", maybe a mispelling or symbol was not used in shader\n");
		}
	}
}



/*
	string generateUniform(string Name, params...)(){
		import std.meta;
		if(__ctfe){
			string body;
			alias paramList = AliasSeq!(params);
			foreach(t; params){
				body ~= t;
			}
			//GLint location = glGetUniformLocation(handle,symbol);
			string code = "int "~Name~"("~body~"){return 0;}";
			return code;
		}else{
			assert(0,"You messed up");
		}
	}

	mixin(generateUniform!("glGet","int m1")());
*/
