#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct course{
    int course_id;
    char course[20];
};

struct student{
    char name[50];
    int roll_no;
    char course[20];
};

void add_course(struct course c, FILE *fp){
    printf("enter course id:-");
    scanf("%d",&c.course_id);
    getchar();

    printf("enter course");
    fgets(c.course,sizeof(c.course),stdin);
    c.course[strcspn(c.course, "\n")] = '\0';

    
    fprintf(fp, "%d %s\n",c.course_id,c.course);

    printf("course added successfull");
    
    
}


 void register_student(struct student s, FILE *fp){
    printf("enter student name ");
    getchar();
    fgets(s.name,sizeof(s.name),stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("enter roll no");
    scanf("%d",&s.roll_no);
    getchar();

    
    printf("enter course");
    fgets(s.course,sizeof(s.course),stdin);
    s.course[strcspn(s.course, "\n")] = '\0';

    
    FILE *fc=fopen("course.txt","r");
    
    int cid;
    char cname[20];
    int found=0;

    while(fscanf(fc,"%d %s",&cid,cname) !=EOF){
        if(strcmp(cname,s.course)==0){
            found=1;
            break;
        }
    }
    fclose(fc);

    if(!found){
        printf("\n course not found please add course first\n");
        return;
    }

    fprintf(fp,"%s %d %s\n",s.name,s.roll_no,s.course);

    printf("student register successful\n");
 }



 void view_registrations() {
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("❌ No students registered yet.\n");
        return;
    }

    struct student s;

    printf("\n==== All Registrations ====\n");
    while (fscanf(fp, "%s %d %s", s.name, &s.roll_no, s.course) != EOF) {
        printf("\nName: %s\nRoll No: %d\nCourse: %s\n", s.name, s.roll_no, s.course);
    }
    fclose(fp);
}

void delete_course(){
    FILE *fc=fopen("course.txt","r");
    if(fc==NULL){
        printf("course file not found");
        return;
    }

    FILE *ftemp= fopen("temp_course.txt","w");

    int cid;
    char cname[20];
    char del_course[20];
    int found=0;

    printf("enter course name to delete");
    getchar();
    fgets(del_course, sizeof(del_course),stdin);
    del_course[strcspn(del_course, "\n")]= '\0';

    while(fscanf(fc, "%d %s",&cid,cname) !=EOF){
        if(strcmp(cname,del_course)==0){
            found=1;
            continue;
        }
        fprintf(ftemp,"%d %s\n",cid,cname);
    }

    fclose(fc);
    fclose(ftemp);

    if(!found){
        printf("course not found");
        remove("temp_course.txt");
        return;
    }

    remove("course.txt");
    rename("temp_course.txt","course.txt");

    printf("course deleted successfull");

}


int main(){

    
    struct course c;
    struct student s;

    while(1){

        FILE *fp;
        printf("\n enter 1 for add course\n");
        printf("enter 2 for register student\n");
        printf("enter 3 to view registration\n");
        printf("enter 4 to delete course\n");
        printf("enter 5 to exit\n");

        int choice;
        printf("enter your choice");
        scanf("%d",&choice);
        
        switch(choice){
            
            case 1:
            fp= fopen("course.txt","a+");
            add_course(c, fp);
            fclose(fp);
            break;

            case 2:
            fp= fopen("student.txt","a+");
            register_student(s,fp);
            fclose(fp);
            break;

            case 3:
            view_registrations();
            break;

            case 4:
            delete_course();
            break;



            case 5:
            printf("exit program successfull");
            exit(0);


            default:
            printf("enter valid choice");
            break;

        }
    }

   
    return 0;
}
