bool validateAdmin(struct admin_details);
bool addStudent(struct student_details*);
bool viewStudent(struct student_details*);
bool addFaculty(struct faculty_details*);
bool viewFaculty(struct faculty_details*);
bool activateStudent(char[]);
bool deactivateStudent(char[]);
bool modifyStudentDetails(char[], char[], int, char[]);
bool modifyFacultyDetails(char[], char[], char[], char[]);