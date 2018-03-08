#include <stdio.h>      
#include <sys/un.h>      
#include <sys/socket.h>      
#include <string.h>  
#include <unistd.h>  
      
int main(void)    
{      
    int i_fd = 0;      
    struct sockaddr_un addr;      
    char psz_clientpath[32] = "/tmp/client_unixsocket_file";      
    char psz_serverpath[32] = "/tmp/server_unixsocket_file";      
    int i_addr_len = 0;     
    char psz_wbuf[32] = "i am client.";  
    char psz_rbuf[32] = {0};   
    int i_readlen = 0;  
    
    if ( ( i_fd = socket( AF_UNIX, SOCK_DGRAM, 0 ) ) < 0 )    
    {      
        perror("socket");  
        return -1;  
    }  
      
    memset( &addr, 0, sizeof( addr ) );      
    addr.sun_family = AF_UNIX;  
    strncpy( addr.sun_path, psz_clientpath, sizeof( addr.sun_path ) - 1 );      
    unlink( psz_clientpath );  
    i_addr_len = strlen( addr.sun_path ) + sizeof( addr.sun_family );  
    if ( bind( i_fd, ( struct sockaddr * )&addr, i_addr_len ) < 0 )    
    {      
        perror("bind");  
        return -1;  
    }  
      
    
    //fill socket adress structure with server's address      
    memset( &addr, 0, sizeof( addr ) );      
    addr.sun_family = AF_UNIX;  
    strncpy( addr.sun_path, psz_serverpath, sizeof( addr.sun_path ) - 1 );      
  
    i_addr_len = strlen( addr.sun_path ) + sizeof( addr.sun_family );   
    if ( sendto( i_fd, psz_wbuf, strlen( psz_wbuf ) + 1, 0,  
        ( struct sockaddr * )&addr, i_addr_len ) < 0 )    
    {  
        perror( "write" );      
        return -1;  
    }      
    
    if ( ( i_readlen = recvfrom( i_fd, psz_rbuf, sizeof( psz_rbuf ) - 1, 0,  
        ( struct sockaddr * )&addr, ( socklen_t * )&i_addr_len ) ) < 0 )    
    {  
        perror("write");      
        return -1;      
    }  
    psz_rbuf[i_readlen] = '\0';  
    printf( "receive msg:%s\n", psz_rbuf );      
    unlink( psz_clientpath );  
    return -1;  
}    