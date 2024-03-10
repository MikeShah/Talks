module object3d;

import std.stdio;
import glad.gl.all;
import glad.gl.loader;

/// 3D Objects
struct Object3D{
    string mName;
    GLuint mVAO = 0;
    GLuint mVBO = 0;
	GLfloat[] mVertexData;

    this(string name){
        this.mName = name;
    }

    void Triangle(){
        // Geometry Data
        mVertexData =
            [
           -0.5f,  -0.5f, 0.0f, 	// Left vertex position
            1.0f,   0.0f, 0.0f, 	// color
            0.5f,  -0.5f, 0.0f,  	// right vertex position
            0.0f,   1.0f, 0.0f,  	// color
            0.0f,   0.5f, 0.0f,  	// Top vertex position
            0.0f,   0.0f, 1.0f,  	// color
            ];

        // Vertex Arrays Object (VAO) Setup
        glGenVertexArrays(1, &mVAO);
        // We bind (i.e. select) to the Vertex Array Object (VAO) that we want to work withn.
        glBindVertexArray(mVAO);

        // Vertex Buffer Object (VBO) creation
        glGenBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
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

    void ScreenQuad(){
        // Geometry Data
        mVertexData =
            [
				// Triangle 1
				-1.0f, -1.0f, 0.0f,
				0.0f, 0.0f,
				
				1.0f, 1.0f, 0.0f,
				1.0f, 1.0f,

				
				-1.0f, 1.0f, 0.0f,
				0.0f, 1.0f,
				// Triangle 2
				-1.0f, -1.0f, 0.0f,
				0.0f, 0.0f,

				1.0f, -1.0f, 0.0f,
				1.0f, 0.0f,

				1.0f, 1.0f, 0.0f,
				1.0f, 1.0f,


            ];

        // Vertex Arrays Object (VAO) Setup
        glGenVertexArrays(1, &mVAO);
        // We bind (i.e. select) to the Vertex Array Object (VAO) that we want to work withn.
        glBindVertexArray(mVAO);

        // Vertex Buffer Object (VBO) creation
        glGenBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mVertexData.length* GLfloat.sizeof, mVertexData.ptr, GL_STATIC_DRAW);

        // Vertex attributes
        // Atribute #0
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLfloat.sizeof*5, cast(void*)0);

        // Attribute #1
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, GLfloat.sizeof*5, cast(GLvoid*)(GLfloat.sizeof*3));

        // Unbind our currently bound Vertex Array Object
        glBindVertexArray(0);
        // Disable any attributes we opened in our Vertex Attribute Arrray,
        // as we do not want to leave them open. 
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    void Draw(GLuint verts){
        // Enable our attributes
        glBindVertexArray(mVAO);
        //Render data
        glDrawArrays(GL_TRIANGLES,0, verts);
    }

}
