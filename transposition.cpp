#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdio>
#include <sstream>
#include <string>
#include <cctype>
#include<cstdlib>
#include<cmath>

using namespace std;

char array_[28][5];


int main()
{
	string input;
	ifstream infile;
   	infile.open("transposition-91.txt");
	// ifstream myfile ("transposition-91.txt");
	ofstream outfile;
   	outfile.open("output.txt");
  	infile>>input;
  	outfile<<input<<endl;
  	input+='\0';
  	//input = input.substr(0, input.size()-1);
	
  	int length;
  //	length=input.length();
  	cout<<length<<endl;

  	transform(input.begin(), input.end(), input.begin(), ::tolower);

  	string words;
  	infile>>words;
  	cout<<words<<endl;

  	string token = words.substr(0, words.find(","));
  	cout<<token<<endl;

  	outfile<<"length of key for this text is: 5 "<<endl;


  	int m=0,j=0;   
        for ( j = 0;j<28; j++) {
                for (int i = j; i < input.length()-1; i = i + 28) {
                
                array_[j][m]=input.at(i);
                m++;
             }
            m=0;
        }

	int arr[] = { 0,1,2,3,4 }; 
  	sort(arr, arr + 5);
    int permutationArr[120][5];
    int i=0;

    do { 
        permutationArr[i][0]=arr[0];
        permutationArr[i][1]=arr[1];
        permutationArr[i][2]=arr[2];
        permutationArr[i][3]=arr[3];
        permutationArr[i][4]=arr[4];
        i++; 
    } while (next_permutation(arr, arr + 5));

	int seq[5];  	
	string decoded;
  	for(int itr=0;itr<120;itr++)
  	{
  		decoded="";
  	 for(int i=0;i<28;i++)
  	 {
  		for (int j = 0; j < 5; ++j)
  		{
  			decoded+=array_[i][permutationArr[itr][j]];
  			seq[j]=permutationArr[itr][j];
  			//cout<<i<<" "<<j<<" "<<seq[j]<<endl;
  		}
  	 }
  	 if (decoded.find(token) != string::npos)
  	 	break;
  	}

  	outfile<<"The sequence of the key is :";
  	for(int i=0;i<5;i++)
  		outfile<<seq[i]<<" ";

  	outfile<<endl;
  	 
  	outfile<<"decoded text is :"<<endl<<decoded<<endl;

  	char encryption[28][5];
  	string En="";

  	for(int i=0;i<28;i++)
  		for(int j=0;j<5;j++)
  		{
  			encryption[i][seq[j]]=decoded.at(j+(i*5));
  		}

  		for(int j=0;j<5;j++)
  			for(int i=0;i<28;i++)
  				En+=encryption[i][j];

  		//transform(En.begin(), En.end(), En.begin(), ::toupper);
  		outfile<<"Encrypted text :\n"<<En<<"  "<<endl;

  		input = input.substr(0, input.size()-1);
  		cout<<input<<"  "<<input.length()<<endl;

  		outfile<<"Accuracy :"<<((input.length()-input.compare(En))/input.length())*100<<"%"<<endl;


	return 0;
}