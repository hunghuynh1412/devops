// C program to Implement Ping 
// run as sudo ./ping <IP address> 
  
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include <netinet/ip_icmp.h> 
#include <time.h> 
#include <fcntl.h> 
#include <signal.h> 
#include <time.h> 
#include <ifaddrs.h>
  
// Define the Packet Constants 
// ping packet size 
#define PING_PKT_S 64 
   
// Automatic port number 
#define PORT_NO 0  
  
// Automatic port number 
#define PING_SLEEP_RATE 1000000 x 
  
// Gives the timeout delay for receiving packets 
// in seconds 
#define RECV_TIMEOUT 1  
  
// Define the signal to interrupt pinging loop 
int interrupt_signal=1; 
  
  
// ping packet structure 
struct ping_pkt 
{ 
    struct icmphdr hdr; 
    char msg[PING_PKT_S-sizeof(struct icmphdr)]; 
}; 

int get_Input_cmd(char *input,char *ip_addr,int* total_host)
{
    int len = 0;
    int i=0;
    int subnet;
    while(input[i]!='/')
    {
        ip_addr[i]=input[i];
        len ++;
        i++;
		
        if(len>15)
            break;
    }
	
    if(len>15)
        return 0;
    ip_addr[len]='\0';
    i++;

    subnet=(input[i]-48)*10 +input[i+1]-48;
    int temp=0;
	*total_host=1;
    while(temp!=32-subnet)
    {
        *total_host=(*total_host)*2;
        temp++;
    }

	if(*total_host>2)
		*total_host -=2;
    return len;
    
}


char* increase_ip(char* ip_addr)
{
	in_addr_t IP=inet_addr(ip_addr);
	IP=ntohl(IP);
	IP +=1;
	IP=htonl(IP);

	struct in_addr IP_struct;
	IP_struct.s_addr=IP;

	return inet_ntoa(IP_struct);
}

// Calculating the Check Sum 
unsigned short checksum(void *b, int len) 
{    unsigned short *buf = b; 
    unsigned int sum=0; 
    unsigned short result; 
  
    for ( sum = 0; len > 1; len -= 2 ) 
        sum += *buf++; 
    if ( len == 1 ) 
        sum += *(unsigned char*)buf; 
    sum = (sum >> 16) + (sum & 0xFFFF); 
    sum += (sum >> 16); 
    result = ~sum; 
    return result; 
} 
  
// Interrupt handler 
void intHandler(int dummy) 
{ 
    interrupt_signal=0; 
} 
  
// filling up address structure 
char *ip_add_structure(char *addr_host, struct sockaddr_in *addr_con) 
{ 
    struct hostent *host_entity; 
    char *ip=(char*)malloc(NI_MAXHOST*sizeof(char)); 
    int i; 
  
    if ((host_entity = gethostbyname(addr_host)) == NULL) 
    { 
        // No ip found for hostname 
        return NULL; 
    } 
      
    //filling up address structure 
    strcpy(ip, inet_ntoa(*(struct in_addr *) host_entity->h_addr)); 
  
    (*addr_con).sin_family = host_entity->h_addrtype; 
    (*addr_con).sin_port = htons (PORT_NO); 
    (*addr_con).sin_addr.s_addr  = *(long*)host_entity->h_addr; 
  
    return ip; 
      
} 

//get IP of interfaces local machine
int check_IP_local(char *ip_addr)
{
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) 
    {
        if (!ifa->ifa_addr) 
        {
            continue;
        }
        
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            // return if ping_addr is local addr
            if(strstr(ip_addr,addressBuffer)!=NULL)
                return 1;
    } 

    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return 0;
}

