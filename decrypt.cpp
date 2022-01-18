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

auto compare_letter = [](const pair<char,int>&a, const pair<char,int>&b){return a.sc>b.sc;};
auto compare_freq = [](const pair<string,int>&a, const pair<string,int>&b){return a.sc>b.sc;};
void print(const set<pair<string,int>,decltype(compare_freq)>&s){cout<<"{";for(auto i:s)cout<<i<<", ";cout<<"}"<<endl;}
void print(const set<pair<char,int>,decltype(compare_letter)>&s){cout<<"{";for(auto i:s)cout<<i<<", ";cout<<"}"<<endl;}

unordered_set<string> one_letter = {"a","i"};

unordered_set<string> two_letter = {"am", "an", "as", "at", "be", "by", "do", "go", "he", "is", "in", "if", "it",
"me","my","no","of","on","or","to","so","up","us","we"};

unordered_set<char> punctuations = {' ', ',', ';', '!', '.'};

vector<char> letter_frequency = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 
'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};

vector<string> solve(string&s){
    unordered_map<string,int> one_cipher, two_cipher, three_cipher;
    set<pair<string,int>,decltype(compare_freq)> one_cipher_order(compare_freq), two_cipher_order(compare_freq), 
    three_cipher_order(compare_freq);
    
    unordered_map<char,int> cipher_letter;
    set<pair<char,int>,decltype(compare_letter)> cipher_letter_order(compare_letter);

    // get frequencies of all uni,bi,tri grams and also store sentences tokenized by punctuations in a list
    int n = s.size();
    vector<string> v;
    string cur = "";
    loop(i,n){
        if(punctuations.count(s[i])){
            if(cur!="")v.pb(cur);
            if(cur.size()==1){
                one_cipher[cur]+=1;
            }
            else if(cur.size()==2){
                two_cipher[cur]+=1;
            }
            else if(cur.size()==3){
                three_cipher[cur]+=1;
            }
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
    for(auto i:one_cipher){
        one_cipher_order.insert(mp(i.fs,i.sc));
    }
    for(auto i:two_cipher){
        two_cipher_order.insert(mp(i.fs,i.sc));
    }
    for(auto i:three_cipher){
        three_cipher_order.insert(mp(i.fs,i.sc));
    }
    for(auto i:cipher_letter){
        cipher_letter_order.insert(mp(i.fs,i.sc));
    }

    
}

int main(){
    string s = "1981y, $pp1n1yuux oq@ 2@3s5u1n $p 1981y, 1v y n$s9o2x 19 v$soq yv1y. 1o 1v oq@ v@6@9oq uy27@vo n$s9o2x 5x y2@y, oq@ v@n$98 0$vo 3$3su$sv n$s9o2x, y98 oq@ 0$vo 3$3su$sv 8@0$n2ynx 19 oq@ #$2u8. 5$s98@8 5x oq@ 1981y9 $n@y9 $9 oq@ v$soq, oq@ y2y51y9 v@y $9 oq@ v$soq#@vo, y98 oq@ 5yx $p 5@97yu $9 oq@ v$soq@yvo, 1o vqy2@v uy98 5$28@2v #1oq 3yw1voy9 o$ oq@ #@vo; nq19y, 9@3yu, y98 5qsoy9 o$ oq@ 9$2oq; y98 5y97uy8@vq y98 0xy90y2 o$ oq@ @yvo. 19 oq@ 1981y9 $n@y9, 1981y 1v 19 oq@ 61n191ox $p v21 uy9wy y98 oq@ 0yu816@v; 1ov y98y0y9 y98 91n$5y2 1vuy98v vqy2@ y 0y21o10@ 5$28@2 #1oq oqy1uy98, 0xy90y2 y98 198$9@v1y. 7$$8, 9$# os29 p$2 oq@ v@n$98 3y2o $p oq@ 4s@vo1$9, 7$$8 usnw!";
    auto v = solve(s);
}