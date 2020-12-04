#include<iostream>

using namespace std;

#define EMPTY -1

template <class T>

struct node                          //singly linear,stach,queue,singly circular
{
 T data;
 struct node<T> *next;
};

template <class T>
struct dnode                       //doubly linear,doubly circular
{
 T data;
 struct dnode<T> *next;
 struct dnode<T> *prev;
};

template <class T>
class SINGLY_LL
{
 private:
 	struct node<T>* head;
 	int iSize;

 public:
 	SINGLY_LL()
 	{
         head=NULL;
         iSize=0;
        }
 	void InsertFirst(T);
 	void InsertLast(T);
 	void InsertAtPos(int,T);
 	void DeleteFirst();
 	void DeleteLast();
 	void DeleteAtPos(int);
 	void Display();
 	int Count();
};
 
template <class T>
class STACK
{
 private:
 	struct node<T>* head;
 	int iSize;
 public:
 	void Push(T);
 	T Pop();
 	void Display();
 	int Count();
};

template <class T>
class QUEUE
{
 private:
	struct node<T>* head;
	int iSize;
	struct node<T>* tail;
 public:
 	QUEUE()
 	{
 	 head=NULL;
 	 tail=NULL;
 	}
 	void Enque(T);
 	T Deque();
 	int Count();
 	void Display();
 };
 	
template <class T>
class DOUBLY_LL
{
 private:
 	struct dnode<T>* head;
 	int iSize;
        struct dnode<T>* tail;
 public:
 	DOUBLY_LL()
 	{
         head=NULL;
         tail=NULL;
         iSize=0;
        }
 	void InsertFirst(T);
 	void InsertLast(T);
 	void InsertAtPos(int,T);
 	void DeleteFirst();
 	void DeleteLast();
 	void DeleteAtPos(int);
 	void Display();
 	int Count();
};
 
template <class T>
class SINGLY_CL
{
 private:
 	struct node<T>* head;
 	int iSize;
 	struct node<T>* tail;

 public:
 	SINGLY_CL()
 	{
         head=NULL;
         tail=NULL;
         iSize=0;
        }
 	void InsertFirst(T);
 	void InsertLast(T);
 	void InsertAtPos(int,T);
 	void DeleteFirst();
 	void DeleteLast();
 	void DeleteAtPos(int);
 	void Display();
 	int Count();
};

template <class T>
class DOUBLY_CL
{
 private:
 	struct dnode<T>* head;
 	int iSize;
 	struct dnode<T>* tail;

 public:
 	DOUBLY_CL()
 	{
         head=NULL;
         tail=NULL;
         iSize=0;
        }
 	void InsertFirst(T);
 	void InsertLast(T);
 	void InsertAtPos(T,int);
 	void DeleteFirst();
 	void DeleteLast();
 	void DeleteAtPos(int);
 	void Display();
 	int Count();
};

template <class T>
class BINARY_SEARCH_TREE
{
 public:
       struct bnode<T>*head;
 	BINARY_SEARCH_TREE()
 	{ 
 	 head=NULL;
 	}
 	
 	void Insert(T);
 	void DisplayInorder(struct bnode<T>*);
	void DisplayPreorder(struct bnode<T>*);
	void DisplayPostorder(struct bnode<T>*);

};


/////////////////////////////////////////////
//
//CLASS  ->SLL
//
//function name:	InsertFirst
//input:		generic data
//return value:	none
//description:		used to insert element to linked list
//author:		Prajakta Aditya Bartakke
//date:		21 sep 2020
//
/////////////////////////////////////////////

template <class T>
void SINGLY_LL<T>::InsertFirst(T iNo) 
{
 struct node<T>* newn=(struct node<T>*)malloc(sizeof(struct node<T>));
 newn->data=iNo;
 newn->next=NULL;
 
 if(head==NULL)
 {
  head=newn;
 }
 else
 {
  newn->next=head;
  head=newn;
 }
}

