/*
 * Wine server protocol definitions
 *
 * This file is automatically generated; DO NO EDIT!
 * Edit server/protocol.def instead and re-run tools/make_requests
 */

#ifndef __WINE_WINE_SERVER_PROTOCOL_H
#define __WINE_WINE_SERVER_PROTOCOL_H

#include <stdlib.h>
#include <time.h>
#include "winbase.h"

struct request_header
{
    int            req;
    unsigned short var_offset;
    unsigned short var_size;
    unsigned int   error;
};

struct reply_header
{
    unsigned int   error;
    unsigned short var_offset;
    unsigned short var_size;
};



struct request_max_size
{
    int pad[16];
};


#define REQUEST_MAX_VAR_SIZE  1024

typedef int handle_t;
typedef unsigned int user_handle_t;

#define FIRST_USER_HANDLE 0x0020
#define LAST_USER_HANDLE  0xffef



struct debug_event_exception
{
    EXCEPTION_RECORD record;
    int              first;
};
struct debug_event_create_thread
{
    handle_t    handle;
    void       *teb;
    void       *start;
};
struct debug_event_create_process
{
    handle_t    file;
    handle_t    process;
    handle_t    thread;
    void       *base;
    int         dbg_offset;
    int         dbg_size;
    void       *teb;
    void       *start;
    void       *name;
    int         unicode;
};
struct debug_event_exit
{
    int         exit_code;
};
struct debug_event_load_dll
{
    handle_t    handle;
    void       *base;
    int         dbg_offset;
    int         dbg_size;
    void       *name;
    int         unicode;
};
struct debug_event_unload_dll
{
    void       *base;
};
struct debug_event_output_string
{
    void       *string;
    int         unicode;
    int         length;
};
struct debug_event_rip_info
{
    int         error;
    int         type;
};
union debug_event_data
{
    struct debug_event_exception      exception;
    struct debug_event_create_thread  create_thread;
    struct debug_event_create_process create_process;
    struct debug_event_exit           exit;
    struct debug_event_load_dll       load_dll;
    struct debug_event_unload_dll     unload_dll;
    struct debug_event_output_string  output_string;
    struct debug_event_rip_info       rip_info;
};


typedef struct
{
    int                      code;
    union debug_event_data   info;
} debug_event_t;


struct send_fd
{
    void  *tid;
    int    fd;
};


struct wake_up_reply
{
    void *cookie;
    int   signaled;
};





struct new_process_request
{
    struct request_header __header;
    int          inherit_all;
    int          create_flags;
    int          start_flags;
    handle_t     exe_file;
    handle_t     hstdin;
    handle_t     hstdout;
    handle_t     hstderr;
    int          cmd_show;
    /* VARARG(filename,string); */
    handle_t     info;
};



struct get_new_process_info_request
{
    struct request_header __header;
    handle_t     info;
    int          pinherit;
    int          tinherit;
    void*        pid;
    handle_t     phandle;
    void*        tid;
    handle_t     thandle;
    handle_t     event;
};



struct new_thread_request
{
    struct request_header __header;
    int          suspend;
    int          inherit;
    int          request_fd;
    void*        tid;
    handle_t     handle;
};



struct boot_done_request
{
    struct request_header __header;
    int          debug_level;
};



struct init_process_request
{
    struct request_header __header;
    void*        ldt_copy;
    int          ppid;
    int          create_flags;
    int          start_flags;
    unsigned int server_start;
    handle_t     exe_file;
    handle_t     hstdin;
    handle_t     hstdout;
    handle_t     hstderr;
    int          cmd_show;
    /* VARARG(filename,string); */
};



struct init_process_done_request
{
    struct request_header __header;
    void*        module;
    void*        entry;
    void*        name;
    handle_t     exe_file;
    int          gui;
    int          debugged;
};



struct init_thread_request
{
    struct request_header __header;
    int          unix_pid;
    void*        teb;
    void*        entry;
    int          reply_fd;
    int          wait_fd;
    void*        pid;
    void*        tid;
    int          boot;
    int          version;
};



struct set_thread_buffer_request
{
    struct request_header __header;
    int          fd;
    unsigned int offset;
    unsigned int size;
};



struct terminate_process_request
{
    struct request_header __header;
    handle_t     handle;
    int          exit_code;
    int          self;
};



