/*
 * Copyright (c) 2013 Juniper Networks, Inc. All rights reserved.
 */

#ifndef SRC_BGP_BGP_MESSAGE_BUILDER_H_
#define SRC_BGP_BGP_MESSAGE_BUILDER_H_

#include "bgp/bgp_proto.h"
#include "bgp/message_builder.h"

class BgpMessage : public Message {
public:
    BgpMessage(const BgpTable *table = NULL);
    virtual ~BgpMessage();
    bool Start(const RibOutAttr *roattr, const BgpRoute *route);
    virtual bool AddRoute(const BgpRoute *route, const RibOutAttr *roattr);
    virtual void Finish();
    virtual const uint8_t *GetData(IPeerUpdate *ipeer_update, size_t *lenp);

private:
    bool StartReach(const RibOutAttr *roattr, const BgpRoute *route);
    bool StartUnreach(const BgpRoute *route);
    bool UpdateLength(const char *tag, int size, int delta);

    const BgpTable *table_;
    EncodeOffsets encode_offsets_;
    uint8_t data_[BgpProto::kMaxMessageSize];
    size_t datalen_;

    DISALLOW_COPY_AND_ASSIGN(BgpMessage);
};

class BgpMessageBuilder : public MessageBuilder {
public:
    BgpMessageBuilder();
    virtual Message *Create(const BgpTable *table,
                            const RibOutAttr *roattr,
                            const BgpRoute *route) const;
    static BgpMessageBuilder *GetInstance();

private:
    static BgpMessageBuilder instance_;
    DISALLOW_COPY_AND_ASSIGN(BgpMessageBuilder);
};

#endif  // SRC_BGP_BGP_MESSAGE_BUILDER_H_