// make a ping request 
int send_ping(int ping_sockfd, struct sockaddr_in *ping_addr, char *ping_ip) 
{ 
    int ttl_val=64, msg_count=0, i, addr_len, flag=1, msg_received_count=0; 
      
    struct ping_pkt pckt; 
    struct sockaddr_in r_addr; 
    struct timespec time_start, time_end, tfs, tfe; 
    long double rtt_msec=0, total_msec=0; 
    struct timeval tv_out; 
    tv_out.tv_sec = RECV_TIMEOUT; 
    tv_out.tv_usec = 0; 
  
    clock_gettime(CLOCK_MONOTONIC, &tfs); 
  
      
    // set socket options at ip to TTL and value to 64, 
    // change to what you want by setting ttl_val 
    if (setsockopt(ping_sockfd, SOL_IP, IP_TTL,  &ttl_val, sizeof(ttl_val)) != 0) 
    { 
        //printf("\nSetting socket options to TTL failed!\n"); 
        return 0; 
    } 
  
    // setting timeout of recv setting 
    setsockopt(ping_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof tv_out); 
  
    // send 5 icmp packet  
	int pingloop=0;
    while(pingloop<5 && interrupt_signal) 
    { 
        // flag is whether packet was sent or not 
        flag=1; 
       
        //filling packet 
        bzero(&pckt, sizeof(pckt)); 
          
        pckt.hdr.type = ICMP_ECHO; 
        pckt.hdr.un.echo.id = getpid(); 
          
        for ( i = 0; i < sizeof(pckt.msg)-1; i++ ) 
    		pckt.msg[i] = i+'0'; 
          
        pckt.msg[i] = 0; 
        pckt.hdr.un.echo.sequence = msg_count++; 
        pckt.hdr.checksum = checksum(&pckt, sizeof(pckt)); 
  
  
        usleep(1000000); 
  
        //send packet 
        clock_gettime(CLOCK_MONOTONIC, &time_start); 
        if ( sendto(ping_sockfd, &pckt, sizeof(pckt), 0,  (struct sockaddr*) ping_addr,  sizeof(*ping_addr)) <= 0) 
        { 
            //printf("\nPacket Sending Failed!\n"); 
            flag=0; 
        } 
  
        //receive packet 
        addr_len=sizeof(r_addr); 
  
        if (recvfrom(ping_sockfd, &pckt, sizeof(pckt), 0,  (struct sockaddr*)&r_addr, &addr_len) <= 0 && msg_count>1)  
        { 
            //printf("\nPacket receive failed!\n"); 
            pingloop++;
			
        } 
        else
        { 
            char *temp = (char*)malloc(sizeof(char)*14);
			temp= inet_ntoa(r_addr.sin_addr);
			if(strstr(temp,ping_ip)==NULL)
            {
                pingloop++;
                continue; 
			}
            clock_gettime(CLOCK_MONOTONIC, &time_end); 
              
            double timeElapsed = ((double)(time_end.tv_nsec -  time_start.tv_nsec))/1000000.0 ;
            rtt_msec = (time_end.tv_sec- time_start.tv_sec) * 1000.0 + timeElapsed; 
              
            // if packet was not sent, don't receive 
            if(flag) 
            { 
				
                if(!(pckt.hdr.type ==69 && pckt.hdr.code==0))  
                { 
                    //printf("\nError..Packet received with ICMP  type %d code %d\n",  pckt.hdr.type, pckt.hdr.code); 
					pingloop++;
				} 
                else
                { 
					char *temp_compare_IP = (char*)malloc(sizeof(char)*14);
					temp_compare_IP= inet_ntoa(r_addr.sin_addr);
					if(strstr(temp_compare_IP,ping_ip)!=NULL)
					{
                        //printf("%d bytes from %s msg_seq=%d ttl=%d  rtt = %Lf ms.\n",  PING_PKT_S, ping_ip, msg_count, ttl_val, rtt_msec); 
						msg_received_count++;
						break;
					}
                } 
            } 
        }     
    } 

	if(msg_received_count)
		return 1;
	else return 0;
} 
  

int main(int argc, char *argv[]) 
{ 
    int sockfd; 
    char *ip_addr, *reverse_hostname; 
    struct sockaddr_in addr_con; 
    int addrlen = sizeof(addr_con); 
    char net_buf[NI_MAXHOST]; 
  
    int checked_local =0;
    if(argc!=2) 
    { 
        printf("\nFormat %s <address>\n", argv[0]); 
        return 0; 
    } 
	
	int total_host=0;
	ip_addr=(char *)malloc(sizeof(char)*15);
    //Split into network and subnet mask
	get_Input_cmd(argv[1],ip_addr,&total_host);

    int temp_count=0;

    //Start loop, only stop when catch the interrupt signal or scanned all hosts in the network o Start increase IP by 1 and open socket
    while (temp_count<=total_host && interrupt_signal)
    {
        ip_addr=increase_ip(ip_addr);
        ip_addr = ip_add_structure(ip_addr, &addr_con); 
    
        printf("Scan %s:",ip_addr);
        
        if (checked_local ==0)
        {
            int ip_local= check_IP_local(ip_addr);
            if(ip_local)
            {
                printf("\tThis is IP local machine\n");
                checked_local++;    // stop checking ip local
                temp_count++;
                continue;
            }
        }
        //socket() 
        sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
        if(sockfd<0) 
        { 
            printf("\nSocket file descriptor not received!!\n"); 
            return 0; 
        } 
        else
            printf("\nSocket file descriptor %d received\n", sockfd); 
        
        signal(2, intHandler);//catching interrupt 
    
        //send pings continuously 
        int check_onl=0;
        check_onl=send_ping(sockfd, &addr_con,  ip_addr); 
        //Check if the host was pinged is online, write down IP address to 1712478.txt. o Close socket and continue the loop. 
        if(check_onl)
        {
            printf("\tONLINE\n");
            FILE *f =fopen("1712478.txt","a+");
            fputs(ip_addr,f);
            putc('\n',f);
            fclose(f);
        }
        else printf("\tOFFLINE\n");

        close(sockfd);
        temp_count++;
    }
    return 0; 
} 