struct terminate_thread_request
{
    struct request_header __header;
    handle_t     handle;
    int          exit_code;
    int          self;
    int          last;
};



struct get_process_info_request
{
    struct request_header __header;
    handle_t     handle;
    void*        pid;
    int          debugged;
    int          exit_code;
    int          priority;
    int          process_affinity;
    int          system_affinity;
};



struct set_process_info_request
{
    struct request_header __header;
    handle_t     handle;
    int          mask;
    int          priority;
    int          affinity;
};
#define SET_PROCESS_INFO_PRIORITY 0x01
#define SET_PROCESS_INFO_AFFINITY 0x02



struct get_thread_info_request
{
    struct request_header __header;
    handle_t     handle;
    void*        tid_in;
    void*        tid;
    void*        teb;
    int          exit_code;
    int          priority;
};



struct set_thread_info_request
{
    struct request_header __header;
    handle_t     handle;
    int          mask;
    int          priority;
    int          affinity;
};
#define SET_THREAD_INFO_PRIORITY 0x01
#define SET_THREAD_INFO_AFFINITY 0x02



struct suspend_thread_request
{
    struct request_header __header;
    handle_t     handle;
    int          count;
};



struct resume_thread_request
{
    struct request_header __header;
    handle_t     handle;
    int          count;
};



struct load_dll_request
{
    struct request_header __header;
    handle_t     handle;
    void*        base;
    int          dbg_offset;
    int          dbg_size;
    void*        name;
};



struct unload_dll_request
{
    struct request_header __header;
    void*        base;
};



struct queue_apc_request
{
    struct request_header __header;
    handle_t     handle;
    int          user;
    void*        func;
    void*        param;
};



struct get_apc_request
{
    struct request_header __header;
    int          alertable;
    void*        func;
    int          type;
    /* VARARG(args,ptrs); */
};
enum apc_type { APC_NONE, APC_USER, APC_TIMER, APC_ASYNC };



struct close_handle_request
{
    struct request_header __header;
    handle_t     handle;
    int          fd;
};



struct set_handle_info_request
{
    struct request_header __header;
    handle_t     handle;
    int          flags;
    int          mask;
    int          fd;
    int          old_flags;
    int          cur_fd;
};



struct dup_handle_request
{
    struct request_header __header;
    handle_t     src_process;
    handle_t     src_handle;
    handle_t     dst_process;
    unsigned int access;
    int          inherit;
    int          options;
    handle_t     handle;
    int          fd;
};
#define DUP_HANDLE_CLOSE_SOURCE  DUPLICATE_CLOSE_SOURCE
#define DUP_HANDLE_SAME_ACCESS   DUPLICATE_SAME_ACCESS
#define DUP_HANDLE_MAKE_GLOBAL   0x80000000



struct open_process_request
{
    struct request_header __header;
    void*        pid;
    unsigned int access;
    int          inherit;
    handle_t     handle;
};



struct select_request
{
    struct request_header __header;
    int          flags;
    void*        cookie;
    int          sec;
    int          usec;
    /* VARARG(handles,handles); */
};
#define SELECT_ALL           1
#define SELECT_ALERTABLE     2
#define SELECT_INTERRUPTIBLE 4
#define SELECT_TIMEOUT       8



struct create_event_request
{
    struct request_header __header;
    int          manual_reset;
    int          initial_state;
    int          inherit;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};


struct event_op_request
{
    struct request_header __header;
    handle_t      handle;
    int           op;
};
enum event_op { PULSE_EVENT, SET_EVENT, RESET_EVENT };



struct open_event_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};



struct create_mutex_request
{
    struct request_header __header;
    int          owned;
    int          inherit;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};



struct release_mutex_request
{
    struct request_header __header;
    handle_t     handle;
};



struct open_mutex_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};



struct create_semaphore_request
{
    struct request_header __header;
    unsigned int initial;
    unsigned int max;
    int          inherit;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};



struct release_semaphore_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int count;
    unsigned int prev_count;
};



struct open_semaphore_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};



struct create_file_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    unsigned int sharing;
    int          create;
    unsigned int attrs;
    /* VARARG(filename,string); */
    handle_t     handle;
};



struct alloc_file_handle_request
{
    struct request_header __header;
    unsigned int access;
    int          fd;
    handle_t     handle;
};



