/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright Authors of Cilium */

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, __u32);
	__type(value, __u64);
	__uint(max_entries, 1024);
} bytecount_map __section_maps_btf;

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "map_read",
      "map_read": [
        {
          "Project": "cilium",
          "Return Type": "void*",
          "Description": "Perform a lookup in <[ map ]>(IP: 0) for an entry associated to key. ",
          "Return": " Map value associated to key, or NULL if no entry was found.",
          "Function Name": "map_lookup_elem",
          "Input Params": [
            "{Type: struct map ,Var: *map}",
            "{Type:  const void ,Var: *key}"
          ],
          "compatible_hookpoints": [
            "socket_filter",
            "kprobe",
            "sched_cls",
            "sched_act",
            "tracepoint",
            "xdp",
            "perf_event",
            "cgroup_skb",
            "cgroup_sock",
            "lwt_in",
            "lwt_out",
            "lwt_xmit",
            "sock_ops",
            "sk_skb",
            "cgroup_device",
            "sk_msg",
            "raw_tracepoint",
            "cgroup_sock_addr",
            "lwt_seg6local",
            "sk_reuseport",
            "flow_dissector",
            "cgroup_sysctl",
            "raw_tracepoint_writable"
          ],
          "capabilities": [
            "map_read"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 11,
  "endLine": 24,
  "File": "/home/sayandes/opened_extraction/examples/cilium/custom/bytecount.h",
  "funcName": "custom_prog",
  "developer_inline_comments": [
    {
      "start_line": 1,
      "end_line": 1,
      "text": "/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */"
    },
    {
      "start_line": 2,
      "end_line": 2,
      "text": "/* Copyright Authors of Cilium */"
    },
    {
      "start_line": 22,
      "end_line": 22,
      "text": "/* No entry for endpoint in hashmap, attempt to create one */"
    }
  ],
  "updateMaps": [
    " bytecount_map"
  ],
  "readMaps": [
    "  bytecount_map"
  ],
  "input": [
    "const struct  __ctx_buff *ctx",
    " __u32 identity"
  ],
  "output": "static__always_inlinevoid",
  "helper": [
    "map_lookup_elem",
    "map_update_elem"
  ],
  "compatibleHookpoints": [
    "cgroup_sock",
    "lwt_xmit",
    "sock_ops",
    "flow_dissector",
    "raw_tracepoint",
    "cgroup_sysctl",
    "tracepoint",
    "kprobe",
    "lwt_out",
    "sched_act",
    "cgroup_device",
    "cgroup_sock_addr",
    "sk_reuseport",
    "perf_event",
    "xdp",
    "lwt_seg6local",
    "sched_cls",
    "sk_skb",
    "socket_filter",
    "cgroup_skb",
    "sk_msg",
    "lwt_in",
    "raw_tracepoint_writable"
  ],
  "source": [
    "static __always_inline void custom_prog (const struct  __ctx_buff *ctx, __u32 identity)\n",
    "{\n",
    "    __u64 len, *bytecount;\n",
    "    len = ctx_full_len (ctx);\n",
    "    bytecount = map_lookup_elem (& bytecount_map, & identity);\n",
    "    if (bytecount)\n",
    "        __sync_fetch_and_add (bytecount, len);\n",
    "    else\n",
    "        map_update_elem (&bytecount_map, &identity, &len, BPF_ANY);\n",
    "}\n"
  ],
  "called_function_list": [
    "ctx_full_len",
    "__sync_fetch_and_add"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    null
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
static __always_inline
void custom_prog(const struct __ctx_buff *ctx, __u32 identity)
{
	__u64 len, *bytecount;

	len = ctx_full_len(ctx);

	bytecount = map_lookup_elem(&bytecount_map, &identity);
	if (bytecount)
		__sync_fetch_and_add(bytecount, len);
	else
		/* No entry for endpoint in hashmap, attempt to create one */
		map_update_elem(&bytecount_map, &identity, &len, BPF_ANY);
}
