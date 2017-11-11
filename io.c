
#include <stdio.h>


// 所有error 错误
// connet 
// send
// sys
// 
enum io_error
{

}




// 任务模式进行逻辑处理
#define ES_CONNECTING 
// #define ES_RECONNECT 
#define ES_ERROE 



// io 数据发送buffer
#define EC_IO_SEND_BUFF_SIZE (2048)
uint8 *es_send_buffer;

// io 数据接收buffer
#define EC_IO_RECV_BUFF_SIZE ()
uint8 *ec_io_recv_buffer

static struct espconn *io_espconn;

static ip_addr io_ip;


// 内存需要进行 - 动态分配
// MARK: 逻辑
// io 部分需要进行单独封装
// 网络 send_buffer 
// 



/**
 * 数据接受回调
 */
void 
io_recv_cb()
{

}

/**
 * 数据发送成功回调
 */
void 
io_send_cb(void *arg)
{

}

/**
 * 
 */
void 
io_send() {

}

void 
io_reconnet_cb() {

}

// 创建成功后 没有正常关闭 表示此系统需要进行重连
void 
io_close(void)
{

}

struct espconn *
io_connet() {
    
    return NULL;
}

int 
io_send(struct espconn *, uint8 pdata, int len)
{

	// TODO: 发送数据 返回error 系统通知
}

void 
init(void) {

}

void 
de_init(void) {

}



int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}