struct get_handle_fd_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int access;
    int          fd;
    int          type;
};
#define FD_TYPE_INVALID    0
#define FD_TYPE_DEFAULT    1
#define FD_TYPE_CONSOLE    2
#define FD_TYPE_OVERLAPPED 3



struct set_file_pointer_request
{
    struct request_header __header;
    handle_t     handle;
    int          low;
    int          high;
    int          whence;
    int          new_low;
    int          new_high;
};



struct truncate_file_request
{
    struct request_header __header;
    handle_t     handle;
};



struct set_file_time_request
{
    struct request_header __header;
    handle_t     handle;
    time_t       access_time;
    time_t       write_time;
};



struct flush_file_request
{
    struct request_header __header;
    handle_t     handle;
};



struct get_file_info_request
{
    struct request_header __header;
    handle_t     handle;
    int          type;
    int          attr;
    time_t       access_time;
    time_t       write_time;
    int          size_high;
    int          size_low;
    int          links;
    int          index_high;
    int          index_low;
    unsigned int serial;
};



struct lock_file_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int offset_low;
    unsigned int offset_high;
    unsigned int count_low;
    unsigned int count_high;
};



struct unlock_file_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int offset_low;
    unsigned int offset_high;
    unsigned int count_low;
    unsigned int count_high;
};



struct create_pipe_request
{
    struct request_header __header;
    int          inherit;
    handle_t     handle_read;
    handle_t     handle_write;
};



struct create_socket_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    int          family;
    int          type;
    int          protocol;
    handle_t     handle;
};



struct accept_socket_request
{
    struct request_header __header;
    handle_t     lhandle;
    unsigned int access;
    int          inherit;
    handle_t     handle;
};



struct set_socket_event_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int mask;
    handle_t     event;
};



struct get_socket_event_request
{
    struct request_header __header;
    handle_t     handle;
    int          service;
    handle_t     s_event;
    handle_t     c_event;
    unsigned int mask;
    unsigned int pmask;
    unsigned int state;
    /* VARARG(errors,ints); */
};



struct enable_socket_event_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int mask;
    unsigned int sstate;
    unsigned int cstate;
};



struct alloc_console_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    handle_t     handle_in;
    handle_t     handle_out;
};



struct free_console_request
{
    struct request_header __header;
};



struct open_console_request
{
    struct request_header __header;
    int          output;
    unsigned int access;
    int          inherit;
    handle_t     handle;
};



struct set_console_fd_request
{
    struct request_header __header;
    handle_t     handle;
    int          fd_in;
    int          fd_out;
    int          pid;
};



struct get_console_mode_request
{
    struct request_header __header;
    handle_t     handle;
    int          mode;
};



struct set_console_mode_request
{
    struct request_header __header;
    handle_t     handle;
    int          mode;
};



struct set_console_info_request
{
    struct request_header __header;
    handle_t     handle;
    int          mask;
    int          cursor_size;
    int          cursor_visible;
    /* VARARG(title,string); */
};
#define SET_CONSOLE_INFO_CURSOR 0x01
#define SET_CONSOLE_INFO_TITLE  0x02


struct get_console_info_request
{
    struct request_header __header;
    handle_t     handle;
    int          cursor_size;
    int          cursor_visible;
    int          pid;
    /* VARARG(title,string); */
};



struct write_console_input_request
{
    struct request_header __header;
    handle_t     handle;
    /* VARARG(rec,input_records); */
    int          written;
};


struct read_console_input_request
{
    struct request_header __header;
    handle_t     handle;
    int          flush;
    int          read;
    /* VARARG(rec,input_records); */
};



struct create_change_notification_request
{
    struct request_header __header;
    int          subtree;
    int          filter;
    handle_t     handle;
};



struct create_mapping_request
{
    struct request_header __header;
    int          size_high;
    int          size_low;
    int          protect;
    int          inherit;
    handle_t     file_handle;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};

#define VPROT_READ       0x01
#define VPROT_WRITE      0x02
#define VPROT_EXEC       0x04
#define VPROT_WRITECOPY  0x08
#define VPROT_GUARD      0x10
#define VPROT_NOCACHE    0x20
#define VPROT_COMMITTED  0x40
#define VPROT_IMAGE      0x80



struct open_mapping_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};



struct get_mapping_info_request
{
    struct request_header __header;
    handle_t     handle;
    int          size_high;
    int          size_low;
    int          protect;
    int          header_size;
    void*        base;
    handle_t     shared_file;
    int          shared_size;
};



