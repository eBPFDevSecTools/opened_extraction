// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef struct bpf_map {
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
     .key_size = sizeof(uint32_t),
     .value_size = sizeof(uint32_t),
     .max_entries = 1};

struct bpf_sock_ops;

static int (*bpf_sock_map_update)(struct bpf_sock_ops *skops, struct bpf_map *map, void *key, uint64_t flags) = (void*) 53;

__attribute__((section("sockops"), used))
/* 
 OPENED COMMENT BEGIN 
{
  "capability": [
    {
      "map_update": [
        {
          "Description": "Add an entry to , or update a <[ map ]>(IP: 1) referencing sockets. The <[ skops ]>(IP: 0) is used as a new value for the entry associated to key. <[ flags ]>(IP: 3) is one of:BPF_NOEXISTThe entry for <[ key ]>(IP: 2) must not exist in the map. BPF_EXISTThe entry for <[ key ]>(IP: 2) must already exist in the map. BPF_ANYNo condition on the existence of the entry for key. If the <[ map ]>(IP: 1) has eBPF programs (parser and verdict) , those will be inherited by the socket being added. If the socket is already attached to eBPF programs , this results in an error. ",
          "Return": "0 on success, or a negative error in case of failure.",
          "Return Type": "int",
          "Function Name": "bpf_sock_map_update",
          "Input Params": [
            "{Type: struct bpf_sock_ops ,Var: *skops}",
            "{Type:  struct bpf_map ,Var: *map}",
            "{Type:  void ,Var: *key}",
            "{Type:  u64 ,Var: flags}"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {
    "bpf_sock_map_update": [
      "{\n \"opVar\": \"    int result \",\n \"inpVar\": [\n  \" ctx\",\n  \" &map\",\n  \" &key\",\n  \" 0\"\n ]\n}"
    ]
  },
  "startLine": 29,
  "endLine": 38,
  "File": "/home/sayandes/opened_extraction/examples/vpf-ebpf-src/ctxoffset.c",
  "Funcname": "func",
  "Update_maps": [
    " ctx",
    ""
  ],
  "Read_maps": [
    ""
  ],
  "Input": [
    "void *ctx"
  ],
  "Output": "int",
  "Helper": "bpf_sock_map_update,",
  "human_func_description": [
    {
      "description": "",
      "author": "",
      "author_email": "",
      "date": ""
    }
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "author_email": "",
      "date": "",
      "params": ""
    }
  ]
}
,
 Func Description: TO BE ADDED, 
 Commentor: TO BE ADDED (<name>,<email>) 
 } 
 OPENED COMMENT END 
 */ 
int func(void* ctx)
{
    uint32_t key = 1;

    // The following should fail because the sock_ops ctx isn't the same pointer passed in
    // but is offset 8 bytes into it.
    ctx = ((char*)ctx) + 8;
    int result = bpf_sock_map_update(ctx, &map, &key, 0);
    return result;
}
