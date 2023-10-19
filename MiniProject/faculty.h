bool validateFaculty(struct faculty_details);
bool addCourse(char[], struct course_details*);
bool viewActiveCourses(char[], struct course_details*);
bool viewRemovedCourses(char[], struct course_details*);
bool removeCourse(char[], char[]);
bool activateCourse(char[], char[]);
bool modifyCourse(char[], char[], int, char[]);
bool changePassword(char[], char[]);
void removeEnrolments(char[], int);