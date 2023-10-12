#include<stdbool.h>
struct student_details{
    char studentId[6];
    char name[100];
    int age;
    char email[200];
    char password[100];
    bool isActivated;
};

struct faculty_details{
    char facultyId[4];
    char name[100];
    char email[200];
    char password[100];
    char department[50];
};
