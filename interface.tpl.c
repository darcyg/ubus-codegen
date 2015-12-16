#include <blobpack/blobpack.h>

void %METHOD_PREFIX%_init(struct ubus_%METHOD_PREFIX% *self){
	memset(self, 0, sizeof(*self)); 
	blob_buf_init(&self->buf, 0, 0); 
	self->ctx = ubus_new(); 
}

int %METHOD_PREFIX%_join(struct ubus_%METHOD_PREFIX% *self, const char *url){
	if(ubus_connect(self->ctx, url) != 0){
		return -1; 
	}
	return 0; 
}

int %METHOD_PREFIX%_attach(struct ubus_%METHOD_PREFIX% *self, const char *object){
	if(ubus_lookup_id(self->ctx, object, &self->object_id) != 0){
		return -1; 
	}
	return 0; 
}

int %METHOD_PREFIX%_publish(struct ubus_%METHOD_PREFIX% *self, const char *path){
	 static struct ubus_method object_methods[] = {
		%METHOD_DEFS%
    };

    static struct ubus_object_type object_type = 
		UBUS_OBJECT_TYPE("%INTERFACE%-type", object_methods);

    struct ubus_object main_object = {
        .name = strdup(path),
        .type = &object_type,
        .methods = object_methods,
        .n_methods = ARRAY_SIZE(object_methods),
    };

    return ubus_add_object(self->ctx, &main_object);
}

void %METHOD_PREFIX%_process_events(struct ubus_%METHOD_PREFIX% *self){
	ubus_handle_event(self->ctx); 
}

