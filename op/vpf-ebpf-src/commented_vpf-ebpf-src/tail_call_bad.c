// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;

#define BPF_MAP_TYPE_ARRAY 2

typedef struct bpf_map {
    uint32_t type;
    uint32_t key_size;
    uint32_t value_size;
    uint32_t max_entries;
    uint32_t map_flags;
    uint32_t inner_map_idx;
    uint32_t numa_node;
} bpf_map_def_t;

struct xdp_md;

static long (*bpf_tail_call)(void *ctx, struct bpf_map *prog_array_map, uint32_t index) = (void*) 12;

__attribute__((section("maps"), used)) struct bpf_map map = {
    BPF_MAP_TYPE_ARRAY, sizeof(uint32_t), sizeof(uint32_t), 1};

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 24,
  "endLine": 32,
  "File": "/home/sayandes/opened_extraction/examples/vpf-ebpf-src/tail_call_bad.c",
  "funcName": "caller",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct xdp_md *ctx"
  ],
  "output": "int",
  "helper": [
    "bpf_tail_call"
  ],
  "compatibleHookpoints": [
    "lwt_xmit",
    "cgroup_skb",
    "lwt_in",
    "kprobe",
    "xdp",
    "cgroup_sock",
    "perf_event",
    "tracepoint",
    "sk_reuseport",
    "cgroup_sock_addr",
    "sock_ops",
    "raw_tracepoint_writable",
    "lwt_out",
    "sched_act",
    "lwt_seg6local",
    "sk_msg",
    "socket_filter",
    "flow_dissector",
    "sched_cls",
    "raw_tracepoint",
    "sk_skb"
  ],
  "source": [
    "int caller (struct xdp_md *ctx)\n",
    "{\n",
    "    long error = bpf_tail_call (ctx, & map, 0);\n",
    "    return (int) error;\n",
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
__attribute__((section("xdp_prog"), used)) int
caller(struct xdp_md* ctx)
{
    // This should fail validation since the map is not a prog array.
    long error = bpf_tail_call(ctx, &map, 0);

    // bpf_tail_call failed at runtime.
    return (int)error;
}

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 34,
  "endLine": 38,
  "File": "/home/sayandes/opened_extraction/examples/vpf-ebpf-src/tail_call_bad.c",
  "funcName": "callee",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct xdp_md *ctx"
  ],
  "output": "int",
  "helper": [],
  "compatibleHookpoints": [
    "lwt_xmit",
    "cgroup_skb",
    "lwt_in",
    "kprobe",
    "xdp",
    "cgroup_sock",
    "perf_event",
    "tracepoint",
    "sk_reuseport",
    "cgroup_sock_addr",
    "sock_ops",
    "raw_tracepoint_writable",
    "lwt_out",
    "cgroup_sysctl",
    "sched_act",
    "cgroup_device",
    "lwt_seg6local",
    "sk_msg",
    "socket_filter",
    "flow_dissector",
    "sched_cls",
    "raw_tracepoint",
    "sk_skb"
  ],
  "source": [
    "int callee (struct xdp_md *ctx)\n",
    "{\n",
    "    return 42;\n",
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
__attribute__((section("xdp_prog/0"), used)) int
callee(struct xdp_md* ctx)
{
    return 42;
}