struct create_device_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    int          id;
    handle_t     handle;
};



struct create_snapshot_request
{
    struct request_header __header;
    int          inherit;
    int          flags;
    void*        pid;
    handle_t     handle;
};



struct next_process_request
{
    struct request_header __header;
    handle_t     handle;
    int          reset;
    int          count;
    void*        pid;
    int          threads;
    int          priority;
};



struct next_thread_request
{
    struct request_header __header;
    handle_t     handle;
    int          reset;
    int          count;
    void*        pid;
    void*        tid;
    int          base_pri;
    int          delta_pri;
};



struct next_module_request
{
    struct request_header __header;
    handle_t     handle;
    int          reset;
    void*        pid;
    void*        base;
};



struct wait_debug_event_request
{
    struct request_header __header;
    int           get_handle;
    void*         pid;
    void*         tid;
    handle_t      wait;
    /* VARARG(event,debug_event); */
};



struct queue_exception_event_request
{
    struct request_header __header;
    int              first;
    /* VARARG(record,exc_event); */
    handle_t         handle;
};



struct get_exception_status_request
{
    struct request_header __header;
    handle_t         handle;
    int              status;
    /* VARARG(context,context); */
};



struct output_debug_string_request
{
    struct request_header __header;
    void*         string;
    int           unicode;
    int           length;
};



struct continue_debug_event_request
{
    struct request_header __header;
    void*        pid;
    void*        tid;
    int          status;
};



struct debug_process_request
{
    struct request_header __header;
    void*        pid;
};



struct read_process_memory_request
{
    struct request_header __header;
    handle_t     handle;
    void*        addr;
    int          len;
    /* VARARG(data,bytes); */
};



struct write_process_memory_request
{
    struct request_header __header;
    handle_t     handle;
    void*        addr;
    int          len;
    unsigned int first_mask;
    unsigned int last_mask;
    /* VARARG(data,bytes); */
};



struct create_key_request
{
    struct request_header __header;
    handle_t     parent;
    unsigned int access;
    unsigned int options;
    time_t       modif;
    /* VARARG(name,unicode_len_str); */
    /* VARARG(class,unicode_str); */
    handle_t     hkey;
    int          created;
};


struct open_key_request
{
    struct request_header __header;
    handle_t     parent;
    unsigned int access;
    /* VARARG(name,unicode_str); */
    handle_t     hkey;
};



struct delete_key_request
{
    struct request_header __header;
    handle_t     hkey;
};



struct enum_key_request
{
    struct request_header __header;
    handle_t     hkey;
    int          index;
    int          full;
    int          subkeys;
    int          max_subkey;
    int          max_class;
    int          values;
    int          max_value;
    int          max_data;
    time_t       modif;
    /* VARARG(name,unicode_len_str); */
    /* VARARG(class,unicode_str); */
};



struct set_key_value_request
{
    struct request_header __header;
    handle_t     hkey;
    int          type;
    unsigned int total;
    unsigned int offset;
    /* VARARG(name,unicode_len_str); */
    /* VARARG(data,bytes); */
};



struct get_key_value_request
{
    struct request_header __header;
    handle_t     hkey;
    unsigned int offset;
    /* VARARG(name,unicode_len_str); */
    int          type;
    int          len;
    /* VARARG(data,bytes); */
};



struct enum_key_value_request
{
    struct request_header __header;
    handle_t     hkey;
    int          index;
    unsigned int offset;
    int          type;
    int          len;
    /* VARARG(name,unicode_len_str); */
    /* VARARG(data,bytes); */
};



struct delete_key_value_request
{
    struct request_header __header;
    handle_t     hkey;
    /* VARARG(name,unicode_str); */
};



struct load_registry_request
{
    struct request_header __header;
    handle_t     hkey;
    handle_t     file;
    /* VARARG(name,unicode_str); */
};



struct save_registry_request
{
    struct request_header __header;
    handle_t     hkey;
    handle_t     file;
};



struct save_registry_atexit_request
{
    struct request_header __header;
    handle_t     hkey;
    /* VARARG(file,string); */
};



struct set_registry_levels_request
{
    struct request_header __header;
    int          current;
    int          saving;
    int          period;
};



struct create_timer_request
{
    struct request_header __header;
    int          inherit;
    int          manual;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};



struct open_timer_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    /* VARARG(name,unicode_str); */
    handle_t     handle;
};


