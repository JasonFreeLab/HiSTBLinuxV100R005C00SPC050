/******************************************************************************

  Copyright (C), 2016-2026, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ssl_adp.c
  Version       : Initial Draft
  Author        : Hisilicon security software group
  Created       : 2016/04/13
  Description   :
  History       :
  1.Date        : 2016/04/13
    Author      : security team
    Modification: Created file
 
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "hi_type.h"
#include "openssl_adp.h"


#ifdef HI_ADVCA_FUNCTION_RELEASE
#define sample_printf(pszFormat...)
#else
#define sample_printf printf
#endif


typedef struct hiOPENSSL_PARAMTERS_S
{
    int          sd;
    SSL_CTX      *ctx;
    SSL          *ssl;
    void         *meth; 
    HI_BOOL      suspended; 
    HI_BOOL      isServer;    /*is Server*/
    SSL_SESSION  *session;    /* SSL session */   
} HI_OPENSSL_PARAMTERS_S;



static int OpenSSL_ServerAccept(HI_OPENSSL_PARAMTERS_S *pSslPara )
{
    int ret,width,err_code;
    fd_set read_fd;

    while (1) 
    {
        ret=SSL_accept(pSslPara->ssl);
        if(ret<=0) 
        {
            err_code =SSL_get_error(pSslPara->ssl,ret);
            if (err_code == SSL_ERROR_WANT_READ) 
            {
                sample_printf("SSL connect retry \n");
                ret=SSL_get_fd(pSslPara->ssl);
                width=ret+1;
                FD_ZERO(&read_fd);
                FD_SET(ret,&read_fd);
                if (select(width,&read_fd,NULL,NULL,NULL) < 0) 
                {
                    sample_printf("%s: Fail to select: err no %d \n", __FUNCTION__, errno);
                    return -1; 
                }
                continue;
            }
            sample_printf("SSL server accept error %d, err no %d \n", err_code, errno);
            return -1; 
        } else
            break;
    }

    sample_printf("%s: SSL server accept successful \n",__FUNCTION__);
    return 0;
}
 
static int OpenSSL_ClientConnect(HI_OPENSSL_PARAMTERS_S *pSslPara )
{
    int ret,width,err_code;
    fd_set read_fd;

    while (1) 
    {
        ret=SSL_connect(pSslPara->ssl);
        if(ret<=0) 
        {
            err_code =SSL_get_error(pSslPara->ssl,ret);
            if (err_code == SSL_ERROR_WANT_READ) 
            {
                sample_printf("SSL connect retry \n");
                ret=SSL_get_fd(pSslPara->ssl);
                width=ret+1;
                FD_ZERO(&read_fd);
                FD_SET(ret,&read_fd);
                if (select(width,&read_fd,NULL,NULL,NULL) < 0) 
                {
                    sample_printf("%s: Fail to select: err no %d \n", __FUNCTION__, errno);
                    return -1; 
                }
                continue;
            }
            sample_printf("SSL client connect error %d, errno %d \n", err_code, errno);
            return -1; 
        } 
        else
        {        
            break;
        }
    }

    sample_printf("%s: SSL client connection OK \n",__FUNCTION__);
    return 0;
 }

#define SSL_SHUTDOWN_RETRIES 300

static void ssl_shutdown( SSL *ssl, unsigned int u32Retries) 
{
    int ret,err_code;
    unsigned int u32Loop = 0;

    if ((u32Retries == 0) || (u32Retries > SSL_SHUTDOWN_RETRIES))
    {
       u32Retries = SSL_SHUTDOWN_RETRIES;
    }

    while(u32Loop < u32Retries) 
    {
        ret =SSL_shutdown(ssl);
        err_code =SSL_get_error(ssl,ret);
        if ((err_code == SSL_ERROR_WANT_WRITE) || (err_code == SSL_ERROR_WANT_READ)) 
        {
            sample_printf("Shutdown err_code %d \n", err_code);
        }

        if (ret == 0) 
        {
            u32Loop++;
            continue;
        }
        else if (ret==1) 
        {
            sample_printf("%s: Shutdown u32Retries %d \n",__FUNCTION__, u32Loop);
            return;
        }
    };

    ERR_clear_error();
    SSL_clear(ssl);
    sample_printf("%s: retries: %d \n",__FUNCTION__, u32Loop);
    return;
}

