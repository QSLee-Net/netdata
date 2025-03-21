// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef NETDATA_STREAM_HANDSHAKE_H
#define NETDATA_STREAM_HANDSHAKE_H

#define HTTP_HEADER_SIZE 8192

#define STREAMING_PROTOCOL_VERSION "1.1"
#define START_STREAMING_PROMPT_V1 "Hit me baby, push them over..."
#define START_STREAMING_PROMPT_V2 "Hit me baby, push them over and bring the host labels..."
#define START_STREAMING_PROMPT_VN "Hit me baby, push them over with the version="

#define START_STREAMING_ERROR_SAME_LOCALHOST "Don't hit me baby, you are trying to stream my localhost back"
#define START_STREAMING_ERROR_ALREADY_STREAMING "This GUID is already streaming to this server"
#define START_STREAMING_ERROR_NOT_PERMITTED "You are not permitted to access this. Check the logs for more info."
#define START_STREAMING_ERROR_BUSY_TRY_LATER "The server is too busy now to accept this request. Try later."
#define START_STREAMING_ERROR_INTERNAL_ERROR "The server encountered an internal error. Try later."
#define START_STREAMING_ERROR_INITIALIZATION "The server is initializing. Try later."

typedef enum {
    // negotiated version values
    // IMPORTANT: maintain compatibility across netdata version - do not change these
    STREAM_HANDSHAKE_OK_V3                              = 3, // v3+
    STREAM_HANDSHAKE_OK_V2                              = 2, // v2
    STREAM_HANDSHAKE_OK_V1                              = 1, // v1
    STREAM_HANDSHAKE_NEVER                              = 0, // never tried to connect
    STREAM_HANDSHAKE_CONNECT_HANDSHAKE_FAILED           = -1, // sent by parent - DO NOT CHANGE
    STREAM_HANDSHAKE_PARENT_IS_LOCALHOST                = -2, // sent by parent - DO NOT CHANGE
    STREAM_HANDSHAKE_PARENT_NODE_ALREADY_CONNECTED      = -3, // sent by parent - DO NOT CHANGE
    STREAM_HANDSHAKE_PARENT_DENIED_ACCESS               = -4, // sent by parent - DO NOT CHANGE
    STREAM_HANDSHAKE_CONNECT_SEND_TIMEOUT               = -5, // generated by child
    STREAM_HANDSHAKE_CONNECT_RECEIVE_TIMEOUT            = -6, // generated by child
    STREAM_HANDSHAKE_CONNECT_INVALID_CERTIFICATE        = -7, // generated by child
    STREAM_HANDSHAKE_CONNECT_SSL_ERROR                  = -8, // generated by child
    STREAM_HANDSHAKE_CONNECTION_FAILED                  = -9, // generated by child
    STREAM_HANDSHAKE_PARENT_BUSY_TRY_LATER              = -10, // sent by parent - DO NOT CHANGE
    STREAM_HANDSHAKE_PARENT_INTERNAL_ERROR              = -11, // sent by parent - DO NOT CHANGE
    STREAM_HANDSHAKE_PARENT_IS_INITIALIZING             = -12, // sent by parent - DO NOT CHANGE

    // --- internal handshake reasons ---

    // receiver-only codes
    STREAM_HANDSHAKE_RCV_DISCONNECT_PARSER_FAILED       = -13,
    STREAM_HANDSHAKE_RCV_DISCONNECT_STALE_RECEIVER      = -14,
    STREAM_HANDSHAKE_RCV_DECOMPRESSION_FAILED           = -15,

    // sender-only codes
    STREAM_HANDSHAKE_SND_DISCONNECT_HOST_CLEANUP        = -16,
    STREAM_HANDSHAKE_SND_DISCONNECT_COMPRESSION_FAILED  = -17,
    STREAM_HANDSHAKE_SND_DISCONNECT_HTTP_UPGRADE_FAILED = -18,
    STREAM_HANDSHAKE_SND_DISCONNECT_RECEIVER_LEFT       = -19, // used only in pulse

    // receiver and sender codes
    STREAM_HANDSHAKE_DISCONNECT_SIGNALED_TO_STOP        = -20, // a fallback when (s|rpt)->exit.reason is not set
    STREAM_HANDSHAKE_DISCONNECT_SHUTDOWN                = -21,
    STREAM_HANDSHAKE_DISCONNECT_SOCKET_READ_FAILED      = -22,
    STREAM_HANDSHAKE_DISCONNECT_SOCKET_WRITE_FAILED     = -23,
    STREAM_HANDSHAKE_DISCONNECT_SOCKET_ERROR            = -24,
    STREAM_HANDSHAKE_DISCONNECT_TIMEOUT                 = -25,
    STREAM_HANDSHAKE_DISCONNECT_SOCKET_CLOSED_BY_REMOTE = -26,
    STREAM_HANDSHAKE_DISCONNECT_BUFFER_OVERFLOW         = -27,
    STREAM_HANDSHAKE_DISCONNECT_REPLICATION_STALLED     = -28,

    // sender (stream parents - SP) failures to connect
    STREAM_HANDSHAKE_SP_PREPARING                       = -29,
    STREAM_HANDSHAKE_SP_NO_HOST_IN_DESTINATION          = -30,
    STREAM_HANDSHAKE_SP_CONNECT_TIMEOUT                 = -31,
    STREAM_HANDSHAKE_SP_CONNECTION_REFUSED              = -32,
    STREAM_HANDSHAKE_SP_CANT_RESOLVE_HOSTNAME           = -33,
    STREAM_HANDSHAKE_SP_CONNECTING                      = -34,
    STREAM_HANDSHAKE_SP_CONNECTED                       = -35,
    STREAM_HANDSHAKE_SP_NO_STREAM_INFO                  = -36,
    STREAM_HANDSHAKE_SP_NO_DESTINATION                  = -37,

    // terminator - keep this positive, bigger than all negative values
    STREAM_HANDSHAKE_NEGATIVE_MAX                       = 38,
} STREAM_HANDSHAKE;

const char *stream_handshake_error_to_string(STREAM_HANDSHAKE reason);
int stream_handshake_error_to_response_code(STREAM_HANDSHAKE reason);

#endif //NETDATA_STREAM_HANDSHAKE_H
