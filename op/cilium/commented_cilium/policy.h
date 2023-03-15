/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright Authors of Cilium */

#ifndef __LIB_POLICY_H_
#define __LIB_POLICY_H_

#include <linux/icmp.h>

#include "drop.h"
#include "dbg.h"
#include "eps.h"
#include "maps.h"

#ifdef SOCKMAP
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
    },
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 15,
  "endLine": 79,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "policy_sk_egress",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [
    " map"
  ],
  "input": [
    "__u32 identity",
    " __u32 ip",
    " __u16 dport"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "map_lookup_elem",
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "sched_cls",
    "xdp",
    "sched_act"
  ],
  "source": [
    "static __always_inline int policy_sk_egress (__u32 identity, __u32 ip, __u16 dport)\n",
    "{\n",
    "    void *map = lookup_ip4_endpoint_policy_map (ip);\n",
    "    int dir = CT_EGRESS;\n",
    "    __u8 proto = IPPROTO_TCP;\n",
    "    struct policy_entry *policy;\n",
    "    struct policy_key key = {\n",
    "        .sec_label = identity,\n",
    "        .dport = dport,\n",
    "        .protocol = proto,\n",
    "        .egress = !dir,\n",
    "        .pad = 0,}\n",
    "    ;\n",
    "    if (!map)\n",
    "        return CTX_ACT_OK;\n",
    "    policy = map_lookup_elem (map, & key);\n",
    "    if (likely (policy)) {\n",
    "        __sync_fetch_and_add (&policy->packets, 1);\n",
    "        if (unlikely (policy->deny))\n",
    "            return DROP_POLICY_DENY;\n",
    "        return policy->proxy_port;\n",
    "    }\n",
    "    key.sec_label = 0;\n",
    "    policy = map_lookup_elem (map, & key);\n",
    "    if (likely (policy)) {\n",
    "        __sync_fetch_and_add (&policy->packets, 1);\n",
    "        if (unlikely (policy->deny))\n",
    "            return DROP_POLICY_DENY;\n",
    "        return policy->proxy_port;\n",
    "    }\n",
    "    key.sec_label = identity;\n",
    "    key.dport = 0;\n",
    "    key.protocol = 0;\n",
    "    policy = map_lookup_elem (map, & key);\n",
    "    if (likely (policy)) {\n",
    "        __sync_fetch_and_add (&policy->packets, 1);\n",
    "        if (unlikely (policy->deny))\n",
    "            return DROP_POLICY_DENY;\n",
    "        return CTX_ACT_OK;\n",
    "    }\n",
    "    key.sec_label = 0;\n",
    "    policy = map_lookup_elem (map, & key);\n",
    "    if (likely (policy)) {\n",
    "        __sync_fetch_and_add (&policy->packets, 1);\n",
    "        if (unlikely (policy->deny))\n",
    "            return DROP_POLICY_DENY;\n",
    "        return CTX_ACT_OK;\n",
    "    }\n",
    "    return DROP_POLICY;\n",
    "}\n"
  ],
  "called_function_list": [
    "likely",
    "lookup_ip4_endpoint_policy_map",
    "unlikely",
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
static __always_inline int
policy_sk_egress(__u32 identity, __u32 ip,  __u16 dport)
{
	void *map = lookup_ip4_endpoint_policy_map(ip);
	int dir = CT_EGRESS;
	__u8 proto = IPPROTO_TCP;
	struct policy_entry *policy;
	struct policy_key key = {
		.sec_label = identity,
		.dport = dport,
		.protocol = proto,
		.egress = !dir,
		.pad = 0,
	};

	if (!map)
		return CTX_ACT_OK;

	/* Start with L3/L4 lookup. */
	policy = map_lookup_elem(map, &key);
	if (likely(policy)) {
		/* FIXME: Need byte counter */
		__sync_fetch_and_add(&policy->packets, 1);
		if (unlikely(policy->deny))
			return DROP_POLICY_DENY;
		return policy->proxy_port;
	}

	/* L4-only lookup. */
	key.sec_label = 0;
	policy = map_lookup_elem(map, &key);
	if (likely(policy)) {
		/* FIXME: Need byte counter */
		__sync_fetch_and_add(&policy->packets, 1);
		if (unlikely(policy->deny))
			return DROP_POLICY_DENY;
		return policy->proxy_port;
	}
	key.sec_label = identity;

	/* If L4 policy check misses, fall back to L3. */
	key.dport = 0;
	key.protocol = 0;
	policy = map_lookup_elem(map, &key);
	if (likely(policy)) {
		/* FIXME: Need byte counter */
		__sync_fetch_and_add(&policy->packets, 1);
		if (unlikely(policy->deny))
			return DROP_POLICY_DENY;
		return CTX_ACT_OK;
	}

	/* Final fallback if allow-all policy is in place. */
	key.sec_label = 0;
	policy = map_lookup_elem(map, &key);
	if (likely(policy)) {
		/* FIXME: Need byte counter */
		__sync_fetch_and_add(&policy->packets, 1);
		if (unlikely(policy->deny))
			return DROP_POLICY_DENY;
		return CTX_ACT_OK;
	}

	return DROP_POLICY;
}
#else
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 81,
  "endLine": 87,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "account",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx",
    " struct policy_entry *policy"
  ],
  "output": "static__always_inlinevoid",
  "helper": [],
  "compatibleHookpoints": [
    "sched_cls",
    "cgroup_sock_addr",
    "cgroup_sysctl",
    "sk_msg",
    "xdp",
    "lwt_in",
    "flow_dissector",
    "sched_act",
    "tracepoint",
    "kprobe",
    "lwt_xmit",
    "sock_ops",
    "raw_tracepoint",
    "sk_reuseport",
    "raw_tracepoint_writable",
    "sk_skb",
    "lwt_out",
    "socket_filter",
    "cgroup_skb",
    "cgroup_device",
    "perf_event",
    "cgroup_sock",
    "lwt_seg6local"
  ],
  "source": [
    "static __always_inline void account (struct  __ctx_buff *ctx, struct policy_entry *policy)\n",
    "{\n",
    "    __sync_fetch_and_add (&policy->packets, 1);\n",
    "    __sync_fetch_and_add (&policy->bytes, ctx_full_len (ctx));\n",
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
static __always_inline void
account(struct __ctx_buff *ctx, struct policy_entry *policy)
{
	/* FIXME: Use per cpu counters */
	__sync_fetch_and_add(&policy->packets, 1);
	__sync_fetch_and_add(&policy->bytes, ctx_full_len(ctx));
}

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
    },
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 89,
  "endLine": 222,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "__policy_can_access",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [
    " map"
  ],
  "input": [
    "const void *map",
    " struct  __ctx_buff *ctx",
    " __u32 local_id",
    " __u32 remote_id",
    " __u16 dport",
    " __u8 proto",
    " int dir",
    " bool is_untracked_fragment",
    " __u8 *match_type"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "map_lookup_elem",
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "sched_cls",
    "xdp",
    "sched_act"
  ],
  "source": [
    "static __always_inline int __policy_can_access (const void *map, struct  __ctx_buff *ctx, __u32 local_id, __u32 remote_id, __u16 dport, __u8 proto, int dir, bool is_untracked_fragment, __u8 *match_type)\n",
    "{\n",
    "    struct policy_entry *policy;\n",
    "    struct policy_key key = {\n",
    "        .sec_label = remote_id,\n",
    "        .dport = dport,\n",
    "        .protocol = proto,\n",
    "        .egress = !dir,\n",
    "        .pad = 0,}\n",
    "    ;\n",
    "\n",
    "#ifdef ALLOW_ICMP_FRAG_NEEDED\n",
    "    if (proto == IPPROTO_ICMP) {\n",
    "        void *data, *data_end;\n",
    "        struct icmphdr icmphdr __align_stack_8;\n",
    "        struct iphdr *ip4;\n",
    "        __u32 off;\n",
    "        if (!revalidate_data (ctx, &data, &data_end, &ip4))\n",
    "            return DROP_INVALID;\n",
    "        off = ((void *) ip4 - data) + ipv4_hdrlen (ip4);\n",
    "        if (ctx_load_bytes (ctx, off, &icmphdr, sizeof (icmphdr)) < 0)\n",
    "            return DROP_INVALID;\n",
    "        if (icmphdr.type == ICMP_DEST_UNREACH && icmphdr.code == ICMP_FRAG_NEEDED)\n",
    "            return CTX_ACT_OK;\n",
    "    }\n",
    "\n",
    "#endif /* ALLOW_ICMP_FRAG_NEEDED */\n",
    "\n",
    "#ifdef ENABLE_ICMP_RULE\n",
    "    if (proto == IPPROTO_ICMP) {\n",
    "        void *data, *data_end;\n",
    "        struct iphdr *ip4;\n",
    "        struct icmphdr icmphdr __align_stack_8;\n",
    "        __u32 off;\n",
    "        if (!revalidate_data (ctx, &data, &data_end, &ip4))\n",
    "            return DROP_INVALID;\n",
    "        off = ((void *) ip4 - data) + ipv4_hdrlen (ip4);\n",
    "        if (ctx_load_bytes (ctx, off, &icmphdr, sizeof (icmphdr)) < 0)\n",
    "            return DROP_INVALID;\n",
    "        key.dport = (__u16) (icmphdr.type << 8);\n",
    "    }\n",
    "    else if (proto == IPPROTO_ICMPV6) {\n",
    "        void *data, *data_end;\n",
    "        struct ipv6hdr *ip6;\n",
    "        __u32 off;\n",
    "        __u8 icmp_type;\n",
    "        if (!revalidate_data (ctx, &data, &data_end, &ip6))\n",
    "            return DROP_INVALID;\n",
    "        off = ((void *) ip6 - data) + ipv6_hdrlen (ctx, &ip6->nexthdr);\n",
    "        if (ctx_load_bytes (ctx, off, &icmp_type, sizeof (icmp_type)) < 0)\n",
    "            return DROP_INVALID;\n",
    "        key.dport = (__u16) (icmp_type << 8);\n",
    "    }\n",
    "\n",
    "#endif /* ENABLE_ICMP_RULE */\n",
    "    if (!is_untracked_fragment) {\n",
    "        policy = map_lookup_elem (map, & key);\n",
    "        if (likely (policy)) {\n",
    "            cilium_dbg3 (ctx, DBG_L4_CREATE, remote_id, local_id, dport << 16 | proto);\n",
    "            account (ctx, policy);\n",
    "            *match_type = POLICY_MATCH_L3_L4;\n",
    "            if (unlikely (policy->deny))\n",
    "                return DROP_POLICY_DENY;\n",
    "            return policy->proxy_port;\n",
    "        }\n",
    "        key.sec_label = 0;\n",
    "        policy = map_lookup_elem (map, & key);\n",
    "        if (likely (policy)) {\n",
    "            account (ctx, policy);\n",
    "            *match_type = POLICY_MATCH_L4_ONLY;\n",
    "            if (unlikely (policy->deny))\n",
    "                return DROP_POLICY_DENY;\n",
    "            return policy->proxy_port;\n",
    "        }\n",
    "        key.sec_label = remote_id;\n",
    "    }\n",
    "    key.dport = 0;\n",
    "    key.protocol = 0;\n",
    "    policy = map_lookup_elem (map, & key);\n",
    "    if (likely (policy)) {\n",
    "        account (ctx, policy);\n",
    "        *match_type = POLICY_MATCH_L3_ONLY;\n",
    "        if (unlikely (policy->deny))\n",
    "            return DROP_POLICY_DENY;\n",
    "        return CTX_ACT_OK;\n",
    "    }\n",
    "    key.sec_label = 0;\n",
    "    policy = map_lookup_elem (map, & key);\n",
    "    if (policy) {\n",
    "        account (ctx, policy);\n",
    "        *match_type = POLICY_MATCH_ALL;\n",
    "        if (unlikely (policy->deny))\n",
    "            return DROP_POLICY_DENY;\n",
    "        return CTX_ACT_OK;\n",
    "    }\n",
    "    if (ctx_load_meta (ctx, CB_POLICY))\n",
    "        return CTX_ACT_OK;\n",
    "    if (is_untracked_fragment)\n",
    "        return DROP_FRAG_NOSUPPORT;\n",
    "    return DROP_POLICY;\n",
    "}\n"
  ],
  "called_function_list": [
    "account",
    "revalidate_data",
    "cilium_dbg3",
    "unlikely",
    "ctx_load_meta",
    "ipv6_hdrlen",
    "ipv4_hdrlen",
    "ctx_load_bytes",
    "likely"
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
static __always_inline int
__policy_can_access(const void *map, struct __ctx_buff *ctx, __u32 local_id,
		    __u32 remote_id, __u16 dport, __u8 proto, int dir,
		    bool is_untracked_fragment, __u8 *match_type)
{
	struct policy_entry *policy;
	struct policy_key key = {
		.sec_label = remote_id,
		.dport = dport,
		.protocol = proto,
		.egress = !dir,
		.pad = 0,
	};

#ifdef ALLOW_ICMP_FRAG_NEEDED
	/* When ALLOW_ICMP_FRAG_NEEDED is defined we allow all packets
	 * of ICMP type 3 code 4 - Fragmentation Needed.
	 */
	if (proto == IPPROTO_ICMP) {
		void *data, *data_end;
		struct icmphdr icmphdr __align_stack_8;
		struct iphdr *ip4;
		__u32 off;

		if (!revalidate_data(ctx, &data, &data_end, &ip4))
			return DROP_INVALID;

		off = ((void *)ip4 - data) + ipv4_hdrlen(ip4);
		if (ctx_load_bytes(ctx, off, &icmphdr, sizeof(icmphdr)) < 0)
			return DROP_INVALID;

		if (icmphdr.type == ICMP_DEST_UNREACH &&
		    icmphdr.code == ICMP_FRAG_NEEDED)
			return CTX_ACT_OK;
	}
#endif /* ALLOW_ICMP_FRAG_NEEDED */

#ifdef ENABLE_ICMP_RULE
	if (proto == IPPROTO_ICMP) {
		void *data, *data_end;
		struct iphdr *ip4;
		struct icmphdr icmphdr __align_stack_8;
		__u32 off;

		if (!revalidate_data(ctx, &data, &data_end, &ip4))
			return DROP_INVALID;
		off = ((void *)ip4 - data) + ipv4_hdrlen(ip4);
		if (ctx_load_bytes(ctx, off, &icmphdr, sizeof(icmphdr)) < 0)
			return DROP_INVALID;

		/* Convert from unsigned char to unsigned short considering byte order(little-endian).
		 * In the little-endian case, for example, 2byte data "AB" convert to "BA".
		 * Therefore, the "icmp_type" should be shifted not just casting.
		 */
		key.dport = (__u16)(icmphdr.type << 8);
	} else if (proto == IPPROTO_ICMPV6) {
		void *data, *data_end;
		struct ipv6hdr *ip6;
		__u32 off;
		__u8 icmp_type;

		if (!revalidate_data(ctx, &data, &data_end, &ip6))
			return DROP_INVALID;
		off = ((void *)ip6 - data) + ipv6_hdrlen(ctx, &ip6->nexthdr);
		if (ctx_load_bytes(ctx, off, &icmp_type, sizeof(icmp_type)) < 0)
			return DROP_INVALID;

		/* Convert from unsigned char to unsigned short considering byte order(little-endian).
		 * In the little-endian case, for example, 2byte data "AB" convert to "BA".
		 * Therefore, the "icmp_type" should be shifted not just casting.
		 */
		key.dport = (__u16)(icmp_type << 8);
	}
#endif /* ENABLE_ICMP_RULE */

	/* L4 lookup can't be done on untracked fragments. */
	if (!is_untracked_fragment) {
		/* Start with L3/L4 lookup. */
		policy = map_lookup_elem(map, &key);
		if (likely(policy)) {
			cilium_dbg3(ctx, DBG_L4_CREATE, remote_id, local_id,
				    dport << 16 | proto);

			account(ctx, policy);
			*match_type = POLICY_MATCH_L3_L4;
			if (unlikely(policy->deny))
				return DROP_POLICY_DENY;
			return policy->proxy_port;
		}

		/* L4-only lookup. */
		key.sec_label = 0;
		policy = map_lookup_elem(map, &key);
		if (likely(policy)) {
			account(ctx, policy);
			*match_type = POLICY_MATCH_L4_ONLY;
			if (unlikely(policy->deny))
				return DROP_POLICY_DENY;
			return policy->proxy_port;
		}
		key.sec_label = remote_id;
	}

	/* If L4 policy check misses, fall back to L3. */
	key.dport = 0;
	key.protocol = 0;
	policy = map_lookup_elem(map, &key);
	if (likely(policy)) {
		account(ctx, policy);
		*match_type = POLICY_MATCH_L3_ONLY;
		if (unlikely(policy->deny))
			return DROP_POLICY_DENY;
		return CTX_ACT_OK;
	}

	/* Final fallback if allow-all policy is in place. */
	key.sec_label = 0;
	policy = map_lookup_elem(map, &key);
	if (policy) {
		account(ctx, policy);
		*match_type = POLICY_MATCH_ALL;
		if (unlikely(policy->deny))
			return DROP_POLICY_DENY;
		return CTX_ACT_OK;
	}

	if (ctx_load_meta(ctx, CB_POLICY))
		return CTX_ACT_OK;

	if (is_untracked_fragment)
		return DROP_FRAG_NOSUPPORT;

	return DROP_POLICY;
}

/**
 * Determine whether the policy allows this traffic on ingress.
 * @arg ctx		Packet to allow or deny
 * @arg src_id		Source security identity for this packet
 * @arg dst_id		Destination security identity for this packet
 * @arg dport		Destination port of this packet
 * @arg proto		L3 Protocol of this packet
 * @arg is_untracked_fragment	True if packet is a TCP/UDP datagram fragment
 *				AND IPv4 fragment tracking is disabled
 * @arg match_type		Pointer to store layers used for policy match
 *
 * Returns:
 *   - Positive integer indicating the proxy_port to handle this traffic
 *   - CTX_ACT_OK if the policy allows this traffic based only on labels/L3/L4
 *   - Negative error code if the packet should be dropped
 */
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 240,
  "endLine": 264,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "policy_can_access_ingress",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx",
    " __u32 src_id",
    " __u32 dst_id",
    " __u16 dport",
    " __u8 proto",
    " bool is_untracked_fragment",
    " __u8 *match_type",
    " __u8 *audited"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "sched_cls",
    "xdp",
    "sched_act"
  ],
  "source": [
    "static __always_inline int policy_can_access_ingress (struct  __ctx_buff *ctx, __u32 src_id, __u32 dst_id, __u16 dport, __u8 proto, bool is_untracked_fragment, __u8 *match_type, __u8 *audited)\n",
    "{\n",
    "    int ret;\n",
    "    ret = __policy_can_access (& POLICY_MAP, ctx, dst_id, src_id, dport, proto, CT_INGRESS, is_untracked_fragment, match_type);\n",
    "    if (ret >= CTX_ACT_OK)\n",
    "        return ret;\n",
    "    cilium_dbg (ctx, DBG_POLICY_DENIED, src_id, dst_id);\n",
    "    *audited = 0;\n",
    "\n",
    "#ifdef POLICY_AUDIT_MODE\n",
    "    if (IS_ERR (ret)) {\n",
    "        ret = CTX_ACT_OK;\n",
    "        *audited = 1;\n",
    "    }\n",
    "\n",
    "#endif\n",
    "    return ret;\n",
    "}\n"
  ],
  "called_function_list": [
    "__policy_can_access",
    "IS_ERR",
    "cilium_dbg"
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
static __always_inline int
policy_can_access_ingress(struct __ctx_buff *ctx, __u32 src_id, __u32 dst_id,
			  __u16 dport, __u8 proto, bool is_untracked_fragment,
			  __u8 *match_type, __u8 *audited)
{
	int ret;

	ret = __policy_can_access(&POLICY_MAP, ctx, dst_id, src_id, dport,
				  proto, CT_INGRESS, is_untracked_fragment,
				  match_type);
	if (ret >= CTX_ACT_OK)
		return ret;

	cilium_dbg(ctx, DBG_POLICY_DENIED, src_id, dst_id);

	*audited = 0;
#ifdef POLICY_AUDIT_MODE
	if (IS_ERR(ret)) {
		ret = CTX_ACT_OK;
		*audited = 1;
	}
#endif

	return ret;
}

#ifdef ENCAP_IFINDEX
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 267,
  "endLine": 270,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "is_encap",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "__u16 dport",
    " __u8 proto"
  ],
  "output": "static__always_inlinebool",
  "helper": [],
  "compatibleHookpoints": [
    "sched_cls",
    "cgroup_sock_addr",
    "cgroup_sysctl",
    "sk_msg",
    "xdp",
    "lwt_in",
    "flow_dissector",
    "sched_act",
    "tracepoint",
    "kprobe",
    "lwt_xmit",
    "sock_ops",
    "raw_tracepoint",
    "sk_reuseport",
    "raw_tracepoint_writable",
    "sk_skb",
    "lwt_out",
    "socket_filter",
    "cgroup_skb",
    "cgroup_device",
    "perf_event",
    "cgroup_sock",
    "lwt_seg6local"
  ],
  "source": [
    "static __always_inline bool is_encap (__u16 dport, __u8 proto)\n",
    "{\n",
    "    return proto == IPPROTO_UDP && dport == bpf_htons (TUNNEL_PORT);\n",
    "}\n"
  ],
  "called_function_list": [
    "bpf_htons"
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
static __always_inline bool is_encap(__u16 dport, __u8 proto)
{
	return proto == IPPROTO_UDP && dport == bpf_htons(TUNNEL_PORT);
}
#endif

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 273,
  "endLine": 296,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "policy_can_egress",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx",
    " __u32 src_id",
    " __u32 dst_id",
    " __u16 dport",
    " __u8 proto",
    " __u8 *match_type",
    " __u8 *audited"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "sched_cls",
    "xdp",
    "sched_act"
  ],
  "source": [
    "static __always_inline int policy_can_egress (struct  __ctx_buff *ctx, __u32 src_id, __u32 dst_id, __u16 dport, __u8 proto, __u8 *match_type, __u8 *audited)\n",
    "{\n",
    "    int ret;\n",
    "\n",
    "#ifdef ENCAP_IFINDEX\n",
    "    if (src_id != HOST_ID && is_encap (dport, proto))\n",
    "        return DROP_ENCAP_PROHIBITED;\n",
    "\n",
    "#endif\n",
    "    ret = __policy_can_access (& POLICY_MAP, ctx, src_id, dst_id, dport, proto, CT_EGRESS, false, match_type);\n",
    "    if (ret >= 0)\n",
    "        return ret;\n",
    "    cilium_dbg (ctx, DBG_POLICY_DENIED, src_id, dst_id);\n",
    "    *audited = 0;\n",
    "\n",
    "#ifdef POLICY_AUDIT_MODE\n",
    "    if (IS_ERR (ret)) {\n",
    "        ret = CTX_ACT_OK;\n",
    "        *audited = 1;\n",
    "    }\n",
    "\n",
    "#endif\n",
    "    return ret;\n",
    "}\n"
  ],
  "called_function_list": [
    "__policy_can_access",
    "IS_ERR",
    "is_encap",
    "cilium_dbg"
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
static __always_inline int
policy_can_egress(struct __ctx_buff *ctx, __u32 src_id, __u32 dst_id,
		  __u16 dport, __u8 proto, __u8 *match_type, __u8 *audited)
{
	int ret;

#ifdef ENCAP_IFINDEX
	if (src_id != HOST_ID && is_encap(dport, proto))
		return DROP_ENCAP_PROHIBITED;
#endif
	ret = __policy_can_access(&POLICY_MAP, ctx, src_id, dst_id, dport,
				  proto, CT_EGRESS, false, match_type);
	if (ret >= 0)
		return ret;
	cilium_dbg(ctx, DBG_POLICY_DENIED, src_id, dst_id);
	*audited = 0;
#ifdef POLICY_AUDIT_MODE
	if (IS_ERR(ret)) {
		ret = CTX_ACT_OK;
		*audited = 1;
	}
#endif
	return ret;
}

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 298,
  "endLine": 305,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "policy_can_egress6",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx",
    " const struct ipv6_ct_tuple *tuple",
    " __u32 src_id",
    " __u32 dst_id",
    " __u8 *match_type",
    " __u8 *audited"
  ],
  "output": "static__always_inlineint",
  "helper": [],
  "compatibleHookpoints": [
    "sched_cls",
    "cgroup_sock_addr",
    "cgroup_sysctl",
    "sk_msg",
    "xdp",
    "lwt_in",
    "flow_dissector",
    "sched_act",
    "tracepoint",
    "kprobe",
    "lwt_xmit",
    "sock_ops",
    "raw_tracepoint",
    "sk_reuseport",
    "raw_tracepoint_writable",
    "sk_skb",
    "lwt_out",
    "socket_filter",
    "cgroup_skb",
    "cgroup_device",
    "perf_event",
    "cgroup_sock",
    "lwt_seg6local"
  ],
  "source": [
    "static __always_inline int policy_can_egress6 (struct  __ctx_buff *ctx, const struct ipv6_ct_tuple *tuple, __u32 src_id, __u32 dst_id, __u8 *match_type, __u8 *audited)\n",
    "{\n",
    "    return policy_can_egress (ctx, src_id, dst_id, tuple->dport, tuple->nexthdr, match_type, audited);\n",
    "}\n"
  ],
  "called_function_list": [
    "policy_can_egress"
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
static __always_inline int policy_can_egress6(struct __ctx_buff *ctx,
					      const struct ipv6_ct_tuple *tuple,
					      __u32 src_id, __u32 dst_id,
					      __u8 *match_type, __u8 *audited)
{
	return policy_can_egress(ctx, src_id, dst_id, tuple->dport,
				 tuple->nexthdr, match_type, audited);
}

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 307,
  "endLine": 314,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "policy_can_egress4",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx",
    " const struct ipv4_ct_tuple *tuple",
    " __u32 src_id",
    " __u32 dst_id",
    " __u8 *match_type",
    " __u8 *audited"
  ],
  "output": "static__always_inlineint",
  "helper": [],
  "compatibleHookpoints": [
    "sched_cls",
    "cgroup_sock_addr",
    "cgroup_sysctl",
    "sk_msg",
    "xdp",
    "lwt_in",
    "flow_dissector",
    "sched_act",
    "tracepoint",
    "kprobe",
    "lwt_xmit",
    "sock_ops",
    "raw_tracepoint",
    "sk_reuseport",
    "raw_tracepoint_writable",
    "sk_skb",
    "lwt_out",
    "socket_filter",
    "cgroup_skb",
    "cgroup_device",
    "perf_event",
    "cgroup_sock",
    "lwt_seg6local"
  ],
  "source": [
    "static __always_inline int policy_can_egress4 (struct  __ctx_buff *ctx, const struct ipv4_ct_tuple *tuple, __u32 src_id, __u32 dst_id, __u8 *match_type, __u8 *audited)\n",
    "{\n",
    "    return policy_can_egress (ctx, src_id, dst_id, tuple->dport, tuple->nexthdr, match_type, audited);\n",
    "}\n"
  ],
  "called_function_list": [
    "policy_can_egress"
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
static __always_inline int policy_can_egress4(struct __ctx_buff *ctx,
					      const struct ipv4_ct_tuple *tuple,
					      __u32 src_id, __u32 dst_id,
					      __u8 *match_type, __u8 *audited)
{
	return policy_can_egress(ctx, src_id, dst_id, tuple->dport,
				 tuple->nexthdr, match_type, audited);
}

/**
 * Mark ctx to skip policy enforcement
 * @arg ctx	packet
 *
 * Will cause the packet to ignore the policy enforcement verdict for allow rules and
 * be considered accepted despite of the policy outcome. Has no effect on deny rules.
 */
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 323,
  "endLine": 326,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "policy_mark_skip",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlinevoid",
  "helper": [],
  "compatibleHookpoints": [
    "sched_cls",
    "cgroup_sock_addr",
    "cgroup_sysctl",
    "sk_msg",
    "xdp",
    "lwt_in",
    "flow_dissector",
    "sched_act",
    "tracepoint",
    "kprobe",
    "lwt_xmit",
    "sock_ops",
    "raw_tracepoint",
    "sk_reuseport",
    "raw_tracepoint_writable",
    "sk_skb",
    "lwt_out",
    "socket_filter",
    "cgroup_skb",
    "cgroup_device",
    "perf_event",
    "cgroup_sock",
    "lwt_seg6local"
  ],
  "source": [
    "static __always_inline void policy_mark_skip (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    ctx_store_meta (ctx, CB_POLICY, 1);\n",
    "}\n"
  ],
  "called_function_list": [
    "ctx_store_meta"
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
static __always_inline void policy_mark_skip(struct __ctx_buff *ctx)
{
	ctx_store_meta(ctx, CB_POLICY, 1);
}

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 328,
  "endLine": 331,
  "File": "/home/sayandes/opened_extraction/examples/cilium/lib/policy.h",
  "funcName": "policy_clear_mark",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlinevoid",
  "helper": [],
  "compatibleHookpoints": [
    "sched_cls",
    "cgroup_sock_addr",
    "cgroup_sysctl",
    "sk_msg",
    "xdp",
    "lwt_in",
    "flow_dissector",
    "sched_act",
    "tracepoint",
    "kprobe",
    "lwt_xmit",
    "sock_ops",
    "raw_tracepoint",
    "sk_reuseport",
    "raw_tracepoint_writable",
    "sk_skb",
    "lwt_out",
    "socket_filter",
    "cgroup_skb",
    "cgroup_device",
    "perf_event",
    "cgroup_sock",
    "lwt_seg6local"
  ],
  "source": [
    "static __always_inline void policy_clear_mark (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    ctx_store_meta (ctx, CB_POLICY, 0);\n",
    "}\n"
  ],
  "called_function_list": [
    "ctx_store_meta"
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
static __always_inline void policy_clear_mark(struct __ctx_buff *ctx)
{
	ctx_store_meta(ctx, CB_POLICY, 0);
}
#endif /* SOCKMAP */
#endif