struct set_timer_request
{
    struct request_header __header;
    handle_t     handle;
    int          sec;
    int          usec;
    int          period;
    void*        callback;
    void*        arg;
};


struct cancel_timer_request
{
    struct request_header __header;
    handle_t     handle;
};



struct get_thread_context_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int flags;
    /* VARARG(context,context); */
};



struct set_thread_context_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int flags;
    /* VARARG(context,context); */
};



struct get_selector_entry_request
{
    struct request_header __header;
    handle_t      handle;
    int           entry;
    unsigned int  base;
    unsigned int  limit;
    unsigned char flags;
};



struct add_atom_request
{
    struct request_header __header;
    int           local;
    /* VARARG(name,unicode_str); */
    int           atom;
};



struct delete_atom_request
{
    struct request_header __header;
    int           atom;
    int           local;
};



struct find_atom_request
{
    struct request_header __header;
    int          local;
    /* VARARG(name,unicode_str); */
    int          atom;
};



struct get_atom_name_request
{
    struct request_header __header;
    int          atom;
    int          local;
    int          count;
    /* VARARG(name,unicode_str); */
};



struct init_atom_table_request
{
    struct request_header __header;
    int          entries;
};



struct get_msg_queue_request
{
    struct request_header __header;
    handle_t     handle;
};



struct inc_queue_paint_count_request
{
    struct request_header __header;
    void*           id;
    int             incr;
};



struct set_queue_mask_request
{
    struct request_header __header;
    unsigned int wake_mask;
    unsigned int changed_mask;
    int          skip_wait;
    unsigned int wake_bits;
    unsigned int changed_bits;
};



struct get_queue_status_request
{
    struct request_header __header;
    int          clear;
    unsigned int wake_bits;
    unsigned int changed_bits;
};



struct wait_input_idle_request
{
    struct request_header __header;
    handle_t     handle;
    int          timeout;
    handle_t     event;
};



struct send_message_request
{
    struct request_header __header;
    void*           id;
    int             type;
    user_handle_t   win;
    unsigned int    msg;
    unsigned int    wparam;
    unsigned int    lparam;
    int             x;
    int             y;
    unsigned int    time;
    unsigned int    info;
    int             timeout;
    /* VARARG(data,bytes); */
};

enum message_type
{
    MSG_ASCII,
    MSG_UNICODE,
    MSG_NOTIFY,
    MSG_CALLBACK,
    MSG_OTHER_PROCESS,
    MSG_POSTED,
    MSG_HARDWARE_RAW,
    MSG_HARDWARE_COOKED
};



struct get_message_request
{
    struct request_header __header;
    int             flags;
    user_handle_t   get_win;
    unsigned int    get_first;
    unsigned int    get_last;
    int             type;
    user_handle_t   win;
    unsigned int    msg;
    unsigned int    wparam;
    unsigned int    lparam;
    int             x;
    int             y;
    unsigned int    time;
    unsigned int    info;
    /* VARARG(data,bytes); */
};
#define GET_MSG_REMOVE      1
#define GET_MSG_SENT_ONLY   2
#define GET_MSG_REMOVE_LAST 4


struct reply_message_request
{
    struct request_header __header;
    unsigned int    result;
    int             remove;
    /* VARARG(data,bytes); */
};



struct get_message_reply_request
{
    struct request_header __header;
    int             cancel;
    unsigned int    result;
    /* VARARG(data,bytes); */
};



struct cleanup_window_queue_request
{
    struct request_header __header;
    user_handle_t   win;
};



struct set_win_timer_request
{
    struct request_header __header;
    user_handle_t   win;
    unsigned int    msg;
    unsigned int    id;
    unsigned int    rate;
    unsigned int    lparam;
};



struct kill_win_timer_request
{
    struct request_header __header;
    user_handle_t   win;
    unsigned int    msg;
    unsigned int    id;
};



struct create_serial_request
{
    struct request_header __header;
    unsigned int access;
    int          inherit;
    unsigned int sharing;
    /* VARARG(name,string); */
    handle_t     handle;
};



struct get_serial_info_request
{
    struct request_header __header;
    handle_t     handle;
    unsigned int readinterval;
    unsigned int readconst;
    unsigned int readmult;
    unsigned int writeconst;
    unsigned int writemult;
    unsigned int eventmask;
    unsigned int commerror;
};



