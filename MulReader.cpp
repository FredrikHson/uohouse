#include "MulReader.h"

struct Color16
{
	unsigned short Color;
};
struct Color24
{
	unsigned char R,G,B;
};
struct Color32
{
	unsigned char R,G,B,A;
};

void Color16toColor24(Color16 from,Color24 &to)
{
	to.R=(((from.Color >> 10) & 0x1f) *256/32);
	to.G=(((from.Color >> 5) & 0x1f) *256/32);
	to.B=(from.Color & 0x1f) *256/32;
}
void Color16toColor32(Color16 from,Color32 &to)
{
	to.R=(((from.Color >> 10) & 0x1f) *256/32);
	to.G=(((from.Color >> 5) & 0x1f) *256/32);
	to.B=(from.Color & 0x1f) *256/32;
	to.A=255;
}
unsigned int NextPowerOf2(unsigned int input)
{
	input -= 1;
	
	input |= input >> 16;
	input |= input >> 8;
	input |= input >> 4;
	input |= input >> 2;
	input |= input >> 1;
	
	return input + 1;
}

void FlipTexture(Texture *Tex)
{
	int i,j;
	int offset;//,offset2;
	GLuint *ImageData;
	
	ImageData=new GLuint[Tex->Height*Tex->Width*4];
	for(i=0;i<Tex->Height*Tex->Width*4;i++)
	{
		ImageData[i]=Tex->ImageData[i];
	}
	offset=0;
	for(i=Tex->Height-1;i>-1;i--)
	{
		for(j=0;j<Tex->Width;j++)
		{
			
			Tex->ImageData[offset] = ImageData[(((i*Tex->Width)+j)*4)];
			offset++;
			Tex->ImageData[offset] = ImageData[(((i*Tex->Width)+j)*4)+1];	
			offset++;
			Tex->ImageData[offset] = ImageData[(((i*Tex->Width)+j)*4)+2];
			offset++;
			Tex->ImageData[offset] = ImageData[(((i*Tex->Width)+j)*4)+3];
			offset++;
		}
	}
	delete [] ImageData;
	/*
	for(i=0;i<Tex->Height;i++)
	{	
	offset=i*Tex->Width*4;
	offset2=Tex->Height-i*Tex->Width*4-Tex->Width;
	for(j=0;j<Tex->Width*4;j++)
	{
	Tex->ImageData[offset+j]=ImageData[offset2+j];
	}
	
}*/
}

//bool LoadArt(Texture *Tex,int i,char* artfilename,char* artidxfilename,char*titledata)
bool LoadArt(Texture *Tex,int i,FILE* art,FILE* artidx)
{
	i+=0x4000;
	Color16 C16;
	Color32 C32;
	//IDX
	int Lookup;//,Size;
	
	//static items 
//	FILE *artidx=fopen(artidxfilename,"rb");
	fseek(artidx,i*12,SEEK_SET);
	
	fread(&Lookup,sizeof(int),1,artidx);
	
	if(Lookup!=-1)
	{
	//	FILE *art=fopen(artfilename,"rb");
		
		unsigned int header;
		unsigned short *rowoffset;
		
		unsigned short xoffset;
		unsigned short numpixels;
		
		bool done=false;
		
		int j,k;
		long here;
		int offset=0;
		
		fseek(art,Lookup,SEEK_SET);
		fread(&header,4,1,art);
		fread(&Tex->Width,2,1,art);
		fread(&Tex->Height,2,1,art);
		
		Tex->realWidth=Tex->Width;
		Tex->realHeight=Tex->Height;
		Tex->Width=	NextPowerOf2(Tex->Width);
		
		Tex->Height=NextPowerOf2(Tex->Height);
		
		rowoffset=new unsigned short[Tex->Height];
	//	if(Tex->ImageData!=NULL)
		//	delete [] Tex->ImageData;
		
		Tex->ImageData=new unsigned char[Tex->Width*Tex->Height*4];
		memset(Tex->ImageData,0,Tex->Width*Tex->Height*4);
		unsigned short tmpushort;
		for(j=0;j<Tex->realHeight;j++)
		{
			fread(&tmpushort,2,1,art);
			rowoffset[j]=tmpushort;
		}
		here=ftell(art);
		for(j=0;j<Tex->realHeight;j++)
		{
			offset=(j+Tex->Height-Tex->realHeight)*Tex->Width*4;
			fseek(art,here+rowoffset[j]*2,SEEK_SET);
			done=false;
			while(!done)
			{
				fread(&xoffset,2,1,art);
				fread(&numpixels,2,1,art);
				offset+=4*xoffset;
				if(xoffset+numpixels==0)
				{
					done=true;
					break;
				}
				for(k=0;k<numpixels;k++)
				{
					fread(&C16.Color,2,1,art);
					Color16toColor32(C16,C32);
					
					Tex->ImageData[offset]=C32.R;
					Tex->ImageData[offset+1]=C32.G;
					Tex->ImageData[offset+2]=C32.B;
					Tex->ImageData[offset+3]=C32.A;
					offset+=4;
				}
				
			}	
			
		}
		FlipTexture(Tex);
		glGenTextures(1, &Tex->TexID);					// Generate OpenGL texture IDs
		
		glBindTexture(GL_TEXTURE_2D, Tex->TexID);			// Bind Our Texture
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// Linear Filtered + MIPMAPPING
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);					// Linear Filtered 
		
	//	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Tex->Width, Tex->Height, GL_RGBA, GL_UNSIGNED_BYTE, Tex->ImageData);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Tex->Width, Tex->Height,0,GL_RGBA,GL_UNSIGNED_BYTE, Tex->ImageData);
		Tex->ItemID=i-0x4000;
	//  delete [] Tex->ImageData;
		delete [] rowoffset;
	//	fclose(art);
	//	fclose(artidx);
	}
	else
	{
		return 0;
	//	fclose(artidx);
	
	}
return 1;
}
