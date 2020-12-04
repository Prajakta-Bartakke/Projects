
#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

typedef int BOOL;

using namespace std;

#define MAXFILES 100
#define FILESIZE 1024
#define READ 4
#define WRITE 2
#define TRUE 1
#define FALSE 0
#define REGULAR 1
#define SPECIAL 2
#define INVALID -1
#define NOFILEPRESENT -2

struct inode
{
 char Fname[50];   
 int Inode_number;
 int File_Size;
 int File_Type;
 int Actual_size;
 int Link_Count;
 int Reference_Count;
 char *data;
 struct inode*next;
}obj_inode;

typedef struct inode INODE;
typedef struct inode*PINODE;
typedef struct inode **PPINODE;

struct SuperBlock
{
 int TotalInodes;
 int FreeInode;
}obj_super;

typedef struct FileTable    
{
 int ReadOffset;
 int WriteOffset;
 int count;
 PINODE ptr;
 int Mode;
}FILETABLE,*PFILETABLE;

struct UFDT
{
 PFILETABLE ufdt[MAXFILES];
}UFDTObj;


PINODE Head=NULL;          


////////////////////////////////////////////
//
//function name:	Create_UFDT
//input parametre:	none
//return value:	none
//description:		used to create file descriptor table
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void Create_UFDT()
{
 int i=0;
 
 for(i=0;i<MAXFILES;i++)
 {
  UFDTObj.ufdt[i]=NULL;
 }

}

////////////////////////////////////////////
//
//function name:	Create_DILB
//input parametre:	none
//return value:	none
//description:		used to disk inode list block linked list of inodes
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void Create_DILB()     //linked list inode chi
{
 int i=1;
 PINODE newn=NULL;
 PINODE temp=Head;
 while(i<=MAXFILES)
 {
  newn=(PINODE)malloc(sizeof(INODE));
  newn->Inode_number=i;
  newn->File_Size=FILESIZE;
  newn->File_Type=0;
  newn->Actual_size=0;
  newn->Link_Count=0;
  newn->Reference_Count=0;
  newn->data=NULL;
  newn->next=NULL;
  
  if(Head==NULL)
  {
   Head=newn;
   temp=newn;
  }
  else    
  {
   temp->next=newn;
   temp=temp->next;
  }
  
 i++;
 }
 printf("\nDILB created succssfully\n");
}

////////////////////////////////////////////
//
//function name:	CreateSuperblock
//input parametre:	none
//return value:	none
//description:		used to create superblock
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////


void CreateSuperBlock()
{
 obj_super.TotalInodes=MAXFILES;
 obj_super.FreeInode=MAXFILES;
 
 printf("\nsuper block created successfully\n");
}

////////////////////////////////////////////
//
//function name:	SetEnvironment
//input parametre:	none
//return value:	none
//description:		whole setup required is made here
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void SetEnvironment()
{
 Create_DILB();
 CreateSuperBlock();
 Create_UFDT();
 printf("\nEnvironment for the virtual file system is set..\n");
}

////////////////////////////////////////////
//
//function name:	ChkFile
//input parametre:	none
//return value:	boolean
//description:		used to check whether file is present or not
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

bool ChkFile(char *name)                    
{
 if(name==NULL)
 {
  return INVALID;
 }
 PINODE temp=Head;  //if file type is 0 means file is deleted
 
 while(temp!=NULL)
 {
  if(temp->File_Type!=0)   //regular or any madhe aat jail
  {
   if(strcmp(temp->Fname,name)==0)
   {
    break;
   }
  }
  temp=temp->next;
 }
 
 if(temp==NULL)    //flase mhnje present nahi
 {
  return FALSE;
 }
 else
 {
  return TRUE;
 } 
}

////////////////////////////////////////////
//
//function name:	LS
//input parametre:	none
//return value:	none
//description:		used to list out all the present files
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void LS()
{
 if(obj_super.TotalInodes-obj_super.FreeInode==0)
 {
  printf("Error:no files present at the moment\n");
  return;
 }
 
 PINODE temp=Head;
 
 while(temp!=NULL)
 {
  if(temp->File_Type!=0)
  {
  printf("%s\n",temp->Fname);
  }
  temp=temp->next;
 }
}

