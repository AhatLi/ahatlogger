# C++ Logger Library

## 개요
윈도우, 리눅스 환경에서 사용 가능한 C++용 로그 라이브러리 입니다.
윈도우 환경에서 VisualStudio에서 빌드 하시면 되고, 리눅스 환경에서는 g++ 로 빌드 하시면 됩니다.

c++11 으로 컴파일 하셔야 하며 이 외의 다른 의존성은 없습니다.

## 로그 종류 및 설명
`AhatLogger::INFO`
일반적인 INFO 로그입니다.

`AhatLogger::ERR`
일반적인 ERROR 로그입니다.

`AhatLogger::DEBUG`
DEBUG 로그입니다.
setting 함수에서 로그 레벨을 0으로 지정했을 경우에만 로그를 남깁니다.

`AhatLogger::CUSTOM`
로그를 남길 때 로그의 종류를 사용자가 직접 String 문자열로 남길 수 있습니다.
그 외에는 INFO와 똑같이 동작합니다.

`AhatLogger::DB`
DB에 요청을 날렸을 때 쿼리의 종류와 요청시간, 응답시간 등을 로그로 남깁니다.
로그를 남기기 전에 `InDBtem`을 생성해 주어야 합니다.

`AhatLogger::DB_ERR`
DB에 요청을 날렸을 때 에러가 발생하였을 경우 쿼리의 종류와 요청시간, 응답시간 등을 로그로 남깁니다.
로그를 남기기 전에 `InDBtem`을 생성해 주어야 합니다.

`AhatLogger::DB_DEBUG`
DB에 요청을 날렸을 때 쿼리의 종류와 요청시간, 응답시간 등을 로그로 남깁니다.
로그를 남기기 전에 `InDBtem`을 생성해 주어야 합니다.
loglevel이 0 일때만 기록합니다.

`AhatLogger::DB_ERR_DEBUG`
DB에 요청을 날렸을 때 에러가 발생하였을 경우 쿼리의 종류와 요청시간, 응답시간 등을 로그로 남깁니다.
로그를 남기기 전에 `InDBtem`을 생성해 주어야 합니다.
loglevel이 0 일때만 기록합니다.

`AhatLogger::IN_REQ`
외부 요청을 날렸을 때 해당 요청에 대한 IP, PORT, URL, 요청시간과 응답시간, Body 등을 기록합니다.
로그를 남기기 전에 `InReqItem`을 생성해 주어야 합니다.

`AhatLogger::IN_REQ_ERR`
외부 요청을 날리고 해당 요청이 실패했을 경우 남깁니다. IP, PORT, URL, 요청시간과 응답시간, Body 등을 기록합니다.
로그를 남기기 전에 `InReqItem`을 생성해 주어야 합니다.

`AhatLogger::IN_REQ_DEBUG`
외부 요청을 날렸을 때 해당 요청에 대한 IP, PORT, URL, 요청시간과 응답시간, Body 등을 기록합니다.
로그를 남기기 전에 `InReqItem`을 생성해 주어야 합니다.
loglevel이 0 일때만 기록합니다.

`AhatLogger::IN_REQ_ERR_DEBUG`
외부 요청을 날리고 해당 요청이 실패했을 경우 남깁니다. IP, PORT, URL, 요청시간과 응답시간, Body 등을 기록합니다.
로그를 남기기 전에 `InReqItem`을 생성해 주어야 합니다.
loglevel이 0 일때만 기록합니다.


## 사용 방법
ahatlogger/AhatLogger/sample 경로에서 사용한 방법 확인하시면 쉽게 사용 할 수 있습니다.

```
	AhatLogger::setting("", "ahatlogtest", 0); 
	AhatLogger::start();
	
	for(int i = 0; i < 10; i++)
	{
		AhatLogger::INFO(CODE, "infolog 1 %d, 2 %f, 3 %c, 4 %s, 5 %.2f", i, 3.14, 'a', "ahatlogger", 1.23456789);
		AhatLogger::ERR(CODE, "errorlog 1 %d, 2 %f, 3 %c, 4 %s, 5 %.2f", i, 3.14, 'a', "ahatlogger", 1.23456789);
		
		//   loglevel 0 print debug log
		AhatLogger::DEBUG(CODE, "debuglog 1 %d, 2 %f, 3 %c, 4 %s, 5 %.2f", i, 3.14, 'a', "ahatlogger", 1.23456789);
	}
	
	AhatLogger::stop();
```

## 컴파일 방법
### 1. VisualStudio
ahatlogger/AhatLogger.sln 파일을 열어 lib 파일을 생성

ahatlogger/AhatLogger/sample/sample.sln 파일을 열어 샘플 바이너리 파일 생성 및 테스트

이후 sample.sln 에서 링킹된 방법과 동일한 방법으로 사용하시면 됩니다.



### 2. Linux
ahatlogger/AhatLogger 경로로 이동

`make`
명령어 실행하여 정적 라이브러리 파일 생성 (c++11 을 지원하는 g++ 컴파일러가 설치되어 있어야 합니다.)

ahatlogger/AhatLogger/sample 경로로 이동

`make`
명령어 실행하여 테스트 바이너리 파일 생성

이후 sample 경로의 Makefile 참고하여 같은 방법으로 사용하시면 됩니다.

