#include <bits/stdc++.h>

using namespace std;

#define loop(i,n) for(int i=0;i<n;i++)
#define fs first
#define sc second
#define mp make_pair
#define pb push_back

using ll = long long int;

template<typename T> ostream& operator<<(ostream&os,const vector<T>&v){loop(i,v.size())os<<v[i]<<"|";os<<endl;return os;}
template<typename T> ostream& operator<<(ostream&os,const set<T>&s){os<<"{";for(auto i:s)os<<i<<", ";os<<"}";os<<endl;return os;}
template<typename T, typename S> ostream& operator<<(ostream&os,const pair<T,S>&p){os<<"["<<p.fs<<","<<p.sc<<"]";return os;}
template<typename T, typename S> ostream& operator<<(ostream&os,const unordered_map<T,S>&h){os<<"{";for(auto i:h)os<<i<<", ";os<<"}";return os;}

auto compare_letter = [](const pair<char,int>&a, const pair<char,int>&b){return a.sc>=b.sc;};
auto compare_freq = [](const pair<string,int>&a, const pair<string,int>&b){return a.sc>=b.sc;};
void print(const set<pair<string,int>,decltype(compare_freq)>&s){cout<<"{";for(auto i:s)cout<<i<<", ";cout<<"}"<<endl;}
void print(const set<pair<char,int>,decltype(compare_letter)>&s){cout<<"{";for(auto i:s)cout<<i<<", ";cout<<"}"<<endl;}

unordered_set<string> one_letter = {"a","i"};
unordered_set<string> two_letter = {"am", "an", "as", "at", "be", "by", "do", "go", "he", "is", "in", "if", "it",
"me","my","no","of","on","or","to","so","up","us","we"};
unordered_set<char> punctuations = {' ', ',', ';', '!', '.','\n','\t'};
vector<char> letter_frequency = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 
'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};

unordered_map<char,char> plain_cipher, cipher_plain;

bool match(const string&a,const string&b){
    // a is reference, b is output
    unordered_map<char,char> temp_cipher, temp_plain;
    if(a.size()==b.size()){
        int n = a.size();
        loop(i,n){
            if(a[i]>='A' && a[i]<='Z' && a[i]!=b[i])return false;
            else if((a[i]>'Z' || a[i]<'A') && ((plain_cipher.count(tolower(b[i])))
                || ((temp_cipher.count(a[i])&&temp_cipher[a[i]]!=b[i])) || 
                ((temp_plain.count(b[i]))&&(temp_plain[b[i]]!=a[i]))
                ))return false;
            if(a[i]>'Z' || a[i]<'A'){
                temp_cipher[a[i]]=b[i];     // add current temporary substitution to check if they don't interfere.
                temp_plain[b[i]]=a[i];
            }
        }
        return true;
    }
    else return false;
}

// construct trie to store dictionary
struct Node{
    bool leaf;
    unordered_map<char,Node*> c;
    Node(){
        leaf=false;
    }
};

class Trie{
private:
    Node* head;
public:
    ll cnt;
    Trie(){
        head = new Node();
        cnt = 0;
    }
    ll size(){
        return cnt;
    }
    void insert(const string&word){
        Node* cur = head;
        for(auto i:word){
            if(!cur->c.count(i)){
                cur->c[i]=new Node();
            }
            cur=cur->c[i];
        }
        cnt+=(!cur->leaf);
        cur->leaf=true;
    }
    bool search(const string&word){
        Node* cur = head;
        for(auto i:word){
            if(!cur->c.count(i))return false;
            cur=cur->c[i];
        }
        return cur->leaf;
    }
    Node* prefix(const string&word){
        Node* cur = head;
        for(auto i:word){
            if(!cur->c.count(i))return nullptr;
            cur=cur->c[i];
        }
        return cur;
    }
    vector<string> get_all(const string&word, const int max_length){
        // returns all the words with given prefix
        Node* cur = prefix(word);
        if(!cur)return {};
        queue<pair<Node*,string>> q;
        q.push(mp(cur,word));
        vector<string> v;
        while(!q.empty()){
            auto temp = q.front();
            q.pop();
            if(temp.fs->leaf && temp.sc.size()==max_length){
                v.pb(temp.sc);
            }
            if(temp.sc.size()<max_length){
                for(auto i:temp.fs->c){
                    string temp1 = temp.sc;
                    temp1+=i.fs;
                    q.push(mp(i.sc,temp1));
                }
            }
        }
        return v;
    }
    vector<string> find_words(const string&word){
        // returns words which match at given places only.
        int n = word.size(), i=0;
        while(i<n){
            if(word[i]>='A' && word[i]<='Z')i++;
            else break;
        }
        if(i==n)return {};
        else{
            string word2 = word.substr(0,i);
            // get the string of words
            vector<string> temp = get_all(word2,word.size());
            // now need to eliminate those words from output which don't match with given word.
            vector<string> output;
            for(auto i:temp){
                if(match(word,i))output.pb(i);
            }
            return output;
        }
    }
};

