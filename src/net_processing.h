// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_NET_PROCESSING_H
#define BITCOIN_NET_PROCESSING_H

#include "net.h"
#include "validationinterface.h"

// The following things handle network-processing logic
// (and should be moved to a separate file)

/** Headers download timeout expressed in microseconds
 *  Timeout = base + per_header * (expected number of headers) */
static constexpr int64_t HEADERS_DOWNLOAD_TIMEOUT_BASE = 15 * 60 * 1000000; // 15 minutes
static constexpr int64_t HEADERS_DOWNLOAD_TIMEOUT_PER_HEADER = 1000; // 1ms/header

/** if disabled, blocks will not be requested automatically, usefull for non-validation mode */
static const bool DEFAULT_AUTOMATIC_BLOCK_REQUESTS = true;
extern std::atomic<bool> fAutoRequestBlocks;

static const bool DEFAULT_FETCH_BLOCKS_WHILE_FETCH_HEADERS = true;
extern std::atomic<bool> fFetchBlocksWhileFetchingHeaders;

class PeerLogicValidation : public CValidationInterface, public NetEventsInterface {
private:
    CConnman* connman;

public:
    explicit PeerLogicValidation(CConnman* connman);

    void BlockConnected(const std::shared_ptr<const CBlock>& pblock, const CBlockIndex* pindexConnected, const std::vector<CTransactionRef>& vtxConflicted) override;
    void UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload) override;
    void BlockChecked(const CBlock& block, const CValidationState& state) override;
    void NewPoWValidBlock(const CBlockIndex *pindex, const std::shared_ptr<const CBlock>& pblock) override;

    void InitializeNode(CNode* pnode) override;
    void FinalizeNode(NodeId nodeid, bool& fUpdateConnectionTime) override;
    /** Process protocol messages received from a given node */
    bool ProcessMessages(CNode* pfrom, std::atomic<bool>& interrupt) override;
    /**
    * Send queued protocol messages to be sent to a give node.
    *
    * @param[in]   pto             The node which we are sending messages to.
    * @param[in]   interrupt       Interrupt condition for processing threads
    * @return                      True if there is more work to be done
    */
    bool SendMessages(CNode* pto, std::atomic<bool>& interrupt) override;
};

struct CNodeStateStats {
    int nMisbehavior;
    int nSyncHeight;
    int nCommonHeight;
    std::vector<int> vHeightInFlight;
};

/** Get statistics from node state */
bool GetNodeStateStats(NodeId nodeid, CNodeStateStats &stats);
/** Increase a node's misbehavior score. */
void Misbehaving(NodeId nodeid, int howmuch);

#endif // BITCOIN_NET_PROCESSING_H