/////////////////////////////////////////////
//
//CLASS  ->SLL
//
//function name:	Display
//input:		none
//return value:	none
//description:		used to display linked list
//author:		Prajakta Aditya Bartakke
//date:		21 sep 2020
//
/////////////////////////////////////////////

template <class T>
void SINGLY_LL<T>::Display() 
{
 if(head==NULL)
 {
  return;
 }
 struct node<T>* temp=head;
 while(temp!=NULL)
 {
  cout<<temp->data<<endl;
  temp=temp->next;
 }
}

/////////////////////////////////////////////
//
//CLASS  ->SLL
//
//function name:	Count
//input:		none
//return value:	integer
//description:		used to count 
//author:		Prajakta Aditya Bartakke
//date:		21 sep 2020
//
/////////////////////////////////////////////

template <class T>
int SINGLY_LL<T>::Count() 
{
 int iCnt=0;
 
 if(head==NULL)
 {
  return EMPTY;
 }
 while(head!=NULL)
 {
  iCnt++;
  head=head->next;
 }
 return iCnt;
}

/////////////////////////////////////////////
//
//CLASS  ->SLL
//
//function name:	InsertLast
//input:		generic data 
//return value:	none
//description:		used to insert element to linked list
//author:		Prajakta Aditya Bartakke
//date:		21 sep 2020
//
/////////////////////////////////////////////

template <class T>
void SINGLY_LL<T>::InsertLast(T iNo) 
{
 struct node<T>* newn=(struct node<T>*)malloc(sizeof(struct node<T>));
 newn->data=iNo;
 newn->next=NULL;
 
 if(head==NULL)
 {
  head=newn;
 }
 else
 {
  struct node<T>* temp=head;
  
  while(temp->next!=NULL)
  {
   temp=temp->next;
  }
  
  temp->next=newn;
 } 
}

/////////////////////////////////////////////
//
//CLASS  ->SLL
//
//function name:	DeleteFirst
//input:		none
//return value:	none
//description:		used to delete element to linked list
//author:		Prajakta Aditya Bartakke
//date:		21 sep 2020
//
/////////////////////////////////////////////

template <class T>
void SINGLY_LL<T>::DeleteFirst() 
{
 if(head==NULL)
 {
  cout<<"Error:empty linked list\n";
  return;
 }
 else
 {
  struct node<T>* temp=head;
  
  head=head->next;
  
  free (temp);
 }
}

/////////////////////////////////////////////
//
//CLASS  ->SLL
//
//function name:	DeleteLast
//input:		none
//return value:	none
//description:		used to delete element to linked list
//author:		Prajakta Aditya Bartakke
//date:		21 sep 2020
//
/////////////////////////////////////////////

template <class T>
void SINGLY_LL<T>::DeleteLast() 
{
 if(head==NULL)
 {
  cout<<"Error:empty linked list\n";
  return;
 }
 else if(head->next==NULL)
 {
  free (head);
  head=NULL;
 }
 else
 {
  struct node<T>* temp=head;
  
  while(temp->next->next!=NULL)
  {
   temp=temp->next;
  }
  
  struct node<T>* temp1=temp->next;
  
  temp->next=NULL;
  
  free (temp1);
 }
}

/////////////////////////////////////////////
//
//CLASS  ->SLL
//
//function name:	InsertAtPos
//input:		generic data ani position
//return value:	none
//description:		used to insert element to linked list
//author:		Prajakta Aditya Bartakke
//date:		21 sep 2020
//
/////////////////////////////////////////////


template <class T>
void SINGLY_LL<T>::InsertAtPos(int iPos,T iNo)
{
 int iCnt=Count();
 
 if(iPos<0 || iPos>iCnt+1)
 {
  return;
 }
 
 if(iPos==1)
 {
  InsertFirst(iNo);
 }
 
 else if(iPos==(iCnt+1))
 {
  InsertLast(iNo);
 }
 
 else
 {
  int i=1;
  
  struct node<T>* newn=(struct node<T>*)malloc(sizeof(struct node<T>));
  newn->next=NULL;
  newn->data=iNo;
  
  struct node<T> temp=head;
  
  for(i=1;i<iPos-1;i++)
  {
   temp=temp->next;
  }
  
  newn->next=temp->next;
  
  temp->next=newn;
 }
}
  
