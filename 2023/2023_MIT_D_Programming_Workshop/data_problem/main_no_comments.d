// @ file ./data_problem/main_no_comments.d
// rdmd main_no_comments.d data.zip
import std.stdio;
import std.file;
import std.zip;
import std.csv;
import std.typecons; 
import std.algorithm;
import std.range;      // takeExactly

void main(string[] args){
    auto zip = new ZipArchive(read(args[1]));
    ubyte[] data; 	// Initial buffer of data
    
    // Look at all of the data files in the zip
    foreach(filename, am; zip.directory){
        data~= zip.expand(am);
    }

    writeln();
    int[string] athletes;
                         
    string string_data = cast(string)data;
    foreach(record; csvReader!(Tuple!(string,int))(string_data)){
        athletes[record[0]] = record[1];
    }

    auto GreatestAthletes = athletes.keys.
							map!((a)=> tuple!("championships","name")(athletes[a],a))
							.array.sort!("a > b")
							.map!((b) => b[1])  // Swap back key and value (so name is now first field)
                            .takeExactly(3);    

    GreatestAthletes.each!(n=> writeln(n," won ", athletes[n]));
}


