// @ file ./data_problem/main.d
// 
// rdmd main.d data.zip
import std.stdio;
import std.file;

void main(string[] args){

    import std.zip;

    // Read in our zip file
    auto zip = new ZipArchive(read(args[1]));
    writeln("archive data members: ", zip.totalEntries());

    // Initial buffer of data
    ubyte[] data;
    
    // Look at all of the data files in the zip
    foreach(filename, am; zip.directory){
        writeln(filename, ":", am.name);

        // Expand the data which retrieves
        // a ubyte[] array
        // We'll then append into our data
        data~= zip.expand(am);
    }

    // Once we have all of the data, let's iterate
    // through
    writeln();
    alias key   = string;
    alias value = int;
    value[key] athletes;

    import std.csv;
    import std.typecons; // For Tuple
                         // Easy way to construct new types
                         // thus 'type cons' name
    string string_data = cast(string)data;
    foreach(record; csvReader!(Tuple!(string,int))(string_data)){
//        writeln(record[0],'\t',record[1]);
        athletes[record[0]] = record[1];
    }


    import std.algorithm;
    import std.range;      // takeExactly

    auto GreatestAthletes = athletes 
                            .keys               // Get all of the athlete names as keys
                            .map!((a)=> tuple!("championships","name")(athletes[a],a)) // Swap key for value
                            .array              // Create an array of the new tuples
                            .sort!("a > b")     // Sort tuples by the 2nd field
                            .map!((b) => b[1])  // Swap back key and value (so name is now first field)
                            .takeExactly(3);    // Take the top three names

    // Print out the top three greatest athletes
    // by using their keys as names
    GreatestAthletes.each!(n=> writeln(n," won ", athletes[n]));

}

