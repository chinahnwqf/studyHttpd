#ifndef _HTTP_H_
#define _HTTP_H_
#include "fastcgi.h"
#include "common.h"
#include "rio.h"
#include "list.h"
#include "threadpool.h"
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<pwd.h>
#include<unistd.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<pthread.h>
#include<netinet/in.h>

#define		PORT	8899
#define		MAX_QUE_CONN_NM	20
#define		MAX_BUF_SIZE	8096
#define		MAX_RECV_SIZE	4000

/* http请求信息结构体, 这里只记录几个关键信息, 其他忽略 */
typedef struct http_request{
	char method[10];		//请求方式
	char path[256];			//文件路径
	char filename[256];		//请求文件名
	char version[10];		//HTTP协议版本
	char url[256];			//请求url
	char param[256];		//请求参数
	char contype[256];		//消息类型
	char conlength[16];		//消息长度
	char ext[10];			//文件后缀
	char *content;			//body
	int sockfd;				//socket描述符
	int epfd;				//事件
	struct list_head list;	
}http_request;

int init_server();
int set_non_blocking(int sockfd);
int init_http_request(http_request *, int, int);
int parse_request(const int, char *, http_request *);
int get_line(const int, char *, int);
void *handle_request(void *);
void send_http_responce(int, const int, const char *, const http_request *);
void get_http_mime(char *, char *);
void exec_static(int, http_request *, int);
void exec_php(int, http_request *);
void exec_dir(int, char *, http_request *);
int conn_fastcgi();
int send_fastcgi(int ,int, http_request *);
void recv_fastcgi(int ,int, http_request *);
char *get_http_Val(const char* str, const char *substr);
void send_client(char *, int, char *, int, int, http_request *);
#endif
