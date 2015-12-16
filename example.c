#include <blobpack/blobpack.h>
#include <libubus2/libubus2.h>

#include "definition.c"

int main(int argc, char **argv){
	struct ubus_netifd_interface net; 
	netifd_interface_init(&net); 
	netifd_interface_join(&net, "ubus.sock"); 
	netifd_interface_publish(&net, "/netifd/test/interface"); 

	while(true){
		netifd_interface_process_events(&net); 
	}
	return 0; 
}
