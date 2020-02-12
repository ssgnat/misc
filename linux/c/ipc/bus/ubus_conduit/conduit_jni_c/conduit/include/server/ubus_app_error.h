#ifndef _ubus_app_error_h_
#define _ubus_app_error_h_

enum
{
	UBUS_APP_ERROR_BASE=-100,
	
	UBUS_APP_ERROR_INTERNAL_NULLPOINTER,
	UBUS_APP_ERROR_PARSEREQ,
	UBUS_APP_ERROR_SUB_NOTFOUND,
	UBUS_APP_ERROR_INTERNAL_PROCESSCMD,
	UBUS_APP_ERROR_INTERNAL_FD,
	UBUS_APP_ERROR_INTERNAL_SOCKET,
	UBUS_APP_ERROR_INTERNAL_OVERRANGE,
	UBUS_APP_ERROR_IEMPTY_NPUT_METHODS,
	UBUS_APP_ERROR_EXISTED,
	UBUS_APP_ERROR_NOIDLE,

	UBUS_APP_OK=0,
};

#endif
