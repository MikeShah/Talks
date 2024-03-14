module object3d;

import glad.gl.all;
import glad.gl.loader;

import std.stdio;
import std.algorithm;
import std.array;
import std.conv;
import std.ascii;

/// 3D Objects
struct Object3D{
    string mName;
    GLuint mVAO = 0;
    GLuint mVBO = 0;
	GLfloat[] mVertexData;
    int mVertices = 0;

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

        mVertices = 3;
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

        mVertices = 6;
    }

    // One or more objects stored within the single .obj file
    void OBJModel(string filepath){
        float[] vertices;
        float[] normals;
        uint[] faces;

        auto f = File(filepath);

        foreach(line ; f.byLine){

            if(line.startsWith("v ")){
                line.splitter(" ").array.remove(0).each!((e) { vertices~= parse!float(e);});
                writeln(line.splitter(" ").array);
            }
            else if(line.startsWith("vn ")){
                line.splitter(" ").array.remove(0).each!((e) { normals ~= parse!float(e);});
                writeln(line.splitter(" ").array);
            }
            else if(line.startsWith("f ")){
                auto face = line.splitter(" ").array.remove(0);
                foreach(indice; face){
                    auto component = indice.splitter("/").array;
                    if(component[0]!=""){
                        int idx = (parse!int(component[0]) - 1 ) * 3;
                        mVertexData~= [vertices[idx], vertices[idx+1], vertices[idx+2]];
                    }
                    if(component[2]!=""){
                        int idx= (parse!int(component[2]) - 1 ) * 3;
                        mVertexData ~= [normals[idx+0], normals[idx+1], normals[idx+2]];
                    }
                }
            }
        }

        mVertices = cast(int)mVertexData.length/6;
        writeln("flattened data length: ",mVertexData.length);
        writeln("vertices", mVertices);
    }

    void make33(){
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

    void make32(){
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


    void Draw(){
        // Enable our attributes
        glBindVertexArray(mVAO);
        //Render data
        glDrawArrays(GL_TRIANGLES,0, mVertices);
    }

}