struct set_serial_info_request
{
    struct request_header __header;
    handle_t     handle;
    int          flags;
    unsigned int readinterval;
    unsigned int readconst;
    unsigned int readmult;
    unsigned int writeconst;
    unsigned int writemult;
    unsigned int eventmask;
    unsigned int commerror;
};
#define SERIALINFO_SET_TIMEOUTS  0x01
#define SERIALINFO_SET_MASK      0x02
#define SERIALINFO_SET_ERROR     0x04



struct create_async_request
{
    struct request_header __header;
    handle_t     file_handle;
    int          count;
    int          type;
    int          timeout;
};
#define ASYNC_TYPE_READ  0x01
#define ASYNC_TYPE_WRITE 0x02
#define ASYNC_TYPE_WAIT  0x03



struct create_named_pipe_request
{
    struct request_header __header;
    unsigned int   openmode;
    unsigned int   pipemode;
    unsigned int   maxinstances;
    unsigned int   outsize;
    unsigned int   insize;
    unsigned int   timeout;
    /* VARARG(filename,string); */
    handle_t       handle;
};



struct open_named_pipe_request
{
    struct request_header __header;
    unsigned int   access;
    /* VARARG(filename,string); */
    handle_t       handle;
};



struct connect_named_pipe_request
{
    struct request_header __header;
    handle_t       handle;
    handle_t       event;
};



struct wait_named_pipe_request
{
    struct request_header __header;
    unsigned int   timeout;
    handle_t       event;
    /* VARARG(filename,string); */
};



struct disconnect_named_pipe_request
{
    struct request_header __header;
    handle_t       handle;
};


struct get_named_pipe_info_request
{
    struct request_header __header;
    handle_t       handle;
    unsigned int   flags;
    unsigned int   maxinstances;
    unsigned int   outsize;
    unsigned int   insize;
};



struct create_window_request
{
    struct request_header __header;
    user_handle_t  parent;
    user_handle_t  owner;
    user_handle_t  handle;
};



struct link_window_request
{
    struct request_header __header;
    user_handle_t  handle;
    user_handle_t  parent;
    user_handle_t  previous;
};



struct destroy_window_request
{
    struct request_header __header;
    user_handle_t  handle;
};



struct get_window_info_request
{
    struct request_header __header;
    user_handle_t  handle;
    user_handle_t  full_handle;
    void*          pid;
    void*          tid;
};



struct get_window_parents_request
{
    struct request_header __header;
    user_handle_t  handle;
    int            count;
    /* VARARG(parents,user_handles); */
};



struct get_window_children_request
{
    struct request_header __header;
    user_handle_t  parent;
    int            count;
    /* VARARG(children,user_handles); */
};



struct get_window_tree_request
{
    struct request_header __header;
    user_handle_t  handle;
    user_handle_t  parent;
    user_handle_t  owner;
    user_handle_t  next_sibling;
    user_handle_t  prev_sibling;
    user_handle_t  first_sibling;
    user_handle_t  last_sibling;
    user_handle_t  first_child;
    user_handle_t  last_child;
};


