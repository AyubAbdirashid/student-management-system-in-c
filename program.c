#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// some global variables
int i,j;
int LineLenth;
char StudentID[10];
FILE *AllStudents;
FILE *AllCourses;
FILE *ExistingAllStudents;
FILE *TempAllStudents;
FILE *ExistingAllCourses;
FILE *TempAllCourses;
// end

bool IsRunning = true;
void Menu();
void AddNewStudent();
void ShowAllStudents();
int  SearchStudent(char StudentID[10]);
void EditStudent(char StudentID[10]);
void  DeleteStudent(char StudentID[10]);
int DeleteAllStudents();
int IsAlreadyExists(char GivenLine[30],char InfoType);
void ErrorAndRestart(char *Error[100]);
void UserGuideline();
void AboutUs();
void GoBackOrExit();
void ExitProject();

int main()
{
    while(IsRunning)
    {
        Menu();
        int Option;
        scanf("%d",&Option);
        switch(Option)
        {
        case 0:
            IsRunning = false;
            break;
        case 1:
            AddNewStudent();
            break;
        case 2:
            ShowAllStudents();
            break;
        case 3:
        {
            system("cls");
            printf("\n\t\t **** Search Students ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int IsFound = SearchStudent(StudentID);
            if(!IsFound)
            {
                printf(" !!!!!!!! No Student Found !!!!!!!!!\n");
            }
            printf("\n");
            GoBackOrExit();
            break;
        }
        case 4:
            system("cls");
            printf("\n\t\t **** Edit a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int IsFound = SearchStudent(StudentID);

            if(IsFound)
            {
                EditStudent(StudentID);
            }
            else
            {
                printf(" No Student Found\n");
            }
            break;
        case 5:
            system("cls");
            printf("\n\t\t **** Delete a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            DeleteStudent(StudentID);
            break;
        case 6:
        {
            char Sure = 'N';
            getchar();
            printf(" Are you sure want to delete all the students? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y')
            {
                int IsDeleted = DeleteAllStudents();
                if(IsDeleted)
                {
                    printf(" Success\n");
                }
                else
                {
                    printf(" Your Data is Safe.\n");
                }
            }
            else
            {
                printf(" Your Data is Safe.\n");
            }
            break;
        }

        case 7:
            //ClearWindow();
            break;
        case 8:
            //UserGuideline();
            break;
        case 9:
            //AboutUs();
            break;
        default:
            break;
        }
    }

    return 0;
} // end main function

void Menu()
{
    printf("\n\n\t***Student Management System Using C***\n\n");
    printf("\t\t\tMAIN MENU\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Add a new student.\n");
    printf("\t\t[2] Show all students.\n");
    printf("\t\t[3] Search students.\n");
    printf("\t\t[4] Edit a student.\n");
    printf("\t\t[5] Delete a student.\n");
    printf("\t\t[6] Delete all students.\n");
    printf("\t\t[7] Clear the window.\n");
    printf("\t\t[i] User Guideline.\n");
    printf("\t\t[a] About Us.\n");
    printf("\t\t[0] Exit the program.\n");
    printf("\t\t=======================\n");
    printf("\t\tEnter The Choice: ");
} // end menu

void AddNewStudent()
{
    system("cls");
    printf("\n\t\t **** Add A New Student ****\n\n");

    char IDStr[10];
    char Name[20];
    char Phone[20];
    char Email[30];
    int NumberOfCourses;
    char NumberOfCoursesStr[2];
    char NewStudent[200];

    char StudentCourses[300];
    char CourseCode[300];
    char CourseName[300];

    int IsValidID = 0;
    while(!IsValidID)
    {
        printf(" Enter The ID: ");
        scanf("%s",&IDStr);
        if(IsAlreadyExists(IDStr,'i'))
        {
            printf(" Error: This ID is already exists.\n\n");
        }
        else if(strlen(IDStr) > 10)
        {
            printf(" Error: ID can not be more than 10 characters.\n\n");
        }
        else
        {
            IsValidID = 1;
        }
    }

    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Enter The Name: ");
        scanf(" %[^\n]s",&Name);
        if(strlen(Name) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }


    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" Enter The Phone: ");
        scanf("%s",&Phone);
        if(IsAlreadyExists(Phone,'p'))
        {
            printf(" This Phone Already Exists\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" Enter The Email: ");
        scanf("%s",&Email);
        if(IsAlreadyExists(Email,'e'))
        {
            printf(" This Email Already Exists.\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }
    int IsValidNumberOfCourse = 0;
    while(!IsValidNumberOfCourse)
    {
        printf(" Number of courses: ");
        scanf("%d",&NumberOfCourses);
        if(NumberOfCourses <= 0 || NumberOfCourses > 4)
        {
            printf(" Error: Number of courses can not be more than 4 and lees than 1.\n\n");
            IsValidNumberOfCourse = 0;
        }
        else
        {
            IsValidNumberOfCourse = 1;
        }
    }

    itoa(NumberOfCourses,NumberOfCoursesStr,10);

    NewStudent[0] = 0;
    strcat(NewStudent,IDStr);
    strcat(NewStudent,"|");
    strcat(NewStudent,Name);
    strcat(NewStudent,"|");
    strcat(NewStudent,Phone);
    strcat(NewStudent,"|");
    strcat(NewStudent,Email);
    strcat(NewStudent,"|");
    strcat(NewStudent,NumberOfCoursesStr);
    strcat(NewStudent,"\n");

    AllCourses  = fopen("data/All-Courses.txt","a");
    StudentCourses[0] = 0;
    strcat(StudentCourses,IDStr);
    int IsValidCourseCode;
    int IsValidCourseName;
    getchar();
    for(i=0; i<NumberOfCourses; i++)
    {
        IsValidCourseCode = 0;
        while(!IsValidCourseCode)
        {
            printf(" Enter Course %d Code: ",i+1);
            scanf("%s",&CourseCode);

            if(strlen(CourseCode) > 5){
                printf(" Error: Course Code can not be more than 5 characters.\n\n");
                IsValidCourseCode = 0;
            }else{
                IsValidCourseCode = 1;
            }
        }

        IsValidCourseName = 0;
        while(!IsValidCourseName)
        {
            printf(" Enter Course %d Name: ",i+1);
            scanf(" %[^\n]s",&CourseName);

            if(strlen(CourseName) > 10){
                printf(" Error: Course Name can not be more than 10 characters.\n");
            }else{
                break;
            }
        }
        strcat(StudentCourses,"|");
        strcat(StudentCourses,CourseCode);
        strcat(StudentCourses,"|");
        strcat(StudentCourses,CourseName);
    }
    strcat(StudentCourses,"\n");
    AllStudents = fopen("data/All-Students.txt","a");
    fprintf(AllStudents,NewStudent);
    fclose(AllStudents);

    fprintf(AllCourses,StudentCourses);
    strcat(StudentCourses,"\n");
    fclose(AllCourses);

    printf(" Successfully Added The Student.\n");
    GoBackOrExit();
}

void ShowAllStudents()
{
    system("cls");

    printf("\n\t\t **** All Students ****\n\n");
    printf("|==========|====================|====================|==============================|=============|\n");
    printf("|    ID    |        Name        |    Phone Number    |          Email               |  NO.Course  |\n");
    printf("|==========|====================|====================|==============================|=============|\n");

    AllStudents = fopen("data/All-Students.txt","r");

    LineLenth = 200;
    char Student[LineLenth];

    while(fgets(Student,LineLenth,AllStudents))
    {
        printf("|");
        int TotalSpace = 10;
        int j;
        int Pipe = 0;
        for(i=0; i<strlen(Student)-1; i++)
        {
            if(Student[i] == '|')
            {
                Pipe++;
                for(j=0; j<TotalSpace; j++)
                {
                    printf(" ");
                }
                printf("|");
                if(Pipe == 1 || Pipe == 2)
                {
                    TotalSpace = 20;
                }
                else if(Pipe == 3)
                {
                    TotalSpace = 30;
                }
                else if(Pipe == 4)
                {
                    TotalSpace = 13;
                }
            }
            else
            {
                printf("%c",Student[i]);
                TotalSpace--;
            }
        }
        for(j=1; j<=TotalSpace; j++)
        {
            printf(" ");
        }
        printf("|\n");
        printf("|----------|--------------------|--------------------|------------------------------|-------------|\n");
    }
    fclose(AllStudents);

    GoBackOrExit();
}

int SearchStudent(char StudentID[10])
{
    system("cls");
    char ThisStudetID[10];
    int StudentFound = 0;
    int Pipe;
    AllStudents = fopen("data/All-Students.txt","r");
    LineLenth = 200;
    char Student[LineLenth];

    while(fgets(Student,LineLenth,AllStudents))
    {
        for(i=0; Student[i] != '|'; i++)
        {
            ThisStudetID[i] = Student[i];
        }
        ThisStudetID[i] = '\0';
        if(strcmp(StudentID,ThisStudetID) == 0)
        {
            StudentFound = 1;
            break;
        }
        else
        {
            StudentFound = 0;
        }
    }

    if(StudentFound)
    {
        printf("\n One Student Found for ID: %s\n\n",StudentID);
        printf(" Student Informations\n");

        printf(" ID:    ");
        Pipe = 0;
        for(i=0; i<strlen(Student); i++)
        {
            if(Student[i] == '|')
            {
                Pipe++;
                printf("\n");
                if(Pipe == 1)
                {
                    printf(" Name:  ");
                }
                else if(Pipe == 2)
                {
                    printf(" Phone: ");
                }
                else if(Pipe == 3)
                {
                    printf(" Email: ");
                }
                else if(Pipe == 4)
                {
                    printf("\n Total Number of Courses: ");
                }
            }
            else
            {
                printf("%c",Student[i]);
            }
        }
    }

    int CourseFound = 0;
    AllCourses = fopen("data/All-Courses.txt","r");
    char Course[LineLenth];

    while(fgets(Course,LineLenth,AllCourses))
    {
        for(i=0; Course[i] != '|'; i++)
        {
            ThisStudetID[i] = Course[i];
        }
        ThisStudetID[i] = '\0';
        if(strcmp(StudentID,ThisStudetID) == 0)
        {
            CourseFound = 1;
            break;
        }
        else
        {
            CourseFound = 0;
        }
    }
    int CourseCount = 1;
    if(CourseFound)
    {
        Pipe = 1;
        for(i=0; i<strlen(Course); i++)
        {
            if(Course[i] == '|')
            {

                Pipe++;
                if(Pipe > 2 && Pipe %2 != 0)
                {
                    printf("\n Course %d Name: ",CourseCount);
                    CourseCount++;
                }
                else
                {
                    if(CourseCount != 1)
                    {
                        printf("\n");
                    }
                    printf(" Course %d Code: ",CourseCount);
                }

            }
            else if(Pipe > 1)
            {
                printf("%c",Course[i]);
            }
        }
    }
    fclose(AllStudents);
    fclose(AllCourses);
    return StudentFound;
}

void EditStudent(char StudentID[10])
{
    printf("\n\t\t **** Update The New Student ****\n\n");

    char OldName[300];
    char OldPhone[300];
    char OldEmail[300];
    char OldEmail2[300];
    OldEmail2[0] = 0;
    char OldNumberOfCoursesStr[300];
    char NewStudent[300];
    NewStudent[0] = 0;
    char StudentCourses[300];
    char OldCourseCode[300];
    char OldCourseName[300];

    char NewName[300];
    char NewPhone[300];
    char NewEmail[300];
    int NewNumberOfCourses;
    char NewNumberOfCoursesStr[2];

    char NewCourseCode[300];
    char NewCourseName[300];


    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Enter The New Name(0 for skip): ");
        scanf(" %[^\n]s",&NewName);
        if(strlen(NewName) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsNewPhone = 0;
    while(!IsNewPhone)
    {
        printf(" Enter The New Phone(0 for skip): ");
        scanf("%s",&NewPhone);
        if(IsAlreadyExists(NewPhone,'p'))
        {
            printf(" This Phone Already Exists\n");
        }
        else if(strlen(NewPhone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
        }
        else
        {
            IsNewPhone = 1;
        }
    }

    int IsNewEmail = 0;
    while(!IsNewEmail)
    {
        printf(" Enter The New Email(0 for skip): ");
        scanf("%s",&NewEmail);
        if(IsAlreadyExists(NewEmail,'e'))
        {
            printf(" This Email Already Exists.\n");
        }
        else if(strlen(NewEmail) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
        }
        else
        {
            IsNewEmail = 1;
        }
    }

    printf(" Number of New courses(0 for skip): ");
    scanf("%d",&NewNumberOfCourses);
    itoa(NewNumberOfCourses,NewNumberOfCoursesStr,10);

    int Index;
    char ThisStudetID[10];
    int StudentFound = 0;
    int Pipe;
    ExistingAllStudents = fopen("data/All-Students.txt", "r");
    TempAllStudents = fopen("data/Temp-All-Students.txt","w");
    LineLenth = 200;
    char Student[LineLenth];

    while (fgets(Student, LineLenth, ExistingAllStudents))
    {
        if (!StudentFound)
        {
            for (i = 0; Student[i] != '|'; i++)
            {
                ThisStudetID[i] = Student[i];
            }
            ThisStudetID[i] = '\0';
            if (strcmp(StudentID, ThisStudetID) == 0)
            {
                StudentFound = 1;
                Pipe = 0;
                Index = 0;
                for (i = 0; i < strlen(Student); i++)
                {
                    if (Student[i] == '|')
                    {
                        Pipe++;
                        if (Pipe == 2)
                        {
                            OldName[Index] = '\0';
                        }
                        else if (Pipe == 3)
                        {
                            OldPhone[Index] = '\0';
                        }
                        else if (Pipe == 4)
                        {
                            OldEmail[Index] = '\0';
                        }
                        Index = 0;
                    }
                    else
                    {
                        if (Pipe == 1)
                        {
                            OldName[Index] = Student[i];
                            Index++;
                        }
                        else if (Pipe == 2)
                        {
                            OldPhone[Index] = Student[i];
                            Index++;
                        }
                        else if (Pipe == 3)
                        {
                            OldEmail[Index] = Student[i];
                            Index++;
                        }
                        else if (Pipe == 4)
                        {
                            OldNumberOfCoursesStr[Index] = Student[i];
                            Index++;
                        }
                    }
                }
                OldNumberOfCoursesStr[Index] = '\0';

                strcat(NewStudent,StudentID);
                strcat(NewStudent,"|");

                if(strcmp(NewName,"0") == 0)
                {
                    strcat(NewStudent,OldName);
                }
                else
                {
                    strcat(NewStudent,NewName);
                }
                strcat(NewStudent,"|");

                if(strcmp(NewPhone,"0") == 0)
                {
                    strcat(NewStudent,OldPhone);
                }
                else
                {
                    strcat(NewStudent,NewPhone);
                }
                strcat(NewStudent,"|");

                if(strcmp(NewEmail,"0") == 0)
                {
                    strcat(NewStudent,OldEmail);
                }
                else
                {
                    strcat(NewStudent,NewEmail);
                }
                strcat(NewStudent,"|");

                if(strcmp(NewNumberOfCoursesStr,"0") == 0)
                {
                    strcat(NewStudent,OldNumberOfCoursesStr);
                }
                else
                {
                    strcat(NewStudent,NewNumberOfCoursesStr);
                    strcat(NewStudent,"\n");
                }

                fprintf(TempAllStudents,NewStudent);
            }
            else
            {
                fprintf(TempAllStudents,Student);
                StudentFound = 0;
            }
        }
        else
        {
            fprintf(TempAllStudents,Student);
        }
    }
    fclose(ExistingAllStudents);
    fclose(TempAllStudents);
    remove("data/All-Students.txt");
    rename("data/Temp-All-Students.txt", "data/All-Students.txt");

    if(NewNumberOfCourses > 0)
    {
        ExistingAllCourses = fopen("data/All-Courses.txt","r");
        TempAllCourses = fopen("data/Temp-All-Courses.txt","w");
        int IsCourseFound = 0;
        LineLenth = 200;

        char StudentCourses[300];
        char Course[LineLenth];
        char CourseCode[300];
        char CourseName[300];

        StudentCourses[0] = 0;
        int IsValidCourseCode;
        int IsValidCourseName;
        while (fgets(Course, LineLenth, ExistingAllCourses))
        {
            if (!IsCourseFound)
            {
                for (i = 0; Course[i] != '|'; i++)
                {
                    ThisStudetID[i] = Course[i];
                }
                ThisStudetID[i] = '\0';
                if (strcmp(StudentID, ThisStudetID) == 0)
                {
                    IsCourseFound = 1;
                    for(i=0; i<NewNumberOfCourses; i++)
                    {
                        strcat(StudentCourses,StudentID);
                        IsValidCourseCode = 0;
                        while(!IsValidCourseCode)
                        {
                            printf(" Enter New Course %d Code: ",i+1);
                            scanf("%s",&CourseCode);

                            if(strlen(CourseCode) > 5){
                                printf(" Error: Course Code can not be more than 5 characters.\n\n");
                                IsValidCourseCode = 0;
                            }else{
                                IsValidCourseCode = 1;
                            }
                        }

                        IsValidCourseName = 0;
                        while(!IsValidCourseName)
                        {
                            printf(" Enter New Course %d Name: ",i+1);
                            scanf(" %[^\n]s",&CourseName);

                            if(strlen(CourseName) > 10){
                                printf(" Error: Course Name can not be more than 10 characters.\n");
                            }else{
                                break;
                            }
                        }

                        strcat(StudentCourses,"|");
                        strcat(StudentCourses,CourseCode);
                        strcat(StudentCourses,"|");
                        strcat(StudentCourses,CourseName);
                    }
                    strcat(StudentCourses,"\n");
                    fprintf(TempAllCourses,StudentCourses);
                }
                else
                {
                    fprintf(TempAllCourses,Course);
                }
            }
            else
            {
                fprintf(TempAllCourses,Course);
            }
        }

        fclose(ExistingAllStudents);
        fclose(TempAllStudents);
        remove("data/All-Courses.txt");
        rename("data/Temp-All-Courses.txt", "data/All-Courses.txt");
    }

    printf(" Student Updated Successfully.\n");
    GoBackOrExit();
}

void DeleteStudent(char StudentID[10])
{
    char ThisStudetID[10];
    int StudentFound = 0;
    int Pipe;
    ExistingAllStudents = fopen("data/All-Students.txt","r");
    TempAllStudents = fopen("data/Temp-All-Students.txt","w");
    LineLenth = 200;
    char Student[LineLenth];

    while(fgets(Student,LineLenth,ExistingAllStudents))
    {
        for(i=0; Student[i] != '|'; i++)
        {
            ThisStudetID[i] = Student[i];
        }
        ThisStudetID[i] = '\0';
        if(strcmp(StudentID,ThisStudetID) == 0)
        {
            StudentFound = 1;
        }
        else
        {
            StudentFound = 0;
            fprintf(TempAllStudents,Student);
        }
    }
    fclose(ExistingAllStudents);
    fclose(TempAllStudents);

    int CourseFound = 0;
    ExistingAllCourses = fopen("data/All-Courses.txt","r");
    TempAllCourses = fopen("data/Temp-All-Courses.txt","w");
    char Course[LineLenth];

    while(fgets(Course,LineLenth,ExistingAllCourses))
    {
        for(i=0; Course[i] != '|'; i++)
        {
            ThisStudetID[i] = Course[i];
        }
        ThisStudetID[i] = '\0';
        if(strcmp(StudentID,ThisStudetID) == 0)
        {
            CourseFound = 1;
        }
        else
        {
            fprintf(TempAllCourses,Course);
            CourseFound = 0;
        }
    }
    fclose(ExistingAllCourses);
    fclose(TempAllCourses);
    remove("data/All-Students.txt");
    remove("data/All-Courses.txt");
    rename("data/Temp-All-Students.txt", "data/All-Students.txt");
    rename("data/Temp-All-Courses.txt", "data/All-Courses.txt");

    if(StudentFound || CourseFound)
    {
        printf(" Successfully Deleted The Student.\n");
    }
    else
    {
        printf(" Student/Courses Not Found!\n Make sure you enter the correct ID.\n\n");
    }
    GoBackOrExit();
}

int DeleteAllStudents()
{
    remove("data/All-Students.txt");
    remove("data/All-Courses.txt");
    return 1;
}

int IsAlreadyExists(char GivenLine[30],char InfoType)
{
    char ThisPhone[20];
    char ThisEmail[30];
    char ThisStudetID[10];
    int Index;
    int Pipe;
    AllStudents = fopen("data/All-Students.txt", "r");
    LineLenth = 200;
    char Student[LineLenth];
    int EmailFound = 0;
    int PhoneFound = 0;
    while (fgets(Student, LineLenth, AllStudents))
    {
        for(i=0; Student[i] != '|'; i++)
        {
            ThisStudetID[i] = Student[i];
        }
        ThisStudetID[i] = '\0';
        if(InfoType == 'i' && strcmp(GivenLine,ThisStudetID) == 0)
        {
            return 1; // id already exists
        }

        Pipe = 0;
        Index = 0;
        for (i = 0; i < strlen(Student); i++)
        {
            if (Student[i] == '|')
            {
                Pipe++;
                if (Pipe == 3)
                {
                    ThisEmail[Index] = '\0';
                }
                else if (Pipe == 4)
                {
                    ThisPhone[Index] = '\0';
                }
                Index = 0;
            }
            else
            {
                if (Pipe == 2)
                {
                    ThisEmail[Index] = Student[i];
                    Index++;
                }
                else if (Pipe == 3)
                {
                    ThisPhone[Index] = Student[i];
                    Index++;
                }
            }
        }

        if(InfoType == 'e' && strcmp(ThisEmail,GivenLine) == 0)
        {
            EmailFound++; // to check when edit
            if(EmailFound > 1)
            {
                return EmailFound; // email already exists
            }
        }
        else if(InfoType == 'p' && strcmp(ThisPhone,GivenLine) == 0)
        {
            PhoneFound++;
            if(PhoneFound > 1)
            {
                return 1; // phone already exists
            }
        }
    }
    fclose(AllStudents);
    if(InfoType == 'p')
    {
        return PhoneFound;
    }
    else if(InfoType == 'e')
    {
        return EmailFound;
    }
    else
    {
        return 0;
    }
}

void ErrorAndRestart(char *error[100])
{
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}

void UserGuideline()
{
    printf("UserGuideline");
}

void AboutUs()
{
    printf("AboutUs");
}

void GoBackOrExit(){
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0'){
        ExitProject();
    }else{
        system("cls");
    }
    return 0;
}

void ExitProject(){
    system("cls");
    int i;
    char ThankYou[100]     = " ========= Thank You =========\n";
    char SeeYouSoon[100]   = " ========= See You Soon ======\n";
    for(i=0;i<strlen(ThankYou);i++){
        printf("%c",ThankYou[i]);
        Sleep(40);
    }
    for(i=0;i<strlen(SeeYouSoon);i++){
        printf("%c",SeeYouSoon[i]);
        Sleep(40);
    }
    exit(0);
}
