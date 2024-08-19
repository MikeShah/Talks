module object3d;

import glad.gl.all;

import std.stdio;
import std.algorithm;
import std.array;
import std.conv;
import std.ascii;

// Vertex Structures for format 
struct Format3v3n{
    float[3] vertices;
    float[3] normals;
}
struct Format3v3c{
    float[3] vertices;
    float[3] colors;
}
struct Format3v2t{
    float[3] vertices;
    float[2] textures;
}
struct Format3v3n2t{
    float[3] vertices;
    float[3] normals;
    float[2] texture; 
}

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
//                writeln(line.splitter(" ").array);
            }
            else if(line.startsWith("vn ")){
                line.splitter(" ").array.remove(0).each!((e) { normals ~= parse!float(e);});
//                writeln(line.splitter(" ").array);
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
//        writeln(mVertexData);
    }

    // Pass in a struct and we will create the appropriate
    // model format
    void make(T)(){
        // Vertex Arrays Object (VAO) Setup
        glGenVertexArrays(1, &mVAO);
        // We bind (i.e. select) to the Vertex Array Object (VAO) that we want to work withn.
        glBindVertexArray(mVAO);

        // Vertex Buffer Object (VBO) creation
        glGenBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mVertexData.length* GLfloat.sizeof, mVertexData.ptr, GL_STATIC_DRAW);

        // Create an array of offsets
        mixin("ulong[",T.tupleof.length,"] offsets;");;
        mixin("offsets[0] = 0;");

		static foreach (idx, m; T.tupleof) {
//          pragma(msg,idx);
//			pragma(msg,typeof(m));
//			pragma(msg,m.stringof);
//			pragma(msg,m.sizeof);

            // Vertex attributes
//            pragma(msg,"glEnableVertexAttribArray(",idx,");");
                 mixin("glEnableVertexAttribArray(",idx,");");
//            pragma(msg,"glVertexAttribPointer(",idx,", ",m.sizeof/float.sizeof,", GL_FLOAT, GL_FALSE, ",T.sizeof,", cast(GLvoid*)(GLfloat.sizeof*offsets[idx]));");
                 mixin("glVertexAttribPointer(",idx,", ",m.sizeof/float.sizeof,", GL_FLOAT, GL_FALSE, ",T.sizeof,", cast(GLvoid*)(GLfloat.sizeof*offsets[idx]));");
            static if(idx+1 < T.tupleof.length){
                mixin("offsets[",idx+1,"] = offsets[",idx,"] + ",m.sizeof/float.sizeof,";");
            }
        }
//        writeln(mixin("offsets"));

        // Unbind vertex array
        glBindVertexArray(0);
        // Disable attributes
		static foreach (idx, m; T.tupleof) {
 //           pragma(msg,"glDisableVertexAttribArray(",idx,");");
                 mixin("glDisableVertexAttribArray(",idx,");");
        }
 //       pragma(msg,"");
    }

    void Draw(){
        // Enable our attributes
        glBindVertexArray(mVAO);
        //Render data
        glDrawArrays(GL_TRIANGLES,0, mVertices);
    }
}