enum request
{
    REQ_new_process,
    REQ_get_new_process_info,
    REQ_new_thread,
    REQ_boot_done,
    REQ_init_process,
    REQ_init_process_done,
    REQ_init_thread,
    REQ_set_thread_buffer,
    REQ_terminate_process,
    REQ_terminate_thread,
    REQ_get_process_info,
    REQ_set_process_info,
    REQ_get_thread_info,
    REQ_set_thread_info,
    REQ_suspend_thread,
    REQ_resume_thread,
    REQ_load_dll,
    REQ_unload_dll,
    REQ_queue_apc,
    REQ_get_apc,
    REQ_close_handle,
    REQ_set_handle_info,
    REQ_dup_handle,
    REQ_open_process,
    REQ_select,
    REQ_create_event,
    REQ_event_op,
    REQ_open_event,
    REQ_create_mutex,
    REQ_release_mutex,
    REQ_open_mutex,
    REQ_create_semaphore,
    REQ_release_semaphore,
    REQ_open_semaphore,
    REQ_create_file,
    REQ_alloc_file_handle,
    REQ_get_handle_fd,
    REQ_set_file_pointer,
    REQ_truncate_file,
    REQ_set_file_time,
    REQ_flush_file,
    REQ_get_file_info,
    REQ_lock_file,
    REQ_unlock_file,
    REQ_create_pipe,
    REQ_create_socket,
    REQ_accept_socket,
    REQ_set_socket_event,
    REQ_get_socket_event,
    REQ_enable_socket_event,
    REQ_alloc_console,
    REQ_free_console,
    REQ_open_console,
    REQ_set_console_fd,
    REQ_get_console_mode,
    REQ_set_console_mode,
    REQ_set_console_info,
    REQ_get_console_info,
    REQ_write_console_input,
    REQ_read_console_input,
    REQ_create_change_notification,
    REQ_create_mapping,
    REQ_open_mapping,
    REQ_get_mapping_info,
    REQ_create_device,
    REQ_create_snapshot,
    REQ_next_process,
    REQ_next_thread,
    REQ_next_module,
    REQ_wait_debug_event,
    REQ_queue_exception_event,
    REQ_get_exception_status,
    REQ_output_debug_string,
    REQ_continue_debug_event,
    REQ_debug_process,
    REQ_read_process_memory,
    REQ_write_process_memory,
    REQ_create_key,
    REQ_open_key,
    REQ_delete_key,
    REQ_enum_key,
    REQ_set_key_value,
    REQ_get_key_value,
    REQ_enum_key_value,
    REQ_delete_key_value,
    REQ_load_registry,
    REQ_save_registry,
    REQ_save_registry_atexit,
    REQ_set_registry_levels,
    REQ_create_timer,
    REQ_open_timer,
    REQ_set_timer,
    REQ_cancel_timer,
    REQ_get_thread_context,
    REQ_set_thread_context,
    REQ_get_selector_entry,
    REQ_add_atom,
    REQ_delete_atom,
    REQ_find_atom,
    REQ_get_atom_name,
    REQ_init_atom_table,
    REQ_get_msg_queue,
    REQ_inc_queue_paint_count,
    REQ_set_queue_mask,
    REQ_get_queue_status,
    REQ_wait_input_idle,
    REQ_send_message,
    REQ_get_message,
    REQ_reply_message,
    REQ_get_message_reply,
    REQ_cleanup_window_queue,
    REQ_set_win_timer,
    REQ_kill_win_timer,
    REQ_create_serial,
    REQ_get_serial_info,
    REQ_set_serial_info,
    REQ_create_async,
    REQ_create_named_pipe,
    REQ_open_named_pipe,
    REQ_connect_named_pipe,
    REQ_wait_named_pipe,
    REQ_disconnect_named_pipe,
    REQ_get_named_pipe_info,
    REQ_create_window,
    REQ_link_window,
    REQ_destroy_window,
    REQ_get_window_info,
    REQ_get_window_parents,
    REQ_get_window_children,
    REQ_get_window_tree,
    REQ_NB_REQUESTS
};

