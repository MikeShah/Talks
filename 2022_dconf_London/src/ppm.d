// ppm.d
module ppm;

import std.stdio;
import std.conv;

class PPM{ 
    /// Enums for PPM class for magic numbers
    enum MagicNumber {P3 = "P3", P6 = "P6"}

    /// Constructor for PPM image
    this(uint width, uint height){
        m_width = width;
        m_height = height;
        m_pixels = new ubyte[width*height*3]; 
    }

    /// Write the file
    void WriteFile(string filename, MagicNumber magicNumber){
        File file = File(filename, "w");

        // Write out the header P3 header
        file.writeln(magicNumber);
        file.writeln(to!string(m_width)~" "~to!string(m_height));
        file.writeln(to!string(m_maxValue));

        if(magicNumber == MagicNumber.P3){
            // Write out the pixel data
            for(uint y=0; y < m_height; ++y){
                // Progress bar
                //writeln("Writing PPM line: "~to!string(y)~"/"~to!string(m_height));
                for(uint x=0; x < m_width; ++x){
                    // Determine the pixel color
                    // Write out one pixel of information
                    int pitch = m_width * 3;
                    file.writeln(to!string(m_pixels[y*pitch+x*3+0])~" "
                                ~to!string(m_pixels[y*pitch+x*3+1])~" "
                                ~to!string(m_pixels[y*pitch+x*3+2]));
                }
                file.writeln();
            } 
        }else if(magicNumber == MagicNumber.P6){

        }
        
        file.close();
        
        writeln("File: "~filename~" written."); 

    }

    /// Set the pixels
    void SetPixel(uint x, uint y, ubyte r, ubyte g, ubyte b){
        int pitch = m_width * 3;
        m_pixels[y*pitch+x*3+0] = r;
        m_pixels[y*pitch+x*3+1] = g;
        m_pixels[y*pitch+x*3+2] = b;
    }


    byte GetPixelR(uint x, uint y){
        return m_pixels[y*m_width*3+x*3+0];
    }
    byte GetPixelG(uint x, uint y){
        return m_pixels[y*m_width*3+x*3+1];
    }
    byte GetPixelB(uint x, uint y){
        return m_pixels[y*m_width*3+x*3+2];
    }

    /// Return the width
    uint GetWidth(){
        return m_width;
    }
    /// Return the height
    uint GetHeight(){
        return m_height;
    }

    void SetPixelArray(){
        
    }

    // Return the pixel array
    ubyte[] GetPixelArrayBytes(){
        return m_pixels;
    }
    
    // Some constant values for the image dimensions
    private ubyte[]  m_pixels;
    private string  m_magicNumber   = "P3";
    private uint    m_width         = 256;
    private uint    m_height        = 256;
    private uint    m_maxValue      = 255;    
}


unittest{
    

}