////////////////////////////////////////////
//
//function name:	LSFD
//input parametre:	none
//return value:	none
//description:		used to list out all the present files with respextive file descriptor
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void LSFD()
{
 if(obj_super.TotalInodes-obj_super.FreeInode==0)
 {
  printf("Error:no files present at this moment\n");
  return;
 }
 else
 {
  int i=0;
  
  for(i=0;i<MAXFILES;i++)
  {
   if(UFDTObj.ufdt[i]==NULL)
   {
    break;
   }
   else
   {
    printf("File name:%s\tFile Descriptor:%d\t",UFDTObj.ufdt[i]->ptr->Fname,i);
    printf("\n");
   }
  }
 
 }

}

////////////////////////////////////////////
//
//function name:	CreateFile
//input parametre:	string and integer
//return value:	integer
//description:		used to create a file returns file descriptor
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

int CreateFile(char *name,int permission)
{
 BOOL bret=ChkFile(name);
 
 if(name==NULL || (permission>READ+WRITE) || permission<WRITE)
 {
  return -1;
 }
 
 if(bret==TRUE)
 {
  printf("Error:file alraedy present\n");
  return -1;
 }
 if(obj_super.FreeInode==0)
 {
  printf("there is no inode to create any file\n");
  return -1;
 }
 //search from empty entry from UFDT
 int i=0;
 
 for(i=0;i<MAXFILES;i++)
 {
  if(UFDTObj.ufdt[i]==NULL)
  {
   break;
  }
 }
 UFDTObj.ufdt[i]=(PFILETABLE)malloc(sizeof(FILETABLE));
 UFDTObj.ufdt[i]->ReadOffset=0;
 UFDTObj.ufdt[i]->WriteOffset=0;
 UFDTObj.ufdt[i]->Mode=permission;
 
 PINODE temp=Head;
 
 while(temp!=NULL)
 {
  if(temp->File_Type==0)
  {
   break;
  }
  temp=temp->next;
 }
 UFDTObj.ufdt[i]->ptr=temp;
 
 strcpy(UFDTObj.ufdt[i]->ptr->Fname,name);   
 UFDTObj.ufdt[i]->ptr->File_Type=REGULAR;    
 UFDTObj.ufdt[i]->ptr->Actual_size=0;
 UFDTObj.ufdt[i]->ptr->Link_Count=1;
 UFDTObj.ufdt[i]->ptr->Reference_Count=1;
 UFDTObj.ufdt[i]->ptr->data=(char*)malloc(sizeof(FILESIZE));
 
 obj_super.FreeInode--;
 
 return i;
}

/*
break;

total-free



*/

////////////////////////////////////////////
//
//function name:	GetFdFromName
//input parametre:	string
//return value:	intger
//description:		used to return the file descriptor for respective file
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

int GetFdFromName(char *name)  
{
 if(name==NULL)
 {
  return -1;
 }
 int i=0,j=obj_super.TotalInodes-obj_super.FreeInode;
 
 if(j==0)     //no files has been created
 {
  return -1;
 }
 
 for(i=0;i<MAXFILES && UFDTObj.ufdt[i]!=NULL ;i++)    
{
  if(strcmp(UFDTObj.ufdt[i]->ptr->Fname,name)==0)
  {
   break;
  }
 }
 if(UFDTObj.ufdt[i]==NULL || i==MAXFILES)
 {
  return -1;
 }
 else
 {
  return i;
 }
}