union generic_request
{
    struct request_max_size max_size;
    struct request_header header;
    struct new_process_request new_process;
    struct get_new_process_info_request get_new_process_info;
    struct new_thread_request new_thread;
    struct boot_done_request boot_done;
    struct init_process_request init_process;
    struct init_process_done_request init_process_done;
    struct init_thread_request init_thread;
    struct set_thread_buffer_request set_thread_buffer;
    struct terminate_process_request terminate_process;
    struct terminate_thread_request terminate_thread;
    struct get_process_info_request get_process_info;
    struct set_process_info_request set_process_info;
    struct get_thread_info_request get_thread_info;
    struct set_thread_info_request set_thread_info;
    struct suspend_thread_request suspend_thread;
    struct resume_thread_request resume_thread;
    struct load_dll_request load_dll;
    struct unload_dll_request unload_dll;
    struct queue_apc_request queue_apc;
    struct get_apc_request get_apc;
    struct close_handle_request close_handle;
    struct set_handle_info_request set_handle_info;
    struct dup_handle_request dup_handle;
    struct open_process_request open_process;
    struct select_request select;
    struct create_event_request create_event;
    struct event_op_request event_op;
    struct open_event_request open_event;
    struct create_mutex_request create_mutex;
    struct release_mutex_request release_mutex;
    struct open_mutex_request open_mutex;
    struct create_semaphore_request create_semaphore;
    struct release_semaphore_request release_semaphore;
    struct open_semaphore_request open_semaphore;
    struct create_file_request create_file;
    struct alloc_file_handle_request alloc_file_handle;
    struct get_handle_fd_request get_handle_fd;
    struct set_file_pointer_request set_file_pointer;
    struct truncate_file_request truncate_file;
    struct set_file_time_request set_file_time;
    struct flush_file_request flush_file;
    struct get_file_info_request get_file_info;
    struct lock_file_request lock_file;
    struct unlock_file_request unlock_file;
    struct create_pipe_request create_pipe;
    struct create_socket_request create_socket;
    struct accept_socket_request accept_socket;
    struct set_socket_event_request set_socket_event;
    struct get_socket_event_request get_socket_event;
    struct enable_socket_event_request enable_socket_event;
    struct alloc_console_request alloc_console;
    struct free_console_request free_console;
    struct open_console_request open_console;
    struct set_console_fd_request set_console_fd;
    struct get_console_mode_request get_console_mode;
    struct set_console_mode_request set_console_mode;
    struct set_console_info_request set_console_info;
    struct get_console_info_request get_console_info;
    struct write_console_input_request write_console_input;
    struct read_console_input_request read_console_input;
    struct create_change_notification_request create_change_notification;
    struct create_mapping_request create_mapping;
    struct open_mapping_request open_mapping;
    struct get_mapping_info_request get_mapping_info;
    struct create_device_request create_device;
    struct create_snapshot_request create_snapshot;
    struct next_process_request next_process;
    struct next_thread_request next_thread;
    struct next_module_request next_module;
    struct wait_debug_event_request wait_debug_event;
    struct queue_exception_event_request queue_exception_event;
    struct get_exception_status_request get_exception_status;
    struct output_debug_string_request output_debug_string;
    struct continue_debug_event_request continue_debug_event;
    struct debug_process_request debug_process;
    struct read_process_memory_request read_process_memory;
    struct write_process_memory_request write_process_memory;
    struct create_key_request create_key;
    struct open_key_request open_key;
    struct delete_key_request delete_key;
    struct enum_key_request enum_key;
    struct set_key_value_request set_key_value;
    struct get_key_value_request get_key_value;
    struct enum_key_value_request enum_key_value;
    struct delete_key_value_request delete_key_value;
    struct load_registry_request load_registry;
    struct save_registry_request save_registry;
    struct save_registry_atexit_request save_registry_atexit;
    struct set_registry_levels_request set_registry_levels;
    struct create_timer_request create_timer;
    struct open_timer_request open_timer;
    struct set_timer_request set_timer;
    struct cancel_timer_request cancel_timer;
    struct get_thread_context_request get_thread_context;
    struct set_thread_context_request set_thread_context;
    struct get_selector_entry_request get_selector_entry;
    struct add_atom_request add_atom;
    struct delete_atom_request delete_atom;
    struct find_atom_request find_atom;
    struct get_atom_name_request get_atom_name;
    struct init_atom_table_request init_atom_table;
    struct get_msg_queue_request get_msg_queue;
    struct inc_queue_paint_count_request inc_queue_paint_count;
    struct set_queue_mask_request set_queue_mask;
    struct get_queue_status_request get_queue_status;
    struct wait_input_idle_request wait_input_idle;
    struct send_message_request send_message;
    struct get_message_request get_message;
    struct reply_message_request reply_message;
    struct get_message_reply_request get_message_reply;
    struct cleanup_window_queue_request cleanup_window_queue;
    struct set_win_timer_request set_win_timer;
    struct kill_win_timer_request kill_win_timer;
    struct create_serial_request create_serial;
    struct get_serial_info_request get_serial_info;
    struct set_serial_info_request set_serial_info;
    struct create_async_request create_async;
    struct create_named_pipe_request create_named_pipe;
    struct open_named_pipe_request open_named_pipe;
    struct connect_named_pipe_request connect_named_pipe;
    struct wait_named_pipe_request wait_named_pipe;
    struct disconnect_named_pipe_request disconnect_named_pipe;
    struct get_named_pipe_info_request get_named_pipe_info;
    struct create_window_request create_window;
    struct link_window_request link_window;
    struct destroy_window_request destroy_window;
    struct get_window_info_request get_window_info;
    struct get_window_parents_request get_window_parents;
    struct get_window_children_request get_window_children;
    struct get_window_tree_request get_window_tree;
};

#define SERVER_PROTOCOL_VERSION 54

#endif /* __WINE_WINE_SERVER_PROTOCOL_H */
