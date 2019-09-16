#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>

using namespace std;
char dataBlock[500];
char keyBlock[64];
int Rold[32];
int PBoxOutput[32];
int ExpandedBit[48];
int shorten_result[32];
int finalKeybit[16][48];
int Lpart[32];
void printASCII(int s[], int size_)
{
    for(int itr =1; itr<=(size_/8); itr++)
    {
        int n = 0;
        int i;

        for (i = (itr*8)-8; i < itr*8; ++i)
        {
            n <<= 1;
            n += s[i];
        }

        printf("%c",n);
    }
}
int PI[] = {58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7
           };
int CP_1[] = {57, 49, 41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10, 2, 59, 51, 43, 35, 27,
              19, 11, 3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14, 6, 61, 53, 45, 37, 29,
              21, 13, 5, 28, 20, 12, 4
             };
int CP_2[] = {14, 17, 11, 24, 1, 5, 3, 28,
              15, 6, 21, 10, 23, 19, 12, 4,
              26, 8, 16, 7, 27, 20, 13, 2,
              41, 52, 31, 37, 47, 55, 30, 40,
              51, 45, 33, 48, 44, 49, 39, 56,
              34, 53, 46, 42, 50, 36, 29, 32
             };
int E[] = {32, 1, 2, 3, 4, 5,
           4, 5, 6, 7, 8, 9,
           8, 9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32, 1
          };
int PI_2[] = {35, 38, 46, 6, 43, 40, 14, 45,
              33, 19, 26, 15, 23, 8, 22, 10,
              12, 11, 5, 25, 27, 21, 16, 31,
              28, 32, 34, 24, 9, 37, 2, 1
             };
int P[] = {16, 7, 20, 21, 29, 12, 28, 17,
           1, 15, 23, 26, 5, 18, 31, 10,
           2, 8, 24, 14, 32, 27, 3, 9,
           19, 13, 30, 6, 22, 11, 4, 25
          };
int PI_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
              39, 7, 47, 15, 55, 23, 63, 31,
              38, 6, 46, 14, 54, 22, 62, 30,
              37, 5, 45, 13, 53, 21, 61, 29,
              36, 4, 44, 12, 52, 20, 60, 28,
              35, 3, 43, 11, 51, 19, 59, 27,
              34, 2, 42, 10, 50, 18, 58, 26,
              33, 1, 41, 9, 49, 17, 57, 25
             };
