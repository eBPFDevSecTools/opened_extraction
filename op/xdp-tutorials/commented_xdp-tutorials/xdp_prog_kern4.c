/* SPDX-License-Identifier: GPL-2.0 */
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

#include "xdp_data_access_helpers.h"

SEC("xdp_test1")
/* 
 OPENED COMMENT BEGIN 
{
  "capability": [],
  "helperCallParams": {},
  "startLine": 8,
  "endLine": 22,
  "File": "/root/examples/xdp-tutorials/xdp_prog_kern4.c",
  "funcName": "_xdp_test1",
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct xdp_md *ctx"
  ],
  "output": "int",
  "helper": [],
  "compatibleHookpoints": [
    "All_hookpoints"
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
int _xdp_test1(struct xdp_md *ctx)
{
//	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	unsigned int len;
//	len = (data_end - data) - 2 ; // Not working, due to verifier
	len = 12;

	unsigned int offset = len - 2;

	if (ctx_store_bytes(ctx, offset, data, 2, 0) < 0)
		return XDP_ABORTED;

	return XDP_PASS;
}

