//int hello (void *ctx)
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {
    "bpf_trace_printk": [
      {
        "opVar": "NA",
        "inpVar": [
          "\t     \"Hello",
          " World!\\\\n\""
        ]
      }
    ]
  },
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
    "lwt_in",
    "raw_tracepoint_writable",
    "sched_act",
    "tracepoint",
    "cgroup_sysctl",
    "cgroup_sock",
    "perf_event",
    "sock_ops",
    "raw_tracepoint",
    "xdp",
    "lwt_xmit",
    "sk_reuseport",
    "sk_msg",
    "cgroup_sock_addr",
    "lwt_seg6local",
    "lwt_out",
    "cgroup_skb",
    "sk_skb",
    "socket_filter",
    "kprobe",
    "cgroup_device",
    "flow_dissector",
    "sched_cls"
  ],
  "humanFuncDescription": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": ""
    },
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
