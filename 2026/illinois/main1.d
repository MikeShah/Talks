import std.stdio;

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
}

void main(){

  // Find all the active students who are elgible for awards
  Student[] elgibleStudents; 
  foreach(s ; gStudents){
    if(s.mGPA >= 3.0 && s.mIsOnCampus){
      elgibleStudents ~= s;
    }
  }
  elgibleStudents.writeln;
}
