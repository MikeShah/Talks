module object3d;


import std.stdio;
import std.algorithm;
import std.array;
import std.conv;
import std.ascii;
import std.string;

import bindbc.sdl;
import bindbc.opengl;
import inmath.linalg;

import texture;
import material;

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


// A 3D object may be broken into 'chunks', and thus
// has its own vertex data.
struct Chunk(T){
		int mVertices = 0;
		GLfloat[] mVertexData;
		Material mMaterial;
		GLuint mVAO = 0;
		GLuint mVBO = 0;
		Texture mTexture;
		this(string materialName){
						
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


/// 3D Objects
struct Object3D{
		string mName;
		int mTotalVertices = 0;
		mat4 mModelMatrix;;
		Chunk[] mChunks;

		void Identity(){
			mModelMatrix = mat4.identity;
		}
		
		void Translate(float x, float y, float z){
				mModelMatrix *= mat4.translation(vec3(x,y,z));
		}
		void Scale(float x, float y, float z){
				mModelMatrix *= mat4.scaling(x,y,z);
		}
		void yRotation(float angle){
				mModelMatrix *= mat4.yRotation(angle);
		}

		this(string name){
				this.mName = name;
				mModelMatrix = mat4.identity;
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
		void LoadGeometry(string filepath){
				float[] vertices;
				float[] normals;
				float[] texture_coords;
				uint[] faces;

				auto f = File(filepath);

				foreach(line ; f.byLine){
						if(line.startsWith("v ")){
								line.splitter(" ").array.remove(0).strip("").each!((e) { 
												if(e!= "" || e!= " " || e!="  "){	
												vertices~= parse!float(e);
												}
												});
								//                writeln(line.splitter(" ").array);
						}
						else if(line.startsWith("vn ")){
								line.splitter(" ").array.remove(0).strip("").each!((e) { 
												if(e!= "" || e!= " " || e!="  "){	
												normals ~= parse!float(e);
												}
												});
								//                writeln(line.splitter(" ").array);
						}
						else if(line.startsWith("vt ")){
								line.splitter(" ").array.remove(0).strip("").each!((e) {
												if(e!= "" || e!= " " || e!="  "){	
												texture_coords ~= parse!float(e);
												}
												});
								//                writeln(line.splitter(" ").array);
						}
						else if(line.startsWith("usemtl")){
							auto tokens = line.splitter(" ").array.remove(0).strip("");
							Chunk newChunk(tokens[1]);
							mChunks ~= newChunk;
						}
						else if(line.startsWith("f ")){
								auto face = line.splitter(" ").array.remove(0).strip("");
								foreach(indice; face){
										auto component = indice.splitter("/").array;
										if(component[0]!=""){
												int idx = (parse!int(component[0]) - 1 ) * 3;
												mChunks[$-1].mVertexData~= [vertices[idx], vertices[idx+1], vertices[idx+2]];
										}
										if(component[2]!=""){
												int idx= (parse!int(component[2]) - 1 ) * 3;
												mChunks[$-1].mVertexData ~= [normals[idx+0], normals[idx+1], normals[idx+2]];
										}
										if(component[1]!=""){
												int idx= (parse!int(component[1]) - 1 ) * 2;
												mChunks[$-1].mVertexData ~= [texture_coords[idx+0], texture_coords[idx+1]];
										}
								}
						}
				}

				mVertices = cast(int)mVertexData.length/8;
				writeln("flattened data length: ",mVertexData.length);
				writeln("vertices", mVertices);
				//        writeln(mVertexData);
		}

		// For now, parses a .mtl file and loads an image per material
		void LoadMaterial(string filepath){
				auto filedirectories = filepath.splitter("/").array;
				auto path = filedirectories[0 .. $-1].join("/") ~ "/";
				writeln(filedirectories);
				writeln(path);

				writeln("Preparing to load materials for:",filepath);
				auto f = File(filepath);

				foreach(line ; f.byLine){
						if(line.indexOf("newmtl")>=0){
								writeln("Adding material",line.strip);
								mMaterials ~= Material(line.strip.to!string);
						}	

						if(line.indexOf(".ppm")>=0 || line.indexOf(".PPM")>=0){
								auto tokens = line.splitter(" ").array;
								if(tokens[0] == "map_Kd"){
										mMaterials[$-1].mDiffuseImage.LoadPPM(path ~ tokens[1].to!string);
								}
						}
				}

		}

}