////////////////////////////////////////////
//
//function name:	Delete
//input parametre:	string
//return value:	none
//description:		used to delete file
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void Delete(char *name)
{
 if(name==NULL)
 {
  printf("Error:Memory not allocated\n");
  return;
 }
 BOOL bret=ChkFile(name);
 
 if(bret==FALSE)
 {
  printf("Error:file not found\n");
  return;
 }
 
 if((obj_super.TotalInodes-obj_super.FreeInode)==0)      
 {
  printf("Error:No files present at this moment\n");
  return;
 }
 //if cha khali ala mhnje 1 tari file present ahe
 int i=0;
 int fd=GetFdFromName(name);
 
 for(;i<fd;){i++;}
 
  //UFDTObj.ufdt[i]->ptr->Fname="";     //??
  UFDTObj.ufdt[i]->ptr->File_Type=0;
  UFDTObj.ufdt[i]->ptr->Actual_size=0;
  UFDTObj.ufdt[i]->ptr->Link_Count=0;
  UFDTObj.ufdt[i]->ptr->Reference_Count=0;
  
  free (UFDTObj.ufdt[i]->ptr->data);
  
  free (UFDTObj.ufdt[i]); 
  
  obj_super.FreeInode++;
}

/*

create kartana cha permissions ani open kartana cha permisiion check kara

*/
////////////////////////////////////////////
//
//function name:	open
//input parametre:	string and integer
//return value:	integer
//description:		used to open file
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

int open(char *name,int permission)
{
 if(name==NULL || permission>READ+WRITE || permission<WRITE)
 {
  return -1;
 }
 
 int j=obj_super.TotalInodes-obj_super.FreeInode;
 BOOL bret=ChkFile(name);
 int i=0;
 
 if(j!=0)
 {
  if(bret==TRUE)
  {
   for(i=0;i<MAXFILES;i++)
   {
    if(strcmp(UFDTObj.ufdt[i]->ptr->Fname,name)==0 && (UFDTObj.ufdt[i]->Mode!=permission))
    {
     break;
    }
    if((strcmp(UFDTObj.ufdt[i]->ptr->Fname,name)==0)  && (UFDTObj.ufdt[i]->Mode==permission))
    {
     break;
    }
   }
   if(i!=MAXFILES && (UFDTObj.ufdt[i]->Mode!=permission))
   {
    return -1;
   }
   if(i!=MAXFILES)
   {
    UFDTObj.ufdt[i]->ptr->Link_Count++;
    UFDTObj.ufdt[i]->ptr->Reference_Count++;
 
    return i;
   }
   else
   {
    return -1;
   }
  }
  else
  {
   return -1;
  }
 
 }
 else
 {
  return -1;
 } 
}
////////////////////////////////////////////
//
//function name:	close
//input parametre:	string 
//return value:	integer
//description:		used to close file
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void close(char *name)
{
 if(name==NULL)
 {
  return;
 }
 if(obj_super.TotalInodes-obj_super.FreeInode==0)
 {
  return;
 }
 BOOL bret=ChkFile(name);
 if(bret==TRUE)
 {
  int fd=GetFdFromName(name);
  int i=0;
  
  for(i=0;i<MAXFILES;i++)
  {
   if(i==fd)
   {
    break;
   }
  }
  UFDTObj.ufdt[i]->ptr->Link_Count--;
  UFDTObj.ufdt[i]->ptr->Reference_Count--;
  UFDTObj.ufdt[i]=NULL;
 }
 else
 {
  return;
 } 
}

////////////////////////////////////////////
//
//function name:	WriteFile
//input parametre:	string and string
//return value:	int
//description:		used to write to file on successful execution returns number of bytes written in file
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

int WriteFile(char *name,char *str)
{

 if(str==NULL)
 {
  return -1;
 }
 if(obj_super.TotalInodes-obj_super.FreeInode==0)
 {
  return -1;
 }
 
 int len=strlen(str);
 int i=0;int fd=0;
 BOOL bret=ChkFile(name);
 
 if(bret==FALSE)
 {
  return -1;
 }
 
 fd=GetFdFromName(name);

 if(UFDTObj.ufdt[fd]->Mode==6 || UFDTObj.ufdt[fd]->Mode==2)  
 { 
 strncpy(UFDTObj.ufdt[fd]->ptr->data+UFDTObj.ufdt[fd]->WriteOffset,str,len);    
 UFDTObj.ufdt[fd]->WriteOffset=UFDTObj.ufdt[fd]->WriteOffset+len;
 UFDTObj.ufdt[fd]->ptr->Actual_size=UFDTObj.ufdt[fd]->WriteOffset;
 
 return len;
 }
 else
 {
  return -2;
 }
 }


