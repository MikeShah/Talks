import core.stdc.stdlib;
import std.stdio;
import std.algorithm;
import std.array;
import std.conv;
import std.string;

struct Image {
		// Filepath to the image loaded
		string m_filepath;
		// Raw pixel data
		ubyte[] mPixelData;
		// Size and format of image
		int mWidth; // Width of the image
		int mHeight; // Height of the image
		int mBPP;   // Bits per pixel (i.e. how colorful are our pixels)
		int maxRange;
		char[] magicNumber; // magicNumber if any for image format
												// Constructor for creating an image

		// Constructor
		this(string filepath){

		}

		// Destructor
		~this(){
		}

		void LoadPPM(string filepath){
				writeln("LoadPPM:",filepath);
				m_filepath = filepath;

				auto f = File(m_filepath);

			import std.file;
				uint iteration=0;
				foreach(line ; f.byLine){
						if(line.startsWith("#")){
								continue;
						}
						if(line[0]=='P'){
								magicNumber=line;
								++iteration;
								continue;
						}else if(iteration==1){
								auto tokens =  line.splitter(" ").array;
								mWidth = to!int(tokens[0]);
								mHeight= to!int(tokens[1]);
								++iteration;
								continue;
						}else if(iteration==2){
								maxRange = line.to!int;
								++iteration;
								continue;
						}else{
								auto tokens = line.splitter(" ").array;
								foreach(token ; tokens){
										if(token!=""){
											mPixelData ~= token.parse!ubyte;
										}
								}
						}
				}

				writeln("Image loaded",m_filepath);
				writeln("\tmaxRange: ",maxRange);
				writeln("\tdata length: ",mPixelData.length);
				writeln("\tDimensions:",mWidth,",",mHeight);
				writeln("\tFirst few bits:",mPixelData[0 ..15]);
				// Flip all of the pixels
				if(true){
						// Copy all of the data to a temporary stack-allocated array
						auto copyData = new ubyte[mWidth*mHeight*3];
						for(int i =0; i < mWidth*mHeight*3; ++i){
								copyData[i]=mPixelData[i];
						}
						uint pos = (mWidth*mHeight*3)-1;
						for(int i =0; i < mWidth*mHeight*3; i+=3){
								mPixelData[pos]=copyData[i+2];
								mPixelData[pos-1]=copyData[i+1];
								mPixelData[pos-2]=copyData[i];
								pos-=3;
						}
				}
		}

		void SetPixel(int x, int y, ubyte r, ubyte g, ubyte b){
				if(x > mWidth || y > mHeight){
						return;
				}
				else{
						mPixelData[(x*3)+mHeight*(y*3)] 	= r;
						mPixelData[(x*3)+mHeight*(y*3)+1] = g;
						mPixelData[(x*3)+mHeight*(y*3)+2] = b;
				}
		}

		void PrintPixels(){
				for(int x = 0; x <  mWidth*mHeight*3; ++x){
						writeln(" ",cast(int)mPixelData[x]);
				}
				writeln();
		}

		ubyte* GetPixelDataPtr(){
				return mPixelData.ptr;
		}

		uint GetWidth() const{
			return mWidth;
		}
		uint GetHeight() const{
			return mHeight;
		}
		
		void WriteP3(){
				File f= File("./debug.ppm","w");
				f.writeln("#",m_filepath);
				f.writeln("P3");
				f.writeln(mWidth, " ", mHeight);
				f.writeln(maxRange);
				foreach(entry ; mPixelData){
					f.write(entry," ");
				}

		}

}