int SHIFT[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
void decToBinary(int n,char *s)
{
    char a;
    for (int i = 7; i >= 0; i--)
    {
        int k = n >> i;
        if (k & 1)
        {
            strcat(s,"1");
        }
        else
        {
            strcat(s,"0");
        }
    }
}
void printCharArray(char *s)
{
    size_t n = strlen(s);
    for(int i=0; i<n; i++)
        cout<<s[i]<<" ";
    cout<<endl;

}
void printIntArray(int *s, int n)
{

    for(int i=0; i<n; i++)
        cout<<s[i]<<" ";
    cout<<endl;

}
void copyArr(int a[], int b[], int n)
{
    for(int i=0; i<n; i++)
        a[i]=b[i];

}
char * shift_left(char *s,int itr)
{
    for(int i=0; i<itr; i++)
    {
        size_t n = strlen(s);
        memmove(s, s + 1, n);
    }
    return s;
}
void rotate_left(int s[], int n)
{
    for(int itr=0; itr<n; itr++)
    {
        int f1 = s[0];
        for(int i=0; i<=27-1; i++)
        {
            s[i] = s[i + 1];
        }
        s[27] = f1;

        int f2=s[28];
        for(int i=28; i<=55-1; i++)
        {
            s[i] = s[i + 1];
        }
        s[55]=f2;
    }
}


void function_(int itr)
{
    // cout<<"R OLD "<<endl;
    // printIntArray(Rold,32);

    for (int i=0; i<48; i++)
        ExpandedBit[i]=Rold[E[i]-1];

    //cout<<"Expanded bit (48)"<<endl;
    //printIntArray(ExpandedBit,48);
    // cout<<"keys"<<endl;
    // printIntArray(finalKeybit[itr],48);

    for(int i=0; i<48; i++)
        ExpandedBit[i]=ExpandedBit[i]^finalKeybit[itr][i];

    //cout<<"After X-OR (48)"<<endl;
    //printIntArray(ExpandedBit,48);


    for(int i=0; i<32; i++)
        shorten_result[i]=ExpandedBit[PI_2[i]-1];

    //cout<<"Shorten result (32)"<<endl;
    //printIntArray(shorten_result,32);

    for(int i=0; i<32; i++)
        PBoxOutput[i]=shorten_result[P[i]-1];

}





int main()
{
    char key[50];
    char plaintext[500];
    int bitChunk[64];
    int keyBit[64];
    int PItranspose[64];
    int modifiedKeybit[56];
    int Lnew[32];
    int out[64];
    int outfinal[500];
    cout<<"Enter the key :"<<endl;
    cin.getline(key,sizeof(key));
    cout<<"Enter the plain text :"<<endl;

    cin.getline(plaintext,sizeof(plaintext));
    int padding=8-(strlen(plaintext)%8);
    //cout<<itr<<endl;
    if(strlen(plaintext)%8)
    {
        for(int i=0; i<padding; i++)
        {
            strcat(plaintext,"~");
        }
    }
    cout<<"padded(if necessary) plain text: "<<plaintext<<endl;

    for(int i=0; i<strlen(key); i++)
    {
        decToBinary((int)key[i],keyBlock);
    }



    for(int i=0; i<64; i++)
    {
        if(keyBlock[i]=='1')
            keyBit[i]=1;
        else
            keyBit[i]=0;
    }


    for(int i=0; i<strlen(plaintext); i++)
    {
        decToBinary((int)plaintext[i],dataBlock);
    }
    printCharArray(dataBlock);
    cout<<"number of datablocks "<<(strlen(dataBlock)/64)<<endl;
    int size_=strlen(dataBlock)/64;
    for(int iteration=0; iteration<size_; iteration++)
    {
        for(int i=0; i<64; i++)
        {
            if(dataBlock[i]=='1')
                bitChunk[i]=1;
            else
                bitChunk[i]=0;
        }
        shift_left(dataBlock,64);

        //printCharArray(dataBlock);
       // printIntArray(bitChunk,64);
        //sprintASCII(bitChunk);
        //cout<<"key in 64 bit"<<endl;
        //printIntArray(keyBit,64);
        //cout<<plaintext<<endl;

        for(int i=0; i<64; i++)
        {
            PItranspose[i]=bitChunk[PI[i]-1];
        }
        //cout<<"PI transpose part 64 bit"<<endl;
        //printIntArray(PItranspose,64);
        for(int i=0; i<56; i++)
        {
            modifiedKeybit[i]=keyBit[CP_1[i]-1];
        }
        //cout<<"56-transposition key"<<endl;
        //printIntArray(modifiedKeybit,56);

        for(int i=0; i<32; i++)
        {
            Lpart[i]=PItranspose[i];
            Rold[i]=PItranspose[32+i];
        }
        for(int itr=0; itr<16; itr++)
        {
            //iteration

            int modifiedKeybit2[56];
            copyArr(modifiedKeybit2,modifiedKeybit,56);
            rotate_left(modifiedKeybit2,SHIFT[itr]);
            //cout<<"56-transposition key rotated left"<<endl;
            //printIntArray(modifiedKeybit2,56);

            for(int i=0; i<48; i++)
            {
                finalKeybit[itr][i]=modifiedKeybit2[CP_2[i]-1];
            }
            //cout<<"final keybit (48) =>"<<itr+1<<endl;
            //printIntArray(finalKeybit,48);
///--------------KEYS DONE------------------

            function_(itr);

            copyArr(Lnew,Rold,32);
            for (int i=0; i<32; i++)
                Rold[i]=Lpart[i]^PBoxOutput[i];
            //copyArr(Rold,PBoxOutput,32);
            copyArr(Lpart,Lnew,32);
           // printIntArray(PBoxOutput,32);

        }

        for(int i=0; i<32; i++)
        {
            out[i]=Rold[i];
            out[32+i]=Lnew[i];
        }
        for(int i=0; i<64; i++)
            outfinal[i+(iteration*64)]=out[PI_1[i]-1];
    }

    cout<<"Encrypted Datablock"<<endl;
        printIntArray(outfinal,64*size_);
     cout<<"Ciphered: ";
        printASCII(outfinal,64*size_);

int Arr[500];

/// __________DECRYPTION___________
for(int iteration=0; iteration<size_; iteration++)
    {

     copyArr(Arr,outfinal,500);
     for(int i=0; i<64; i++)
        {
            outfinal[i+iteration*64]=Arr[(PI[i]-1)+iteration*64];
        }

    for(int i=0; i<32; i++)
    {
        Lpart[i]=outfinal[i+iteration*64];
        Rold[i]=outfinal[(32+i)+iteration*64];
    }
    for(int itr=0; itr<16; itr++)
    {

        function_(15-itr);

        copyArr(Lnew,Rold,32);
        for (int i=0; i<32; i++)
            Rold[i]=Lpart[i]^PBoxOutput[i];
        copyArr(Lpart,Lnew,32);
    }

    for(int i=0; i<32; i++)
    {
        out[i]=Rold[i];
        out[32+i]=Lnew[i];
    }
    for(int i=0; i<64; i++)
        outfinal[i+(iteration*64)]=out[PI_1[i]-1];

    }

    cout<<"\nDecrypted Datablock"<<endl;
        printIntArray(outfinal,64*size_);
     cout<<"Deciphered: ";
    printASCII(outfinal,(64*size_-(padding%8)*8));
    cout<<endl;


    return 0;
}
