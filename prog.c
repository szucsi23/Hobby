#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum hely { I, O } hely;

typedef struct hordozo
{
	char nevh[15];
	double bef;
	hely holh;
	/*char elonyh[20];*/
	struct hordozo *next;
} hordozo, *hordl;

typedef struct folyadek
{
	char nevf[15];
	unsigned int egh;
	hely holf;
	/*char elonyf[20];*/
	struct folyadek *next;
} folyadek, *folyl;

hordl ujhlist(void)
{

	char nevpuff[15];
	double befpuff;
	hely holpuff = I;

	hordozo* act;
	int i,j;


	hordl head = (hordl)malloc(sizeof(hordozo));
	
	hordl ujhlist = (hordozo*)malloc(sizeof(hordozo));
	head->next = NULL;
	
	FILE *fsz = fopen("szoveges.txt", "r");
	FILE *fb = fopen("binaris.bin", "rb");
	if (fsz == NULL) 
	{
		return NULL;
	}
	if (fb == NULL)
	{
		return NULL;		
	}
	int sordb=0;
	fscanf(fsz,"%d",&sordb);
	//while (fscanf(fsz, "%s \t %lf", nevpuff, &befpuff) && j < 10)
	for(j=0;j<sordb;j++)
	{
		fscanf(fsz, "%s \t %lf", nevpuff, &befpuff);
	//	if (befpuff>2.0) fscanf(fb, "%c", &holpuff);
	//	else fscanf(fb, "\t %c", &holpuff);
		act = (hordozo*)malloc(sizeof(hordozo));
		for (i = 0; i < 15; i++)
			act->nevh[i] = nevpuff[i];
		act->bef = befpuff;
		act->holh = holpuff;
		/*act.elonyh = h.elonyh; */
		act->next = head->next;
		head->next = act;

	}

	fclose(fsz);
	fclose(fb);
	return head;
}

folyl ujflist(void)
{
	char nevpuff[15];
	int eghpuff;
	hely holpuff;

	folyadek* act;
	int i;


	folyl head = (folyl)malloc(sizeof(folyadek));

	folyl ujhlist = (folyadek*)malloc(sizeof(folyadek));
	head->next = NULL;

	FILE *fsz = fopen("szoveges.txt", "r");
	FILE *fb = fopen("binaris.bin", "rb");
	if (fsz == NULL) return 0;
	if (fb == NULL) return 0;

	while (fscanf(fsz, "%s %d" , nevpuff, &eghpuff))
	{

		//if (eghpuff<7) fscanf(fb, "%c", &holpuff);
		//else fscanf(fb, "\t %c", &holpuff);
		act = (folyadek*)malloc(sizeof(folyadek));
		for (i = 0; i < 15; i++)
			act->nevf[i] = nevpuff[i];
		act->egh = eghpuff;
		act->holf = holpuff;
		/*act.elonyh = h.elonyh; */
		act->next = head->next;
		head->next = act;

	}
	return head;
}

hordozo* sokaig(hordozo *list)
{
	hordozo *x = list->next;
	hordozo *max = list->next;

	while (x != NULL)
	{
		if ((x->bef) > max->bef && (x->holh) == I) max->bef = x->bef;
		x = x->next;
	}
	return max;
}

folyadek* intenziv(folyadek *list)
{
	folyadek *x = list->next;
	folyadek *max = list->next;

	while (x != NULL)
	{
		if ((x->egh) > max->egh && (x->holf) == I) max->egh = x->egh;
		x = x->next;
	}
	return max;
}
void listat_kiir(hordl lista)
{
	int i = 1;
	hordl act = lista->next;
	while (act != NULL)
	{
		printf("%d - %s\n",i, act->nevh);
		//csak formazas, hogy szepen nezzen ki.
		act = act->next;
		++i;
	}
}

void ujlist(hordozo **hlist, folyadek **flist)
{
	char nevpuff[15];
	double befpuff;
	int eghpuff;
	hely holpuff = I;

	hordozo* act1;
	folyadek* act2;
	int i,j;


	hordl head1 = (hordl)malloc(sizeof(hordozo));
	folyl head2 = (folyl)malloc(sizeof(folyadek));
	
	head1->next = NULL;
	
	FILE *fsz = fopen("szoveges.txt", "r");
	FILE *fb = fopen("binaris.bin", "rb");
	if (fsz == NULL || fb == NULL)
	{
		return;		
	}
	//fájl elsõ fele
	int sordb=0;
	fscanf(fsz,"%d",&sordb);
	//while (fscanf(fsz, "%s \t %lf", nevpuff, &befpuff) && j < 10)
	for(j=0;j<sordb;j++)
	{
		fscanf(fsz, "%s \t %lf", nevpuff, &befpuff);
	//	if (befpuff>2.0) fscanf(fb, "%c", &holpuff);
	//	else fscanf(fb, "\t %c", &holpuff);
		act1 = (hordozo*)malloc(sizeof(hordozo));
		for (i = 0; i < 15; i++)
			act1->nevh[i] = nevpuff[i];
		act1->bef = befpuff;
		act1->holh = holpuff;
		/*act.elonyh = h.elonyh; */
		act1->next = head1->next;
		head1->next = act1;
	}
	
	//második rész
	fscanf(fsz,"%d",&sordb);
	//while (fscanf(fsz, "%s \t %lf", nevpuff, &befpuff) && j < 10)
	for(j=0;j<sordb;j++)
	{
		fscanf(fsz, "%s \t %d", nevpuff, &eghpuff);
	//	if (befpuff>2.0) fscanf(fb, "%c", &holpuff);
	//	else fscanf(fb, "\t %c", &holpuff);
		act2 = (folyadek*)malloc(sizeof(folyadek));
		for (i = 0; i < 15; i++)
			act2->nevf[i] = nevpuff[i];
		act2->egh = eghpuff;
		act2->holf = holpuff;
		/*act.elonyh = h.elonyh; */
		act2->next = head2->next;
		head2->next = act2;
	}


	
	*hlist = head1;
	*flist = head2;
	
	fclose(fsz);
	fclose(fb);
}




int main(void)
{

	hordozo* hlist=NULL;
	folyadek* flist=NULL;

	ujlist(&hlist,&flist);
	if(hlist != NULL)	listat_kiir(hlist);
	//if(flist != NULL)	listat_kiir(flist);
	//listat_kiir(flist);
	
	
	printf("asd1");
	//hordozo *hord = sokaig(hlist);
	printf("asd2");
	//folyadek *foly = intenziv(flist);
	printf("asd3");

//	printf("\n A legjobb osszeallitas: %s eszközök, %s-el atitatva.", hord->nevh, foly->nevf);

	return 0;
}