static HI_S32 ssl_resume(HI_OPENSSL_PARAMTERS_S *pSslPara)
{
     pSslPara->ssl=SSL_new(pSslPara->ctx);
     if (!pSslPara->ssl) 
     {
       sample_printf("%s: SSL handle is NULL", __FUNCTION__ );
       return HI_FAILURE;
     }
     
     /* Connect the SSL socket */
     SSL_set_fd(pSslPara->ssl, pSslPara->sd);
     SSL_set_session(pSslPara->ssl,pSslPara->session);

    if (pSslPara->isServer == HI_TRUE)
    {
        sample_printf("%s: start to resume server accept \n",__FUNCTION__);
        if (OpenSSL_ServerAccept(pSslPara))
        {
           sample_printf("%s: Fail to resume server accept \n",__FUNCTION__);
           return HI_FAILURE;
        }
    }
    else
    {
       sample_printf("%s: start to resume client connect\n",__FUNCTION__);
       if (OpenSSL_ClientConnect(pSslPara))
       {
           sample_printf("%s: Fail to resume client connect \n",__FUNCTION__);
           return HI_FAILURE;
       }
    }
    
     pSslPara->suspended = HI_FALSE;
     return HI_SUCCESS;
}


HI_S32 HI_OpenSSL_SocketRead(HI_OPENSSL_HANDLE sslHandle, char *DataBuf, int Datalen)
{    
    int ret;
    int err_code; 
    HI_OPENSSL_PARAMTERS_S *pSslPara;

    if (sslHandle == HI_NULL)
    {
      sample_printf("SSL Handle not set \n");
      return -1;
    }

    if (!DataBuf || Datalen <=0) 
    {
        sample_printf("%s: invalid parameters to read \n", __FUNCTION__);
        return -1;
    }

    pSslPara = (HI_OPENSSL_PARAMTERS_S *)sslHandle;
    
    if (pSslPara->ssl == HI_NULL) 
    {
        sample_printf("%s: Security session invalid \n", __FUNCTION__ );
        return -1;
    }   

    if (pSslPara->suspended == HI_TRUE)
    {
         if (HI_SUCCESS != ssl_resume(pSslPara))
         {
             sample_printf("%s:Fail to resume SSL\n", __FUNCTION__ );
             return -1;
         }
    }

    ret=SSL_read(pSslPara->ssl,DataBuf,Datalen);
    err_code = SSL_get_error(pSslPara->ssl,ret);
    switch(err_code)
    {
       case SSL_ERROR_NONE:
       case SSL_ERROR_WANT_READ:
       case SSL_ERROR_WANT_WRITE:
           break;
       case SSL_ERROR_ZERO_RETURN:
           sample_printf("SSL Error Zero return \n");
           goto shutdown;
       case SSL_ERROR_SYSCALL:
           sample_printf("SSL Read Error: Premature close, rc = %d \n", ret);
           return -1;
       default:
           sample_printf("SSL Read Error: %d, rc %d \n",err_code, ret);
           ret = -1;
    }
    
    if (ret < 0) 
    {
       if (errno == EINTR || errno == EAGAIN)
       {
           sample_printf("%s: Read call is interrupted or timed out \n", __FUNCTION__);
           return ret;
       }
       sample_printf("%s: read error:%d \n", __FUNCTION__, errno);
       return -1;
    }
    else if (ret == 0) 
    {
        sample_printf("%s: Reached EOF, closed the connection!\n", __FUNCTION__);
        return 0;
    }
    
    //sample_printf("%s: %d bytes is read \n", __FUNCTION__, rc);
    return ret;    

shutdown:
    sample_printf("%s: SSL session closed.\n", __FUNCTION__);
    ssl_shutdown(pSslPara->ssl,5); 
    if (pSslPara->session != NULL)
    {
        SSL_SESSION_free(pSslPara->session);
    }
    SSL_free(pSslPara->ssl);
    pSslPara->ssl=NULL;
    pSslPara->session = NULL;
    return 0;
}


