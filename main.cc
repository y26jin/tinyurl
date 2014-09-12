#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <algorithm>
using namespace std;

string tiny(string u, string dict, map<int, string> & record, int current_token){
  int base = dict.length();  
  record.insert(pair<int, string>(current_token, u));  
  /*
   * Map current token to a 8-bit string
   */
  deque<int> digits;
  if(current_token == 0){
    digits.push_back(current_token);
  }
  else{
    int num = current_token;
    while(num > 0){
      digits.push_front(num%base);
      num = num/base;
    }
  }
  if(digits.size() < 8){
    int addon = 8 - digits.size();
    for(int i=0;i<addon;i++) digits.push_front(0);
  }
  string shorten_string;
  deque<int>::iterator it;
  for(it = digits.begin(); it != digits.end(); it++){
    shorten_string.insert(shorten_string.end(), dict[*it]);
  }

  return shorten_string;
}

static int count_pow(int base, int exp){
  if(exp == 0) return 1;
  else return base * count_pow(base, exp-1);
}

string origin(string s, string dict, map<int, string> & record){
  /*
   * Should access a key-value record to obtain the original url
   */
  int base = dict.length();
  int id = 0, count = 0;
  reverse(s.begin(), s.end());
  for(int i=0;i<s.length();i++){
    int index = dict.find(s[i], 0);
    id += index * count_pow(base, count);
    count++;
  }
  cout<<endl;
  cout<<"ID retrieved: "<<id<<endl;
  return record[id];
}

int main(){
  string dict = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.?-+!/:";
  map<int, string> record;
  int token = 0;
  for(int i=0;i<5;i++){
    string url;
    cin>>url;
    cout<<"Input = "<<url<<endl;
    
    string tinyurl = tiny(url, dict, record, token);
    token++;
    cout<<"Tinyurl = "<<tinyurl<<endl;
    cout<<"Origin url = "<<origin(tinyurl, dict, record)<<endl;
    cout<<endl;
  }

  return 0;
}
