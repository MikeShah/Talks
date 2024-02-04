// @ inheritance.d
import std.stdio;

interface Dog{
	void Bark();
	void Walk();
}

class Husky : Dog{
	void Bark(){ writeln("Husky Bark!"); }
	void Walk(){ writeln("Husky Walk!"); }
}

class GoldenRetriever : Dog{
	void Bark(){ writeln("GoldenRetriever Bark!"); }
	void Walk(){ writeln("GoldenRetriever Walk!"); }
}

void main(){

	Dog dog1 = new Husky;
	Dog dog2 = new GoldenRetriever;
	
	Dog[] collection;
	collection ~= dog1;
	collection ~= dog2;
	foreach(doggy ; collection){
		doggy.Bark();
	}

}