unordered_map<string,int> one_cipher, two_cipher, three_cipher, four_cipher, five_cipher, six_cipher;
set<pair<string,int>,decltype(compare_freq)> one_cipher_order(compare_freq), two_cipher_order(compare_freq), three_cipher_order(compare_freq),
four_cipher_order(compare_freq), five_cipher_order(compare_freq), six_cipher_order(compare_freq);
unordered_map<char,int> cipher_letter;
set<pair<char,int>,decltype(compare_letter)> cipher_letter_order(compare_letter);
vector<string> v;
Trie* trie;


pair<string,vector<bool>> substitute(const string&s){
    string output = "";
    vector<bool> v1(s.size(),false);
    for(int i=0;i<s.size();i++){
        if(cipher_plain.count(s[i])){
            output+=(cipher_plain[s[i]]-'a')+'A';
            v1[i]=true;
        }
        else output+=s[i];
    }
    return mp(output,v1);
}

pair<int,vector<bool>> count_substituted(string&a){
    int count = 0;
    vector<bool> arr(a.size(),false);
    loop(i,a.size()){
        arr[i]=cipher_plain.count(a[i]);
        count+=arr[i];
    }
    return mp(count,arr);
}

inline void add_cipher(const char a,const char b){
    cipher_plain[a]=b;
    plain_cipher[b]=a;
}


int count_frequency_at_index(unordered_map<string,int>&h,char c,int i,bool total){
    // counts frequency of character at index i.
    int count = 0;
    for(auto j:h){
        if(total)count+=((j.fs[i]==c)?j.sc:0);
        else count+=(j.fs[i]==c);
    }
    return count;
}

void check_on(){
    /*
        Here we have two cases, either we know 'n' (through "and") and we don't know n.
        if n: just substitute palindrome with 'o'.
        else: just take two letters on the palindrome and do the following
        1. count first letter frequencies of each, 'n' would have only 1 and 'o' would have more.
        2. count second letter frequencies of each, 'n' would have higher.
    */
    for(auto i:two_cipher){
        string temp = i.fs;
        reverse(temp.begin(),temp.end());
        if(two_cipher.count(temp)){
            if(plain_cipher.count('n')){
                loop(i,temp.size()){
                    if(cipher_plain.count(temp[i]))continue;
                    else{
                        add_cipher(temp[i],'o');
                    }
                }
            }
            else{
                vector<pair<int,char>> arr0, arr1;
                loop(i,temp.size()){
                    arr0.pb(mp(count_frequency_at_index(two_cipher,temp[i],0,false),temp[i]));
                    arr1.pb(mp(count_frequency_at_index(two_cipher,temp[i],1,true),temp[i]));
                }
                auto compare = [](const pair<int,char>&a1,const pair<int,char>&a2){return a1.fs<a2.fs;};
                sort(arr0.begin(),arr0.end(),compare);
                sort(arr1.begin(),arr1.end(),compare);
                auto temp_function = [](vector<pair<int,char>>&arr){
                    add_cipher(arr[0].sc,'n');
                    add_cipher(arr[1].sc,'o');
                };
                if(arr0[0].fs==1){
                    temp_function(arr0);
                }
                else if(arr0[1].fs==1){
                    reverse(arr0.begin(),arr0.end());
                    temp_function(arr0);
                }
                else{
                    reverse(arr1.begin(),arr1.end());
                    temp_function(arr1);
                }
            }
            break;
        }
    }
    if(plain_cipher.count('n')){
        for(auto i:two_cipher){
            string temp = i.fs;
            if(cipher_plain.count(temp[0]) && cipher_plain[temp[0]]=='n' && !cipher_plain.count(temp[1])){
                add_cipher(temp[1],'o');
                break;
            }
        }
    }
}

