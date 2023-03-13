/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright Authors of Cilium */

#ifndef __LIB_CONNTRACK_MAP_H_
#define __LIB_CONNTRACK_MAP_H_

#include "common.h"
#include "config.h"

#if defined(CT_MAP_TCP4) && defined(CT_MAP_TCP6)
#ifdef HAVE_LRU_HASH_MAP_TYPE
#define CT_MAP_TYPE BPF_MAP_TYPE_LRU_HASH
#else
#define CT_MAP_TYPE BPF_MAP_TYPE_HASH
#endif

#ifdef ENABLE_IPV6
struct {
	__uint(type, CT_MAP_TYPE);
	__type(key, struct ipv6_ct_tuple);
	__type(value, struct ct_entry);
	__uint(pinning, LIBBPF_PIN_BY_NAME);
	__uint(max_entries, CT_MAP_SIZE_TCP);
#ifndef HAVE_LRU_HASH_MAP_TYPE
	__uint(map_flags, CONDITIONAL_PREALLOC);
#endif
} CT_MAP_TCP6 __section_maps_btf;

struct {
	__uint(type, CT_MAP_TYPE);
	__type(key, struct ipv6_ct_tuple);
	__type(value, struct ct_entry);
	__uint(pinning, LIBBPF_PIN_BY_NAME);
	__uint(max_entries, CT_MAP_SIZE_ANY);
#ifndef HAVE_LRU_HASH_MAP_TYPE
	__uint(map_flags, CONDITIONAL_PREALLOC);
#endif
} CT_MAP_ANY6 __section_maps_btf;

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 40,
  "endLine": 47,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/conntrack_map.h",
  "funcName": "get_ct_map6",
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "const struct ipv6_ct_tuple *tuple"
  ],
  "output": "static__always_inlinevoid",
  "helper": [],
  "compatibleHookpoints": [
    "sk_skb",
    "sk_msg",
    "lwt_seg6local",
    "lwt_in",
    "xdp",
    "sched_act",
    "lwt_out",
    "lwt_xmit",
    "flow_dissector",
    "cgroup_sock_addr",
    "tracepoint",
    "sk_reuseport",
    "cgroup_sysctl",
    "cgroup_skb",
    "socket_filter",
    "raw_tracepoint_writable",
    "cgroup_sock",
    "sock_ops",
    "raw_tracepoint",
    "perf_event",
    "kprobe",
    "sched_cls",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline void *get_ct_map6 (const struct ipv6_ct_tuple *tuple)\n",
    "{\n",
    "    if (tuple->nexthdr == IPPROTO_TCP)\n",
    "        return &CT_MAP_TCP6;\n",
    "    return &CT_MAP_ANY6;\n",
    "}\n"
  ],
  "called_function_list": [],
  "call_depth": 0,
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
static __always_inline void *
get_ct_map6(const struct ipv6_ct_tuple *tuple)
{
	if (tuple->nexthdr == IPPROTO_TCP)
		return &CT_MAP_TCP6;

	return &CT_MAP_ANY6;
}
#endif

#ifdef ENABLE_IPV4
struct {
	__uint(type, CT_MAP_TYPE);
	__type(key, struct ipv4_ct_tuple);
	__type(value, struct ct_entry);
	__uint(pinning, LIBBPF_PIN_BY_NAME);
	__uint(max_entries, CT_MAP_SIZE_TCP);
#ifndef HAVE_LRU_HASH_MAP_TYPE
	__uint(map_flags, CONDITIONAL_PREALLOC);
#endif
} CT_MAP_TCP4 __section_maps_btf;

struct {
	__uint(type, CT_MAP_TYPE);
	__type(key, struct ipv4_ct_tuple);
	__type(value, struct ct_entry);
	__uint(pinning, LIBBPF_PIN_BY_NAME);
	__uint(max_entries, CT_MAP_SIZE_ANY);
#ifndef HAVE_LRU_HASH_MAP_TYPE
	__uint(map_flags, CONDITIONAL_PREALLOC);
#endif
} CT_MAP_ANY4 __section_maps_btf;

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 73,
  "endLine": 80,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/conntrack_map.h",
  "funcName": "get_ct_map4",
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "const struct ipv4_ct_tuple *tuple"
  ],
  "output": "static__always_inlinevoid",
  "helper": [],
  "compatibleHookpoints": [
    "sk_skb",
    "sk_msg",
    "lwt_seg6local",
    "lwt_in",
    "xdp",
    "sched_act",
    "lwt_out",
    "lwt_xmit",
    "flow_dissector",
    "cgroup_sock_addr",
    "tracepoint",
    "sk_reuseport",
    "cgroup_sysctl",
    "cgroup_skb",
    "socket_filter",
    "raw_tracepoint_writable",
    "cgroup_sock",
    "sock_ops",
    "raw_tracepoint",
    "perf_event",
    "kprobe",
    "sched_cls",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline void *get_ct_map4 (const struct ipv4_ct_tuple *tuple)\n",
    "{\n",
    "    if (tuple->nexthdr == IPPROTO_TCP)\n",
    "        return &CT_MAP_TCP4;\n",
    "    return &CT_MAP_ANY4;\n",
    "}\n"
  ],
  "called_function_list": [],
  "call_depth": 0,
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
static __always_inline void *
get_ct_map4(const struct ipv4_ct_tuple *tuple)
{
	if (tuple->nexthdr == IPPROTO_TCP)
		return &CT_MAP_TCP4;

	return &CT_MAP_ANY4;
}
#endif
#endif
#endif /* __LIB_CONNTRACK_MAP_H_ */