HI_S32 HI_OpenSSL_SocketWrite(HI_OPENSSL_HANDLE sslHandle, HI_CHAR *DataBuf, HI_S32 DataLen)
{
    int ret;
    HI_OPENSSL_PARAMTERS_S *pSslPara;

    if (sslHandle == HI_NULL)
    {
        sample_printf("%s: invalid parameter, SSL handle \n", __FUNCTION__);
    }

    if (!DataBuf || DataLen <=0) 
    {
        sample_printf("%s: invalid parameters to write \n", __FUNCTION__);
        return -1;
    }

    pSslPara = (HI_OPENSSL_PARAMTERS_S *)sslHandle;

    if (pSslPara->suspended == HI_TRUE)
    {
         if (HI_SUCCESS != ssl_resume(pSslPara))
         {
             sample_printf("%s:Fail to resume SSL\n", __FUNCTION__ );
             return -1;
         }
    }
    
    if (pSslPara->ssl) 
    {
        ret=SSL_write(pSslPara->ssl,DataBuf, DataLen);
        switch(SSL_get_error(pSslPara->ssl,ret))
        {
            case SSL_ERROR_NONE:
            case SSL_ERROR_WANT_READ:
            case SSL_ERROR_WANT_WRITE:
                if(DataLen!=ret)
                    sample_printf("SSL write operation is incomplete! \n");
                break;
            default:
                 sample_printf("SSL write problem occurs \n");
                 return -1;
         }
    }
    else 
    {
        sample_printf("pSslPara->ssl is not initialized \n");
        return -EBUSY;
    }

    return ret;
}


static HI_S32 cert_check(SSL *ssl, HI_BOOL isServer)
{    
    long int  ret_code;
    X509 *pstPeerCert;
    char *pstr, strBuf[256];
    
    ret_code = SSL_get_verify_result(ssl);
    switch(ret_code)
    {
        case X509_V_OK:
                sample_printf("Cert is OK.\n");
                break;
        case X509_V_ERR_CERT_NOT_YET_VALID:
                sample_printf("Cert not valid. Verify date and time. x509: %ld \n", ret_code);
                return -1;
                break;
        case X509_V_ERR_CERT_HAS_EXPIRED:
                sample_printf("Cert expired. Verify cert and date. x509: %ld \n", ret_code);
                return -1;
                break;
        case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
                sample_printf("Can not get local issuer cert.  x509: %ld \n", ret_code);
                return -1;
                break;
        default:
                sample_printf("Fail to verify cert: X509_V_ERR: %ld \n", ret_code);
                return -1;
    }

    //if (isServer == HI_FALSE)
    {
        pstPeerCert=SSL_get_peer_certificate(ssl);
        if (!pstPeerCert) 
        {
            sample_printf("Can't obtain cert \n");
            goto cert_err;
        }
    
        pstr = X509_NAME_oneline(X509_get_subject_name(pstPeerCert),0,0);
        if (pstr == NULL)
        {
            sample_printf("CERT subject NULL string \n");
            goto cert_err;
        }
        sample_printf("\t CERT subject: %s \n", pstr);
        OPENSSL_free (pstr);
    
        pstr = X509_NAME_oneline(X509_get_issuer_name(pstPeerCert),0,0);
        if (pstr == NULL)
        {
            sample_printf("CERT issuer NULL string \n");
            goto cert_err;
        }
        sample_printf("\t CERT issuer: %s \n", pstr);
        OPENSSL_free(pstr);
    
        X509_NAME_get_text_by_NID(X509_get_subject_name(pstPeerCert),
          			      NID_commonName, 
                                  strBuf,
                                  256);
    
        sample_printf("\t CERT host: %s \n",strBuf);
    
        X509_free(pstPeerCert);
    }
    return HI_SUCCESS;

cert_err:
    if (pstPeerCert)
    {
        X509_free(pstPeerCert);
    }
    return HI_FAILURE;
}

