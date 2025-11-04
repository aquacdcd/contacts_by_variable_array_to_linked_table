#include "utils.h"

int add(int a,int b)
{
    int c;
    c=a+b;
    return c;
}

contact* creat_contact()
{   static int id_counter=1;
    contact *p=(contact *)malloc(sizeof(contact));
    p->id=id_counter;
    id_counter++;
    printf("请输入联系人的姓名 电话号码 邮箱(按name回车phone回车email回车格式输入)\n");
    fgets(p->name,50,stdin);
    p->name[strcspn(p->name, "\n")] = '\0'; // 去掉换行符
    fgets(p->phone,20,stdin);
    p->phone[strcspn(p->phone, "\n")] = '\0'; // 去掉换行符
    fgets(p->email,50,stdin);
    p->email[strcspn(p->email, "\n")] = '\0'; // 去掉换行符
    return p;
}
void safe_free(contact** p)
{
    if (p != NULL && *p != NULL)
    {
        free(*p);  
        *p = NULL; 
    }
}
void ensure_capacity(int *num_ptr,int *capacity_ptr,contact ***contacts_ptr)
{
    int new_capacity=0;
    if(*num_ptr==*capacity_ptr){
        new_capacity=(*capacity_ptr==0)?8:*capacity_ptr*2;
        contact **temp=realloc(*contacts_ptr,sizeof(contact *)*(new_capacity));
            if(temp==NULL){
                printf("内存分配失败\n");
            }else{
                *contacts_ptr=temp;
                *capacity_ptr=new_capacity;
            }
    }
}
void delete_contact(int *num_ptr,contact **contacts)
{
    int fnum=0;
    printf("请输入想要删除的联系人的序号\n");
    scanf("%d",&fnum);
    while (getchar() != '\n');  // 读取并丢弃直到回车为止
    if(fnum>*num_ptr||fnum<1){
        printf("该联系人不存在，目前共有%d个联系人/n",*num_ptr);
    }else{
        safe_free(&contacts[fnum-1]);
        int i;
            for(i=fnum-1;i<*num_ptr-1;i++){
                contacts[i]=contacts[i+1];
            }
            contacts[i]=NULL;
            *num_ptr=*num_ptr-1;
    }
}
void print_all_contact(contact **contacts,int num)
{
    int i=0;
    printf("--- 所有联系人 ---\n");
    for(i=0;i<num;i++){
        printf("id=%d %d: %s %s %s\n",contacts[i]->id,i+1,contacts[i]->name,contacts[i]->phone,contacts[i]->email);
    }
    printf("-------------------\n");

}
void cleanup(contact **contacts,int num)
{
    int i;
    for(i=0;i<num;i++){
        if(contacts[i]!=NULL){
            free(contacts[i]);
            contacts[i]=NULL;
        }
    }
    free(contacts);
}
void sort_contact(contact **contacts,int num)
{
    int i,j;
    contact* temp;
    for(i=0;i<num-1;i++){
        for(j=0;j<num-1-i;j++){
            if(strcmp(contacts[j]->name,contacts[j+1]->name)>0){
                temp=contacts[j];
                contacts[j]=contacts[j+1];
                contacts[j+1]=temp;
            }
        }
    }
}
void save_contacts(contact **contacts,int num)
{
    FILE *f=fopen("contacts.dat","wb");
    if(f==NULL){
        printf("保存失败，无法创建文件。\n");
        return;
    }
    for(int i=0;i<num;i++){
        if(contacts[i]!=NULL){
            fwrite(contacts[i],sizeof(contact),1,f);
        }
    }
    fclose(f);
    printf("通讯录已经成功保存到contacts.dat文件\n");
}
void load_contacts(int *num_ptr,int *capacity_ptr,contact ***contacts_ptr)
{
    FILE *f=fopen("contacts.dat","rb");
    if(f==NULL){
        printf("未找到contacts.dat文件,启用一个新的空通讯录\n");
        return;
    }
    contact temp_contact_buffer;
    contact *new_insurance_key=NULL;
    while(fread(&temp_contact_buffer,sizeof(contact),1,f)){
        ensure_capacity(num_ptr,capacity_ptr,contacts_ptr);
        new_insurance_key=(contact *)malloc(sizeof(contact));
        if(new_insurance_key==NULL){
            printf("加载失败，内存不足\n");
            break;
        }
        *new_insurance_key=temp_contact_buffer;
        add_contact_to_list(*contacts_ptr,num_ptr,new_insurance_key);
        /*(*contacts_ptr)[*num_ptr]=new_insurance_key;
        *num_ptr=*num_ptr+1;*/
    }
    fclose(f);
    printf("已从contacts.dat文件加载到%d个联系人\n",*num_ptr);
}
void add_contact_to_list(contact **contacts,int *num_ptr,contact *new_key)
{
    contacts[*num_ptr]=new_key;
    (*num_ptr)++;
}
void find_contact(int num,contact **contacts)
{
    int fnum;
    printf("请输入该联系人的数字\n");//查找和删除联系人先用数字查找，之后升级成可以用名字查找，再之后可用phone和email查找
            scanf("%d",&fnum);
            while (getchar() != '\n');  // 读取并丢弃直到回车为止
            if(fnum>num||fnum<1){
                printf("该联系人不存在\n");
                return;
            }
    printf("%s %s %s\n",contacts[fnum-1]->name,contacts[fnum-1]->phone,contacts[fnum-1]->email);

}