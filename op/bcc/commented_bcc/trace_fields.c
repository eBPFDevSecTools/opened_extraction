//int hello (void *ctx)
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 2,
  "endLine": 6,
  "File": "/home/sayandes/opened_extraction/examples/bcc/trace_fields.c",
  "funcName": "hello",
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "NA"
  ],
  "output": "int",
  "helper": [
    "bpf_trace_printk"
  ],
  "compatibleHookpoints": [
    "cgroup_sock",
    "sock_ops",
    "sk_skb",
    "flow_dissector",
    "socket_filter",
    "sk_reuseport",
    "raw_tracepoint",
    "kprobe",
    "xdp",
    "lwt_in",
    "cgroup_sysctl",
    "lwt_xmit",
    "cgroup_sock_addr",
    "sched_cls",
    "perf_event",
    "sched_act",
    "lwt_out",
    "raw_tracepoint_writable",
    "tracepoint",
    "cgroup_device",
    "sk_msg",
    "lwt_seg6local",
    "cgroup_skb"
  ],
  "source": [
    "int hello ()\n",
    "{\n",
    "    bpf_trace_printk (\"Hello, World!\\\\n\");\n",
    "    return 0;\n",
    "}\n"
  ],
  "called_function_list": [],
  "call_depth": 0,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
int hello ()
{
	    bpf_trace_printk ("Hello, World!\\n");
	        return 0;
}
