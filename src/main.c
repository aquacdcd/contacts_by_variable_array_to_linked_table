
#include "utils.h"
void find_contact_by_name(int num,contact **contacts);
int main(void)
{
    int mode=0;
    int num=0;
    int capacity=0;
    contact *new_key=NULL;
    contact **contacts = NULL; 
    load_contacts(&num,&capacity,&contacts);
    while(mode!=-1){
    printf("请输入数字 -1:退出通讯录 1:新建联系人 2:查找联系人 3:删除联系人 4:打印所有联系人 5:按名字重新排序\n");
    scanf("%d",&mode);
    while (getchar() != '\n');  
    if(mode==-1){
        break;
    }    
    switch (mode){
        case 1:
            ensure_capacity(&num,&capacity,&contacts);
            new_key=creat_contact();
            add_contact_to_list(contacts,&num,new_key);
            break;
        case 2:
            find_contact_by_name(num,contacts);
            break;
        case 3:
            delete_contact(&num,contacts);
            break;
            
        case 4:
            print_all_contact(contacts,num);
            break;  
        case 5:
            sort_contact(contacts,num);
            break;
    }   
}
    save_contacts(contacts,num);
    cleanup(contacts,num);
    return 0;
}

void find_contact_by_name(int num,contact **contacts)
{
    int isfind=0;
    char name_to_find[50];
    printf("请输入要查找联系人的名字\n");
    fgets(name_to_find,50,stdin);
    name_to_find[strcspn(name_to_find, "\n")] = '\0'; // 去掉换行符
    for(int i=0;i<num;i++){
        if(strcmp(name_to_find,contacts[i]->name)==0){
            printf("%d: %s %s %s\n",i+1,contacts[i]->name,contacts[i]->phone,contacts[i]->email);
            isfind=1;
        }
    }
    if(isfind==0){
        printf("该联系人不存在\n");
    }
}