HI_S32 HI_OpenSSL_SessionOpen(HI_S32 sd, HI_OPENSSL_CTX_S *pSslCtx, HI_OPENSSL_HANDLE *pSSLHandle) 
{
    HI_OPENSSL_PARAMTERS_S *pSslPara = HI_NULL;
    
    if (pSSLHandle == NULL )
    {
        sample_printf("%s: invalid paramter \n", __FUNCTION__);
        goto _ERR_EXIT_;
    }

    if (sd <= 0) 
    {
      sample_printf("%s: invalid socket, sd = %d \n", __FUNCTION__, sd);
      goto _ERR_EXIT_;
    }

    pSslPara = (HI_OPENSSL_PARAMTERS_S *)malloc(sizeof(HI_OPENSSL_PARAMTERS_S));
    if (!pSslPara)
    {
        sample_printf("%s: Failed allocation \n", __FUNCTION__);
        goto _ERR_EXIT_;
    }

    memset(pSslPara, 0x0, sizeof(sizeof(HI_OPENSSL_PARAMTERS_S)));

    /* Create our session/object */
    pSslPara->sd = sd;
    pSslPara->ctx = pSslCtx->ctx;
    
    pSslPara->suspended = HI_FALSE; 
    pSslPara->ssl=SSL_new(pSslPara->ctx);
    if (!pSslPara->ssl) 
    {
        sample_printf("%s: SSL_new failed \n", __FUNCTION__ );
        goto _ERR_EXIT_;
    }

    /* Connect the SSL socket */
    SSL_set_fd(pSslPara->ssl, sd);
    
    if (pSslCtx->bIsServer == HI_TRUE)
    {
        sample_printf("%s: start server accept \n",__FUNCTION__);
        if (OpenSSL_ServerAccept(pSslPara))
        {
           sample_printf("%s: Fail to server accept \n",__FUNCTION__);
           goto _ERR_EXIT_;
        }
    }
    else
    {
       sample_printf("%s: start client accept \n",__FUNCTION__);
       if (OpenSSL_ClientConnect(pSslPara))
       {
           sample_printf("%s: Fail client connect \n",__FUNCTION__);
           goto _ERR_EXIT_;
       }
    }

    sample_printf("%s: SSL connection successful \n",__FUNCTION__);

    /* certificate verification */
    if (cert_check(pSslPara->ssl, pSslCtx->bIsServer)) 
    {
        sample_printf("%s: Fail to verify certificate \n", __FUNCTION__);
        goto _ERR_EXIT_;
    }
    pSslPara->isServer = pSslCtx->bIsServer;
    pSslPara->session=SSL_get1_session(pSslPara->ssl);

    *pSSLHandle = (HI_OPENSSL_HANDLE)pSslPara;

    return HI_SUCCESS;

_ERR_EXIT_:
    if (pSslPara) 
    {      
        if (pSslPara->ssl)
        {
            ssl_shutdown(pSslPara->ssl, 0);
            if (pSslPara->session != NULL)
            {
                SSL_SESSION_free(pSslPara->session);
            }
            SSL_free(pSslPara->ssl);
            pSslPara->ssl = HI_NULL;
            pSslPara->session = NULL;
        }
        
        free(pSslPara);
        pSslPara = HI_NULL;
    }

    return HI_FAILURE;
}

HI_S32 HI_OpenSSL_SessionClose(HI_OPENSSL_HANDLE sslHandle)
{   
    HI_OPENSSL_PARAMTERS_S *pSslPara;
    
    if (sslHandle == HI_NULL) 
    {
        sample_printf("%s: invalid parameter, SSL handle %p \n", __FUNCTION__, sslHandle);
        return HI_FAILURE;
    }

    pSslPara = (HI_OPENSSL_PARAMTERS_S *)sslHandle;
    
    if (pSslPara->ssl != NULL)
    {
        ssl_shutdown(pSslPara->ssl, 1);
        if (pSslPara->session != NULL)
        {
           SSL_SESSION_free(pSslPara->session);
        }
        SSL_free(pSslPara->ssl);
        pSslPara->ssl = NULL;
        pSslPara->session = NULL;
    }

    free(pSslPara);
    pSslPara = NULL;

    return HI_SUCCESS;
}