void check_on2(){
    for(auto i:two_cipher){
        string temp = i.fs;
        if(cipher_plain.count(temp[1]) && cipher_plain[temp[1]]=='n' && !cipher_plain.count(temp[0])){
            // then this is definitely o
            add_cipher(temp[0],'o');
            break;
        }
    }
}

void check_of(){
    for(auto i:two_cipher){
        string temp = i.fs;
        if(cipher_plain.count(temp[0]) && cipher_plain[temp[0]]=='o' && !cipher_plain.count(temp[1])){
            add_cipher(temp[1],'f');
            break;
        }
    }
}

void check_for(){
    // r was not found till now
    for(auto i:three_cipher){
        string temp = i.fs;
        if(cipher_plain.count(temp[0]) && cipher_plain[temp[0]]=='f' && 
            cipher_plain.count(temp[1]) && cipher_plain[temp[1]]=='o'){
            add_cipher(temp[2],'r');
            break;
        }
    }
}

void check_there(){
    // there, their
    // r was not found till now
    for(auto i:five_cipher){
        string temp = i.fs;
        if(cipher_plain.count(temp[0]) && cipher_plain[temp[0]]=='t' &&
            temp[2]==temp[4] && cipher_plain.count(temp[1]) && cipher_plain[temp[1]]=='h' &&
            cipher_plain.count(temp[2]) && cipher_plain[temp[2]]=='e' &&
            !cipher_plain.count(temp[3])
            ){
            // this is definitely r because s has already been found
            add_cipher(temp[3],'r');
            break;
        }
        else if(cipher_plain.count(temp[0]) && cipher_plain[temp[0]]=='t' &&
            cipher_plain.count(temp[1]) && cipher_plain[temp[1]]=='h' &&
            cipher_plain.count(temp[2]) && cipher_plain[temp[2]]=='e' &&
            cipher_plain.count(temp[3]) && cipher_plain[temp[3]]=='i' &&
            !cipher_plain.count(temp[4])
            ){
            add_cipher(temp[4],'r');
            break;
        }
    }
}

void check_here(){
    // here
    for(auto i:four_cipher){
        string temp = i.fs;
        if(cipher_plain.count(temp[0]) && cipher_plain[temp[0]]=='h' &&
            temp[1]==temp[3] &&
            cipher_plain.count(temp[1]) && cipher_plain[temp[1]]=='e'
            ){
            add_cipher(temp[2],'r');
            break;
        }
    }
}

void check_s(){
    // s may not be found, then check in another way
    for(auto i:three_cipher){
        string temp = i.fs;
        if(!cipher_plain.count(temp[0]) && cipher_plain.count(temp[1]) && cipher_plain[temp[1]]=='h' &&
            cipher_plain.count(temp[2]) && cipher_plain[temp[2]]=='e'){
            add_cipher(temp[0],'s');
        }
    }
}

void check_is(){
    unordered_map<string,int> is_find;
    string prev="";
    loop(i,v.size()){
        if(punctuations.count(v[i][0]))continue;
        string temp = v[i];
        if(temp.size()==1 && plain_cipher.count('a') && cipher_plain[temp[0]]=='a'){
            if(prev.size()==2){
                is_find[prev]++;
            }
        }
        prev=temp;
    }
    set<pair<string,int>,decltype(compare_freq)> s(compare_freq);
    for(auto i:is_find){
        string temp_string = i.fs;
        auto temp = count_substituted(temp_string);
        if(temp.fs==0){
            add_cipher(temp_string[0],'i');
            add_cipher(temp_string[1],'s');
            break;
        }
    }
}

