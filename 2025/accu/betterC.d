// dmd -betterC betterC.d

extern(C) int main(){
	import core.stdc.stdio;

	auto a = 5;
	a = 5 + 2;

	printf("Hello!");

	return a;
}
