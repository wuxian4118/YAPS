#include "packet.h"
#include "../run/params.h"

extern DCExpParams params;
uint32_t Packet::instance_count = 0;

Packet::Packet(
        double sending_time, 
        Flow *flow, 
        uint32_t seq_no, 
        uint32_t pf_priority,
        uint32_t size, 
        Host *src, 
        Host *dst
    ) {
    this->sending_time = sending_time;
    this->flow = flow;
    this->seq_no = seq_no;
    this->pf_priority = pf_priority;
    this->size = size;
    this->src = src;
    this->dst = dst;

    this->type = NORMAL_PACKET;
    this->unique_id = Packet::instance_count++;
    this->total_queuing_delay = 0;
}

PlainAck::PlainAck(Flow *flow, uint32_t seq_no_acked, uint32_t size, Host* src, Host *dst) : Packet(0, flow, seq_no_acked, 0, size, src, dst) {
    this->type = ACK_PACKET;
}

Ack::Ack(Flow *flow, uint32_t seq_no_acked, std::vector<uint32_t> sack_list, uint32_t size, Host* src, Host *dst) : Packet(0, flow, seq_no_acked, 0, size, src, dst) {
    this->type = ACK_PACKET;
    this->sack_list = sack_list;
}

RTSCTS::RTSCTS(bool type, double sending_time, Flow *f, uint32_t size, Host *src, Host *dst) : Packet(sending_time, f, 0, 0, f->hdr_size, src, dst) {
    if (type) {
        this->type = RTS_PACKET;
    }
    else {
        this->type = CTS_PACKET;
    }
}

RTS::RTS(Flow *flow, Host *src, Host *dst, double delay, int iter) : Packet(0, flow, 0, 0, params.hdr_size, src, dst) {
    this->type = RTS_PACKET;
    this->delay = delay;
    this->iter = iter;
}


OfferPkt::OfferPkt(Flow *flow, Host *src, Host *dst, bool is_free, int iter) : Packet(0, flow, 0, 0, params.hdr_size, src, dst) {
    this->type = OFFER_PACKET;
    this->is_free = is_free;
    this->iter = iter;
}

DecisionPkt::DecisionPkt(Flow *flow, Host *src, Host *dst, bool accept) : Packet(0, flow, 0, 0, params.hdr_size, src, dst) {
    this->type = DECISION_PACKET;
    this->accept = accept;
}

CTS::CTS(Flow *flow, Host *src, Host *dst) : Packet(0, flow, 0, 0, params.hdr_size, src, dst) {
    this->type = CTS_PACKET;
}

StatusPkt::StatusPkt(Flow *flow, Host *src, Host *dst, int num_flows_at_sender) : Packet(0, flow, 0, 0, params.hdr_size, src, dst) {
    this->type = STATUS_PACKET;
    this->num_flows_at_sender = num_flows_at_sender;
}