bool dictionary_substitution(string a){
    int count = count_substituted(a).fs;
    if(count==a.size())return false;
    // now need to convert a
    a = substitute(a).fs;
    vector<string> words = trie->find_words(a);
    if(words.size()==0)return false;
    else if(words.size()==1){
        // ideal, we assume that dictionary contains all the words, 
        // so there would be no issues during substitution
        int n = a.size();
        string temp = words[0];
        // perform substitution
        loop(i,n){
            if(a[i]>='A' && a[i]<='Z')continue;
            else{
                add_cipher(a[i],tolower(temp[i]));
            }
        }
        return true;
    }
    else return false;
}

int infer(){
    // run loop until none can be substituted
    int count = 0;
    for(auto i:v){
        if(!punctuations.count(i[0])){
            bool flag = dictionary_substitution(i);
            // if(flag){
            //     cout<<i<<endl;
            //     cout<<substitute(i).fs<<endl;
            // }
            count+=flag;
        }
    }
    return count;
}

void run(){
    int count = 1;
    while(count){
        count = infer();
    }
}

void read_dictionary(const string&dictionary_file){
    ll words_read = 0;
    trie=new Trie();
    ifstream file;
    file.open(dictionary_file);
    string line;
    getline(file,line);
    string cur = "";
    loop(i,line.size()){
        if(line[i]==','){
            if(cur.size()){
                words_read++;
                trie->insert(cur);
            }
            cur="";
        }
        else cur+=line[i];
    }
    if(cur.size() && cur!=",")trie->insert(cur);
}

inline void add_ordered(unordered_map<string,int>&h, set<pair<string,int>,decltype(compare_freq)>&s){for(auto i:h) s.insert(mp(i.fs,i.sc));}
inline void add_ordered(unordered_map<char,int>&h,set<pair<char,int>,decltype(compare_letter)>&s){for(auto i:h) s.insert(mp(i.fs,i.sc));}

void read_ciphertext(const string&s){
    // get frequencies of all uni,bi,tri grams and also store sentences tokenized by punctuations in a list
    int n = s.size();
    string cur = "";
    loop(i,n){
        if(punctuations.count(s[i])){
            if(cur.size()!=0)v.pb(cur);
            if(cur.size()==1){one_cipher[cur]+=1;}
            else if(cur.size()==2){two_cipher[cur]+=1;}
            else if(cur.size()==3){three_cipher[cur]+=1;}
            else if(cur.size()==4){four_cipher[cur]+=1;}
            else if(cur.size()==5){five_cipher[cur]+=1;}
            else if(cur.size()==6){six_cipher[cur]+=1;}
            cur="";cur+=s[i];
            v.pb(cur);
            cur="";
            continue;
        }
        cur+=s[i];
        cipher_letter[s[i]]+=1;
    }
    if(cur!="")v.pb(cur);
    // store in set for ordering the grams with frequency.
    add_ordered(one_cipher, one_cipher_order);
    add_ordered(two_cipher, two_cipher_order);
    add_ordered(three_cipher, three_cipher_order);
    add_ordered(four_cipher, four_cipher_order);
    add_ordered(five_cipher, five_cipher_order);
    add_ordered(cipher_letter, cipher_letter_order);
}

void clear(){
    plain_cipher.clear();
    cipher_plain.clear();
    one_cipher.clear(), two_cipher.clear(), three_cipher.clear(), four_cipher.clear(), five_cipher.clear(), six_cipher.clear();
    one_cipher_order.clear(), two_cipher_order.clear(), three_cipher_order.clear(), four_cipher_order.clear(), five_cipher_order.clear(), six_cipher_order.clear();
    cipher_letter.clear();
    cipher_letter_order.clear();
}

void solve_dictionary(const string &s){
    clear();
    run();
}

