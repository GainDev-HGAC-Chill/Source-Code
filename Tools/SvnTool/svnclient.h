#pragma once
#include <tchar.h>
#include "svnclient_inc.h"

// svn client 
struct svnclient_t
{
	// svn context
	svn_client_ctx_t *ctx;
	// root pool
	apr_pool_t *root_pool;
	// pool
	apr_pool_t *pool;
	// 버젼 정보
	const svn_version_t *version;	
	// error 
	svn_error_t* err;
};

/// @brief svnclient 을 초기화 한다.
/// @param sc 초기화된 svnclient_t 
/// @return 0 실패, 1 성공 (실패에 sc가 할당되어 잇고 err 이 존재하면 내용을 확인해볼수 있음)
int svnclient_initialize(svnclient_t** sc);

/// @brief svnclient 을 끝낸다.
/// @param sc 생성되어진 svnclient_t 의 포인터
void svnclient_terminate(svnclient_t* sc);

/// @brief error string 을 구한다.
/// @param err 에러
std::string svnclient_get_error_string(svn_error_t * err);

/// @brief 저장소의 root 주소를 구한다.
/// @brief sc svnclient
/// @brief 저장소 주소
const char* svnclient_get_respository_root( svnclient_t* sc, const char* path_or_url );

/// @brief 저장소에 있는 파일의 리스트를 본다.
/// @param sc svnclient
/// @param repos_path_or_url 저장소 주소
void svnclient_ls( svnclient_t* sc, const char* repos_path_or_url );

/// @brief checkout 을 수행한다.
/// @param sc svnclient 
/// @param repos_path_or_url 저장소의 주소
/// @param dest_path_or_url 목적지 주소
void svnclient_checkout( svnclient_t* sc, const char *repos_path_or_url, const char* dest_path_or_url);

/// @brief 파일을 추가한다.
/// @param sc svnclient 
/// @param dest_path_or_url 목적지 주소
/// @param recursive 재귀 수행할것인가
void svnclient_add(svnclient_t* sc, const char *dest_path, BOOL recursive);

/// @brief 파일을 복구한다.
/// @param sc svnclient 
/// @param dest_path_or_url 목적지 주소
/// @param recursive 재귀 수행할것인가
void svnclient_revert(svnclient_t* sc, const char* dest_path, BOOL recursive);

/// @brief 파일을 Commit 한다.
/// @param sc svnclient 
/// @param dest_path_or_url 목적지 주소
/// @param recursive 재귀 수행할것인가
/// @param message 메세지
void svnclient_commit(svnclient_t* sc, const char* dest_path, BOOL recursive, const char* message );

/// @brief 파일을 삭제한다.
/// @param sc svnclient 
/// @param dest_path 목적지 주소
/// @param message 메세지
void svnclient_remove(svnclient_t* sc, const char* dest_path, const char* message );

/// @brief 파일을 Update 한다.
/// @param sc svnclient 
/// @param dest_path 목적지 주소
/// @param message 메세지
void svnclient_update(svnclient_t* sc, const char *dest_path, bool recursive);

/// @brief 파일을 copy 한다.
/// @param sc svnclient 
/// @param src_path 복사할 대상
/// @param dest_path 복사할 목적지
/// @param message 메세지
void svnclient_copy(svnclient_t* sc, const char *src_path, const char *dest_path, const char *message);

/// @brief 파일을 move 한다.
/// @param sc svnclient
/// @param src_path 이동 대상
/// @param dest_path 이동 목적지
/// @param message 메세지
void svnclient_move(svnclient_t* sc, const char *src_path, const char *dest_path,  const char *message);

/// @brief dir를 만든다.
/// @param sc svnclient 
/// @param src_path 만들곳의 위치
/// @param message 메세지
void svnclient_mkdir(svnclient_t* sc, const char *src_path, const char *message);




//로그 메세지를 출력
void my_svnclient_log(svnclient_t* pkSc, char const* const pcDest_Path);

//위 함수서, 로그 메세지를 출력 하는데 필요한 함수
svn_error_t* my_svnclient_log_message_receiver(void* pBaton,
											   apr_hash_t* pkChanged_Paths,
											   svn_revnum_t liRevision,
											   char const* pcAuthor,
											   char const* pcDate, /* use svn_time_from_cstring() if need apr_time_t */
											   char const* pcMessage,
											   apr_pool_t* pkPool);