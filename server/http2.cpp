#include <string>
#include <unordered_map>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
map<string,string> queryKV;
// pos:偏移量注意是个引用,endIndex:参数结尾的下标.addPos:校正偏移量
pair<string,string> spilt(const string& s,string sep,size_t& pos,size_t endIndex,size_t addPos){
    size_t startIndex = s.find(sep,pos);
    if(startIndex == string::npos)return pair<string,string>();
    string key = s.substr(pos,startIndex - pos);

    string value ="";
    if(endIndex == string::npos){ // 比如 name=dxgzg,后面没有&就需要走第一个了。
        value =  s.substr(startIndex + 1);
        pos = s.size(); // endIndex + 1就等于0了，正数溢出
    } else{
        value = s.substr(startIndex + 1, endIndex - startIndex - 1);
        pos = endIndex + addPos;// ex: \r\n偏移量加2,&偏移量加1
    }

    pair<string,string> ans(key,value);
    return ans;
}
// query url
void example(){
    string s = "POST /addMsg HTTP/1.1\r\nHost: 192.168.0.106 : 9996\r\nConnection : keep - alive\r\n\r\n{\"content\":\"test\"}";

    // 第一行数据
    size_t oneIndex = s.find("\r\n");
    string oneData = s.substr(0, oneIndex);
    size_t index1 = oneData.find(" ");
    size_t index2 = oneData.find(" ",index1 + 1);
    string method = oneData.substr(0,index1);
    string path = oneData.substr(index1 + 1,index2 - index1 - 1);
    size_t flagSpilt = path.find("?"); // 找到"?"
    
    string query = "";    
    if(flagSpilt != string::npos){
        query = path.substr(flagSpilt + 1);
        size_t pos = 0;
        while(1){
            size_t endIndex = query.find("&",pos);
            cout << endIndex << endl;
            auto p = spilt(query,"=",pos,endIndex,1);
            if(p.first == "" && p.second == "")break;
            cout << p.first << " " << p.second << endl;
//        cout << pos << endl;

            queryKV[p.first] = p.second;
        }
    }


    string httpVersion = oneData.substr(index2 + 1,oneIndex - index2 - 1);

    cout << "method:" << method << endl;
    cout << "path:" << path <<endl;
    cout << "query:" << query << endl;
    cout << "httpVersion:" << httpVersion << endl;

    for(auto p: queryKV){
        cout << "key:" << p.first;
        cout << " value:" << p.second << endl;
    }
}
void example2(){
    string s = "POST /addMsg?name=dxgzg&age=19 HTTP/1.1\r\nHost: 192.168.0.106 : 9996\r\nConnection : keep - alive\r\n\r\n{\"content\":\"test\"}";

    // 第一行数据
    size_t oneIndex = s.find("\r\n");
    string oneData = s.substr(0, oneIndex);
    example();
    size_t lastlineIndex = 0;
    lastlineIndex = s.find("\r\n\r\n");

    size_t index = oneIndex + 2; // 偏移量,第一行的后面
    size_t endIndex = 0;
    map<string,string> m;
    while( index < lastlineIndex && ((endIndex = s.find("\r\n",index)) != string::npos)){
        auto p = spilt(s,":",index,endIndex,2);
        m[p.first] = p.second;
    }

    for(auto& p : m){
        cout << "key:" << p.first;
        cout << " value:" << p.second << endl;
    }

    size_t dataIndex = lastlineIndex + 4;
    string data = s.substr(dataIndex);

    cout << data.size() << endl;
    cout << data << endl;
}
int main() {
    // 解析url的
    example();
    
    // 解析http header
    example2();
	return 0;
}
