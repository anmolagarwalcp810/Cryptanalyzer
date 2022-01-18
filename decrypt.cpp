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
unordered_set<char> punctuations = {' ', ',', ';', '!', '.'};
vector<char> letter_frequency = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 
'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};

unordered_map<char,char> plain_cipher, cipher_plain;
unordered_map<string,int> one_cipher, two_cipher, three_cipher, four_cipher, five_cipher, six_cipher;
set<pair<string,int>,decltype(compare_freq)> one_cipher_order(compare_freq), two_cipher_order(compare_freq), three_cipher_order(compare_freq),
four_cipher_order(compare_freq), five_cipher_order(compare_freq), six_cipher_order(compare_freq);
unordered_map<char,int> cipher_letter;
set<pair<char,int>,decltype(compare_letter)> cipher_letter_order(compare_letter);
vector<string> v;

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
                        cipher_plain[temp[i]]='o';
                        plain_cipher['o']=temp[i];
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
                    cipher_plain[arr[0].sc]='n';
                    cipher_plain[arr[1].sc]='o';
                    plain_cipher['n']=arr[0].sc;
                    plain_cipher['o']=arr[1].sc;
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
                cipher_plain[temp[1]]='o';
                plain_cipher['o']=temp[1];
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
            cipher_plain[temp[0]]='o';
            plain_cipher['o']=temp[0];
            break;
        }
    }
}

void check_of(){
    for(auto i:two_cipher){
        string temp = i.fs;
        if(cipher_plain.count(temp[0]) && cipher_plain[temp[0]]=='o' && !cipher_plain.count(temp[1])){
            cipher_plain[temp[1]]='f';
            plain_cipher['f']=temp[1];
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
            cipher_plain[temp[2]]='r';
            plain_cipher['r']=temp[2];
            break;
        }
    }
}

void check_there(){
    // r was not found till now
    for(auto i:five_cipher){
        string temp = i.fs;
        if(cipher_plain.count(temp[0]) && cipher_plain[temp[0]]=='t' &&
            temp[2]==temp[4] && cipher_plain.count(temp[1]) && cipher_plain[temp[1]]=='h' &&
            cipher_plain.count(temp[2]) && cipher_plain[temp[2]]=='e' &&
            !cipher_plain.count(temp[3])
            ){
            // this is definitely r because s has already been found
            cipher_plain[temp[3]]='r';
            plain_cipher['r']=temp[3];
        }
    }
}

void check_s(){
    // s may not be found, then check in another way
    for(auto i:three_cipher){
        string temp = i.fs;
        if(!cipher_plain.count(temp[0]) && cipher_plain.count(temp[1]) && cipher_plain[temp[1]]=='h' &&
            cipher_plain.count(temp[2]) && cipher_plain[temp[2]]=='e'){
            cipher_plain[temp[0]]='s';
            plain_cipher['s']=temp[0];
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
            cipher_plain[temp_string[0]]='i';
            cipher_plain[temp_string[1]]='s';
            plain_cipher['i']=temp_string[0];
            plain_cipher['s']=temp_string[1];
            break;
        }
    }
}

// void check_is_probabilistic(){
//     for(auto i:two_cipher_order){
//         string temp = i.fs;
//         if(count_substituted(temp).fs==0){
            
//         }
//     }
// }

inline void add_ordered(unordered_map<string,int>&h, set<pair<string,int>,decltype(compare_freq)>&s){for(auto i:h) s.insert(mp(i.fs,i.sc));}
inline void add_ordered(unordered_map<char,int>&h,set<pair<char,int>,decltype(compare_letter)>&s){for(auto i:h) s.insert(mp(i.fs,i.sc));}

vector<string> solve(const string&s){
    // get frequencies of all uni,bi,tri grams and also store sentences tokenized by punctuations in a list
    int n = s.size();
    vector<bool> substituted(n,false);
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
            cur="";
            cur+=s[i];
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
    int count = 0;
    // check for 1 letter words, if highest frequency then replace with 'a', if no one letter then directly jump to next step
    if(one_cipher_order.size()>0){
        vector<pair<int,char>>temp;
        for(auto i:one_cipher_order){
            temp.pb(mp(cipher_letter[i.fs[0]],i.fs[0]));
        }
        auto compare = [](const pair<int,char>&a,const pair<int,char>&b){return a.fs>b.fs;};
        sort(temp.begin(),temp.end(),compare);
        vector<char> temp2 = {'a','i'};
        for(int i=0;i<temp.size();i++){
            cipher_plain[temp[i].sc]=temp2[i];
            plain_cipher[temp2[i]]=temp[i].sc;
        }
    }
    // now check for two letters which begin with 'a' or 'i' : LATER
    if(three_cipher.size()){
        // find most frequent three letters and replace with "the".
        string temp = (*three_cipher_order.begin()).fs;
        vector<char> arr = {'t','h','e'};
        loop(i,3){
            cipher_plain[temp[i]]=arr[i];
            plain_cipher[arr[i]]=temp[i];
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
                            cipher_plain[temp[i+1]]=arr[i];
                            plain_cipher[arr[i]]=temp[i+1];
                        }
                    }
                    else if(temp_count.fs==2){
                        // possibly "are"
                        if(temp_count.sc[2] && cipher_plain[temp[2]]=='e'){
                            cipher_plain[temp[1]]='r';
                            plain_cipher['r']=temp[1];
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
    // if(!plain_cipher.count('s'))check_s();
    // IS backup : high frequency two letter (IMPLEMENT), verify with individual characters
    check_on2();
    check_there();
    check_their();
    check_here();
    // if(plain_cipher.count('r')){
    //     check_for();
    //     check_of();
    // }


    cout<<substitute(s).fs<<endl;
    cout<<v<<endl;
    print(one_cipher_order);
    print(two_cipher_order);
    print(three_cipher_order);
    print(four_cipher_order);
    print(five_cipher_order);
    print(six_cipher_order);
    print(cipher_letter_order);
    cout<<cipher_plain<<endl;
}

int main(){
    string s = "1981y, $pp1n1yuux oq@ 2@3s5u1n $p 1981y, 1v y n$s9o2x 19 v$soq yv1y. 1o 1v oq@ v@6@9oq uy27@vo n$s9o2x 5x y2@y, oq@ v@n$98 0$vo 3$3su$sv n$s9o2x, y98 oq@ 0$vo 3$3su$sv 8@0$n2ynx 19 oq@ #$2u8. 5$s98@8 5x oq@ 1981y9 $n@y9 $9 oq@ v$soq, oq@ y2y51y9 v@y $9 oq@ v$soq#@vo, y98 oq@ 5yx $p 5@97yu $9 oq@ v$soq@yvo, 1o vqy2@v uy98 5$28@2v #1oq 3yw1voy9 o$ oq@ #@vo; nq19y, 9@3yu, y98 5qsoy9 o$ oq@ 9$2oq; y98 5y97uy8@vq y98 0xy90y2 o$ oq@ @yvo. 19 oq@ 1981y9 $n@y9, 1981y 1v 19 oq@ 61n191ox $p v21 uy9wy y98 oq@ 0yu816@v; 1ov y98y0y9 y98 91n$5y2 1vuy98v vqy2@ y 0y21o10@ 5$28@2 #1oq oqy1uy98, 0xy90y2 y98 198$9@v1y. 7$$8, 9$# os29 p$2 oq@ v@n$98 3y2o $p oq@ 4s@vo1$9, 7$$8 usnw!";
    auto v = solve(s);
}