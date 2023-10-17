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

struct admin_details{
    char adminId[4];
    char password[100];
};

struct course_details{
    char courseId[5];
    char name[100];
    int total_seats;
    int available_seats;
    char facultyId[4];
    bool isActive;
};
