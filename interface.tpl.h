#pragma once

struct ubus_%METHOD_PREFIX% {
	struct ubus_context *ctx; 
	uint32_t object_id; 
	struct blob_buf buf; 
	%CALLBACKS%
}; 

void %METHOD_PREFIX%_init(struct ubus_%METHOD_PREFIX% *self); 
int %METHOD_PREFIX%_join(struct ubus_%METHOD_PREFIX% *self, const char *url); 
int %METHOD_PREFIX%_attach(struct ubus_%METHOD_PREFIX% *self, const char *object); 
int %METHOD_PREFIX%_publish(struct ubus_%METHOD_PREFIX% *self, const char *path); 
void %METHOD_PREFIX%_process_events(struct ubus_%METHOD_PREFIX% *self); 