HI_S32 HI_OpenSSL_SessionOpenEx(HI_S32 sd, HI_OPENSSL_HANDLE SrcSslHandle, HI_OPENSSL_HANDLE *pNewSSLHandle) 
{
    HI_OPENSSL_PARAMTERS_S *pSrcSslPara;
    HI_OPENSSL_PARAMTERS_S *pSslPara = HI_NULL;
    
    if (SrcSslHandle == NULL )
    {
        sample_printf("%s: invalid paramter \n", __FUNCTION__);
        goto _ERR_EXIT_;
    }

    if (sd <= 0) {
      sample_printf("%s: invalid socket, sd = %d\n", __FUNCTION__, sd);
      goto _ERR_EXIT_;
    }

    pSrcSslPara = (HI_OPENSSL_PARAMTERS_S *)SrcSslHandle;

    pSslPara = (HI_OPENSSL_PARAMTERS_S *)malloc(sizeof(HI_OPENSSL_PARAMTERS_S));
    if (!pSslPara){
        sample_printf("%s: Failed allocation\n", __FUNCTION__);
        goto _ERR_EXIT_;
    }

    memset(pSslPara, 0x0, sizeof(sizeof(HI_OPENSSL_PARAMTERS_S)));    

    /* Create the session/object */
    pSslPara->sd = sd;
    pSslPara->ctx = pSslPara->ctx;
    
    pSslPara->suspended = HI_FALSE; 
    pSslPara->ssl=SSL_new(pSslPara->ctx);
    if (!pSslPara->ssl) 
    {
        sample_printf("%s: create SSL_new failed\n", __FUNCTION__ );
        goto _ERR_EXIT_;
    }
    
    /* Connect the SSL socket */
    SSL_set_fd(pSslPara->ssl, sd);
    
    SSL_set_session(pSslPara->ssl, pSrcSslPara->session); 

    if (pSrcSslPara->isServer == HI_TRUE)
    {
        if (OpenSSL_ServerAccept(pSslPara))
        {
           goto _ERR_EXIT_;
        }
    }
    else
    {
       if (OpenSSL_ClientConnect(pSslPara))
       {
           goto _ERR_EXIT_;
       }
    }

    sample_printf("%s: SSL connection OK\n",__FUNCTION__);

    pSslPara->session = pSrcSslPara->session;

    *pNewSSLHandle = (HI_OPENSSL_HANDLE)pSslPara;

    return HI_SUCCESS;

_ERR_EXIT_:
    if (pSslPara) 
    {      
        if (pSslPara->ssl){
            ssl_shutdown(pSslPara->ssl, 0);
            if (pSslPara->session != NULL)
            {
               SSL_SESSION_free(pSslPara->session);
            }
            
            SSL_free(pSslPara->ssl);
            pSslPara->ssl = HI_NULL;
            pSslPara->session = NULL;
        }
        
        free(pSslPara);
        pSslPara = HI_NULL;
    }

    return HI_FAILURE;
}

HI_S32 HI_OpenSSL_SessionSuspend(HI_OPENSSL_HANDLE sslHandle)
{
    HI_OPENSSL_PARAMTERS_S *pSslPara;

    if (!sslHandle) 
    {
        sample_printf("%s:invalid SSL Handle\n", __FUNCTION__);
        return HI_FAILURE;
    }

    pSslPara = (HI_OPENSSL_PARAMTERS_S *)sslHandle;

    if (pSslPara->suspended)
    {
        sample_printf("%s: SSL session has been suspended\n", __FUNCTION__);
        return HI_SUCCESS;
    }

    pSslPara->suspended = HI_TRUE; 

    if (pSslPara->ssl != NULL)
    {
        ssl_shutdown(pSslPara->ssl, 0);
        if (pSslPara->session != NULL)
        {
           SSL_SESSION_free(pSslPara->session);
        }
        
        SSL_free(pSslPara->ssl);
        pSslPara->ssl=NULL;
        pSslPara->session = NULL;
    }   
    
    return HI_SUCCESS;
}

