// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef struct bpf_map_def {
    uint32_t type;
    uint32_t key_size;
    uint32_t value_size;
    uint32_t max_entries;
    uint32_t map_flags;
    uint32_t inner_map_idx;
    uint32_t numa_node;
} bpf_map_def_t;
#define BPF_MAP_TYPE_ARRAY 2

__attribute__((section("maps"), used))
bpf_map_def_t map =
    {.type = BPF_MAP_TYPE_ARRAY,
     .key_size = sizeof(int),
     .value_size = sizeof(uint32_t),
     .max_entries = 1};

static void* (*bpf_map_lookup_elem)(bpf_map_def_t* map, void* key) = (void*) 1;

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "map_read",
      "map_read": [
        {
          "Project": "libbpf",
          "Return Type": "void*",
          "Description": "Perform a lookup in <[ map ]>(IP: 0) for an entry associated to key. ",
          "Return": " Map value associated to key, or NULL if no entry was found.",
          "Function Name": "bpf_map_lookup_elem",
          "Input Params": [
            "{Type: struct bpf_map ,Var: *map}",
            "{Type:  const void ,Var: *key}"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {
    "bpf_map_lookup_elem": [
      {
        "opVar": "    uint64_t* ptr ",
        "inpVar": [
          " &map",
          " &key"
        ]
      }
    ]
  },
  "startLine": 26,
  "endLine": 39,
  "File": "/home/sayandes/opened_extraction/examples/vpf-ebpf-src/mapvalue-overrun.c",
  "funcName": "func",
  "updateMaps": [],
  "readMaps": [
    " map"
  ],
  "input": [
    "void *ctx"
  ],
  "output": "int",
  "helper": [
    "bpf_map_lookup_elem"
  ],
  "compatibleHookpoints": [
    "socket_filter",
    "raw_tracepoint_writable",
    "sk_reuseport",
    "lwt_seg6local",
    "cgroup_skb",
    "sock_ops",
    "lwt_out",
    "sched_act",
    "raw_tracepoint",
    "lwt_xmit",
    "xdp",
    "kprobe",
    "sk_msg",
    "cgroup_device",
    "lwt_in",
    "cgroup_sysctl",
    "flow_dissector",
    "tracepoint",
    "cgroup_sock_addr",
    "cgroup_sock",
    "sched_cls",
    "perf_event",
    "sk_skb"
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
int func(void* ctx)
{
    uint32_t key = 1;

    uint64_t* ptr = bpf_map_lookup_elem(&map, &key);
    if (ptr == 0) {
        return 0;
    }

    // The map's value size can only hold a uint32_t.
    // So verification should fail if we try to read past the space returned.
    uint64_t i = *ptr;
    return (uint32_t)i;
}
