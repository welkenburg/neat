protocols = {1:"ICMP",6:"TCP",17:"UDP"}

#TOS
precedence = {
	0: "Routine",
	1: "Priority", 
	2: "Immediate", 
	3: "Flash", 
	4: "Flash override", 
	5: "CRITIC/ECP",
	6: "Internetwork control", 
	7: "Network control"
}
delay = {0: "Normal delay", 1: "Low delay"}
throughput = {0: "Normal throughput", 1: "High throughput"}
reliability = {0: "Normal reliability", 1: "High reliability"}
cost = {0: "Normal monetary cost", 1: "Minimize monetary cost"}

#icmp
typeOfControl = {
	0:'Echo Reply (used to ping)',
	1:'Reserved',
	2:'Reserved',
	3:{
		'name':'Destination Unreachable',
		0:'Destination network unreachable',
		1:'Destination host unreachable',
		2:'Destination protocol unreachable',
		3:'Destination port unreachable',
		4:'Fragmentation required, and DF flag set',
		5:'Source route failed',
		6:'Destination network unknown',
		7:'Destination host unknown',
		8:'Source host isolated',
		9:'Network administratively prohibited',
		10:'Host administratively prohibited',
		11:'Network unreachable for ToS',
		12:'Host unreachable for ToS',
		13:'Communication administratively prohibited',
		14:'Host Precedence Violation',
		15:'Precedence cutoff in effect'
	},
	4:'Source quench (congestion control)',
	5:{
		'name':'Redirect Message',
		0:'Redirect Datagram for the Network',
		1:'Redirect Datagram for the Host',
		2:'Redirect Datagram for the ToS & network',
		3:'Redirect Datagram for the ToS & host'
    },
	6:'Alternate Host Address',
	7:'Reserved',
	8:'Echo request (used to ping)',
	9:'Router Advertisement',
	10:'Router Solicitation',
	11:{
		'name':'Time Exceeded',
		0:'TTL expired in transit',
		1:'Fragment reassembly time exceeded'
	},
	12:{
		'name':'Parameter Problem: Bad IP header',
		0:'Pointer indicates the error',
		1:' Missing a required option',
		2:'Bad length'
	},
	13:'Timestamp',
	14:'Timestamp Reply',
	15:'Information Request',
	16:'Information Reply',
	17:'Address Mask Request',
	18:'Address Mask Reply',
	19:'Reserved for security',
	20:'Reserved for robustness experiment',
	30:'Traceroute',
	31:'Datagram Conversion Error',
	32:'Mobile Host Redirect',
	33:'Where-Are-You (originally meant for IPv6)',
	34:'Here-I-Am (originally meant for IPv6)',
	35:'Mobile Registration Request',
	36:'Mobile Registration Reply',
	37:'Domain Name Request',
	38:'Domain Name Reply',
	39:'SKIP Algorithm Discovery Protocol, Simple Key-Management for Internet Protocol',
	40:'Photuris, Security failures',
	41:'ICMP for experimental mobility protocols such as Seamoby',
	42:'Extended Echo Request',
	43:{
		'name':'Extended Echo Reply',
		0:'No Error',
		1:'Malformed Query',
		2:'No Such Interface',
		3:'No Such Table Entry',
		4:'Multiple Interfaces Satisfy Query'
	},
	253:'RFC3692-style Experiment 1',
	254:'RFC3692-style Experiment 2',
	255:'Reserved'
}