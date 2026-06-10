import std.stdio, std.algorithm;

Student[] gStudents = 
  [
    Student("Mike"          ,2.7f, 42, true),
    Student("Bob"           ,4.0f, 43, false),
    Student("Abdhul"        ,3.9f, 44, true),
    Student("Sara"          ,3.9f, 45, true),
    Student("Sushmita"      ,4.0f, 46, true),
    Student("Homer Simpson" ,1.0f, 47, false),
  ];

struct Student{
  string mName;
  float  mGPA;
  int    mStudentID;
  bool   mIsOnCampus;

  bool IsElgible(){
    return mGPA >=3.0 && mIsOnCampus;
  }

  string toString(){
    return mName;
  }
}

void main(){
  gStudents.filter!(s => s.IsElgible)().writeln;
}
