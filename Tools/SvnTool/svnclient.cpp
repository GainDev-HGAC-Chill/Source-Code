#include <iostream>
#include <windows.h>
#include <string>
#include "svnclient.h"

struct log_msg_baton3
{
	const char *message;			/* the message. */
	const char *message_encoding;	/* the locale/encoding of the message. */
	const char *base_dir;			/* the base directory for an external edit. UTF-8! */
	const char *tmpfile_left;		/* the tmpfile left by an external edit. UTF-8! */
	apr_pool_t *pool;				/* a pool. */
};

//// 거북이 SVN - CTSVNPathList 참조(참고)
//apr_array_header_t * CTSVNPathList::MakePathArray (apr_pool_t *pool) const
//{
//	apr_array_header_t *targets = apr_array_make (pool, GetCount(), sizeof(const char *));
//
//	for(int nItem = 0; nItem < GetCount(); nItem++)
//	{
//		const char * target = m_paths[nItem].GetSVNApiPath(pool);
//		(*((const char **) apr_array_push (targets))) = target;
//	}
//
//	return targets;
//}

apr_array_header_t * MakePathArray(const char *pPath, apr_pool_t *pool)
{
	apr_array_header_t *targets = apr_array_make(pool, 1 , sizeof(const char *));

	const char * target = apr_pstrdup (pool, pPath);
	(*((const char **) apr_array_push (targets))) = target;

	return targets;
}


// 거북이 SVN - svn.h 에서 참조(참고)
svn_error_t* svn_cl__get_log_message (const char **log_msg,
									  const char **tmp_file,
									  apr_array_header_t * /*commit_items*/,
									  void *baton, 
									  apr_pool_t * pool)
{
	log_msg_baton3 *lmb = (log_msg_baton3 *) baton;
	*tmp_file = NULL;
	if (lmb->message)
	{
		*log_msg = apr_pstrdup (pool, lmb->message);
	}

	return SVN_NO_ERROR;
}

// 거북이 SVN - svn.h 에서 참고
void notify( void *baton, const svn_wc_notify_t *notify,
			apr_pool_t *pool)
{
	switch (notify->action)
	{ 

	case svn_wc_notify_add:
		printf("\nAdded Files: %s", notify->path);
		break;
	case svn_wc_notify_commit_added:
		printf("\nCommitting an addition : %s", notify->path);
		break;
	case svn_wc_notify_delete:
		printf("\nDeleting a versioned path : %s", notify->path);
		break;
	case svn_wc_notify_commit_deleted:
		printf("\nCommitting a deletion : %s", notify->path);
		break;
	case svn_wc_notify_update_delete:
		printf("\nGot a delete in an update : %s", notify->path);
		break;
	case svn_wc_notify_update_add:
		printf("\nGot an add in an update : %s", notify->path);
		break;
	case svn_wc_notify_copy:
		printf("\nCopying a versioned path: %s", notify->path);
		break;
	case svn_wc_notify_revert:
		printf("\nReverting a modified : %s", notify->path);
		break;
	}  
}

// 거북이 SVN - svn.h 에서 참고
svn_error_t* cancel(void *baton)
{
	/*SVN * svn = (SVN *)baton;
	if ((svn->Cancel())||((svn->m_pProgressDlg)&&(svn->m_pProgressDlg->HasUserCancelled())))
	{
		CString temp;
		temp.LoadString(IDS_SVN_USERCANCELLED);
		return svn_error_create(SVN_ERR_CANCELLED, NULL, CUnicodeUtils::GetUTF8(temp));
	}*/
	return SVN_NO_ERROR;
}

// 거북이 SVN - svn.h 에서 참고 
void * logMessage (const char * message, apr_pool_t *pool)
{ 
	log_msg_baton3* baton = (log_msg_baton3 *) apr_palloc (pool, sizeof (*baton));
	if( baton == NULL )
		return NULL;

	baton->message = apr_pstrdup(pool, message);
	baton->base_dir = "";

	baton->message_encoding = NULL;
	baton->tmpfile_left = NULL;
	baton->pool = pool;

	return baton;
}