static int s_SslInited = 0;

static int verify_callback(int preverify_ok, X509_STORE_CTX *ctx)
{
    sample_printf("%s: the value preverify_ok=%d \n", __FUNCTION__, preverify_ok);

    if (preverify_ok == 0)
    {
       sample_printf("%s: Fail to verify certification ",__FUNCTION__);
    }

    return preverify_ok;
}

static const SSL_METHOD *getSslMethod(Hi_SSL_VERSION_TYPE_E eSSLVersion, HI_BOOL isServer)
{
    const SSL_METHOD *meth;
    
    switch (eSSLVersion)
    {
        case SSL_VERSION_SSL_V2:
        case SSL_VERSION_SSL_V3:
            sample_printf("%s: Use SSL_VERSION_SSL_V2 or SSL_VERSION_SSL_V3 \n", __FUNCTION__);
            meth = (isServer == HI_TRUE) ? SSLv23_server_method() : SSLv23_client_method();
            break;
        case SSL_VERSION_TLS_V1:
            sample_printf("%s: Use SSL_VERSION_TLS_V1 \n", __FUNCTION__);
            meth = (isServer == HI_TRUE) ? TLSv1_server_method() : TLSv1_client_method();
            break;
        case SSL_VERSION_TLS_V1_1:
            sample_printf("%s: Use SSL_VERSION_TLS_V1_1 \n", __FUNCTION__);
            meth = (isServer == HI_TRUE) ? TLSv1_1_server_method() : TLSv1_1_client_method();
            break;
        case SSL_VERSION_TLS_V1_2:
            sample_printf("%s: Use SSL_VERSION_TLS_V1_2 \n", __FUNCTION__);
            meth = (isServer == HI_TRUE) ? TLSv1_2_server_method() : TLSv1_2_client_method();
            break;    
        default:
            meth = HI_NULL;
            sample_printf("%s: Unknown SSL Version type \n", __FUNCTION__);
           break;
    }
    
    return meth;
}


