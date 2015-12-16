#!/usr/bin/nodejs

var JSON = require("JSON"); 
var fs = require("fs"); 

var def = JSON.parse(fs.readFileSync("definition.json")); 

var tpl_method = String(fs.readFileSync("method.tpl.c")); 
var tpl_method_def = String(fs.readFileSync("method-def.tpl.c")); 
var tpl_interface = String(fs.readFileSync("interface.tpl.c")); 
var tpl_interface_h = String(fs.readFileSync("interface.tpl.h")); 
var tpl_callback = String(fs.readFileSync("callback.tpl.h")).replace(/\n/g, ""); 

var method_defs = []; 

Object.keys(def).map(function(ifname){
	var methods = def[ifname]["methods"]; 
	var events = def[ifname]["events"]; 
	var code_methods = []; 
	var callbacks = []; 
	var method_prefix = ifname.replace(/\./g, "_"); 
	if(methods) {
		Object.keys(methods).map(function(mname){
			var text = tpl_method_def.replace(/%METHOD_PREFIX%/g, method_prefix) 
				.replace(/%INTERFACE%/g, ifname)
				.replace(/%METHOD%/g, mname); 
			method_defs.push(text); 
			callbacks.push(tpl_callback
				.replace(/%INTERFACE%/g, ifname)
				.replace(/%METHOD_PREFIX%/g, method_prefix)
				.replace(/%METHOD%/g, mname)); 
			code_methods.push(tpl_method
				.replace(/%METHOD_PREFIX%/g, method_prefix)
				.replace(/%INTERFACE%/g, ifname.replace(/\./g, "_"))
				.replace(/%METHOD%/g, mname)); 
		}); 
	}
	
	var code_c = code_methods.join("\n") + tpl_interface.replace(/%METHOD_PREFIX%/g, method_prefix)
		.replace(/%METHOD_DEFS%/g, method_defs.join(","))
		.replace(/%INTERFACE%/g, ifname);  
	var code_h = tpl_interface_h.replace(/%METHOD_PREFIX%/g, method_prefix)
		.replace(/%CALLBACKS%/g, callbacks.join(";\n")+";")
		.replace(/%INTERFACE%/g, ifname); 
	
	console.log(code_h); 
	console.log("/// C implementation"); 
	console.log(code_c); 
}); 