/////////////////////////////////////////////
//
//CLASS  ->SLL
//
//function name:	DeleteAtPos
//input:		position 
//return value:	none
//description:		used to insert element to linked list
//author:		Prajakta Aditya Bartakke
//date:		21 sep 2020
//
/////////////////////////////////////////////  


template <class T>
void SINGLY_LL<T>::DeleteAtPos(int pos)
{
 int iCnt=Count();
 
 if(pos<1 || pos>iCnt)
 {
  return;
 }
 if(pos==1)
 {
  DeleteFirst();
 }
 else if(pos==iCnt)
 {
  DeleteLast();
 }
 else 
 {
  int i=1;
  struct node<T>* temp=head;
  
  for(i=1;i<pos;i++)
  {
   temp=temp->next;
  }
  
  struct node<T>* temp1=(temp->next);
  
  temp->next=temp->next->next;
  
  free (temp1);
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DLL
//
//function name:	InsertFirst
//input:		generic data
//return value:	none
//description:		used to insert element to doubly linear linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
/////////////////////////////////////////////

template <class T>
void DOUBLY_LL<T>::InsertFirst(T no)
{
 struct dnode<T>* newn=(struct dnode<T>*)malloc(sizeof(struct dnode<T>));
 newn->data=no;
 newn->next=NULL;
 newn->prev=NULL;
 
 if(head==NULL && tail==NULL)
 {
  head=newn;
  tail=newn;
 }
 else if(head->next==NULL)
 {
  newn->next=head;
  tail=head;
  head->prev=newn;
  head=newn;
 }
  
 else
 {
  newn->next=head;
  head->prev=newn;
  head=newn;
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DLL
//
//function name:	display
//input:		none
//return value:	none
//description:		used to display element to linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
/////////////////////////////////////////////

template <class T>
void DOUBLY_LL<T>::Display()
{
 if(head==NULL)
 {
  printf("Empty linked list\n");
  return;
 }
 struct dnode<T>* temp=head;
 
 while(temp!=NULL)
 {
  printf("%d\n",temp->data);
  temp=temp->next;
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DLL
//
//function name:	Count
//input:		none
//return value:	int
//description:		used to count element to linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
/////////////////////////////////////////////

template <class T>
int DOUBLY_LL<T>::Count()
{
 if(head==NULL)
 {
  printf("Empty linked list\n");
  return -1;
 }
 struct dnode<T>* temp=head;
 int iNo=0;
 while(temp!=NULL)
 {
  iNo++;
  temp=temp->next;
 }
 return iNo;
}




/////////////////////////////////////////////
//
//CLASS  ->DLL
//
//function name:	DeleteFirst
//input:		none
//return value:	none
//description:		used to delete element to doubly linear linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
/////////////////////////////////////////////

template <class T>
void DOUBLY_LL<T>::DeleteFirst()
{
 if(head==NULL)
 {
  return;
 }
 else if(head->next==NULL)
 {
  free (head);
  head=NULL;
  tail=NULL;
 }
 else
 {
  head=head->next;
  free (head->prev);
  head->prev=NULL;
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DLL
//
//function name:	InsertLast
//input:		generic data
//return value:	none
//description:		used to insert element to doubly linear linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
/////////////////////////////////////////////

template <class T>
void DOUBLY_LL<T>::InsertLast(T no)                                      
{
 struct dnode<T>* newn=(struct dnode<T>*)malloc(sizeof(struct dnode<T>));
 newn->data=no;
 newn->next=NULL;
 newn->prev=NULL;
 if(head==NULL && tail==NULL)
 {
  head=newn;
  tail=newn;
 }
 
 else
 {
  newn->prev=tail;
  tail->next=newn;
  tail=tail->next;
 }

}

/////////////////////////////////////////////
//
//CLASS  ->DLL
//
//function name:	DeleteLast
//input:		none
//return value:	none
//description:		used to delet element to doubly linear linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
/////////////////////////////////////////////

template <class T>
void DOUBLY_LL<T>::DeleteLast()                             
{
 if(head==NULL)
 {
  return;
 }
 else if(head->next==NULL)
 {
  free (tail);
  tail=NULL;
  head=NULL;
 }
 else
 {
  
  tail=tail->prev;
  
  free (tail->next);
  
  tail->next=NULL;
  
  /*struct dnode<T>* temp=head;
  
  while(temp->next!=NULL)
  {
   temp=temp->next;
  }
  
  free (temp->prev->next);
  temp->prev->next=NULL;*/
  
  
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DLL
//
//function name:	InsertAtPos
//input:		generic data and position
//return value:	none
//description:		used to insert element to doubly linear LL
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
/////////////////////////////////////////////

template <class T>
void DOUBLY_LL<T>::InsertAtPos(int pos,T no)
{
 int iCnt=Count();
 
 if(pos<1 || pos>iCnt+1)
 {
  return;
 }
 else if(pos==1)
 {
  InsertFirst(no);
 }
 else if(pos==iCnt+1)
 {
  InsertLast(no);
 }
 else
 {
  struct dnode<T>* newn=(struct dnode<T>*)malloc(sizeof(struct dnode<T>));
  newn->data=no;
  newn->prev=NULL;
  newn->next=NULL;
  
  int i=0;
  struct dnode<T>* temp=head; 
  for(i=1;i<=pos;i++)
  {
   temp=temp->next;
  }//temp=400
  
  newn->next=temp->prev;
  newn->prev=temp->prev->prev;
  newn->next->prev=newn;
  newn->prev->next=newn;
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DLL
//
//function name:	DeleteAtPos
//input:		position
//return value:	none
//description:		used to delete element to doubly linear LL
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
/////////////////////////////////////////////

template <class T>

void DOUBLY_LL<T>::DeleteAtPos(int pos)
{
 int iCnt=Count();
 
 if(pos<1 || pos>iCnt)
 {
  return;
 }
 else if(pos==1)
 {
  DeleteFirst();
 }
 else if(pos==iCnt)
 {
  DeleteLast();
 }
 else
 {
  int i=0;
  
  struct dnode<T>* temp=head;
  
  for(i=1;i<pos;i++)
  {
   temp=temp->next;
  }
  temp->prev->next=temp->next;
  temp->next->prev=temp->prev;
  
  free (temp);
 }
}
 
/////////////////////////////////////////////
//
//CLASS  ->SCL
//
//function name:	InsertFirst
//input:		generic data
//return value:	none
//description:		used to insert element to singly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
///////////////////////////////////////////// 

template <class T>
void SINGLY_CL<T>::InsertFirst(T no)
{
 struct node<T>* newn=(struct node<T>*)malloc(sizeof(struct node<T>));
 newn->data=no;
 newn->next=NULL;
 
 if(head==NULL && tail==NULL)
 {
  head=newn;
  tail=newn;
 }
 
 else
 {
  newn->next=head;
  head=newn;
 }
 
 tail->next=head;
}

/////////////////////////////////////////////
//
//CLASS  ->SCL
//
//function name:	Display
//input:		none
//return value:	none
//description:		used to display element to singly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
///////////////////////////////////////////// 

template <class T>
void SINGLY_CL<T>::Display()
{
 struct node<T>* temp=head;
 if(head==NULL)
 {
  printf("empty linked list\n");
  return;
 }
 do
 {
  printf("%d\n",temp->data);   //100 cha data,200 cha data,300 cha data,400 cha data
  temp=temp->next;		//200,300,400,100
 }while(temp!=(tail->next));	//200!=100,300!=100,400!=100,100!=100(FALSE)
  
}
/////////////////////////////////////////////
//
//CLASS  ->SCL
//
//function name:	Count
//input:		none
//return value:	int
//description:		used to count element to singly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
///////////////////////////////////////////// 

template <class T>
int SINGLY_CL<T>::Count()
{
 struct node<T>* temp=head;
 if(head==NULL)
 {
  printf("empty linked list\n");
  return -1;
 }
 int iNo=0;
 
 do
 {
  iNo++;
  temp=temp->next;		
 }while(temp!=(tail->next));	
 return iNo;
}
/////////////////////////////////////////////
//
//CLASS  ->SCL
//
//function name:	InsertLast
//input:		generic data
//return value:	none
//description:		used to insert element to singly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
///////////////////////////////////////////// 

template <class T>
void SINGLY_CL<T>::InsertLast(T no)
{
 struct node<T>*newn=(struct node<T>*)malloc(sizeof(struct node<T>));
 newn->next=NULL;
 newn->data=no;
 
 if(head==NULL && tail==NULL)
 {
  head=newn;
  tail=newn;
 }
 
 else
 {
  tail->next=newn;
  tail=newn;
 }
 tail->next=head;
}

/////////////////////////////////////////////
//
//CLASS  ->SCL
//
//function name:	DeleteFirst
//input:		none
//return value:	none
//description:		used to delete element to singly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
///////////////////////////////////////////// 

template <class T>
void SINGLY_CL<T>::DeleteFirst()
{
 if(head==NULL)
 {
  return;
 }
 
 else if(head->next==NULL)
 {
  free (tail);
  head=NULL;
  tail=NULL;
 }
 
 else
 {
  struct node<T>*temp=head;
  
  head=head->next;
  
  free (temp);
  
  tail->next=head;
 }
}
 
/////////////////////////////////////////////
//
//CLASS  ->SCL
//
//function name:	DeleteLast
//input:		none
//return value:	none
//description:		used to delete element to singly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
///////////////////////////////////////////// 

template <class T>
void SINGLY_CL<T>::DeleteLast()
{
 if(head==NULL)
 {
  printf("empty linked list\n");
  return;
 
 }
 
 else if(head->next==tail)
 {
  free (head);
  head=NULL;
  tail=NULL;
 }
 
 else
 {
  struct node<T>*temp=head;
  
  while(temp->next!=tail)
  {
   temp=temp->next;
  }
  
  free (temp->next);
  
  tail=temp;
  
  tail->next=head;
 }
}
  
/////////////////////////////////////////////
//
//CLASS  ->SCL
//
//function name:	InsertAtPos
//input:		generic data and position
//return value:	none
//description:		used to insert element to singly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
///////////////////////////////////////////// 

template <class T>
void SINGLY_CL<T>::InsertAtPos(int pos,T no)
{
 int iCnt=Count();
 
 if(pos<1 || pos>(iCnt+1))
 {
  return;
 }
 
 else if(pos==1)
 {
  InsertFirst(no);
 }
 
 else if(pos==iCnt+1)
 {
  InsertLast(no);
 }
 
 else
 {
  int i=0;
  
  struct node<T>* temp=head;
  struct node<T>* newn=(struct node<T>*)malloc(sizeof(struct node<T>));
  newn->data=no;
  newn->next=NULL;
  
  for(i=1;i<pos-1;i++)
  {
   temp=temp->next;
  }
  
  newn->next=temp->next;
  temp->next=newn;
  
 }
}

/////////////////////////////////////////////
//
//CLASS  ->SCL
//
//function name:	DeleteAtPos
//input:		position
//return value:	none
//description:		used to delete element to singly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		27 sep 2020
//
///////////////////////////////////////////// 

template <class T>
void SINGLY_CL<T>::DeleteAtPos(int pos)
{
 int iCnt=Count();
 
 if(pos<1 || pos>iCnt)
 {
  return;
 }
 
 else if(pos==1)
 {
  DeleteFirst();
 }
 
 else if(pos==iCnt)
 {
  DeleteLast();
 }
 
 else
 {
  int i=0;
  
  struct node<T>* temp=head;
  
  for(i=1;i<pos-1;i++)
  {
   temp=temp->next;
  }
  
  struct node<T>* temp1=temp->next;
  
  temp->next=temp->next->next;
  
  free (temp1);
  
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DCL
//
//function name:	InsertFirst
//input:		generic data
//return value:	none
//description:		used to insert element to doubly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		12 oct 2020
//
///////////////////////////////////////////// 

template <class T>
void DOUBLY_CL<T>::InsertFirst(T no)
{
 struct dnode<T>* newn=(struct dnode<T>*)malloc(sizeof(struct dnode<T>));
 newn->data=no;
 newn->next=NULL;
 newn->prev=NULL;
 
 if(head==NULL && tail==NULL)
 {
  head=newn;
  tail=newn;
 }
 
 else if(head->next==NULL)
 {
  newn->next=head;
  head->prev=newn;
  tail=head;
  head=newn;
 }
 
 else
 {
  newn->next=head;
  head->prev=newn;
  head=newn;
 }
 
 head->prev=tail;
 tail->next=head;
}
 


/////////////////////////////////////////////
//
//CLASS  ->DCL
//
//function name:	InsertLast
//input:		generic data
//return value:	none
//description:		used to insert element to doubly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
//
///////////////////////////////////////////// 

template <class T>
void DOUBLY_CL<T>::InsertLast(T no)
{
 struct dnode<T>* newn=(struct dnode<T>*)malloc(sizeof(struct dnode<T>*));
 newn->data=no;
 newn->next=NULL;
 newn->prev=NULL;
 
 if(head==NULL && tail==NULL)                       //no node present
 {
  head=newn;
  tail=newn;
 }
 else if(head->next==head)                          //single node present
 {
  newn->prev=head;
  head->next=newn;
  tail=newn;
 }
 else
 {
  newn->prev=tail;
  tail->next=newn;
  tail=newn;
 }
 head->prev=tail;
 tail->next=head;

 }

/////////////////////////////////////////////
//
//CLASS  ->DCL
//
//function name:	InsertAtPos
//input:		generic data
//return value:	none
//description:		used to insert element to doubly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
//
///////////////////////////////////////////// 

template <class T>
void DOUBLY_CL<T>::InsertAtPos(T data,int pos)
{
 int cnt=Count();
 
 if(pos<1 || pos>cnt+1)
 {
  return;
 }
 
 if(pos==1)
 {
  InsertFirst(data);
 }
 else if(pos==cnt+1)
 {
  InsertLast(data);
 }
 else
 {
  int i=0;
   struct dnode<T>* newn=new  (struct dnode<T>);
   newn->data=data;
   newn->next=NULL;
   newn->prev=NULL;
  struct dnode<T>* temp=head;
  
  for(int i=1;i<pos;i++)
  {
   temp=temp->next;
  }
  
  newn->next=temp;
  temp->prev->next=newn;
  newn->prev=temp->prev;
  temp->prev=newn;
 }

}
 
 
/////////////////////////////////////////////
//
//CLASS  ->DCL
//
//function name:	Display
//input:		none
//return value:	none
//description:		used to display element to doubly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		12 oct 2020
//
///////////////////////////////////////////// 

template <class T>
void DOUBLY_CL<T>::Display()
{
 if(head==NULL)
 {
  cout<<"Error:linked list is empty\n";
  return;
 }
 struct dnode<T>* temp=head;
 do
 {
  cout<<temp->data<<"\t";
  temp=temp->next;
 }while(temp!=head);
 
 cout<<endl;
}

/////////////////////////////////////////////
//
//CLASS  ->DCL
//
//function name:	Count
//input:		none
//return value:	int
//description:		used to count element to doubly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		28 sep 2020
//
///////////////////////////////////////////// 

template <class T>
int DOUBLY_CL<T>::Count()
{
 if(head==NULL)
 {
  return -1;
 }
 struct dnode<T>* temp=head;
 int cnt=0;
 do
 {
  cnt++;
  temp=temp->next;
 }while(temp!=head);
 
 return cnt;
}



/////////////////////////////////////////////
//
//CLASS  ->DCL
//
//function name:	DeleteFirst
//input:		none
//return value:	none
//description:		used to delete element to doubly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
//
///////////////////////////////////////////// 


template <class T>
void DOUBLY_CL<T>::DeleteFirst()
{
 if(head==NULL)
 {
  return;
 }
 
 if(head==tail)
 {
  delete head;
  head=NULL;
  tail=NULL;
 }
 
 else 
 {
  head=head->next;
  free (head->prev);
  head->prev=tail;
  tail->next=head;
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DCL
//
//function name:	DeleteLast
//input:		none
//return value:	none
//description:		used to delete element to doubly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
//
///////////////////////////////////////////// 

template <class T>
void DOUBLY_CL<T>::DeleteLast()
{
 if(head==NULL)
 {
  return;
 }
 if(head==tail)        
 {
  free (head);
  head=NULL;
  tail=NULL;
 }
 else
 {
  tail=tail->prev;
  free (tail->next);
  tail->next=head;
  head->prev=tail;
 }
}

/////////////////////////////////////////////
//
//CLASS  ->DCL
//
//function name:	DeleteAtPos
//input:		none
//return value:	none
//description:		used to delete element to doubly circular linked list
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
//
///////////////////////////////////////////// 

template <class T>
void DOUBLY_CL<T>::DeleteAtPos(int pos)
{
 int cnt=Count();
 
 if(pos<1 || pos>cnt)
 {
  return;
 }
 if(pos==1)
 {
  DeleteFirst();
 }
 else if(pos==cnt)
 {
  DeleteLast();
 }
 else
 {
  int i=0;
  
  struct dnode<T>*temp=head;
  
  for(i=1;i<pos;i++)
  {
   temp=temp->next;
  }
  temp->prev->next=temp->next;
  temp->next->prev=temp->prev;

 }
}

////////////////////////////////////////////////
//
//class ->STACK
//function name:	push
//input:		generic data
//output:		none
//description:		used to insert data in stack
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
////////////////////////////////////////////////


template <class T>
void STACK<T>::Push(T no)                            
{
 struct node<T>* newn=(struct node<T>*)malloc(sizeof(struct node<T>));
 newn->data=no;
 newn->next=NULL;
 
 if(head==NULL)
 {
  head=newn;
 }
 
 else
 {
  newn->next=head;
  head=newn;
 }
}

////////////////////////////////////////////////
//
//class ->STACK
//function name:	pop
//input:		none
//output:		data
//description:		used to remove data in stack
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
////////////////////////////////////////////////


template <class T>
T STACK<T>::Pop()                            
{
 T no;
 
 if(head==NULL)
 {
  return -1;
 }
 
 else
 {
  struct node<T>* temp=head;
  no=head->data;
  free (temp);
  head=head->next;
 }
 
 return no;
 
}

////////////////////////////////////////////////
//
//class ->STACK
//function name:       Count
//input:		none
//output:		int
//description:		used to count data in stack
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
////////////////////////////////////////////////

template <class T>
int STACK<T>::Count()
{
 int cnt=0;
 if(head==NULL)
 {
  return -1;
 }
 
 else
 {
  struct node<T>*temp=head;
  
  while(temp!=NULL)
  {
   cnt++;
   temp=temp->next;
  }
 } 
  return cnt;
 
}

////////////////////////////////////////////////
//
//class ->STACK
//function name:       display
//input:		none
//output:		none
//description:		used to display data in stack
//author:		Prajakta Aditya Bartakke
//date:		13 oct 2020
////////////////////////////////////////////////

template <class T>
void STACK<T>::Display()
{
 if(head==NULL)
 {
  return;
 }
 
 struct node<T>*temp=head;
 
 for(int i=0;i<Count();i++)
 {
  cout<<temp->data<<"\t";
  temp=temp->next;
 }
 cout<<endl;
}
//////////////////////////////////////
//
//class ->QUEUE
//function name:	Enque
//input:		generic data
//output:		none
//description:		usd to insert data inside a queue
//author:		Prajakta Aditya Bartakke
//date:		21 october 2020
//////////////////////////////////////

template <class T>
void QUEUE<T>::Enque(T no)  //insertlast
{
 struct node<T>* newn=(struct node<T>*)malloc(sizeof(struct node<T>));
 newn->data=no;
 newn->next=NULL;
 
 if(head==NULL && tail==NULL)    
 {
  head=newn;
  tail=newn;
 }
 else
 {
  if(head->next==NULL)
  {
   head->next=newn;
   tail=newn;
  }
  else
  {
   tail->next=newn;
   tail=newn;
  }
 } 

}

//////////////////////////////////////
//
//class ->QUEUE
//function name:	Deque
//input:		none
//output:		none
//description:		usd to delete data inside a queue
//author:		Prajakta Aditya Bartakke
//date:		21 october 2020
//////////////////////////////////////

template <class T>
T QUEUE<T>::Deque()  //deletefirst
{
 T no=T();
 
 no=head->data;
 head=head->next;
 
 return no;

}

//////////////////////////////////////
//
//class ->QUEUE
//function name:	Display
//input:		none
//output:		none
//description:		usd to display data inside a queue
//author:		Prajakta Aditya Bartakke
//date:		21 october 2020
//////////////////////////////////////

template <class T>
void QUEUE<T>::Display()  //deletefirst
{
 struct node<T>*temp=head;
 
 while(temp!=NULL)
 {
  cout<<temp->data<<"\t";
  temp=temp->next;
 }
 cout<<endl;

}


int main()
{
 //singly linked list
 SINGLY_LL<int> obj;
 obj.InsertFirst(11);
 obj.InsertFirst(21);
 obj.InsertFirst(51);
 obj.InsertFirst(101);
 obj.Display();
 
 
 DOUBLY_LL<int> obj1; 
 
 SINGLY_CL<int> obj2;
 
 DOUBLY_CL<int> obj3;
 
 STACK<int> obj4;
 
 QUEUE<int> obj5;
 
 
 //doubly linked list
 printf("----------------------------\n");
 obj1.InsertFirst(11);
 obj1.InsertFirst(21);
 obj1.InsertFirst(51);
 obj1.InsertFirst(101);
 obj1.Display();
 printf("----------------------------\n");
 obj1.InsertLast(101);
 obj1.InsertLast(121);
 obj1.InsertLast(151);
 obj1.Display();
 printf("----------------------------\n");
 obj1.DeleteLast();
 obj1.Display();
 obj1.InsertAtPos(3,189);
 printf("----------------------------\n");
 obj1.Display();
 obj1.DeleteAtPos(3);
 printf("----------------------------\n");
 obj1.Display();
 
 //singly circular linked list
 obj2.InsertFirst(11);
 obj2.InsertLast(21);
 obj2.InsertLast(101);
 obj2.InsertLast(111);
 obj2.InsertLast(151);
 obj2.Display();
 obj2.DeleteLast();
 printf("----------------------------\n");
 obj2.Display();
 obj2.InsertAtPos(3,159);
 printf("----------------------------\n");
 obj2.Display();
 
 obj2.DeleteFirst();
 printf("----------------------------\n");
 obj2.Display();
 
 //doubly circular linked list
 obj3.InsertLast(101);
 obj3.InsertLast(51);
 obj3.InsertLast(21);
 obj3.InsertLast(11);
 
 obj3.DeleteLast();
 obj3.DeleteLast();
 obj3.DeleteLast();
 obj3.DeleteLast();
 
 obj3.Display();
 
 
 obj3.InsertAtPos(11234,3);
 
 obj3.Display();
 
 obj3.DeleteAtPos(3);
 
 obj3.Display();
 
 
 //stack
 obj4.Push(11);
 obj4.Push(21);
 obj4.Push(51);
 obj4.Push(101);
 obj4.Push(111);
 
 obj4.Display();
 int no=obj4.Pop();
 cout<<"popped data is "<<no<<endl;
 
 obj4.Count();
 
 
 //queu
 obj5.Enque(11);
 obj5.Enque(21);
 obj5.Enque(51);
 obj5.Enque(101);
 obj5.Enque(111);
 obj5.Display();
 int no=obj5.Deque();
 cout<<no<<endl;
 
 
 
 return 0;
}