////////////////////////////////////////////
//
//function name:	ReadFile
//input parametre:	string and integer
//return value:	integer
//description:		used to read the file,on successful execution it returns no of bytes read
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

int ReadFile(char *name,int bytes)
{
 if(name==NULL)
 {
  return -1;
 }
 if(bytes<0)
 {
  bytes=-bytes;
 }
 BOOL bret=ChkFile(name);
 int i=0;
 if(bret==FALSE)
 {
  return -2;
 }
 else
 {
  int fd=GetFdFromName(name);
  if(UFDTObj.ufdt[fd]->Mode==READ || UFDTObj.ufdt[fd]->Mode==READ+WRITE)
  {
  if(UFDTObj.ufdt[fd]->WriteOffset==0)    
  {
   return 0;
  }
  char *arr=(char*)malloc(sizeof(int)*FILESIZE);    
  int size=0;
  
  while(i!=bytes)
  {
   size=UFDTObj.ufdt[fd]->ReadOffset;
   arr[i]=UFDTObj.ufdt[fd]->ptr->data[size];
   i++;
   UFDTObj.ufdt[fd]->ReadOffset++;
  }
  printf("entered data from file is :%s\n",arr);
  printf("read offset is :%d\n",UFDTObj.ufdt[fd]->ReadOffset);
  return i;
 }
 else
 {
  return -3;
 }
 }
}
////////////////////////////////////////////
//
//function name:	fstat
//input parametre:	string
//return value:	none
//description:		used to give the information of inode
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void fstat(char *name)
{
 if(name==NULL)
 {
  printf("Error:invalid input\n");
  return;
 }
 if(obj_super.TotalInodes-obj_super.FreeInode==0)
 {
  printf("Error:no files are present at this moment\n");
  return;
 }
 BOOL bret=ChkFile(name);
 int i=0;
 char Name[10];
 if(bret==TRUE)
 {
  for(i=0;i<MAXFILES  &&  (UFDTObj.ufdt[i]!=NULL);i++)
  {
   if(strcmp(UFDTObj.ufdt[i]->ptr->Fname,name)==0)
   {
    break;
   }
  }
   if(UFDTObj.ufdt[i]==NULL)
   {
    printf("cannot show information because file may be closed or deleted\n");
    return;
   }
   
   printf("--------------------------------\n");
   printf("File :%d\n",i+1);
   
   //strcpy(Name,UFDTObj.ufdt[i]->ptr->Fname);
   //printf("name of file:%S\n",Name);
   printf("inode number:%d\n",UFDTObj.ufdt[i]->ptr->Inode_number);
   printf("file size:%d\n",UFDTObj.ufdt[i]->ptr->File_Size);
   printf("actual size:%d\n",UFDTObj.ufdt[i]->ptr->Actual_size);
   printf("file type:%d\n",UFDTObj.ufdt[i]->ptr->File_Type);
   printf("mode of file:%d\n",UFDTObj.ufdt[i]->Mode);
   printf("link count of file is :%d\n",UFDTObj.ufdt[i]->ptr->Link_Count);
   printf("Reference count of file is :%d\n",UFDTObj.ufdt[i]->ptr->Reference_Count);
   printf("write offset:%d\n",UFDTObj.ufdt[i]->WriteOffset);
   
 }
 else
 {
  printf("Error:this file is not available\n");
 }
}

