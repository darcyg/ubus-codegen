static void _ubus_%METHOD%_completed(struct ubus_request *req, int type, struct blob_attr *msg){
	struct ubus_%INTERFACE% *self = (struct ubus_%INTERFACE%*)req->priv; 
	if(!self) return; 
	if(self->on_%METHOD%_completed){
		self->on_%METHOD%_completed(msg); 
	}
}

int %METHOD_PREFIX%_%METHOD%(struct ubus_%INTERFACE% *self, struct blob_attr *args, struct blob_buf *result){
	int ret = ubus_invoke(self->ctx, self->object_id, "%METHOD_PREFIX%.%METHOD%", args, _ubus_%METHOD%_completed, self, 1000); 
	return ret; 
}

static __attribute__((unused)) int %METHOD_PREFIX%_%METHOD%_cb(struct ubus_context *ctx, struct ubus_object *obj,
          struct ubus_request_data *req, const char *method,
          struct blob_attr *msg){   
	struct blob_buf bb; 

    blob_buf_init(&bb, 0, 0);           
    
    ubus_send_reply(ctx, req, blob_buf_head(&bb));
	blob_buf_free(&bb); 
    return 0;
}   


