module shader;

import std.stdio;
import std.conv;
import bindbc.sdl;
import bindbc.opengl;

struct Shader{

		GLuint mHandle;
		string mName;
		string mVertexShaderPath;
		string mFragmentShaderPath;
		/**
		 * Create the graphics pipeline
		 *
		 * @return void
		 */
		this(string name, string vertexShaderFile, string fragmentShaderFile){
				mName = name;
				mVertexShaderPath = vertexShaderFile;
				mFragmentShaderPath = fragmentShaderFile;
				char[] vertexShaderSource      = LoadShaderAsString(vertexShaderFile);
				char[] fragmentShaderSource    = LoadShaderAsString(fragmentShaderFile);
				
				// Duplicate strings so that they do not get accidently destroyed
				mHandle = CreateShaderProgram(vertexShaderSource.dup,fragmentShaderSource.dup);
		}

		/**
			Get the shader mHandle which is returned as an integer
		 */
		GLuint GetHandle() const{
				return mHandle;
		}

		/**
			Use the shader program
		 */
		void Use(){
				glUseProgram(mHandle);
		}

		/**
			appender allows for more efficient allocations
		 */
		char[] LoadShaderAsString(string filename){
				import std.file;
				import std.stdio;

				if(exists(filename)){
						auto file = File(filename);

						// writeln(file.size);
						char[] bytes = new char[file.size];
						file.rawRead(bytes);

						//writeln("bytes:",bytes);

						return bytes;
				}
				return null;
		}

		/**
		 * CompileShader will compile any valid vertex, fragment, geometry, tesselation, or compute shader.
		 */
		GLuint CompileShader(GLuint type)(char[] source)
				if(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER)
				{
						import std.string;

						// Compile our shaders
						GLuint shaderObject;

						// Based on the type passed in, we create a shader object specifically for that
						// type.
						shaderObject = glCreateShader(type);
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

								writeln("ERROR: "~to!string(type)~" compilation failed!\n", errorMessages, "\n");
								if(type==GL_VERTEX_SHADER){
									writeln("=========failed: vertex shader",mVertexShaderPath,"\n",source);
								}else{
									writeln("=========failed: fragment shader",mFragmentShaderPath,"\n",source);
								}

								// Delete our broken shader
								glDeleteShader(shaderObject);

								// Terminate the program
								// TODO: Consider if we do or do not want to
								//       terminate with a broken shader.
								//       This probably is not the right long
								//       term behavior.
								import core.stdc.stdlib;
								exit(1);

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
				GLuint myVertexShader   = CompileShader!GL_VERTEX_SHADER(vertexShaderSource);
				GLuint myFragmentShader = CompileShader!GL_FRAGMENT_SHADER(fragmentShaderSource);

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
				GLint location = GetAndCheckUniformLocation(symbol);
				glUniform1i(location,value);
		}
		void SetVec3(const char* symbol, float x, float y, float z){	
				GLint location = GetAndCheckUniformLocation(symbol);
				glUniform3f(location,x,y,z);
		}

		void SetMat4x4(const char* symbol, const GLfloat* value){	
				GLint location = GetAndCheckUniformLocation(symbol);
				glUniformMatrix4fv(location,1,GL_TRUE,value);
		}

		private:

		// Helper function to retrieve uniform symbol names
		// Will return the location if a valid location is found, otherwise
		// the program will terminate
		// TODO: Consider if I want to 'terminate' or otherwise assert, or log the error.
		int GetAndCheckUniformLocation(const char* symbol){
				GLint location = glGetUniformLocation(mHandle, symbol);
				if(location < 0){
						writeln("Could not find ",symbol.to!string,", maybe a mispelling or symbol was not used in shader\n");
						import core.stdc.stdlib;
						exit(1);
				}
				return location;
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
//GLint location = glGetUniformLocation(mHandle,symbol);
string code = "int "~Name~"("~body~"){return 0;}";
return code;
}else{
assert(0,"You messed up");
}
}

mixin(generateUniform!("glGet","int m1")());
 */
