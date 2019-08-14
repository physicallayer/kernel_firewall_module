#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sanghee Choi");
MODULE_DESCRIPTION("A simple Linux firewall module.");
MODULE_VERSION("0.01");

static struct nf_hook_ops *nfho = NULL;


static unsigned int hfunc(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr *iph;
	struct udphdr *udph;
	if (!skb)
		return NF_ACCEPT;

    iph = ip_hdr(skb);
	if (iph->protocol == IPPROTO_ICMP) {
        printk(KERN_INFO "Drop ICMP!\n");
		return NF_DROP;
	}

    return NF_ACCEPT;
    /*
	iph = ip_hdr(skb);
	if (iph->protocol == IPPROTO_UDP) {
		udph = udp_hdr(skb);
		if (ntohs(udph->dest) == 53) {
			return NF_ACCEPT;
		}
	}
	else if (iph->protocol == IPPROTO_TCP) {
		return NF_ACCEPT;
	}
	
	return NF_DROP;*/
}


static int __init LKM_init(void) {
    printk(KERN_INFO "Init!\n");

    nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);

    /* Netfilter hook */
    nfho->hook      = (nf_hookfn*)hfunc;
    nfho->hooknum   = NF_INET_PRE_ROUTING;
    nfho->pf        = PF_INET;
    nfho->priority  = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, nfho);

 
    return 0;
}
static void __exit LKM_exit(void) {
    nf_unregister_net_hook(&init_net, nfho);
    kfree(nfho);
    printk(KERN_INFO "Exit!\n");
}

module_init(LKM_init);
module_exit(LKM_exit);