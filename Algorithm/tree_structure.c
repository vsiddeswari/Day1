#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

typedef struct node{
	struct dirent *d;
	struct node *child;
	struct node *next;
}NODE;


NODE *head = NULL,*temp_1;
void store_directory(char *,NODE *);
void print_directory(NODE *);
int main()
{
	char path[100];
	printf("Enter the path: ");
	scanf("%s",path);
	path[strlen(path)] = '\0';
	store_directory(path,head);
	//printf("%s\n",head->child->d->d_name);
	//print_directory(head);

	return 0;
}

void store_directory(char *path,NODE *temp)
{
	DIR *dir;

	struct dirent *dir_p;
	char path1[256];
	char name[100];
	NODE *nu;
//	dir = opendir(path);

	errno=0;
if ((dir = opendir(path)) == NULL) {
        switch (errno) {
            case EACCES: printf("Permission denied\n"); break;
            case ENOENT: printf("Directory does not exist\n"); break;
            case ENOTDIR: printf("'%s' is not a directory\n",path); break;
        }
}
	while(dir_p = readdir(dir))
	{
		if((strcmp(dir_p->d_name,".") == 0) || (strcmp(dir_p->d_name,"..")==0))
		{
			continue;
		}

		nu = (NODE *)malloc(sizeof(NODE));
		nu->d = dir_p;
		nu->next = NULL;
		nu->child = NULL;

		if(head == NULL)
		{
			head = nu;
			temp = nu;
		}
		else
		{
			temp = nu;
		}

		if(dir_p->d_type == DT_DIR)
		{
			strcpy(name,dir_p->d_name);
			name[strlen(name)] = '\0';
			printf("..%s\n",name);
			sprintf(path1,"%s/%s",path,name);
			if(temp->child)
			{
				store_directory(path1,temp->next);
			}
			else
			{
				store_directory(path1,temp->child);
			}
		}
		else
		{
			printf(" --%s\n",nu->d->d_name);
			temp->next = nu;
		}
	}

	closedir(dir);


}



void print_directory(NODE *head)
{
	if(head == NULL)
	{
		printf("tree is empty..\n");
	}
	else
	{
		NODE *temp = head;
		printf("...%s\n",head->d->d_name);
		if(temp->child)
		{
			print_directory(temp->child);
		}
		else
		{
			NODE *temp_2 = head;
			while(temp_2)
			{
				printf(" %s\n",temp_2->d->d_name);
				if(temp_2->child)
				{
					print_directory(temp_2->child);
				}
				temp_2 =temp_2->next;
			}
		}
			
	}
}
		