bool check(const string&s){
    unordered_set<char> h;
    loop(i,s.size()){
        if(!punctuations.count(s[i]))h.insert(s[i]);
    }
    return h.size() == cipher_plain.size();
}

void solve_frequency(const string&s){
    clear();
    // check for 1 letter words, if highest frequency then replace with 'a', if no one letter then directly jump to next step
    if(one_cipher_order.size()){
        vector<pair<int,char>>temp;
        for(auto i:one_cipher_order){
            temp.pb(mp(cipher_letter[i.fs[0]],i.fs[0]));
        }
        auto compare = [](const pair<int,char>&a,const pair<int,char>&b){return a.fs>b.fs;};
        sort(temp.begin(),temp.end(),compare);
        vector<char> temp2 = {'a','i'};
        for(int i=0;i<temp.size();i++){
            add_cipher(temp[i].sc,temp2[i]);
        }
    }
    // now check for two letters which begin with 'a' or 'i' : LATER
    if(three_cipher.size()){
        // find most frequent three letters and replace with "the".
        string temp = (*three_cipher_order.begin()).fs;
        vector<char> arr = {'t','h','e'};
        loop(i,3){
            add_cipher(temp[i],arr[i]);
        }
        // find most frequent three letters starting with 'a' and replace with "and" and possibly "are"
        if(plain_cipher.count('a')){
            for(auto i:three_cipher_order){
                if(i.fs[0]==plain_cipher['a']){
                    temp = i.fs;
                    auto temp_count = count_substituted(temp);
                    if(temp_count.fs==1){
                        // most likely "and"
                        vector<char> arr = {'n', 'd'};
                        loop(i,2){
                            add_cipher(temp[i+1],arr[i]);
                        }
                    }
                    else if(temp_count.fs==2){
                        // possibly "are"
                        if(temp_count.sc[2] && cipher_plain[temp[2]]=='e'){
                            add_cipher(temp[1],'r');
                        }
                    }
                }
            }
        }
    }

    // now check for two letters which are palindromic : O(n) -> on, no
    check_on();
    // now search for "is", can be found though "is a" type phrases
    check_is();
    if(!plain_cipher.count('s'))check_s();
    // IS backup : high frequency two letter (IMPLEMENT), verify with individual characters
    check_on2();
    check_there();
    check_here();
    if(plain_cipher.count('r')){
        check_for();
        check_of();
    }
    // finally do substitution using dictionary.
    run();
}

string extract_key(){
    string s = "";
    for(int i=0;i<26;i++){
        char c = i+'a';
        if(plain_cipher.count(c)){
            s+=plain_cipher[c];
        }
        else s+="_";
    }
    return s;
}

string get_plaintext(const string&s){
    string output = "";
    loop(i,s.size()){
        if(!punctuations.count(s[i]))output+=cipher_plain[s[i]];
        else output+=s[i];
    }
    return output;
}

void solve(const string&s){
    // create dictionary
    read_dictionary("dictionary.txt");
    read_ciphertext(s);
    // cout<<"Solving through dictionary"<<endl;
    solve_dictionary(s);
    if(!check(s)){
        // cout<<"Solving through frequency analysis"<<endl;
        solve_frequency(s);
    }
}

int main(int argc,char* argv[]){
    if(argc<2){
        cout<<"Please enter file name"<<endl;
        exit(0);
    }
    ifstream file;
    file.open(argv[1]);
    string s = "";
    string line;
    while(!file.eof()){
        if(s.size())s+='\n';
        getline(file,line);
        s+=line;
    }
    solve(s);
    if(argc==2){
        cout<<"Plaintext:"<<endl;
        cout<<get_plaintext(s)<<endl;
        cout<<"Secret key:"<<endl;
        cout<<extract_key()<<endl;
    }
    else{
        if(!strcmp(argv[2],"decryptText")) cout<<get_plaintext(s)<<endl;
        else if(!strcmp(argv[2],"extractKey")) cout<<extract_key()<<endl;
        else cout<<"Wrong input"<<endl;
    }
    return 0;
}