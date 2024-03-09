module object3d;

import std.stdio;
import glad.gl.all;
import glad.gl.loader;

import shader;

struct Object3D{
    GLuint vertexArrayObject = 0;
    GLuint vertexBufferObject = 0;

    this(string name){
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
        glGenVertexArrays(1, &vertexArrayObject);
        // We bind (i.e. select) to the Vertex Array Object (VAO) that we want to work withn.
        glBindVertexArray(vertexArrayObject);

        // Vertex Buffer Object (VBO) creation
        glGenBuffers(1, &vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
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

    void Draw(){
        // Enable our attributes
        glBindVertexArray(vertexArrayObject);
        //Render data
        glDrawArrays(GL_TRIANGLES,0,3);
    }

}
