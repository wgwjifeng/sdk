#ifndef _aio_tcp_transport_h_
#define _aio_tcp_transport_h_

#include "aio-socket.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct aio_tcp_transport_t aio_tcp_transport_t;

struct aio_tcp_transport_handler_t
{
	/// aio transport destroy
	void (*ondestroy)(void* param);

	/// @param[in] param user-defined pointer return by onconnected
	void (*onrecv)(void* param, const void* data, size_t bytes);

	/// @param[in] param user-defined pointer return by onconnected
	void (*onsend)(void* param, int code, size_t bytes);
};

/// Create tcp transport
/// @param[in] socket transport socket, hold and close by internal
/// @param[in] handler user-defined callback functions
/// @param[in] param user-defined callback parameter
/// @return NULL-error(user must close socket), other-ok
aio_tcp_transport_t* aio_tcp_transport_create(socket_t socket, struct aio_tcp_transport_handler_t *handler, void* param);
aio_tcp_transport_t* aio_tcp_transport_create2(aio_socket_t aio, struct aio_tcp_transport_handler_t *handler, void* param);

/// start recv, call once only
int aio_tcp_transport_start(aio_tcp_transport_t* transport);
/// cancel tcp transport recv/send
int aio_tcp_transport_stop(aio_tcp_transport_t* transport);

/// Send data to peer
/// @param[in] data use data send to peer, MUST BE VALID until onsend
/// @param[in] bytes data length in byte
/// @return 0-ok, other-error
int aio_tcp_transport_send(aio_tcp_transport_t* transport, const void* data, size_t bytes);

/// Send data to peer
/// @param[in] vec data vector, MUST BE VALID until onsend
/// @param[in] n vector count
/// @return 0-ok, other-error
int aio_tcp_transport_sendv(aio_tcp_transport_t* transport, socket_bufvec_t *vec, int n);

/// @param[in] timeout recv/send timeout(millisecond), default 4min
void aio_tcp_transport_set_timeout(aio_tcp_transport_t* transport, int timeout);
int aio_tcp_transport_get_timeout(aio_tcp_transport_t* transport);

#ifdef __cplusplus
}
#endif
#endif /* !_aio_tcp_transport_h_ */
