#include <bits/stdc++.h>
#include <fstream>

using namespace std;

unordered_set<string> s;

void solve(string&line){
	int n = line.size();
	int i = 0;
	string temp = "";
	while(i<n && line[i]>='A' && line[i]<='Z'){
		temp+=line[i];
		i++;
	}
	s.insert(temp);
}

void convert_to_upper(string&line){
	int n = line.size();
	for(int i=0;i<n;i++){
		line[i] = toupper(line[i]);
	}
}

void solve2(string&line){
	int n = line.size(), i=0;
	convert_to_upper(line);
	string temp = "";
	while(i<n && line[i]>='A' && line[i]<='Z'){
		temp+=line[i];
		i++;
	}
	s.insert(temp);
}

int main(){
	// TODO: take file name as argument
	ifstream file;
	file.open("words/dictionary_full.txt");
	string line;
	while(file){
		getline(file,line);
		solve(line);
	}
	file.close();
	file.open("words/words.txt");
	while(file){
		getline(file,line);
		solve2(line);
	}
	file.close();
	// file.open("wordlist_10000.txt");
	// while(file){
	// 	getline(file,line);
	// 	solve2(line);
	// }
	// file.close();
	ofstream file2;
	file2.open("dictionary.txt");
	vector<string> v;
	for(auto i:s){
		v.push_back(i);	
	}
	sort(v.begin(),v.end());
	for(auto i:v){
		if(i.size()>3)file2<<i<<",";
		file2.flush();
	}
	file2<<endl;
	file2.close();
}