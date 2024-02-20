/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM skb

#if !defined(_TRACE_SKB_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_SKB_H

#include <linux/mm_types.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/tracepoint.h>

#undef FN
#define FN(reason)	TRACE_DEFINE_ENUM(SKB_DROP_REASON_##reason);
DEFINE_DROP_REASON(FN, FN)

#undef FN
#undef FNe
#define FN(reason)	{ SKB_DROP_REASON_##reason, #reason },
#define FNe(reason)	{ SKB_DROP_REASON_##reason, #reason }

/*
 * Tracepoint for free an sk_buff:
 */
TRACE_EVENT(kfree_skb,

	TP_PROTO(struct sk_buff *skb, void *location,
		 enum skb_drop_reason reason),

	TP_ARGS(skb, location, reason),

	TP_STRUCT__entry(
		__field(void *,		skbaddr)
		__field(void *,		location)
		__field(unsigned short,	protocol)
		__field(enum skb_drop_reason,	reason)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
		__entry->location = location;
		__entry->protocol = ntohs(skb->protocol);
		__entry->reason = reason;
	),

	TP_printk("skbaddr=%p protocol=%u location=%pS reason: %s",
		  __entry->skbaddr, __entry->protocol, __entry->location,
		  __print_symbolic(__entry->reason,
				   DEFINE_DROP_REASON(FN, FNe)))
);

#undef FN
#undef FNe

TRACE_EVENT(consume_skb,

	TP_PROTO(struct sk_buff *skb, void *location),

	TP_ARGS(skb, location),

	TP_STRUCT__entry(
		__field(	void *,	skbaddr)
		__field(	void *,	location)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
		__entry->location = location;
	),

	TP_printk("skbaddr=%p location=%pS", __entry->skbaddr, __entry->location)
);

TRACE_EVENT(skb_copy_datagram_iovec,

	TP_PROTO(const struct sk_buff *skb, int len),

	TP_ARGS(skb, len),

	TP_STRUCT__entry(
		__field(	const void *,		skbaddr		)
		__field(	int,			len		)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
		__entry->len = len;
	),

	TP_printk("skbaddr=%p len=%d", __entry->skbaddr, __entry->len)
);

TRACE_EVENT(napi_alloc_frag,

	TP_PROTO(void* location, const struct page *page, const void* data, unsigned int len),

	TP_ARGS(location, page, data, len),

	TP_STRUCT__entry(
		__field(	void *,	location)
		__field(	unsigned long,	physaddr)
		__field(	const void *,		pageaddr		)
		__field(	const void *,		dataaddr		)
		__field(	int,			len		)
	),

	TP_fast_assign(
		__entry->location = location;
		__entry->pageaddr = page;
		__entry->dataaddr = data;
		__entry->physaddr = virt_to_phys(data);
		__entry->len = len;
	),

	TP_printk("location=%pS page=%p ptr=%p physaddr=%llx len=%d", __entry->location, __entry->pageaddr, __entry->dataaddr, __entry->physaddr, __entry->len)
);

TRACE_EVENT(netdev_alloc_frag,

	TP_PROTO(void* location, const struct page *page, const void* data, unsigned int len),

	TP_ARGS(location, page, data, len),

	TP_STRUCT__entry(
		__field(	void *,		location		)
		__field(	const void *,		pageaddr		)
		__field(	const void *,		dataaddr		)
		__field(	int,			len		)
	),

	TP_fast_assign(
		__entry->location = location;
		__entry->pageaddr = page;
		__entry->dataaddr = data;
		__entry->len = len;
	),

	TP_printk("location=%pS page=%p ptr=%p,len=%d", __entry->location, __entry->pageaddr, __entry->dataaddr, __entry->len)
);

TRACE_EVENT(skb_head_kmalloc,

	TP_PROTO(void* location, const void* data, unsigned int len),

	TP_ARGS(location, data, len),

	TP_STRUCT__entry(
		__field( void*, location )
		__field(	const void *,		dataaddr		)
		__field(	int,			len		)
	),

	TP_fast_assign(
		__entry->location = location;
		__entry->dataaddr = data;
		__entry->len = len;
	),

	TP_printk("location=%pS ptr=%p len=%d", __entry->location, __entry->dataaddr, __entry->len)
);

TRACE_EVENT(skb_head_frag_free,

	TP_PROTO(const struct sk_buff *skb, const struct page *page, const void* data),


	TP_ARGS(skb, page, data),

	TP_STRUCT__entry(
		__field( const void*, skbaddr )
		__field( const void*, pageaddr )
		__field(	const void *,		dataaddr		)
	),

	TP_fast_assign(
		__entry->dataaddr = data;
		__entry->pageaddr = page;
		__entry->skbaddr = skb;
	),

	TP_printk("skb=%p page=%p ptr=%p", __entry->skbaddr, __entry->pageaddr, __entry->dataaddr)
);