void lseek(int fd,int offset,int SEEK_MOVE)
{
 if(fd==-1)
 {
  return;
 }
 if(SEEK_MOVE>2 || SEEK_MOVE<0)
 {
  return;
 }
 if(offset>FILESIZE)
 {
  return;
 }
 if(offset<0)
 {
  offset=-offset;
 }
 
 switch(SEEK_MOVE)
 {
  case 0:                                                
        if(SEEK_MOVE==0   &&    UFDTObj.ufdt[fd]->Mode==READ)         
 {
  if(UFDTObj.ufdt[fd]->ReadOffset==0)
  {
   UFDTObj.ufdt[fd]->ReadOffset=UFDTObj.ufdt[fd]->ReadOffset+offset;
  }
  else
  {
   UFDTObj.ufdt[fd]->ReadOffset=0;
   UFDTObj.ufdt[fd]->ReadOffset=UFDTObj.ufdt[fd]->ReadOffset+offset;
  }
 }
 else if(SEEK_MOVE==0   &&    UFDTObj.ufdt[fd]->Mode==WRITE)        
 {
  if(UFDTObj.ufdt[fd]->WriteOffset==0)
  {
   UFDTObj.ufdt[fd]->WriteOffset=UFDTObj.ufdt[fd]->WriteOffset+offset;
  }
  else
  {
   UFDTObj.ufdt[fd]->WriteOffset=0;
   UFDTObj.ufdt[fd]->WriteOffset=UFDTObj.ufdt[fd]->WriteOffset+offset;
  }
 }
 else if(SEEK_MOVE==0  &&  UFDTObj.ufdt[fd]->Mode==READ+WRITE)      
 {
  if(UFDTObj.ufdt[fd]->ReadOffset==0)
  {
   UFDTObj.ufdt[fd]->ReadOffset=UFDTObj.ufdt[fd]->ReadOffset+offset;
  }
  if(UFDTObj.ufdt[fd]->ReadOffset!=0)
  {
   UFDTObj.ufdt[fd]->ReadOffset=0;
   UFDTObj.ufdt[fd]->ReadOffset=UFDTObj.ufdt[fd]->ReadOffset+offset;
   printf("new read cha offset :%d\n",UFDTObj.ufdt[fd]->ReadOffset);
  }
  if(UFDTObj.ufdt[fd]->WriteOffset==0)
  {
   UFDTObj.ufdt[fd]->WriteOffset=UFDTObj.ufdt[fd]->WriteOffset+offset;
  }
  if(UFDTObj.ufdt[fd]->WriteOffset!=0)
  {
   UFDTObj.ufdt[fd]->WriteOffset=0;
   UFDTObj.ufdt[fd]->WriteOffset=UFDTObj.ufdt[fd]->WriteOffset+offset;
  }
 }

  
  break;
  
  case 1:                                                        
      if(SEEK_MOVE==1   &&    UFDTObj.ufdt[fd]->Mode==READ)         
 {
    UFDTObj.ufdt[fd]->ReadOffset=UFDTObj.ufdt[fd]->ReadOffset+offset;
 }
 else if(SEEK_MOVE==1   &&    UFDTObj.ufdt[fd]->Mode==WRITE)            
 {
  UFDTObj.ufdt[fd]->WriteOffset=UFDTObj.ufdt[fd]->WriteOffset+offset;
 }
 else if(SEEK_MOVE==1  &&  UFDTObj.ufdt[fd]->Mode==READ+WRITE)      
 {
  UFDTObj.ufdt[fd]->ReadOffset=UFDTObj.ufdt[fd]->ReadOffset+offset;
  UFDTObj.ufdt[fd]->WriteOffset=UFDTObj.ufdt[fd]->WriteOffset+offset;
 }
 
  break;
  
  case 2:
        if(SEEK_MOVE==2   &&    UFDTObj.ufdt[fd]->Mode==READ)         
 {
        UFDTObj.ufdt[fd]->ReadOffset=FILESIZE-offset;
 }
 else if(SEEK_MOVE==2   &&    UFDTObj.ufdt[fd]->Mode==WRITE)            
 {
        UFDTObj.ufdt[fd]->WriteOffset=FILESIZE-offset;
 }
 else if(SEEK_MOVE==2  &&  UFDTObj.ufdt[fd]->Mode==READ+WRITE)      
 {
        UFDTObj.ufdt[fd]->ReadOffset=FILESIZE-offset;
        UFDTObj.ufdt[fd]->WriteOffset=FILESIZE-offset;
 }     
  
  break;
  
 }
}