HI_S32 HI_OpenSSL_Init(Hi_SSL_INIT_PARAMETERS *pInitParamers, HI_OPENSSL_CTX_S *pSslCtx)
{
    const SSL_METHOD *meth = HI_NULL;
    SSL_CTX *ctx = NULL;

    if (pInitParamers == HI_NULL || pSslCtx == HI_NULL) 
    {
        sample_printf("%s: invalid parameter, SSL pInitParamers ", __FUNCTION__);
        return HI_FAILURE;
    }
    
    if (!s_SslInited) 
    {
        SSL_library_init();
        SSL_load_error_strings();
        ERR_load_crypto_strings();  
        
        meth = getSslMethod(pInitParamers->eSSLVersion, pInitParamers->bIsServer);        
        if (!meth) 
        {
            sample_printf("%s: Fail to get ssl method\n", __FUNCTION__);
            return HI_FAILURE;
        }
        
        ctx = SSL_CTX_new(meth);
        if (HI_NULL == ctx) 
        {
            sample_printf("%s: Fail to call SSL_CTX_new\n", __FUNCTION__);
            return HI_FAILURE;
        }

        /*Set cipher list*/
        sample_printf("%s: pInitParamers->cipherList=%s\n", __FUNCTION__, pInitParamers->cipherList);
        if (SSL_CTX_set_cipher_list(ctx,pInitParamers->cipherList) <= 0) 
        {
           sample_printf("Error setting the cipher list.\n");
           SSL_CTX_free(ctx);
           return HI_FAILURE;
        }

        /*Prefer sever cipher order*/
        SSL_CTX_ctrl(ctx, SSL_CTRL_OPTIONS,SSL_OP_CIPHER_SERVER_PREFERENCE, NULL);

        /* Load the CAs we trust */
        if(pInitParamers->rootCaCertPath) 
        {
            sample_printf("%s: Launch Root CA certificate %s.....",__FUNCTION__,pInitParamers->rootCaCertPath );
            if(!(SSL_CTX_load_verify_locations(ctx, pInitParamers->rootCaCertPath, 0))) 
            {
                sample_printf("\n%s: Can't read CA list %s\n", __FUNCTION__, pInitParamers->rootCaCertPath);
                SSL_CTX_free(ctx);
                return HI_FAILURE;
            }
            sample_printf("Launch OK!!!!!\n");
        } 
        else 
        {
            sample_printf("%s: Can not find Root CA certificate.\n",__FUNCTION__ );
            SSL_CTX_free(ctx);
            return HI_FAILURE;
        }

        if (pInitParamers->bIdentityAuth) 
        {
 
           if (pInitParamers->bIsServer == HI_TRUE)
           {
              sample_printf("%s: Send a client certificate request to the client\n",__FUNCTION__ );
              /* Set SSL_VERIFY_PEER flag, the server sends a client certificate request to the client*/
              SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, verify_callback);
           }
        
            /* Load keys and certificates*/
            if (pInitParamers->certPath ) 
            {
                sample_printf("%s: Launch %s certificate %s......",__FUNCTION__, pInitParamers->bIsServer?"server":"client", pInitParamers->certPath);
                if (SSL_CTX_use_certificate_file(ctx, pInitParamers->certPath, SSL_FILETYPE_PEM) <= 0)  
                {
                    sample_printf("\n%s: Certificate file failure %s\n", __FUNCTION__, pInitParamers->certPath);
                    SSL_CTX_free(ctx);
                    return HI_FAILURE;
                }
                sample_printf("Launch OK!!!!!!\n");
            } 
            else 
            {
                sample_printf("%s: Can not find cert path\n", __FUNCTION__ );
                return HI_FAILURE;
            }

            if (pInitParamers->funPasswdCb) 
            {
                SSL_CTX_set_default_passwd_cb(ctx, pInitParamers->funPasswdCb);
            }

            if(pInitParamers->privKeyPath) 
            {
                sample_printf("%s: Launch %s private key %s......",__FUNCTION__, pInitParamers->bIsServer?"server":"client", pInitParamers->privKeyPath);
                if(!(SSL_CTX_use_PrivateKey_file(ctx, pInitParamers->privKeyPath, SSL_FILETYPE_PEM))) 
                {
                    sample_printf("\n%s: Key file failure %s\n", __FUNCTION__, pInitParamers->privKeyPath);
                    SSL_CTX_free(ctx);
                    return HI_FAILURE;
                }
                sample_printf("Launch OK!!!!!\n");
            } 
            else
            {
                 sample_printf("%s:Can not find private key path\n", __FUNCTION__ );
                 SSL_CTX_free(ctx);
                 return HI_FAILURE;
            }

            sample_printf("%s: check %s private key......",__FUNCTION__, pInitParamers->bIsServer?"server":"client");
            if (!SSL_CTX_check_private_key(ctx)) 
            {
                sample_printf("\n%s: Private key does not match the certificate public key\n", __FUNCTION__ );
                SSL_CTX_free(ctx);
                return HI_FAILURE;
            }
            sample_printf("Check OK!!!!!\n");
            
        }

#if (OPENSSL_VERSION_NUMBER < 0x00905100L)
        SSL_CTX_set_verify_depth(ctx,1);
#endif
        pSslCtx->bIsServer = pInitParamers->bIsServer;
        pSslCtx->ctx = (void *)ctx;
        pSslCtx->meth = (void *)meth;
    }
    
    return HI_SUCCESS;
}


HI_VOID HI_OpenSSL_UnInit(HI_OPENSSL_CTX_S *pSslCtx)
{    
    if (!s_SslInited) 
    {
       SSL_CTX_free(pSslCtx->ctx);
       s_SslInited = 0;
    }    

    return;
}

