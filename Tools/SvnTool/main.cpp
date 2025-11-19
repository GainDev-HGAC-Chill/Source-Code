#include <iostream>
#include "svnclient.h"


//svnclient.h, svnclient.cpp, svnclient_inc.h는 
//윤지훈 팀장님이 알려주신 블로그에서 얻어왔으며
//(http://blog.naver.com/laster40/57591156) 
//my_svnclient_log, my_svnclient_log_message_receiver만 직접 작성하였음.

//로그를 가져올 디렉토리는 이미 한번 svn을 사용한적이 있어야 하고
//로그를 출력하기는 하나, 한글이 깨져서 나온다.

void main()
{
	svnclient_t* pkSc;		
	if( !svnclient_initialize(&pkSc) ) 	
	{		
		std::cout<<"Failed to Init"<<std::endl;
		return;
	}
	
	//svn의 로그를 가져올 디렉토리 위치(직접 지정해주어야 함)
	char const* const pcDest_Path = "D:\\Work\\Svn_Test";

	my_svnclient_log(pkSc,pcDest_Path);
	svnclient_terminate(pkSc);
}