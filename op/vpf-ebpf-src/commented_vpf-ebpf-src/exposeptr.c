// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

struct ebpf_map {
    uint32_t type;
    uint32_t key_size;
    uint32_t value_size;
    uint32_t max_entries;
    uint32_t map_flags;
    uint32_t inner_map_idx;
    uint32_t numa_node;
};
#define BPF_MAP_TYPE_ARRAY 2

__attribute__((section("maps"), used))
struct ebpf_map map =
    {.type = BPF_MAP_TYPE_ARRAY,
     .key_size = sizeof(int),
     .value_size = sizeof(uint64_t),
     .max_entries = 1};

static int (*ebpf_map_update_elem)(struct ebpf_map* map, const void* key,
                                   const void* value, uint64_t flags) = (void*) 2;

struct ctx;

/* 
 OPENED COMMENT BEGIN 
{
  "capability": [
    {
      "capability": "map_update",
      "map_update": [
        {
          "Return Type": "int",
          "Description": "Add or update the <[ value ]>(IP: 2) of the entry associated to <[ key ]>(IP: 1) in <[ map ]>(IP: 0) with value. <[ flags ]>(IP: 3) is one of: BPF_NOEXIST The entry for <[ key ]>(IP: 1) must not exist in the map. BPF_EXIST The entry for <[ key ]>(IP: 1) must already exist in the map. BPF_ANY No condition on the existence of the entry for key. Flag <[ value ]>(IP: 2) BPF_NOEXIST cannot be used for maps of types BPF_MAP_TYPE_ARRAY or BPF_MAP_TYPE_PERCPU_ARRAY (all elements always exist) , the helper would return an error. ",
          "Return": " 0 on success, or a negative error in case of failure.",
          "Function Name": "bpf_map_update_elem",
          "Input Params": [
            "{Type: struct bpf_map ,Var: *map}",
            "{Type:  const void ,Var: *key}",
            "{Type:  const void ,Var: *value}",
            "{Type:  u64 ,Var: flags}"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {
    "bpf_map_update_elem": [
      {
        "opVar": "NA",
        "inpVar": [
          "            return e&map",
          " &key",
          " &ctx",
          " 0"
        ]
      }
    ]
  },
  "startLine": 29,
  "endLine": 36,
  "File": "/home/sayandes/opened_extraction/examples/vpf-ebpf-src/exposeptr.c",
  "funcName": "func",
  "updateMaps": [
    " map"
  ],
  "readMaps": [],
  "input": [
    "struct ctx *ctx"
  ],
  "output": "int",
  "helper": [
    "bpf_map_update_elem"
  ],
  "compatibleHookpoints": [
    "raw_tracepoint",
    "cgroup_sock_addr",
    "sk_reuseport",
    "sk_msg",
    "raw_tracepoint_writable",
    "sched_cls",
    "kprobe",
    "cgroup_skb",
    "tracepoint",
    "lwt_xmit",
    "sched_act",
    "cgroup_sysctl",
    "xdp",
    "sk_skb",
    "perf_event",
    "flow_dissector",
    "sock_ops",
    "cgroup_sock",
    "lwt_out",
    "socket_filter",
    "lwt_in",
    "lwt_seg6local",
    "cgroup_device"
  ],
  "humanFuncDescription": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": ""
    }
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
int func(struct ctx* ctx)
{
    uint32_t key = 0;

    // The following should fail verification since it stores
    // a pointer in shared memory, thus exposing it to user-mode apps.
    return ebpf_map_update_elem(&map, &key, &ctx, 0);
}
