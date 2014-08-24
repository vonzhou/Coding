#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

void reverse(string *words, int count){
	int i,j;
	if(words == NULL)
		return ;
	i = 0;
	j = count - 1;
	while(i < j){
		string tmp = words[j];
		words[j] = words[i];
		words[i] = tmp;
		i ++;
		j --;
	}
	return ;
}


void reverseWords(string &s) {
	int i,j,count = 0;
	string *words = new string[6000];
	if(s.empty())
		return;
	i = 0;
	while(i < s.length()){
		while(i < s.length() && s[i] == ' ')
			i++;
		j = i;		
		while(j < s.length() && s[j] != ' ')
			j++;
		if(i != j)
			words[count++] = s.substr(i, j - i);
		i = j;
	}
	reverse(words, count);
	
	s = "";
	if(count ==0)
		s = "";
	else if(count == 1)
		s = words[0];
	else{
		for(i =0;i < count-1 ; i++){
			s += words[i];
			s += " ";
		}
		s += words[count-1];
	}
	delete[] words;
}



int  main(){
	string s = "   abc  cao  dan ren   ";
	reverseWords(s);
	cout << s << endl;

//	cout << s.substr(3,10) <<endl;
	return 0;
}