TRACE_EVENT(skb_head_kfree,

	TP_PROTO(const struct sk_buff *skb, const void* data),


	TP_ARGS(skb, data),

	TP_STRUCT__entry(
		__field( const void*, skbaddr )
		__field(	const void *,		dataaddr		)
	),

	TP_fast_assign(
		__entry->dataaddr = data;
		__entry->skbaddr = skb;
	),

	TP_printk("skb=%p ptr=%p", __entry->skbaddr, __entry->dataaddr)
);

TRACE_EVENT(finalize_skb_around,

	TP_PROTO(const struct sk_buff *skb, const void* data, unsigned int size),


	TP_ARGS(skb, data, size),

	TP_STRUCT__entry(
		__field( const void*, skbaddr )
		__field(const void *,		dataaddr		)
		__field(unsigned int,		size		)
	),

	TP_fast_assign(
		__entry->dataaddr = data;
		__entry->skbaddr = skb;
		__entry->size = size;
	),

	TP_printk("skb=%p ptr=%p size=%d", __entry->skbaddr, __entry->dataaddr, __entry->size)
);

TRACE_EVENT(skb_small_head_alloc,

	TP_PROTO(void* location, const void* data, unsigned int len),

	TP_ARGS(location, data, len),

	TP_STRUCT__entry(
		__field( void*, location )
		__field(	const void *,		dataaddr		)
		__field(	int,			len		)
	),

	TP_fast_assign(
		__entry->location = location;
		__entry->dataaddr = data;
		__entry->len = len;
	),

	TP_printk("location=%pS ptr=%p len=%d", __entry->location, __entry->dataaddr, __entry->len)
);

TRACE_EVENT(skb_small_head_free,

	TP_PROTO(void* location, const void* data),

	TP_ARGS(location, data),

	TP_STRUCT__entry(
		__field( void*, location )
		__field(	const void *,		dataaddr		)
	),

	TP_fast_assign(
		__entry->location = location;
		__entry->dataaddr = data;
	),

	TP_printk("location=%pS ptr=%p", __entry->location, __entry->dataaddr)
);

TRACE_EVENT(alloc_skb_with_frags,

	TP_PROTO(void* location, const struct sk_buff* skb, unsigned int head_len, unsigned int data_len),

	TP_ARGS(location, skb, head_len, data_len),

	TP_STRUCT__entry(
		__field(	void *,	location)
		__field(	const void *,		skbaddr		)
		__field(	int,			head_len		)
		__field(	int,			data_len		)
	),

	TP_fast_assign(
		__entry->location = location;
		__entry->skbaddr = skb;
		__entry->head_len = head_len;
		__entry->data_len = data_len;
	),

	TP_printk("location=%pS skb=%p head_len=%d data_len=%d", __entry->location, __entry->skbaddr, __entry->head_len, __entry->data_len)
);


TRACE_EVENT(skb_release_data_info,

	TP_PROTO(void* location, const struct sk_buff* skb, unsigned int len, unsigned int head_len, unsigned int data_len),

	TP_ARGS(location, skb, len, head_len, data_len),

	TP_STRUCT__entry(
		__field(	void *,	location)
		__field(	const void *,		skbaddr		)
		__field(	int,			len		)
		__field(	int,			head_len		)
		__field(	int,			data_len		)
	),

	TP_fast_assign(
		__entry->location = location;
		__entry->skbaddr = skb;
		__entry->len = len;
		__entry->head_len = head_len;
		__entry->data_len = data_len;
	),

	TP_printk("location=%pS skb=%p, len=%d head_len=%d data_len=%d", __entry->location, __entry->skbaddr, __entry->len, __entry->head_len, __entry->data_len)
);

TRACE_EVENT(kfree_skb_partial,

	TP_PROTO(void* location, const struct sk_buff* skb, bool head_stolen),

	TP_ARGS(location, skb, head_stolen),

	TP_STRUCT__entry(
		__field(	void *,	location)
		__field(	const void *,		skbaddr		)
		__field(	bool,			head_stolen		)
	),

	TP_fast_assign(
		__entry->location = location;
		__entry->skbaddr = skb;
		__entry->head_stolen = head_stolen;
	),

	TP_printk("location=%pS skb=%p, head_stolen=%d", __entry->location, __entry->skbaddr, __entry->head_stolen)
);


#endif /* _TRACE_SKB_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