// 거북이 SVN - svnprompt 에서 참고(참조)
svn_error_t* userprompt(svn_auth_cred_username_t **cred, void *baton, const char * realm, svn_boolean_t may_save, apr_pool_t *pool)
{
	svn_auth_cred_username_t *ret = (svn_auth_cred_username_t *)apr_pcalloc (pool, sizeof (*ret));
	if( ret )
	{
		ret->username = "";
		ret->may_save = 0;//may_save;
		*cred = ret;
	}
	return SVN_NO_ERROR;
	/*SVNPrompt * svn = (SVNPrompt *)baton;
	svn_auth_cred_username_t *ret = (svn_auth_cred_username_t *)apr_pcalloc (pool, sizeof (*ret));
	CString username;
	CString temp;
	temp.LoadString(IDS_AUTH_USERNAME);
	if (svn->Prompt(username, FALSE, temp, may_save))
	{
		ret->username = apr_pstrdup(pool, CUnicodeUtils::GetUTF8(username));
		ret->may_save = may_save;
		*cred = ret;
		Creds c;
		c.username = username;
		tsvn_creds[realm] = c;
	}
	else
		*cred = NULL;
	if (svn->m_app)
		svn->m_app->DoWaitCursor(0);*/
}

// 거북이 SVN - svnprompt 에서 참고(참조)
svn_error_t* simpleprompt(svn_auth_cred_simple_t **cred, void *baton, const char * realm, const char *username, svn_boolean_t may_save, apr_pool_t *pool)
{
	svn_auth_cred_simple_t *ret = (svn_auth_cred_simple_t *)apr_pcalloc (pool, sizeof (*ret));
	if( ret )
	{
		ret->username = "";
		ret->password = "";
		ret->may_save = 0;//may_save;
		*cred = ret;
	}

	return SVN_NO_ERROR;
	/*SVNPrompt * svn = (SVNPrompt *)baton;
	svn_auth_cred_simple_t *ret = (svn_auth_cred_simple_t *)apr_pcalloc (pool, sizeof (*ret));
	CString UserName = CUnicodeUtils::GetUnicode(username);
	CString PassWord;
	CString Realm = CUnicodeUtils::GetUnicode(realm);
	if (svn->SimplePrompt(UserName, PassWord, Realm, may_save))
	{
		ret->username = apr_pstrdup(pool, CUnicodeUtils::GetUTF8(UserName));
		ret->password = apr_pstrdup(pool, CUnicodeUtils::GetUTF8(PassWord));
		ret->may_save = may_save;
		*cred = ret;
		Creds c;
		c.username = ret->username;
		c.password = ret->password;
		tsvn_creds[realm] = c;
	}
	else
		*cred = NULL;
	if (svn->m_app)
		svn->m_app->DoWaitCursor(0);
	return SVN_NO_ERROR;*/
}

// 거북이 SVN - svnprompt 에서 참고(참조)
svn_error_t* sslserverprompt(svn_auth_cred_ssl_server_trust_t **cred_p, void *baton, 
							 const char *realm, apr_uint32_t failures, 
							 const svn_auth_ssl_server_cert_info_t *cert_info, 
							 svn_boolean_t may_save, apr_pool_t *pool)
{  
	if (failures & SVN_AUTH_SSL_UNKNOWNCA)
	{    

	}
	if (failures & SVN_AUTH_SSL_CNMISMATCH)
	{

	}
	if (failures & SVN_AUTH_SSL_NOTYETVALID)
	{

	}
	if (failures & SVN_AUTH_SSL_EXPIRED)
	{

	}
	if (may_save)
	{  
		*cred_p = (svn_auth_cred_ssl_server_trust_t*)apr_pcalloc (pool, sizeof (**cred_p));
		(*cred_p)->may_save = TRUE;
		(*cred_p)->accepted_failures = failures;    

	}
	else
	{
		*cred_p = NULL;
	}

	return SVN_NO_ERROR;
}

