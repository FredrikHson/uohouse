#include <iostream.h>
#include <stdio.h>
#include <string.h>
struct point
{
	int x,y,z;
};
struct Item
{
	int x,y,z;
	int renderorder; //0 =floor 1 = wall
	int itemid;
	int id;
	bool used;
};
point origin;
char Filename[255];
/*
TITLE=Sphere World Script
VERSION=0.55i
TIME=6308373
SAVECOUNT=415

[WORLDITEM 093]
SERIAL=040000000
DISPID=093
P=9,5,-4


[EOF]
*/
FILE *house;
FILE *input=fopen("sphereworld.scp","rt");;
FILE *input2=fopen("spherechars.scp","rt");;
FILE *output=fopen("sphereworld_house.scp","wt");
Item item;
int serial=0x040000001;
int maxSavedSerial=0x040000001;
int tmpSerial=0x040000001;
int numItems;
bool done;

    char Line[256];
void SaveItem()
{
	fread(&item,sizeof(Item),1,house);
	fprintf(output,"[WORLDITEM 0%x]\nSERIAL=0%x\nDISPID=0%x\nP=%i,%i,%i\n\n",item.itemid,serial,item.itemid,item.x+origin.x,item.y+origin.y,item.z+origin.z);
	serial++;
}

int main()
{
	int i;
	cout << "Origin X:";
	cin >> origin.x;
	
	cout << "Origin Y:";
	cin >> origin.y;
	cout << "Origin Z:";
	cin >> origin.z;
	cout << "Filename:";
	cin >>Filename; 
	house=fopen(Filename,"rb");

	if(house!=NULL)
	{
		while(done==false)
		{  
			fgets(Line,256,input);
			if (!strncmp (Line, "[EOF]", 5))
				done=true;
			
			if (sscanf (Line, "SERIAL=%x", &tmpSerial) == 1)
			{
				if(tmpSerial>maxSavedSerial)
					maxSavedSerial=tmpSerial;
			}

		}
		done=false;
		while(done==false)
		{  
			fgets(Line,256,input2);
			if (!strncmp (Line, "[EOF]", 5))
				done=true;
			
			if (sscanf (Line, "SERIAL=%x", &tmpSerial) == 1)
			{
				if(tmpSerial>maxSavedSerial)
					maxSavedSerial=tmpSerial;
			}

		}
		serial=maxSavedSerial+1;
		fread(&numItems,sizeof(int),1,house);
	
		fprintf(output,"TITLE=Sphere World Script\nVERSION=0.55i\nTIME=0\nSAVECOUNT=0\n\n");
		for(i=0;i<numItems;i++)
		{
			SaveItem();
		}
	fprintf(output,"[EOF]");
	
	}
	

	return 0;
}