void format()
{
 PINODE temp=Head;
 PINODE temp1=NULL;
 int i=0;
 
 while(temp->File_Type!=0 && Head!=NULL) 
 {
  free (temp->data);
  temp=temp->next;
 }
 
 temp=Head;
 
 while(Head!=NULL)    //inode completely delete 
 {
  temp1=Head;
  Head=Head->next;
  free (temp1);
 }
 
 for(i=0;i<MAXFILES  &&  UFDTObj.ufdt[i]!=NULL;i++)
 {
  free (UFDTObj.ufdt[i]);
  UFDTObj.ufdt[i]=NULL;
 }
 
 printf("\nsuccess : old file system deleted successfully...ready to format\n");
 
 SetEnvironment();


}

////////////////////////////////////////////
//
//function name:	DisplayHelp
//input parametre:	none
//return value:	none
//description:		this function lists out all the commands on which our project work
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

void DisplayHelp()
{
 printf("--------------------------------\n");
 printf("open		used to open existing file\n");
 printf("ls		used to list out present files\n");
 printf("lsfd		used to list the files with its file descriptor\n");
 printf("close		used to close opened file\n");
 printf("read		used to read contents of file\n");
 printf("write		used to write data into file\n");
 printf("stat		used to display information of file\n");
 printf("create		used to create file\n");
 printf("delete		used to delete existing file\n");
 printf("search		used to search whether file is present or not\n");
 printf("lseek		used to move file position\n");
 printf("\nfor more information regarding above commands use man command\n");
 printf("---------------------------------\n");
 
}
void ManPage(char *str)      //creating man page..command ani tyaccha description
{
 if(strcmp(str,"open")==0)
 {
  printf("\nDescription	it is used to open existing file\n");
  printf("Usage		open File_Name Mode\n");
 }
 else if(strcmp(str,"close")==0)
 {
  printf("\nDescription	used to close opened file\n");
  printf("Usage		close File_Name\n");
 }
 else if(strcmp(str,"ls")==0)
 {
  printf("\nDescription	used to show the list of files\n");
  printf("Usage		ls\n");
 }
 else if(strcmp(str,"create")==0)
 {
  printf("\nDescription	used to create files\n");
  printf("Usage		create File_name Permision\n");
  printf("note		here permission parametre is like for read you have to enter 4 and for write enter 2 for both 6\n");
 }
 else if(strcmp(str,"delete")==0)
 {
  printf("\nDescription	used to delete file\n");
  printf("Usage		delete File_name\n");
 }
 else if(strcmp(str,"search")==0)
 {
  printf("\nDescription	used to search file\n");
  printf("Usage		search File_name\n");
 }
 else if(strcmp(str,"lsfd")==0)
 {
  printf("\nDescription 	used to show the list of files with its file descriptor\n");
  printf("Usage		lsfd\n");
 }
 else if(strcmp(str,"stat")==0)
 {
  printf("\nDescription	used to show the information of inode\n");
  printf("Usage		stat File_name\n");
 }
 else if(strcmp(str,"write")==0)
 {
  printf("\nDescription	used to write into file\n");
  printf("usage		Write File_name");
 }
 else if(strcmp(str,"read")==0)
 {
  printf("\nDescription	used to read from file\n");
  printf("usage		Read File_name");
 }
 else if(strcmp(str,"lseek")==0)
 {
  printf("\nDescription	used to change the file position\n");
  printf("usage		lseek File_name offset whence\n");
  printf("offset		offset is number of bytes you have to move the position of offset\n");
  printf("whence		press 0 to start from begining, 1 to move position from curent position, 2 to move from end of file\n");
 }
 else
 {
  printf("\nMan page not found\n");
 }
}

////////////////////////////////////////////
//
//function name:	Search
//input parametre:	string
//return value:	boolean
//description:		used to serach a file
//author:		Prajakta Aditya Bartakke
//date:		1 November 2020
//
///////////////////////////////////////////

BOOL Search(char *name)
{
 BOOL bret=FALSE;
 
 bret=ChkFile(name);
 
 if(bret==TRUE)
 {
  return TRUE;
 }
 else
 {
  return FALSE;
 } 
}

