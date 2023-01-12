python3 src/extraction_runner.py -f is_under_flood -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f get_packet_dst -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f connection_table_lookup -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f process_l3_headers -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f process_l3_headers -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f check_decap_dst -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f reals_have_same_addr -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f perform_global_lru_lookup -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f process_encaped_ipip_pckt -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f process_encaped_ipip_pckt -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f process_encaped_gue_pckt -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f process_encaped_gue_pckt -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f increment_quic_cid_version_stats -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f increment_quic_cid_drop_no_real -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f increment_quic_cid_drop_real_0 -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f process_packet -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f process_packet -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f balancer_ingress -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f get_packet_hash -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f xdpdecap -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f xdp_prog_simple -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f xdp_root -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f xdp_val -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f healthcheck_encap -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f healthcheck_encap -d cilium.db -g op/fcg  -r cilium
python3 src/extraction_runner.py -f pktcntr -d cilium.db -g op/fcg  -r cilium
#Skipping: encap_v6 in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: encap_v4 in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: decap_v6 in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: decap_v4 in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: gue_csum in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: gue_encap_v4 in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: gue_encap_v6 in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: gue_decap_v4 in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: gue_decap_v6 in /home/sayandes/opened_extraction/examples/katran/pckt_encap.h
#Skipping: set_hc_key in /home/sayandes/opened_extraction/examples/katran/healthchecking_helpers.h
#Skipping: hc_encap_ipip in /home/sayandes/opened_extraction/examples/katran/healthchecking_helpers.h
#Skipping: gue_sport in /home/sayandes/opened_extraction/examples/katran/healthchecking_helpers.h
#Skipping: hc_encap_gue in /home/sayandes/opened_extraction/examples/katran/healthchecking_helpers.h
#Skipping: create_v4_hdr in /home/sayandes/opened_extraction/examples/katran/encap_helpers.h
#Skipping: create_v6_hdr in /home/sayandes/opened_extraction/examples/katran/encap_helpers.h
#Skipping: create_udp_hdr in /home/sayandes/opened_extraction/examples/katran/encap_helpers.h
#Skipping: rol32 in /home/sayandes/opened_extraction/examples/katran/jhash.h
#Skipping: jhash in /home/sayandes/opened_extraction/examples/katran/jhash.h
#Skipping: __jhash_nwords in /home/sayandes/opened_extraction/examples/katran/jhash.h
#Skipping: jhash_2words in /home/sayandes/opened_extraction/examples/katran/jhash.h
#Skipping: jhash_1word in /home/sayandes/opened_extraction/examples/katran/jhash.h
#Skipping: submit_event in /home/sayandes/opened_extraction/examples/katran/balancer_helpers.h
#Skipping: recirculate in /home/sayandes/opened_extraction/examples/katran/balancer_helpers.h
#Skipping: decrement_ttl in /home/sayandes/opened_extraction/examples/katran/balancer_helpers.h
#Skipping: calc_offset in /home/sayandes/opened_extraction/examples/katran/pckt_parsing.h
#Skipping: parse_udp in /home/sayandes/opened_extraction/examples/katran/pckt_parsing.h
#Skipping: parse_tcp in /home/sayandes/opened_extraction/examples/katran/pckt_parsing.h
#Skipping: parse_hdr_opt in /home/sayandes/opened_extraction/examples/katran/pckt_parsing.h
#Skipping: tcp_hdr_opt_lookup in /home/sayandes/opened_extraction/examples/katran/pckt_parsing.h
#Skipping: parse_quic in /home/sayandes/opened_extraction/examples/katran/pckt_parsing.h
#Skipping: get_next_ports in /home/sayandes/opened_extraction/examples/katran/flow_debug_helpers.h
#Skipping: gue_record_route in /home/sayandes/opened_extraction/examples/katran/flow_debug_helpers.h
#Skipping: csum_fold_helper in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: min_helper in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: ipv4_csum in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: ipv4_csum_inline in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: ipv4_l4_csum in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: ipv6_csum in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: add_pseudo_ipv6_header in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: rem_pseudo_ipv6_header in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: add_pseudo_ipv4_header in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: rem_pseudo_ipv4_header in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: gue_csum_v6 in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: gue_csum_v4 in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: gue_csum_v4_in_v6 in /home/sayandes/opened_extraction/examples/katran/csum_helpers.h
#Skipping: swap_mac_and_send in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
#Skipping: swap_mac in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
#Skipping: send_icmp_reply in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
#Skipping: send_icmp6_reply in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
#Skipping: send_icmp4_too_big in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
#Skipping: send_icmp6_too_big in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
#Skipping: send_icmp_too_big in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
#Skipping: parse_icmpv6 in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
#Skipping: parse_icmp in /home/sayandes/opened_extraction/examples/katran/handle_icmp.h
