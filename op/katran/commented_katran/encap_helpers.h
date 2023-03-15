/* Copyright (c) Facebook, Inc. and its affiliates. All Rights Reserved,
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __ENCAP_HELPERS_H
#define __ENCAP_HELPERS_H

#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/udp.h>
#include <string.h>

#include "balancer_consts.h"
#include "bpf.h"
#include "bpf_endian.h"
#include "bpf_helpers.h"
#include "csum_helpers.h"

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 31,
  "endLine": 55,
  "File": "/home/sayandes/opened_extraction/examples/katran/encap_helpers.h",
  "funcName": "create_v4_hdr",
  "developer_inline_comments": [
    {
      "start_line": 1,
      "end_line": 15,
      "text": "/* Copyright (c) Facebook, Inc. and its affiliates. All Rights Reserved,\n *\n * This program is free software; you can redistribute it and/or modify\n * it under the terms of the GNU General Public License as published by\n * the Free Software Foundation; version 2 of the License.\n *\n * This program is distributed in the hope that it will be useful,\n * but WITHOUT ANY WARRANTY; without even the implied warranty of\n * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n * GNU General Public License for more details.\n *\n * You should have received a copy of the GNU General Public License along\n * with this program; if not, write to the Free Software Foundation, Inc.,\n * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.\n */"
    }
  ],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct iphdr *iph",
    " __u8 tos",
    " __u32 saddr",
    " __u32 daddr",
    " __u16 pkt_bytes",
    " __u8 proto"
  ],
  "output": "staticinlinevoid",
  "helper": [],
  "compatibleHookpoints": [
    "sk_msg",
    "perf_event",
    "lwt_in",
    "cgroup_sock_addr",
    "tracepoint",
    "cgroup_sock",
    "sched_cls",
    "cgroup_sysctl",
    "socket_filter",
    "sk_skb",
    "sock_ops",
    "kprobe",
    "sched_act",
    "flow_dissector",
    "raw_tracepoint",
    "raw_tracepoint_writable",
    "lwt_seg6local",
    "lwt_out",
    "lwt_xmit",
    "cgroup_skb",
    "cgroup_device",
    "sk_reuseport",
    "xdp"
  ],
  "source": [
    "static inline void create_v4_hdr (struct iphdr *iph, __u8 tos, __u32 saddr, __u32 daddr, __u16 pkt_bytes, __u8 proto)\n",
    "{\n",
    "    __u64 csum = 0;\n",
    "    iph->version = 4;\n",
    "    iph->ihl = 5;\n",
    "    iph->frag_off = 0;\n",
    "    iph->protocol = proto;\n",
    "    iph->check = 0;\n",
    "\n",
    "#ifdef COPY_INNER_PACKET_TOS\n",
    "    iph->tos = tos;\n",
    "\n",
    "#else\n",
    "    iph->tos = DEFAULT_TOS;\n",
    "\n",
    "#endif\n",
    "    iph->tot_len = bpf_htons (pkt_bytes + sizeof (struct iphdr));\n",
    "    iph->daddr = daddr;\n",
    "    iph->saddr = saddr;\n",
    "    iph->ttl = DEFAULT_TTL;\n",
    "    ipv4_csum_inline (iph, &csum);\n",
    "    iph->check = csum;\n",
    "}\n"
  ],
  "called_function_list": [
    "ipv4_csum_inline",
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
__attribute__((__always_inline__)) static inline void create_v4_hdr(
    struct iphdr* iph,
    __u8 tos,
    __u32 saddr,
    __u32 daddr,
    __u16 pkt_bytes,
    __u8 proto) {
  __u64 csum = 0;
  iph->version = 4;
  iph->ihl = 5;
  iph->frag_off = 0;
  iph->protocol = proto;
  iph->check = 0;
#ifdef COPY_INNER_PACKET_TOS
  iph->tos = tos;
#else
  iph->tos = DEFAULT_TOS;
#endif
  iph->tot_len = bpf_htons(pkt_bytes + sizeof(struct iphdr));
  iph->daddr = daddr;
  iph->saddr = saddr;
  iph->ttl = DEFAULT_TTL;
  ipv4_csum_inline(iph, &csum);
  iph->check = csum;
}

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 57,
  "endLine": 77,
  "File": "/home/sayandes/opened_extraction/examples/katran/encap_helpers.h",
  "funcName": "create_v6_hdr",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct ipv6hdr *ip6h",
    " __u8 tc",
    " __u32 *saddr",
    " __u32 *daddr",
    " __u16 payload_len",
    " __u8 proto"
  ],
  "output": "staticinlinevoid",
  "helper": [],
  "compatibleHookpoints": [
    "sk_msg",
    "perf_event",
    "lwt_in",
    "cgroup_sock_addr",
    "tracepoint",
    "cgroup_sock",
    "sched_cls",
    "cgroup_sysctl",
    "socket_filter",
    "sk_skb",
    "sock_ops",
    "kprobe",
    "sched_act",
    "flow_dissector",
    "raw_tracepoint",
    "raw_tracepoint_writable",
    "lwt_seg6local",
    "lwt_out",
    "lwt_xmit",
    "cgroup_skb",
    "cgroup_device",
    "sk_reuseport",
    "xdp"
  ],
  "source": [
    "static inline void create_v6_hdr (struct ipv6hdr *ip6h, __u8 tc, __u32 *saddr, __u32 *daddr, __u16 payload_len, __u8 proto)\n",
    "{\n",
    "    ip6h->version = 6;\n",
    "    memset (ip6h->flow_lbl, 0, sizeof (ip6h->flow_lbl));\n",
    "\n",
    "#ifdef COPY_INNER_PACKET_TOS\n",
    "    ip6h->priority = (tc & 0xF0) >> 4;\n",
    "    ip6h->flow_lbl[0] = (tc & 0x0F) << 4;\n",
    "\n",
    "#else\n",
    "    ip6h->priority = DEFAULT_TOS;\n",
    "\n",
    "#endif\n",
    "    ip6h->nexthdr = proto;\n",
    "    ip6h->payload_len = bpf_htons (payload_len);\n",
    "    ip6h->hop_limit = DEFAULT_TTL;\n",
    "    memcpy (ip6h->saddr.s6_addr32, saddr, 16);\n",
    "    memcpy (ip6h->daddr.s6_addr32, daddr, 16);\n",
    "}\n"
  ],
  "called_function_list": [
    "memcpy",
    "bpf_htons",
    "memset"
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
__attribute__((__always_inline__)) static inline void create_v6_hdr(
    struct ipv6hdr* ip6h,
    __u8 tc,
    __u32* saddr,
    __u32* daddr,
    __u16 payload_len,
    __u8 proto) {
  ip6h->version = 6;
  memset(ip6h->flow_lbl, 0, sizeof(ip6h->flow_lbl));
#ifdef COPY_INNER_PACKET_TOS
  ip6h->priority = (tc & 0xF0) >> 4;
  ip6h->flow_lbl[0] = (tc & 0x0F) << 4;
#else
  ip6h->priority = DEFAULT_TOS;
#endif
  ip6h->nexthdr = proto;
  ip6h->payload_len = bpf_htons(payload_len);
  ip6h->hop_limit = DEFAULT_TTL;
  memcpy(ip6h->saddr.s6_addr32, saddr, 16);
  memcpy(ip6h->daddr.s6_addr32, daddr, 16);
}

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 79,
  "endLine": 89,
  "File": "/home/sayandes/opened_extraction/examples/katran/encap_helpers.h",
  "funcName": "create_udp_hdr",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct udphdr *udph",
    " __u16 sport",
    " __u16 dport",
    " __u16 len",
    " __u16 csum"
  ],
  "output": "staticinlinevoid",
  "helper": [],
  "compatibleHookpoints": [
    "sk_msg",
    "perf_event",
    "lwt_in",
    "cgroup_sock_addr",
    "tracepoint",
    "cgroup_sock",
    "sched_cls",
    "cgroup_sysctl",
    "socket_filter",
    "sk_skb",
    "sock_ops",
    "kprobe",
    "sched_act",
    "flow_dissector",
    "raw_tracepoint",
    "raw_tracepoint_writable",
    "lwt_seg6local",
    "lwt_out",
    "lwt_xmit",
    "cgroup_skb",
    "cgroup_device",
    "sk_reuseport",
    "xdp"
  ],
  "source": [
    "static inline void create_udp_hdr (struct udphdr *udph, __u16 sport, __u16 dport, __u16 len, __u16 csum)\n",
    "{\n",
    "    udph->source = sport;\n",
    "    udph->dest = bpf_htons (dport);\n",
    "    udph->len = bpf_htons (len);\n",
    "    udph->check = csum;\n",
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
__attribute__((__always_inline__)) static inline void create_udp_hdr(
    struct udphdr* udph,
    __u16 sport,
    __u16 dport,
    __u16 len,
    __u16 csum) {
  udph->source = sport;
  udph->dest = bpf_htons(dport);
  udph->len = bpf_htons(len);
  udph->check = csum;
}

#endif // of __ENCAP_HELPERS_H