int main()
{
 char str[80];
 int count=0;
 char command[4][80];   //4 word asu shaktat having 80 letters
 SetEnvironment();    //environment ekdach setup karaycha
 char arr[50];
 while(1)
 {
  printf("\nmarvellous vfs:>");
  //fgets(str,80,stdin);
  //fflush(stdin);
  scanf(" %[^'\n']s",str);
  
  count=sscanf(str,"%s%s%s%s",command[0],command[1],command[2],command[3]);  //break commands into tokens...number of words
  
  if(count==1)
  {
   if(strcmp(command[0],"help")==0)
   {
    DisplayHelp();
    
   }
   else if(strcmp(command[0],"exit")==0)
   {
    printf("Thank you for using appliaction\n");
    break;
   }
   else if(strcmp(command[0],"clear")==0)
   {
    system("clear");      //cls windows sathi use karto
   }
   else if(strcmp(command[0],"ls")==0)
   {
    LS();
   }
   else if(strcmp(command[0],"lsfd")==0)
   {
    LSFD();
   }
   else if(strcmp(command[0],"format")==0)
   {
    format();
   }
   else
   {
    printf("command not found\n");
   }
  }
  else if(count==2)    //man ani command cha nav
  {
   if(strcmp(command[0],"man")==0)
   {
    ManPage(command[1]);
   }
   else if(strcmp(command[0],"delete")==0)
   {
    Delete(command[1]);
   }
   else if(strcmp(command[0],"search")==0)
   {
    BOOL bret=FALSE;
    bret=Search(command[1]);
    if(bret==TRUE)
    {
     printf("File found!!\n");
    }
    else
    {
     printf("Error:File not found\n");
    }
   }
   else if(strcmp(command[0],"stat")==0)
   {
    fstat(command[1]);
   }
   else if(strcmp(command[0],"Write")==0)
   {
    printf("Enter text:\n");
    scanf(" %[^'\n']s",arr);
   
    int ret=WriteFile(command[1],arr);
    if(ret==-1)
    {
     printf("Error:no such file present\n");
    }
    else if(ret==-2)
    {
     printf("Error:permission denied\n");
    }
    else
    {
    printf("%d of bytes written succesfully\n",ret);
    }
   }
   else if(strcmp(command[0],"Read")==0)
   {
    int bytes=0;
    
    printf("how many bytes you want to read\n");
    scanf("%d",&bytes);
    
    int ret=ReadFile(command[1],bytes);
    
    if(ret==-1)
    {
     printf("Error:permission denied\n");
    }
    else if(ret==-2)
    {
     printf("Error:no files present\n");
    }
    else if(ret==-3)
    {
     printf("Error:permission denified for reading operation\n");
    }
    else
    {
    printf("%d bytes read successfully\n",ret);
    }
   }
   else if(strcmp(command[0],"close")==0)
   {
    close(command[1]);
   }
   else
   {
    printf("command not found\n");
   }
   
  }
  else if(count==3)          //3 word ahet   create demo.c 6  -> command file_name permission
  { 
   if(strcmp(command[0],"create")==0)
   {
    int fd=0;
    fd=CreateFile(command[1],atoi(command[2]));
    if(fd==-1)
    {
     printf("Error:unable to create\n");
    }
    else 
    {
     printf("file successfully created with file descriptor:%d\n",fd);
   }
   
  }
  else if(strcmp(command[0],"open")==0)
   {
    int fd=0;
  
    fd=open(command[1],atoi(command[2]));
    
    if(fd>=0)
    {
     printf("File successfully opened with file descriptor:%d\n",fd);
    }
    else 
    {
     printf("Error:unable to open file\n");
    }
   }
   else
   {
    printf("Error:command not found\n");
   }
  }
   
   else if(count==4)
   {
    if(strcmp(command[0],"lseek")==0)
    {
     lseek(atoi(command[1]),atoi(command[2]),atoi(command[3]));
    }
    else
    {
     printf("command not found\n");
    }
   }
  
  /*else 
  {
   printf("bad command or file name\n");
  }*/
   
 }
 
 return 0;
}











