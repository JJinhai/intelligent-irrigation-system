#include "Http.h"
#include "TcpClient.h"
#include "Logger.h"


#include <regex>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <unordered_map>
// 用于test
#include <iostream>

using namespace std;
void Http::addHeader(const string& head)
{
    if (!head.empty())
    {
        header_ += head;
        header_ += "\r\n";
    // Console.WriteLine("我在这里 head!= null" + header_);
    }
    // 自动加个结尾
    else
    {
        header_ += "\r\n";
    // Console.WriteLine("我在这里 head == null" + header_);
    }
}

void Http::Header(bool flag)
{
    // 判断要发送的头部 true 表示200 false 表示404
    if(flag == true)
    { 
        header_ = "HTTP/1.1 200 OK\r\n";
    }
    else
    {
        header_ = "HTTP/1.1 404 NOTFOUND\r\nContent-Length:0\r\n\r\n";
    }
}

void Http::processHead()
{
    string ContentType = "Content-Type:";
    if (fileType_ == "html")
    {
        ContentType += "text/html";
    }
    else if(fileType_ == "js")
    {
        ContentType += "application/x-javascript";
    }
    else if(fileType_ == "css")
    {
        ContentType += "text/css";
    }
    else if(fileType_=="jpg" || fileType_== "png")
    {
        ContentType += "image/" + fileType_;
    }
    else if (fileType_== "zip" || fileType_ == "tar")
    {
        ContentType += "application/" + fileType_;
    }
    addHeader(ContentType);

    // 代完善，要打开文件 filePath_是请求文件的路径
    fileSize_= fileStat_.st_size;
    string ContentLength = "Content-Length:" + to_string(fileSize_);
    addHeader(ContentLength);
    // 最后加了一个结尾
    addHeader("");
    // Console.WriteLine("process fileContent_:" + );
}

void Http::addFilePath(const string& requestFile)
{
    filePath_ += requestFile;
}

void Http::analyseFileType(const string& requestFile)
{
    for (int i = 0; i < requestFile.size(); ++i)
    {
        if (requestFile[i] == '.')
        {
            // 获取请求文件以什么结尾的
            fileType_ = requestFile.substr(i + 1);
        }
    }
}

bool Http::fileIsExist(){
    fileFd_ = ::open(filePath_.c_str(),O_CLOEXEC | O_RDWR);
    if (fileFd_ < 0)
    {   // 说明为找到请求的文件
        return false;
    }
    return true;
}

bool Http::analyseFile(const string& request)
{
    // 调用header的
    // 在[]的^是以什么什么开头，放在[]里面的是非的意思
    string pattern = "^([A-Z]+) ([A-Za-z./1-9-]*)";
    regex reg(pattern);
    smatch mas;
    regex_search(request,mas,reg);
    // 因为下标0是代表匹配的整体
    if(mas.size() < 3){
        LOG_INFO("不是正常请求");
        // 啥都不是直接返回false
        return false;
    }
    string requestMode = mas[1];
    if(requestMode == "POST"){
        isPostMode_ = true;
        cout << "POST请求！！！！！" << endl;
    }
    // 请求的具体文件
    string requestFile = mas[2];
    // 先获取请求的文件

    bool flag;
    if (requestFile == "/")
    { // 如果是/的话就给默认值
        filePath_.clear(); // 先清个零
        filePath_ = path_;
        filePath_ += "/run.html";
        // 文件的类型也要给人家加上
        fileType_ = "html"; 
    }
    else
    {
        filePath_.clear(); // 先清个零
        filePath_ = path_;
        addFilePath(requestFile);
        // 利用open函数
        
    }
    flag = fileIsExist();
    // 未找到文件的话
    if(!flag){
        LOG_INFO("未找到客户要的文件");
        cout << filePath_ << endl;
        return false;
    }
    ::fstat(fileFd_,&fileStat_);
    // 如果文件不存在的话也就不需要解析类型
    analyseFileType(requestFile);
    return true;
}


void Http::SendFile(int clientFd,bool isRequestOk)
{
    long len = 0;
    // 头部一定是有的。
    while(len < header_.size()){
        len += ::send(clientFd,header_.c_str(),header_.size(),0);
        cout << "len header" << header_ <<endl;
    }
    // 发完了头，在发请求文件的信息。如果是404这里是没有的
    if (isRequestOk == true)
    {
        len = 0;
	int num = 0;
       	int tmpLen = 0;// 连续好几次没变的话就加一个num
	 while (len < fileSize_)
        {
	    // 发送的文件个数已经写入在len当中了 
            ::sendfile(clientFd,fileFd_,(off_t*)&len,fileStat_.st_size- len);
            cout << "len sendfile" <<"len:" << len << "fileSize" << fileSize_ <<endl;
            if(len <= 0 ){
		break;
	    }
	    if(tmpLen == len){
		++num;
		if(num > 10){
			break;
		}
	    }
	    tmpLen = len;
	}

    }

}

void Http::ReadCallback(TcpClient* t){
    cout << "ReadCallback" << endl;
    int  sockFd = t->getFd();
    char buff[1024];
    int r = ::recv(sockFd,buff,sizeof(buff),0);
    if (r == 0)
    {
        t->CloseCallback();
        return;
    }
    buff[r] = '\0';
    string str = buff;
    cout << str << endl;
    // 未找到文件直接回应404.
    bool flag = analyseFile(str);
    Header(flag);
    if(!flag){
        SendFile(sockFd,false);
       // t->CloseCallback();
        return ;
    }
    // 这个修改头文件的，先调用这个
    processHead();
    //这是文件找到了发送的
    SendFile(sockFd,true);

    if(isPostMode_){
        int fd = ::open("./postLog/message.txt",O_RDWR);
        if(fd < 0){
            LOG_ERROR("未找到文件");
            
        }
        else{
            // 文件偏移到末尾
            ::lseek(fd,0,SEEK_END);
            ::write(fd,str.c_str(),str.size());
            close(fd);
        }
        isPostMode_ = true;
    }

    // 关闭文件套接字
    close(fileFd_);
    // 发完就关闭连接,主要是为了多去几个线程还能跑的快一些
    //t->CloseCallback();
}