// 거북이 SVN - svnprompt 에서 참고(참조)
svn_error_t* sslclientprompt(svn_auth_cred_ssl_client_cert_t **cred, void *baton, const char * realm, 
							 svn_boolean_t /*may_save*/, apr_pool_t *pool)
{    
	/* Build and return the credentials. */
	*cred = (svn_auth_cred_ssl_client_cert_t*)apr_pcalloc (pool, sizeof (**cred));
	(*cred)->cert_file = apr_pstrdup(pool, "");
	(*cred)->may_save = false;

	return SVN_NO_ERROR;
}

// 거북이 SVN - svnprompt 에서 참고(참조)
// svnprompt::init 에서 참고
svn_error_t* sslpwprompt(svn_auth_cred_ssl_client_cert_pw_t **cred, void *baton, const char * realm, svn_boolean_t may_save, apr_pool_t *pool)
{  
	svn_auth_cred_ssl_client_cert_pw_t *ret = (svn_auth_cred_ssl_client_cert_pw_t *)apr_pcalloc (pool, sizeof (*ret));

	ret->password = apr_pstrdup(pool, "");
	ret->may_save = may_save;
	*cred = ret;

	return SVN_NO_ERROR;
}

// 거북이 SVN - svnprompt 에서 참고(참조)
// svnprompt::init 에서 참고
void setup_authentication(apr_pool_t *pool, svn_client_ctx_t* ctx)
{
	// set up authentication
	svn_auth_baton_t *			auth_baton;
	svn_auth_provider_object_t *provider;

	/* The whole list of registered providers */
	apr_array_header_t *providers = apr_array_make (pool, 11, sizeof (svn_auth_provider_object_t *));

	/* The main disk-caching auth providers, for both
	'username/password' creds and 'username' creds.  */
	svn_client_get_windows_simple_provider (&provider, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;

	svn_client_get_simple_provider (&provider, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;

	svn_client_get_username_provider (&provider, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;

	/* The server-cert, client-cert, and client-cert-password providers. */
	svn_client_get_ssl_server_trust_file_provider (&provider, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;

	svn_client_get_ssl_client_cert_file_provider (&provider, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;

	svn_client_get_ssl_client_cert_pw_file_provider (&provider, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;

	/* Two prompting providers, one for username/password, one for
	just username. */
	svn_client_get_simple_prompt_provider (&provider, (svn_auth_simple_prompt_func_t)simpleprompt, NULL, 2, /* retry limit */ pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;
	svn_client_get_username_prompt_provider (&provider, (svn_auth_username_prompt_func_t)userprompt, NULL, 2, /* retry limit */ pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;

	///* Three prompting providers for server-certs, client-certs,
	//and client-cert-passphrases.  */
	svn_client_get_ssl_server_trust_prompt_provider (&provider, sslserverprompt, NULL, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;
	svn_client_get_ssl_client_cert_prompt_provider (&provider, sslclientprompt, NULL, 2, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;
	svn_client_get_ssl_client_cert_pw_prompt_provider (&provider, sslpwprompt, NULL, 2, pool);
	APR_ARRAY_PUSH (providers, svn_auth_provider_object_t *) = provider;

	/* Build an authentication baton to give to libsvn_client. */
	svn_auth_open (&auth_baton, providers, pool);
	ctx->auth_baton = auth_baton;
}

int svnclient_initialize(svnclient_t** sc)
{
	//----------------------------------------------------------------------------
	// Win32 Socket 을 초기화 한다.
	//----------------------------------------------------------------------------

	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);  

	//----------------------------------------------------------------------------
	// svnclient_t 할당하기
	//----------------------------------------------------------------------------

	(*sc) = (svnclient_t*)malloc( sizeof svnclient_t );
	if( *sc == NULL )
		goto e_0;

	memset( *sc, 0x0, sizeof svnclient_t );
	// 버젼 정보 읽기
	(*sc)->version = svn_client_version();

	//----------------------------------------------------------------------------
	// 초기화 ( pool / ctx )
	//----------------------------------------------------------------------------

	// apr pool 을 초기화
	apr_pool_initialize();
	// 메모리 풀 초기화 
	(*sc)->root_pool = svn_pool_create(NULL);
	if( (*sc)->root_pool == NULL )
		goto e_0;
	// ctx 초기화
	(*sc)->err = svn_client_create_context(&(*sc)->ctx, (*sc)->root_pool);//클라이언트 컨텍스트 초기화
	if ( (*sc)->err )
		goto e_0;
	// config 파일 존재 여부 확인하기
	(*sc)->err = svn_config_ensure(NULL, (*sc)->root_pool);
	if ( (*sc)->err )
		goto e_0;
	// config 파일에서 설정 정보 읽음
	(*sc)->err = svn_config_get_config (&((*sc)->ctx->config), "", (*sc)->root_pool);
	// sub pool 을 생성함
	(*sc)->pool = svn_pool_create( (*sc)->root_pool );
	if ( (*sc)->pool == NULL )
		goto e_0;
	//----------------------------------------------------------------------------
    // 인증시 필요한 정보 셋팅
	//----------------------------------------------------------------------------
	setup_authentication((*sc)->root_pool, (*sc)->ctx);

	(*sc)->ctx->log_msg_func = svn_cl__get_log_message;
	(*sc)->ctx->log_msg_baton = logMessage("", (*sc)->pool );
	(*sc)->ctx->notify_func2 = notify;
	(*sc)->ctx->notify_baton2 = NULL;
	(*sc)->ctx->notify_func = NULL;
	(*sc)->ctx->notify_baton = NULL;
	(*sc)->ctx->cancel_func = cancel;
	(*sc)->ctx->cancel_baton = NULL;

	return 1;

e_0:
	svnclient_terminate( *sc );

	return 0;
}


void svnclient_terminate(svnclient_t* sc)
{
	// null 인지 확인한다.
	if( sc == NULL )
		return ;
	
	// pool 이 생성되어 있으면 없앤다.
	if( sc->pool )
	{
		svn_pool_destroy( sc->pool );
		sc->pool = NULL;
	}

	// root pool을 지운다.
	if( sc->root_pool )
	{
		svn_pool_destroy( sc->root_pool );
		sc->root_pool = NULL;
	}

	// pool을 해제한다.
	apr_pool_terminate();

	// 메모리 sc 를 해제한다.
	free( sc );

	// 윈속을 날림
	WSACleanup();
}
 
const char* svnclient_get_respository_root( svnclient_t* sc, const char* path_or_url )
{
	const char *root;
	const char *new_root;
	apr_pool_t *pool;
	svn_ra_session_t *ras;

	// pool 를 생성한다.
	pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		goto e_0;
	// 정리된 new Path 를 구함
	new_root = svn_path_canonicalize(path_or_url, pool);
	if( new_root == NULL )
		goto e_0;
	// open 'ra session'
	sc->err = svn_client_open_ra_session(&ras, new_root, sc->ctx, pool);
	if( sc->err )
		goto e_0;
	// root 를 구한다.
	sc->err = svn_ra_get_repos_root2(ras, &root, pool);
	if( sc->err )
		goto e_0;
	// pool 를 날린다.
	svn_pool_destroy(pool);

	return root;
e_0:
	if( pool )
		svn_pool_destroy( pool );
	return NULL;

}

void svnclient_ls( svnclient_t* sc, const char* repos_path_or_url )
{
	apr_pool_t* pool; 
	svn_opt_revision_t rev;
	apr_hash_t* hash;
	apr_hash_index_t *hi;
	svn_dirent_t* val;
	const char* key;

	// pool 를 만듦
	pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		goto e_0;
	// ls 에서 사용할 hash 를 만듦
	hash = apr_hash_make(pool);
	if( hash == NULL )
		goto e_0;

	// 리비젼 정보 ( Head )
	rev.kind = svn_opt_revision_head;
	rev.value.date = 0;
	rev.value.number = 0;

	// err 을 초기화 한다.
	svn_error_clear( sc->err );	

	// LS 호출
	sc->err = svn_client_ls2(&hash, repos_path_or_url, &rev, &rev, true, sc->ctx, pool);
	if( sc->err )
		goto e_0;

	// 탐색
	for (hi = apr_hash_first(sc->pool, hash); hi; hi = apr_hash_next(hi)) {
		apr_hash_this(hi, (const void**)&key, NULL, (void**)&val);
		printf("%s\n", key);
	}

	// pool 를 제거
	svn_pool_destroy(pool);
	return;

e_0:
	if( pool )
	{
		svn_pool_destroy(pool);
	}
}


void svnclient_checkout( svnclient_t* sc, const char *repos_path_or_url, const char* dest_path_or_url)
{
	apr_pool_t* pool;
	svn_opt_revision_t revision;

	pool = svn_pool_create( sc->pool );
	if( pool == NULL )
		return ; 
	
	// err 을 초기화 한다.
	svn_error_clear( sc->err );	

	revision.kind = svn_opt_revision_head;
	revision.value.date = 0;
	revision.value.number = 0;

	sc->err = svn_client_checkout2(	NULL,			// we don't need the resulting revision
									repos_path_or_url,
									dest_path_or_url,
									&revision,
									&revision,
									TRUE,
									FALSE,
									sc->ctx,
									pool );
	svn_pool_destroy( pool );
 
	return;
}

void svnclient_add(svnclient_t* sc, const char *dest_path, BOOL recursive)
{
	apr_pool_t *pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		return ;

	// err 을 초기화 한다.
	svn_error_clear( sc->err );	

	// 파일은 한번에 하나
	sc->err = svn_client_add3(dest_path, recursive, false, false, sc->ctx, pool);

	svn_pool_destroy(pool);
}

void svnclient_revert(svnclient_t* sc, const char* dest_path, BOOL recursive)
{
	apr_pool_t *pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		return ;

	// err 을 초기화 한다.
	svn_error_clear( sc->err );	

	sc->err = svn_client_revert(MakePathArray(dest_path, pool), recursive, sc->ctx, pool);

	svn_pool_destroy(pool);
}

void svnclient_commit(svnclient_t* sc, const char* dest_path, BOOL recursive, const char* message )
{
	svn_commit_info_t *commit_info;
	apr_pool_t *pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		return ;

	svn_error_clear(sc->err);
	commit_info = svn_create_commit_info(pool);
	if( commit_info == NULL )
		return ;
	sc->ctx->log_msg_baton2 = logMessage(message, pool);
	if( sc->ctx->log_msg_baton2 == NULL )
		return ;
	sc->err = svn_client_commit3 (&commit_info, MakePathArray(dest_path, pool), recursive, false, sc->ctx, pool);

	svn_pool_destroy(pool);

}

void svnclient_remove(svnclient_t* sc, const char* dest_path, const char* message )
{
	svn_commit_info_t *commit_info;
	apr_pool_t *pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		return ;

	svn_error_clear(sc->err);
	commit_info = svn_create_commit_info(pool);
	if( commit_info == NULL )
		return ;
	sc->ctx->log_msg_baton2 = logMessage(message, pool);
	if( sc->ctx->log_msg_baton2 == NULL )
		return ;
	sc->err = svn_client_delete2(&commit_info, MakePathArray(dest_path, pool), true, sc->ctx, pool);

	svn_pool_destroy(pool);

}

void svnclient_update(svnclient_t* sc, const char *dest_path, bool recursive)
{	
	svn_opt_revision_t rev;

	apr_pool_t *pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		return ;

	svn_error_clear(sc->err);

	rev.kind = svn_opt_revision_head;
	rev.value.date = 0;
	rev.value.number = 0;

	sc->err = svn_client_update2(NULL, MakePathArray(dest_path, pool), &rev, recursive, false, sc->ctx, pool);

	svn_pool_destroy(pool);
}

void svnclient_copy(svnclient_t* sc, const char *src_path, const char *dest_path, const char *message)
{
	svn_commit_info_t *commit_info;
	svn_opt_revision_t rev;

	apr_pool_t *pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		return ;

	svn_error_clear(sc->err);

	commit_info = svn_create_commit_info(pool);  
	if( commit_info == NULL )
		return ;

	rev.kind = svn_opt_revision_head;
	rev.value.date = 0;
	rev.value.number = 0;

	sc->ctx->log_msg_baton2 = logMessage(message, pool);
	if( sc->ctx->log_msg_baton2 == NULL )
		return ;

	sc->err = svn_client_copy2(&commit_info, src_path, &rev, dest_path, sc->ctx, pool);

	svn_pool_destroy(pool);
}

void svnclient_move(svnclient_t* sc, const char *src_path, const char *dest_path,  const char *message)
{
	svn_commit_info_t *commit_info;
	svn_opt_revision_t rev;

	apr_pool_t *pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		return ;

	svn_error_clear(sc->err);

	commit_info = svn_create_commit_info(pool);  
	if( commit_info == NULL )
		return ;

	rev.kind = svn_opt_revision_head;
	rev.value.date = 0;
	rev.value.number = 0;

	sc->ctx->log_msg_baton2 = logMessage(message, pool);
	if( sc->ctx->log_msg_baton2 == NULL )
		return ;

	sc->err = svn_client_move3(&commit_info, src_path, dest_path, false, sc->ctx, pool);

	svn_pool_destroy(pool);
}

void svnclient_mkdir(svnclient_t* sc, const char *src_path, const char *message)
{
	svn_commit_info_t *commit_info;
	apr_pool_t *pool = svn_pool_create(sc->pool);
	if( pool == NULL )
		return ;

	svn_error_clear(sc->err);
	commit_info = svn_create_commit_info(pool);
	if( commit_info == NULL )
		return ;

	sc->ctx->log_msg_baton2 = logMessage(message, pool);
	if( sc->ctx->log_msg_baton2 == NULL )
		return ;

	sc->err = svn_client_mkdir2 (&commit_info, MakePathArray(src_path, pool), sc->ctx, pool);

	svn_pool_destroy(pool);
}

std::string svnclient_get_error_string(svn_error_t * Err)
{
	std::string msg;
	std::string temp;
	char errbuf[256];

	if (Err != NULL)
	{
		svn_error_t * ErrPtr = Err;
		if (ErrPtr->message)
			msg = ErrPtr->message;
		else
		{
			/* Is this a Subversion-specific error code? */
			if ((ErrPtr->apr_err > APR_OS_START_USEERR)
				&& (ErrPtr->apr_err <= APR_OS_START_CANONERR))
				msg = svn_strerror (ErrPtr->apr_err, errbuf, sizeof (errbuf));
			/* Otherwise, this must be an APR error code. */
			else
			{
				svn_error_t *temp_err = NULL;
				const char * err_string = NULL;
				temp_err = svn_utf_cstring_to_utf8(&err_string, apr_strerror (ErrPtr->apr_err, errbuf, sizeof (errbuf)-1), ErrPtr->pool);
				if (temp_err)
				{
					svn_error_clear (temp_err);
					msg = _T("Can't recode error string from APR");
				}
				else
				{
					msg = /*CUnicodeUtils::GetUnicode*/(err_string);
				}
			}
		}
		while (ErrPtr->child)
		{
			ErrPtr = ErrPtr->child;
			msg += _T("\n");
			if (ErrPtr->message)
				temp = /*CUnicodeUtils::GetUnicode*/(ErrPtr->message);
			else
			{
				/* Is this a Subversion-specific error code? */
				if ((ErrPtr->apr_err > APR_OS_START_USEERR)
					&& (ErrPtr->apr_err <= APR_OS_START_CANONERR))
					temp = svn_strerror (ErrPtr->apr_err, errbuf, sizeof (errbuf));
				/* Otherwise, this must be an APR error code. */
				else
				{
					svn_error_t *temp_err = NULL;
					const char * err_string = NULL;
					temp_err = svn_utf_cstring_to_utf8(&err_string, apr_strerror (ErrPtr->apr_err, errbuf, sizeof (errbuf)-1), ErrPtr->pool);
					if (temp_err)
					{
						svn_error_clear (temp_err);
						temp = _T("Can't recode error string from APR");
					}
					else
					{
						temp = /*CUnicodeUtils::GetUnicode*/(err_string);
					}
				}
			}
			msg += temp;
		}
		temp.clear();
		// add some hint text for some of the error messages
		switch (Err->apr_err)
		{
		case SVN_ERR_BAD_FILENAME:
		case SVN_ERR_BAD_URL:
			temp = "please check the path or URL you've entered.";
			// please check the path or URL you've entered.
			//temp.LoadString(IDS_SVNERR_CHECKPATHORURL);
			break;
		case SVN_ERR_WC_LOCKED:
		case SVN_ERR_WC_NOT_LOCKED:
			// do a "cleanup"
			//temp.LoadString(IDS_SVNERR_RUNCLEANUP);
			temp = "run cleanup.";
			break;
		case SVN_ERR_WC_NOT_UP_TO_DATE:
		case SVN_ERR_FS_TXN_OUT_OF_DATE:
			// do an update first
			//temp.LoadString(IDS_SVNERR_UPDATEFIRST);
			temp = "do an update first";
			break;
		case SVN_ERR_WC_CORRUPT:
		case SVN_ERR_WC_CORRUPT_TEXT_BASE:
			// do a "cleanup". If that doesn't work you need to do a fresh checkout.
			//temp.LoadString(IDS_SVNERR_CLEANUPORFRESHCHECKOUT);
			temp = "do a 'cleanup'.";
			break;
		default:
			break;
		}
		if ((Err->apr_err == SVN_ERR_FS_PATH_NOT_LOCKED)||
			(Err->apr_err == SVN_ERR_FS_NO_SUCH_LOCK)||
			(Err->apr_err == SVN_ERR_RA_NOT_LOCKED))
		{
			// the lock has already been broken from another working copy
			//temp.LoadString(IDS_SVNERR_UNLOCKFAILEDNOLOCK);
			temp = "the lock has already been broken from another working copy";
		}
		else if (SVN_ERR_IS_UNLOCK_ERROR(Err))
		{
			// if you want to break the lock, use the "check for modifications" dialog
			// temp.LoadString(IDS_SVNERR_UNLOCKFAILED);
			temp = "if you want to break the lock, use the \"check for modifications\" dialog";
		}
		if (!temp.empty())
		{
			msg += _T("\n");
			msg += temp;
		}
		return msg;
	}
	return _T("");
}

void my_svnclient_log(svnclient_t* pkSc, char const* const pcDest_Path)
{
	apr_pool_t *pool = svn_pool_create(pkSc->pool);
	if( pool == NULL )
		return;

	svn_error_clear(pkSc->err);

	//enum svn_opt_revision_kind 정보는 아래 사이트를 참조
	//(http://svn.collab.net/svn-doxygen/svn__opt_8h.html#a4)
	
	svn_opt_revision_t revStart;
	revStart.kind = svn_opt_revision_head;		//svn_opt_revision_head는 최근 저장소
	revStart.value.date = 0;
	revStart.value.number = 0;

	svn_opt_revision_t revEnd;
	revEnd.kind = svn_opt_revision_previous ;	//svn_opt_previous는 이전 저장소
	revEnd.value.date = 0;
	revEnd.value.number = 0;
		
	pkSc->err = svn_client_log2(MakePathArray(pcDest_Path, pool), 
				  &revStart, 
				  &revEnd, 
				  0,								  //리미트 - 의미를 모르겠음
				  true,								  //바뀐패스를 discover		-정보를 모르겠음
				  true,								  //strict한 노드히스토리	-정보를 모르겠음
				  my_svnclient_log_message_receiver,  //메세지 리시버 함수 (인자값이 함수 포인터임)
				  NULL,								  //바톤 - 의미를 모르겠음
				  pkSc->ctx, 
				  pool);

	svn_pool_destroy(pool);
}

//Log 출력 함수, svn_client_log2의 인자값으로 이 함수가 들어감
svn_error_t* my_svnclient_log_message_receiver(void* pBaton,
											   apr_hash_t* pkChanged_Paths,
											   svn_revnum_t liRevision,
											   char const* pcAuthor,
											   char const* pcDate,
											   char const* pcMessage,
											   apr_pool_t* pkPool)
{
	printf("revision: %ld\n",liRevision);
	printf("author  : %s\n",pcAuthor);
	printf("date    : %s\n",pcDate);

	//commit하면서 추가한 메세지를 출력하나 깨져서 나옴
	printf("message : %s\n",pcMessage);

	//모두 ????? 형태로 나온다
//	wprintf(L"message : %s\n",message);

	printf("end line ----------------------------------------\n\n");
	return SVN_NO_ERROR;
}